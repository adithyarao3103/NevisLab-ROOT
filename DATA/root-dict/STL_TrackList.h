// STL_TrackList.h
// 06-Jun-2023 WGS

// This is a skeleton of a typical class that might be used in a
// ROOT-based analysis. Its use is to test to use an
// externally-defined set of classes within a ROOT ntuple.

// Note that these structures and classes don't make any sense. The
// goal is to test code syntax and ROOT storage, not to work with
// actual data.

// These C pre-processor lines basically mean: If this header has been
// previously included in the code, don't include it again.
#ifndef _STL_TrackList_h_
#define _STL_TrackList_h_

#include <vector>
#include <map>

// Define a simple struct to hold information for a given track
// ID. The rough idea is that a track consists of many steps within a
// detector.
struct trackInfo {
  int track;                  // The ID number of the track within an event.
  std::vector<double> steps;  // A list of steps within that track. 
};

// This is a sketch of a class that holds a collection of tracks.

class TrackList {

public:

  // Simple class constructor. We let the compiler auto-create the destructor. 
  TrackList() {}

  // These are various "access" methods (also called "getters" and
  // "setters") that are typical of C++ classes. Remember, a central
  // design principle of C++ is to "hide" how information is stored
  // within a class.
  
  // How to add a step to a given track ID. We're not being
  // sophisticated here; the track ID in the map is always the same as
  // the track number. Remember, this is an example, not actual
  // functional code.
  void AddStep( int track, double step ) {
    tracklist[track].track = track;
    tracklist[track].steps.push_back( step );
  }

  int GetNumberTracks() {
    return tracklist.size();
  }

  // Get the "i-th" track ID in the collection. 
  int GetTrack( int i ) {
    auto entry = tracklist.cbegin();
    std::advance(entry, i);
    return (*entry).first;
  }

  // The number of steps in for a given Track ID.
  int GetNumberSteps( int track ) {
    return tracklist[track].steps.size();
  }

  // Get the "j-th" step in track "i". 
  double GetStep( int track, int step ) {
    return tracklist[track].steps[step];
  }

  // How to empty our collection.
  void Clear() {
    tracklist.clear(); 
  }

private:

  // The actual information stored within the class. Note that this is
  // the only part of the class definition that actually defines data
  // to be stored.

  // Also note that when rootcling creates a dictionary for this
  // class, the internal name of the branch within the TTree will be
  // the name we've given to this variable: "tracklist".
  std::map< int, trackInfo > tracklist; // The list of tracks for this event
};

#endif // _STL_TrackList_h_
