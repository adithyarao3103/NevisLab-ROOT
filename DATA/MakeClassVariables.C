#define MakeClass_cxx
#include "MakeClass.h"
#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"

void MakeClass::Loop()
{
//   In a Root session, you can do:
//      Root > .L MakeClass.C
//      Root > MakeClass t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(i);  // read all branches
//by  b_branchname->GetEntry(i); //read only this branch
   if (fChain == 0) return;

   // The Set-up code goes here.
   TCanvas* ptCanvas = new TCanvas("c1", "pt canvas",10,10,700,500);   // Exercise 3
   TH1* ptHist = new TH1F("pt","Histogram of pt",100,0,35);
   ptHist->GetXaxis()->SetTitle("pt [GeV]");
   ptHist->GetYaxis()->SetTitle("number of events");

   TCanvas* thetaCanvas = new TCanvas("c2", "theta canvas",50,50,700,500);     // Exercise 3
   TH1* thetaHist = new TH1F("theta","Histogram of Theta",100,0,.240);
   thetaHist->GetXaxis()->SetTitle("theta [radians]");
   thetaHist->GetYaxis()->SetTitle("number of events");

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // The Loop code goes here.
      Float_t pt = TMath::Sqrt(px*px + py*py);
      Float_t theta = TMath::ATan2(pt,pz);         // Exercise 7

      ptHist->Fill(pt);
      thetaHist->Fill(theta);

   }

   // The Wrap-up code goes here.
   ptCanvas->cd();            // Exercise 6
   ptHist->Draw("e1"); 
   thetaCanvas->cd();         // Exercise 7
   thetaHist->Draw("e1"); 

}
