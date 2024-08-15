#!/bin/bash
# The above line means to make sure this file is executed as a Bourne
# shell script.

# In bash, command-line arguments are stored in special variables: $1
# is the first argument, $2 is the second, etc. ($0 is the full
# pathname of the script.) In condor-example.cmd, we specified that
# first argument on the command line is the process number.

process=$1

# Set up the Nevis environment, including our custom environments,
export PATH=/sbin:/usr/sbin:/bin:/usr/bin
source /usr/nevis/adm/nevis-init.sh

# Set up root.
conda activate /usr/nevis/conda/root

# Create the name of our output file. 
outputfile="condor-example-${process}.root"

# Run our program. 
./condor-example.py ${process} ${outputfile}
