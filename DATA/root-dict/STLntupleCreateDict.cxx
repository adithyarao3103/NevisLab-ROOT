// 28-Feb-2024 WGS

// Create a test n-tuple with STL structures to see if we can read it
// in C++ and Python. Here, we're using a compiled dictionary (as opposed
// to STLntupleCreate.cxx, which uses a dynamically-generated dictionary). 

// To compile this program:
// g++ `root-config --cflags --libs` STLntupleCreateDict.cxx ./STLntupleDict.so -o STLntupleCreateDict

// Then you can execute it with:
// ./STLntupleCreateDict

// Note that the g++ command takes a very simple approach to linking
// the shared library STLntupleDict.so into the executable. In real
// life, you'd probably want to look up using the -Wl,rpath= option.

#include "STL_TrackList.h"
#include "STLntupleTypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TRandom.h"
#include <iostream>

void STLntupleCreate() 
{
  bool debug = false;

  // We don't have to explicitly load any dictionaries. However, if we
  // want to use the fancy typedefs in STLntuple.icc, we have to
  // include them here.
  
  // Some typedefs for practice in making things easier. If this doesn't
  // look "easy", ask which looks simpler: map2D_vt (for 'map2D value type'),
  //  or std::pair<std::tuple<int,int>, double>
  typedef std::map<int,double>      vMap_t;
  typedef vMap_t::value_type        vMap_vt;
  typedef std::tuple<int,int>       axes_t;
  typedef std::map< axes_t, double> map2D_t;
  typedef map2D_t::value_type       map2D_vt;

  if (debug) std::cout << "debug 10" << std::endl;

  auto output = new TFile("STLntupleDict.root","RECREATE");
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
  
  for ( int rows = 0; rows < 10000; ++rows ) {

    if (debug && rows % 100 == 0) std::cout << "debug 100 - row " << rows << std::endl;

    // Create some dummy values for testing. 
    intSize = gRandom->Integer(1000);
    doubleSize = gRandom->Integer(1000);
    int mapSize = gRandom->Integer(1000);
    int trackSize = gRandom->Integer(1000);

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
      int steps = gRandom->Integer(100);
      for ( int s = 0; s < steps; ++s ) {
	double step = gRandom->Gaus();
	trackList->AddStep( trackID, step );
      }
    }

    if (debug && rows % 100 == 0) std::cout << "debug 300 - row " << rows << std::endl;

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
