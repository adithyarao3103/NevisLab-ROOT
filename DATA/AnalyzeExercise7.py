from ROOT import TFile, gDirectory, TH1D, TCanvas, TMath

# Open the file. Note that the name of your file outside this class
# will probably NOT be experiment.root.

myfile = TFile( 'experiment.root' )

# Retrieve the n-tuple of interest. In this case, the n-tuple's name is
# "tree1". You may have to use the TBrowser to find the name of the
# n-tuple that someone gives you.
mychain = gDirectory.Get( 'tree1' )
entries = mychain.GetEntriesFast()

### The Set-up code goes here.

# Create histograms
ptHist = TH1D("ptHist","transverse momentum",100,0,30)
ptHist.GetXaxis().SetTitle("pt [GeV]")
ptHist.GetYaxis().SetTitle("number of events")

thetaHist = TH1D("thetaHist","theta (radians)",100,0,0.25)
thetaHist.GetXaxis().SetTitle("theta [radians]")
thetaHist.GetYaxis().SetTitle("number of events")
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
   # myValue = mychain.vertex 
   # myHist.Fill(myValue)

   ### The Loop code goes here.
   px = mychain.px
   py = mychain.py
   pz = mychain.pz
   pt = TMath.Sqrt(px*px + py*py)
   ptHist.Fill(pt)
   theta = TMath.ATan2(pt,pz)
   thetaHist.Fill(theta)
   ###
   
### The Wrap-up code goes here
ptCanvas = TCanvas("ptCanvas", "pt",6,99,800,600)
ptCanvas.cd()
ptHist.Draw("E")
thetaCanvas = TCanvas("thetaCanvas", "theta",26,119,800,600)
thetaCanvas.cd()
thetaHist.Draw("E")

ptCanvas.Draw()
thetaCanvas.Draw()
###
