from ROOT import TFile, gDirectory
# You probably also want to import TH1D,
# unless you're not making any histograms.
from ROOT import TH1D

# Open the file. Note that the name of your file outside this class
# will probably NOT be experiment.root.

myfile = TFile( 'experiment.root' )

# Retrieve the n-tuple of interest. In this case, the n-tuple's name is
# "tree1". You may have to use the TBrowser to find the name of the
# n-tuple that someone gives you.
mychain = gDirectory.Get( 'tree1' )
entries = mychain.GetEntriesFast()

### The Set-up code goes here.
count = 0
###

for jentry in xrange( entries ):
   # Get the next tree in the chain and verify.
   ientry = mychain.LoadTree( jentry )
   if ientry < 0:
      break

   # Copy next entry into memory and verify.
   nb = mychain.GetEntry( jentry )
   if nb <= 0:
      continue

   # Use the values directly from the tree. This is an example using a
   # variable "vertex". This variables does not exist in the example
   # n-tuple experiment.root, to force you to think about what you're
   # doing.  

   ### The Loop code goes here.
   pz = mychain.pz
   if ( pz < 145 ):
      count = count + 1
   ###
   
### The Wrap-up code goes here
print "The number of events with pz < 145 is", count
###
