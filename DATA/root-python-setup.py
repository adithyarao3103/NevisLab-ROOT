#!/usr/bin/env python3
# The above line makes sure this file is executed as a python 3 program.

########################## Environment modules ############################
# The following lines set up the ROOT environment within python
# without resorting to an external shell script to set up the
# environment.

import os, sys

# Set up our conda environment.
import conda.cli
conda.cli.main("conda", "activate", "/usr/nevis/conda/root")

# Problem: The previous commands update the environment variables, but
# python doesn't see the change in variables such as
# $LD_LIBRARY_PATH. The solution is a dumb python trick: If we can't
# import ROOT, then re-run this script with the modified environment
# variables from 'conda activate /usr/nevis/conda/root'.
try:
    import ROOT
except ImportError as error_message:
    os.execve(os.path.realpath(__file__), sys.argv, os.environ)
##########################################################################

##################### Parsing command-line arguments #####################
# This module helps you get arguments from the command line. See
# <http://www.tutorialspoint.com/python/python_command_line_arguments.htm>
# for how this works.
import getopt

# Get the name of this program.
progname = os.path.basename(sys.argv[0])
# Explain how to use this program.
usage = progname + ' -m <mean> -o <outputfile>'
# The first "argument" in sys.argv is the name of the program, so omit
# that when parsing the argument list. 
arguments = sys.argv[1:]

mean = 0
outputfile = ''
try:
    opts, args = getopt.getopt(arguments,"hm:o:",["help","mean=","outputfile="])
except getopt.GetoptError:
    print ("could not process these arguments:",arguments)
    print (usage)
    sys.exit(2)
# Go through all the allowed options.
for opt, arg in opts:
    if opt in ('-h',"--help"):
        print ("create a histogram of a gaussian with a given mean and write it to a file")
        print (usage)
        sys.exit()
    elif opt in ("-m", "--mean"):
        # Make sure arg is a valid number.
        try:
            mean = float(arg)
        except ValueError:
            print ("'",arg,"' is not a number")
            print (usage)
            sys.exit(2)
    elif opt in ("-o", "--outputfile"):
        outputfile = arg

# If no output file was specified, exit the program.
if outputfile == '':
    print ('no output file specified')
    print (usage)
    sys.exit(2)
##########################################################################


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

