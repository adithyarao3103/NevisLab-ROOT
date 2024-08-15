#!/usr/bin/env python3

# STLntupleReadDict.py
# 28-Feb-2024 WGS

# This is a Python duplicate of the functionality of
# STLntupleReadDict.cxx. It's meant to demonstrate using Python to work
# with C++-based ROOT dictionaries. 

# As a practical matter, a C++ program is going to be much faster than
# Python for this. However, if you must work in Python, hopefully the
# following code will be a guide.

# To run this program, you only have to do the following command once:
# chmod +x STLntupleReadDict.py

# Then:
# ./STLntupleRead.py

# The ROOT classes we'll use.
from ROOT import TFile, TH1D, TH2D
from ROOT import gDirectory, gSystem

# Load in the ROOT compiled shared-library dictionary.
gSystem.Load("STLntupleDict.so")

# Open the input file and access the n-tuple. 
inputFile = TFile("STLntuple.root")
ntuple = gDirectory.Get( 'STLntuple' )

# The number of rows in the n-tuple.
rows = ntuple.GetEntriesFast()

# Create the output file.
outputFile = TFile("STLntuplePython.root","RECREATE")

# Define the histograms we'll fill.
ivSizeHist  = TH1D("ivSizeHist","intVector size",100,0,100)
dvSizeHist  = TH1D("dvSizeHist","doubleVector size",100,0,100)
mapHist     = TH1D("mapHist","valueMap contents",100,0,10000)
map2DHist   = TH2D("map2DHist","map2D contents",100,0,1000,100,0,1000)
mapValues   = TH1D("mapValues","valueMap values",100,-3,3)
map2DValues = TH1D("map2DValues","map2D values",100,-3,3)
trackID     = TH1D("trackID","trackID numbers",100,0,1000)
steps       = TH1D("steps","step values",100,-3,3)

for row in range( rows ):
    # Fetch the "row-th" entry in the n-tuple.
    ntuple.GetEntry( row )

    # In STLntupleCreate.cxx, columns vectorInt and vectorDouble are defined
    # to be std::vector<int> and std::vector<double> respectively. For
    # an STL vector in Python, I could use 'ntuple.intVector.size()', but
    # since we're all Python-ers here, let's use the standard Python
    # 'len' method.
    ivSizeHist.Fill( len( ntuple.vectorInt ) )
    dvSizeHist.Fill( len( ntuple.vectorDouble ) )
    
    # For more information on how to use C++ standard template library
    # containers within Python, see
    # <https://cppyy.readthedocs.io/en/latest/stl.html>

    # Histogramming values in std::map. As noted in the above web
    # page, the Python interface to std::vector and std::map makes
    # these containers iterable.

    for entry in ntuple.mapBranch:
        # In C++, maps are composed of std::pair, and the values in
        # the pair are referred to as 'first' and 'second'. I could
        # also use Python indexing, and have entry[0] and entry[1]
        # instead.
        mapHist.Fill( entry.first, entry.second )
        mapValues.Fill( entry.second )

    for entry in ntuple.map2DBranch:
        key = entry.first
        value = entry.second
        # The key to this map is a std::tuple, whose members can be
        # accessed by standard Python indexing.
        map2DHist.Fill( key[0], key[1], value )
        map2DValues.Fill( value )

    # Thanks to the dictionary that we loaded the top of the program,
    # we can access the C++ class TrackList (defined in
    # STL_TrackList.h) via its methods without any special adapters in
    # our Python code.
    track = ntuple.trackBranch
    nTracks = track.GetNumberTracks()
    for t in range(nTracks):
        ID = track.GetTrack(t)
        trackID.Fill( ID )
        nSteps = track.GetNumberSteps(ID)
        for s in range(nSteps):
            step = track.GetStep(ID, s)
            steps.Fill( step )

# Write the histograms.
ivSizeHist.Write()
dvSizeHist.Write()
mapHist.Write()
map2DHist.Write()
mapValues.Write()
map2DValues.Write()
trackID.Write()
steps.Write()

# Clean up the files, just in case.
outputFile.Close()
inputFile.Close()
