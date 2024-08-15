// 20-Jun-2023 WGS

// This has the same function as STLntupleRead, except that it uses
// RDataFrame to process the n-tuple.

// To compile this program:
// g++ `root-config --cflags --libs` STLntupleRDF.cxx -o STLntupleRDF

// Note that we're demonstrating several things at once:

// - Like STLntupleRead, we're showing how to read ntuple with columns
// that are complex STL classes.

// - We're showing how to make histograms using RDataFrame's Hist1D()
// method.

// - A nice feature of RDataFrame is that it can easily be told to
// execute in multi-thread mode. However, if we do this, we have to
// create a separate histogram for each thread (or "slot"). After
// reading the TTree, we have to sum the histograms of all the slots
// into a single histogram.

// Important: This routine seems long compared to STLntupleRead. Most
// of that is because I've overly-commented the code for teaching
// purposes. The rest is because the requirements for multi-threaded
// execution.

#include "STL_TrackList.h"
#include "STLntupleTypes.h"
#include "ROOT/RDataFrame.hxx"
#include "ROOT/RDFHelpers.hxx" // for SaveGraph
#include "TFile.h"
#include "TInterpreter.h" // required for STLntuple.icc
#include <vector>
#include <string>
#include <iostream>

void STLntupleRead() 
{
  bool debug = false;

#include "STLntuple.icc"

  if (debug) std::cout << "debug 00" << std::endl;

  auto dataframe = ROOT::RDataFrame("STLntuple","STLntuple.root");

  // Test this by making histograms.
  auto output = new TFile("STLntupleRDF.root","RECREATE");

  // These two lines are the standard way of making simple histograms
  // using RDataFrame. However, they are executed in a separate event
  // loop from the ForeachSlot loop below; this means that this
  // program is reading the input file twice.  The "better" way to
  // make these histograms is to use the same technique as shown in
  // the ForeachSlot example below, so that the input file is read
  // only once.
  auto ivSizeHist = dataframe
    .Define("isize","vectorInt.size()")
    .Histo1D({"ivSizeHist","intVector size",100,0,100},"isize");
  auto dvSizeHist = dataframe
    .Define("dsize","vectorDouble.size()")
    .Histo1D({"dvSizeHist","doubleVector size",100,0,100},"dsize");

  // The above operations were easy. For more complicated operations,
  // we might want to use Foreach; for multi-threaded compatibility,
  // we probably want to use ForeachSlot.

  // How many "slots" (threads) are available?
  auto slots = dataframe.GetNSlots();
  if ( slots == 0 ) { slots = 1; }

  // In this example code, we're making histograms. For a real
  // analysis, we might create separate arrays to accumulate
  // information or values for the n-tuple rows, one set of arrays (or
  // whatever) for each slot.

  // Note that this is overkill if we've decided not to support
  // multi-threading. But anything worth doing is worth overdoing!

  // For every slot, define our set of histograms. As noted above, as
  // an example, we're duplicating the "ivSize" and "dvSize"
  // histograms by filling them using ForeachSlot.
  std::vector<TH1D*> ivSizeHists(slots);
  std::vector<TH1D*> dvSizeHists(slots);
  std::vector<TH1D*> mapHists(slots);
  std::vector<TH2D*> map2DHists(slots);
  std::vector<TH1D*> mapValuesHists(slots);
  std::vector<TH1D*> map2DValuesHists(slots);
  std::vector<TH1D*> trackIDHists(slots);
  std::vector<TH1D*> stepsHists(slots);
  
  if (debug) std::cout << "debug 10" << std::endl;

  // More decltype tricks: When you're not sure of the correct type to
  // use, just copy it.
  for ( decltype(slots) slot = 0; slot < slots; ++slot ) {
    // Convert the slot number into a string. 
    auto sslot = std::to_string(slot);

    // Define the histograms for this slot. We want to do this in a
    // way that each time the function (defined below) executes in a
    // slot, it only affects objects that were defined or manipulated
    // solely within that slot.

    // Because TH1 still only accepts old C-style strings for the
    // names and titles, we have to convert the results of the string
    // concatentation (e.g., "mapHist"+sslot) into C-strings using the
    // c_str method; e.g., ("mapHist"+sslot).c_str()
    ivSizeHists[slot] = new TH1D(("ivSizeHist"+sslot).c_str(), ("ivSize "+sslot).c_str(), 100,0,100);
    dvSizeHists[slot] = new TH1D(("dvSizeHist"+sslot).c_str(), ("dvSize "+sslot).c_str(), 100,0,100);
    mapHists[slot] = new TH1D(("mapHist"+sslot).c_str(), ("valueMap "+sslot).c_str(), 100,0,10000);
    map2DHists[slot] =  new TH2D(("map2DHist"+sslot).c_str(), ("map2D "+sslot).c_str(), 100,0,1000,100,0,1000);
    mapValuesHists[slot] = new TH1D(("mapValues"+sslot).c_str(), ("mapValues "+sslot).c_str(), 100,-3,3);
    map2DValuesHists[slot] = new TH1D(("map2DValues"+sslot).c_str(), ("map2DValues "+sslot).c_str(), 100,-3,3);
    trackIDHists[slot] = new TH1D(("trackID"+sslot).c_str(), ("track ID "+sslot).c_str(), 100,0,1000);
    stepsHists[slot] = new TH1D(("steps"+sslot).c_str(), ("steps "+sslot).c_str(), 100,-3,3);

    // We know we're going to be adding these histograms together at
    // the end of processing. Use Sumw2 to make sure the errors are
    // propagated correctly.
    ivSizeHists[slot]->Sumw2();
    dvSizeHists[slot]->Sumw2();
    mapHists[slot]->Sumw2();
    map2DHists[slot]->Sumw2();
    mapValuesHists[slot]->Sumw2();
    map2DValuesHists[slot]->Sumw2();
    trackIDHists[slot]->Sumw2();
    stepsHists[slot]->Sumw2();
    
  } // loop over number of slots

  if (debug) std::cout << "debug 20" << std::endl;

  // Let's break this down:

  // RDataFrame::Foreach() perform some operation for each row of the
  // n-tuple, as shown above. 

  // RDataFrame::ForeachSlot() does the same thing, but it applies a
  // custom function to each row.  This operation has to be
  // "thread-safe"; that is, what happens within the function called
  // for one slot can't affect anything in another slot, or in the
  // calling program.

  // First, define a function that will operate on each row of the
  // TTree. Here we define the function using C++ lambda syntax. The
  // general format is:

  // auto my_function = [ variable-list ] (function-arguments) { function-body }

  // "variable-list" contains those variables from the outside code
  // that are to be referenced within the function. Often there are
  // none, which is why one often sees "[]" for that list. Here, we'll
  // simplify our lives and accept _all_ the external variables outside
  // the lambda definition to be brought into the lambda's code; hence
  // "[&]".

  // "function-arguments" are the arguments to the function-body in
  // curly brankets. In a function that will be invoked by
  // ForEachSlot, the first argument is the slot (thread) number. The
  // remaining arguments must have the types of the branches in the
  // list of columns. For example, mapBranch has the type is vMap_t
  // (as defined in STLntupleTypes.h).
  
  // This function, to be perfomed on each row of the TTree, does the
  // same operations as in STLntupleRead: Go through the various
  // structures and histogram their values.
  auto processEntry = [&]( unsigned int slot, 
			   std::vector<int> intVector,
			   std::vector<double> doubleVector,
			   vMap_t valueMap, 
			   map2D_t map2D, 
			   TrackList tracklist )
  {
    ivSizeHists[slot]->Fill( intVector.size() );
    dvSizeHists[slot]->Fill( doubleVector.size() );

    // Another trick: How to do range-based for loops using maps.
    for ( const auto& [key, value] : valueMap ) { 
        mapHists[slot]->Fill( key, value );
        mapValuesHists[slot]->Fill( value );
    }

    for ( const auto& [key, value] : map2D ) { 
        // Recall that this map's key is a tuple, so we can use std::get to access its elements.
        map2DHists[slot]->Fill( std::get<0>(key), std::get<1>(key), value );
        map2DValuesHists[slot]->Fill( value );
    }
    
    auto nTracks = tracklist.GetNumberTracks();
    for ( decltype(nTracks) t = 0; t < nTracks; ++t ) {
      auto ID = tracklist.GetTrack(t);
      trackIDHists[slot]->Fill( ID );
      auto nSteps = tracklist.GetNumberSteps(ID);
      for ( decltype(nSteps) i = 0; i < nSteps; ++i ) {
	auto step = tracklist.GetStep(ID, i);
	stepsHists[slot]->Fill( step );
      } // loop over steps
    } // loop over tracks
  }; // end of processEntry function definition.

  // ForeachSlot takes two arguments: a function that will operate on
  // column(s) of the n-tuple, and a list of columns that will be
  // arguments to the function.

  // Here we're working with columns of the n-tuple defined in
  // STLntupleCreate. We list those columns we're using in the format
  // {"column1", "column2", ...}, where "columnN" is the name of the
  // branch (aka column) defined in STLntupleCreate.

  // Note that ForeachSlot is an "instant" operation; that is, it's
  // not queued the way Histo1D is, but executed immediately upon its
  // declaration below.

  dataframe.ForeachSlot( processEntry,
		 {"vectorInt", "vectorDouble", "mapBranch", "map2DBranch", "trackBranch"}
		 );

  if (debug) std::cout << "debug 30" << std::endl;

  // Define the histograms that we'll actually write.
  TH1D ivSizeHistDuplicate("ivSizeHistDuplicate","size of intVector",100,0,100);
  TH1D dvSizeHistDuplicate("dvSizeHistDuplicate","size of doubleVector",100,0,100);
  TH1D mapHist("mapHist","valueMap contents",100,0,10000);
  TH2D map2DHist("map2DHist","map2D contents",100,0,1000,100,0,1000);
  TH1D mapValues("mapValues","valueMap values",100,-3,3);
  TH1D map2DValues("map2DValues","map2D values",100,-3,3);
  TH1D trackID("trackID","trackID numbers",100,0,1000);
  TH1D steps("steps","step values",100,-3,3);

  if (debug) std::cout << "debug 40" << std::endl;

  // For error propagation:
  ivSizeHistDuplicate.Sumw2();
  dvSizeHistDuplicate.Sumw2();
  mapHist.Sumw2();
  map2DHist.Sumw2();
  mapValues.Sumw2();
  map2DValues.Sumw2();
  trackID.Sumw2();
  steps.Sumw2();

  if (debug) std::cout << "debug 50" << std::endl;

  // Sum the histograms from the individual threads.
  for ( decltype(slots) slot = 0; slot < slots; ++slot ) {
    ivSizeHistDuplicate.Add( ivSizeHists[slot] );
    dvSizeHistDuplicate.Add( dvSizeHists[slot] );
    mapHist.Add( mapHists[slot] );
    map2DHist.Add( map2DHists[slot] );
    mapValues.Add( mapValuesHists[slot] );
    map2DValues.Add( map2DValuesHists[slot] );
    trackID.Add( trackIDHists[slot] );
    steps.Add( stepsHists[slot] );
  }

  if (debug) std::cout << "debug 60" << std::endl;

  ivSizeHist->Write();
  dvSizeHist->Write();
  ivSizeHistDuplicate.Write();
  dvSizeHistDuplicate.Write();
  mapHist.Write();
  map2DHist.Write();
  mapValues.Write();
  map2DValues.Write();
  trackID.Write();
  steps.Write();

  output->Close();

  if (debug) std::cout << "debug 70" << std::endl;

  // Take a look at the RDataFrame execution diagram.
  // To see the graphical representation, do:
  //    display STLntupleDiagram.dot
  ROOT::RDF::SaveGraph(dataframe,"STLntupleDiagram.dot");

}

int main( int, char** ) {
  STLntupleRead();
}
