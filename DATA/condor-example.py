#!/usr/bin/env python3
# The above line makes sure this file is executed as a python 3
# program.

# You'll usually want these packages.
import os, sys

# This one you know
import ROOT

# Getting arguments from the command line: sys.argv[1] is the first
# argument, sys.argv[2] is the second argument, and so on. sys.argv[0]
# is the full pathname of the program. (See root-python-setup.py for a
# more robust way to do this.)
mean=float(sys.argv[1]) # convert text string to number.
outputfile=sys.argv[2]

# Now do ROOT stuff.

# Create a histogram
myhist = ROOT.TH1D("hist","Example histogram",100,-3+mean,3+mean)
# Create a gaussian function
mygaus = ROOT.TF1("mygaus","gaus")
# Set the mean of the gaussian to the user's specified value.
mygaus.SetParameters(1.0,mean,1.0)
# Fill it
myhist.FillRandom("mygaus",10000)
# Open a file
myfile = ROOT.TFile(outputfile,"UPDATE")
# Write the histogram
myhist.Write()
# Close the file
myfile.Close()

