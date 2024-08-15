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
   TCanvas* ebeamCanvas = new TCanvas("c1", "ebeam canvas",10,10,700,500);   // Exercise 3
   TH1* ebeamHist = new TH1F("ebeam","Histogram of ebeam",100,149,151);
   ebeamHist->GetXaxis()->SetTitle("ebeam [GeV]");
   ebeamHist->GetYaxis()->SetTitle("number of events");

   TCanvas* chi2Canvas = new TCanvas("c2", "chi2 canvas",50,50,700,500);     // Exercise 3
   TH1* chi2Hist = new TH1F("chi2","Histogram of Chi2",100,0,20);
   chi2Hist->GetXaxis()->SetTitle("chi2");
   chi2Hist->GetYaxis()->SetTitle("number of events");

   Long64_t nentries = fChain->GetEntries();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      // The Loop code goes here.
      ebeamHist->Fill(ebeam);    // Exercise 3
      chi2Hist->Fill(chi2);

   }

   // The Wrap-up code goes here.
   ebeamHist->Fit("gaus");       // Exercise 4
   gStyle->SetOptFit();          // Exercise 4
   ebeamCanvas->cd();            // Exercise 3
   ebeamHist->Draw("e1"); 

   chi2Canvas->cd();
   chi2Hist->Draw("e1");         // Exercise 2
}
