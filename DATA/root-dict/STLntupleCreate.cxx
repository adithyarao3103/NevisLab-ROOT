// 31-May-2023 WGS

// Create a test n-tuple with STL structures to see if we can read it
// in C++ and Python.

// To compile this program:
// g++ `root-config --cflags --libs` STLntupleCreate.cxx -o STLntupleCreate

// Then you can execute it with:
// ./STLntupleCreate

#include "STL_TrackList.h"
#include "STLntupleTypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include "TInterpreter.h" // required for STLntuple.icc
#include <iostream>

void STLntupleCreate() 
{
  bool debug = false;

  // Load the dictionaries we'll need to read the complicated structures.
#include "STLntuple.icc"

  if (debug) std::cout << "debug 10" << std::endl;

  auto output = new TFile("STLntuple.root","RECREATE");
  auto ntuple = new TTree("STLntuple","Test ntuple to see what STL collections we can handle");

  if (debug) std::cout << "debug 20" << std::endl;

  // This is the standard procedure for creating a new TTree: Define
  // new Branches within the tree. Each Branch is copied from a
  // corresponding C++ variable, whose address must be supplied to
  // TTree::Branch.

  // Here we're creating simple branches of "int", "vector<int>", and
  // "vector<double>". There's no need to create dictionaries for
  // them, since ROOT has such simple definitions built-in.
  
  int run = 0;
  ntuple->Branch("run",   &run,   "run/I");
  int event = 0;
  ntuple->Branch("event", &event, "event/I");

  if (debug) std::cout << "debug 30" << std::endl;

  // Store the vector sizes in their own branches. 
  int intSize;
  int doubleSize;
  ntuple->Branch("intSize", &intSize);
  ntuple->Branch("doubleSize", &doubleSize);

  if (debug) std::cout << "debug 40" << std::endl;

  // For STL collections, we want to save the branch variable, to use
  // in SetAddress later.
  auto intVector = new std::vector<int>;
  auto doubleVector = new std::vector<double>;
  auto vectorIntBranch = ntuple->Branch("vectorInt", &intVector);
  auto vectorDoubleBranch = ntuple->Branch("vectorDouble", &doubleVector);

  // Now we've reached the point for which the dictionaries are
  // necessary: to write our custom classes. See STL_Tracklist.h and
  // STLntupleTypes.h for the definitions of these custom types.
  auto valueMap = new vMap_t;
  auto map2D = new map2D_t;
  auto mapBranch = ntuple->Branch("mapBranch", &valueMap);
  auto map2DBranch = ntuple->Branch("map2DBranch", &map2D);
  auto trackList = new TrackList;
  auto trackBranch = ntuple->Branch("trackBranch", &trackList);

  if (debug) std::cout << "debug 50" << std::endl;

  // Fill the various variables with random values. There's no physics
  // here. We're just writing uniform distributions or Gaussian
  // distributions to make pretty plots later.
  
  for ( int rows = 0; rows < 100; ++rows ) {

    if (debug && rows % 100 == 0) std::cout << "debug 100 - row " << rows << std::endl;

    // Create some dummy values for testing. 
    intSize = gRandom->Integer(100);
    doubleSize = gRandom->Integer(100);
    int mapSize = gRandom->Integer(100);
    int trackSize = gRandom->Integer(100);

    if (debug && rows % 100 == 0) std::cout << "debug 200 - intSize,doubleSize= " 
					    << intSize << " " << doubleSize << std::endl;

    // Populate the STL containers with random values.
    for ( int i = 0; i < intSize; ++i ) {
      intVector->push_back( gRandom->Integer(1000) );
    }
    for ( int d = 0; d < doubleSize; ++d ) {
      doubleVector->push_back( gRandom->Gaus() );
    }
    for ( int m = 0; m < mapSize; ++m ) {
      valueMap->insert( vMap_vt( gRandom->Integer(10000), gRandom->Gaus() ) );
      auto axes = axes_t( gRandom->Integer(1000), gRandom->Integer(1000) );
      map2D->insert( map2D_vt( axes, gRandom->Gaus() ) );
    }

    for ( int t = 0; t < trackSize; ++t ) {
      int trackID = gRandom->Integer(1000);
      int steps = gRandom->Integer(10);
      for ( int s = 0; s < steps; ++s ) {
	double step = gRandom->Gaus();
	trackList->AddStep( trackID, step );
      }
    }

    if (debug && rows % 100 == 0) std::cout << "debug 300 - row " << rows << std::endl;

    // If these structures are dynamic (they contain pointers), the
    // following may be needed if they're liable to relocate in
    // memory.
    //vectorIntBranch->SetAddress( &intVector );
    //vectorDoubleBranch->SetAddress( &doubleVector );

    if (debug && rows % 100 == 0) std::cout << "debug 400 - intSize,doubleSize= " 
					    << intSize << " " << doubleSize << std::endl;

    // This apparently simple statement takes the variables we defined
    // in the Branch methods above and adds them to a new row in the
    // TTree.
    ntuple->Fill();

    if (debug && rows % 100 == 0) std::cout << "debug 500 - intSize,doubleSize= " 
					    << intSize << " " << doubleSize << std::endl;

    ++event;
    intVector->clear();
    doubleVector->clear();
    valueMap->clear();
    map2D->clear();
    trackList->Clear();

    if (debug && rows % 100 == 0) std::cout << "debug 600 - row " << rows << std::endl;
  }

  if (debug) std::cout << "debug 60" << std::endl;

  // Wrap everything up, to avoid memory leaks and such. 
  ntuple->Write();
  output->Close();
  delete intVector;
  delete doubleVector;
  delete valueMap;
  delete map2D;
  delete trackList;

  if (debug) std::cout << "debug 70" << std::endl;

}

int main( int, char** ) {
  STLntupleCreate();
}
