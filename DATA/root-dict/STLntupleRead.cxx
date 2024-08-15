// 31-May-2023 WGS

// Read the ntuple created with STLntupleCreate.

// To compile this program:
// g++ `root-config --cflags --libs` STLntupleRead.cxx -o STLntupleRead

// To run it:
// ./STLntupleRead

#include "STL_TrackList.h"
#include "STLntupleTypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TInterpreter.h" // required for STLntuple.icc
#include <iostream>

void STLntupleRead() 
{
  bool debug = false;

  // Load the dictionaries we'll need to read the complicated structures.
#include "STLntuple.icc"

  if (debug) std::cout << "debug 10" << std::endl;

  auto input = new TFile("STLntuple.root");

  // Let's use an efficient method of reading a TTree.
  TTreeReader myReader("STLntuple", input);

  if (debug) std::cout << "debug 20" << std::endl;

  // This parallels similar variable definitions in STLntupleCreate.

  // For each branch that we'll read, create a TTreeReaderValue.
  TTreeReaderValue<int> run(myReader, "run");
  TTreeReaderValue<int> event(myReader, "event");
  TTreeReaderValue<int> intSize(myReader, "intSize");
  TTreeReaderValue<int> doubleSize(myReader, "doubleSize");
  TTreeReaderValue<std::vector<int>> intVector(myReader, "vectorInt");
  TTreeReaderValue<std::vector<double>> doubleVector(myReader, "vectorDouble");
  // For these custom types, see STL_Tracklist.h and STLntupleTypes.h
  TTreeReaderValue<vMap_t> valueMap(myReader, "mapBranch");
  TTreeReaderValue<map2D_t> map2D(myReader, "map2DBranch");
  TTreeReaderValue<TrackList> tracklist(myReader, "trackBranch");

  if (debug) std::cout << "debug 50" << std::endl;

  // Test this by making histograms.
  auto output = new TFile("STLntupleHist.root","RECREATE");
  TH1D ivSizeHist("ivSizeHist","intVector size",100,0,1000);
  TH1D dvSizeHist("dvSizeHist","doubleVector size",100,0,1000);
  TH1D mapHist("mapHist","valueMap contents",100,0,10000);
  TH2D map2DHist("map2DHist","map2D contents",100,0,1000,100,0,1000);
  TH1D mapValues("mapValues","valueMap values",100,-3,3);
  TH1D map2DValues("map2DValues","map2D values",100,-3,3);
  TH1D trackID("trackID","trackID numbers",100,0,1000);
  TH1D steps("steps","step values",100,-3,3);

  // For each row in the TTree:
  while (myReader.Next()) {

    // Fill test histograms.
    ivSizeHist.Fill( intVector->size() );
    dvSizeHist.Fill( doubleVector->size() );

    // Learning a new trick: How to do range-based for loops using maps.
    // Remember that the map variables are actually pointers here. 
    for ( const auto& [key, value] : *valueMap ) { 
        mapHist.Fill( key, value );
        mapValues.Fill( value );
    }

    for ( const auto& [key, value] : *map2D ) { 
        // Recall that this map's key is a tuple, so we can use std::get to access its elements.
        map2DHist.Fill( std::get<0>(key), std::get<1>(key), value );
        map2DValues.Fill( value );
    }

    // When you're too lazy to look up a return type: Use decltype to
    // let the compiler duplicate a C++ type for you.
    auto nTracks = tracklist->GetNumberTracks();
    for ( decltype(nTracks) t = 0; t < nTracks; ++t ) {
      auto ID = tracklist->GetTrack(t);
      trackID.Fill( ID );
      auto nSteps = tracklist->GetNumberSteps(ID);
      for ( decltype(nSteps) s = 0; s < nSteps; ++s ) {
	auto step = tracklist->GetStep(ID, s);
	steps.Fill( step );
      }
    }
  }

  if (debug) std::cout << "debug 60" << std::endl;

  // Wrap-up: explicitly write the histograms, close the output files,
  // and delete pointers that we don't need anymore.
  ivSizeHist.Write();
  dvSizeHist.Write();
  mapHist.Write();
  map2DHist.Write();
  mapValues.Write();
  map2DValues.Write();
  trackID.Write();
  steps.Write();

  output->Close();
  input->Close();

  if (debug) std::cout << "debug 70" << std::endl;

}

int main( int, char** ) {
  STLntupleRead();
}
