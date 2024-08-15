#ifdef __ROOTCLING__

// This is a ROOT dictionary link definitions file. It's to test
// dictionary generation for the classes used in the "STLntuple" code
// examples. The format is described (too briefly) at
// <https://root.cern/manual/io_custom_classes/#selecting-dictionary-entries-linkdefh>.

// To create the C++ code for ROOT I/O for the classes listed below:
// rootcling -f STLntupleDict.cxx STL_TrackList.h STL_LinkDef.h

// To compile the C++ code in STLntupleDict.cxx into a shared library,
// STLntupleDict.so:
// g++ `root-config --cflags --libs` -shared STLntupleDict.cxx -o STLntupleDict.so -fPIC

// These initial #pragma statement define the structures for some of
// the branches in our example TTree, as created by
// STLntupleCreateDict.

#pragma link C++ class std::map<int,double>+;
#pragma link C++ class std::tuple<int,int>+;
#pragma link C++ class std::map<std::tuple<int,int>,double>+;

// These are required to generate the dictionary for the struct and
// class defined in STL_TrackList.h. If you look at that that header
// file, you'll see that it has both a struct definition and a class
// definition. We have to tell ROOT to generate dictionaries for both,
// since trackInfo is part of the definition of TrackList's internal
// data.
#pragma link C++ struct trackInfo+;
#pragma link C++ class TrackList+;

// The following statements may not be necessary, but I include them
// for "safety"; see
// https://root.cern.ch/root/htmldoc/guides/users-guide/AddingaClass.html
// for more information.
#pragma link C++ nestedclass;
#pragma link C++ nestedtypedef;

#endif // __CLING__
