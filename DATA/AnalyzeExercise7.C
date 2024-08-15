#define AnalyzeExercise7_cxx

#include "AnalyzeExercise7.h"
#include <TH2.h>
#include <TStyle.h>

//******** Definition section *********

TCanvas* ptCanvas = nullptr;
TH1* ptHist = nullptr;

TCanvas* thetaCanvas = nullptr;
TH1* thetaHist = nullptr;

void AnalyzeExercise7::Begin(TTree * /*tree*/)
{
  TString option = GetOption();

  //******** Initialization section *********
  ptCanvas = new TCanvas("c1", "pt canvas",10,10,700,500);   // Exercise 3
  ptHist = new TH1D("pt","Histogram of pt",100,0,35);
  ptHist->GetXaxis()->SetTitle("pt [GeV]");
  ptHist->GetYaxis()->SetTitle("number of events");

  thetaCanvas = new TCanvas("c2", "theta canvas",50,50,700,500);     // Exercise 3
  thetaHist = new TH1D("theta","Histogram of Theta",100,0,.240);
  thetaHist->GetXaxis()->SetTitle("theta [radians]");
  thetaHist->GetYaxis()->SetTitle("number of events");
}

void AnalyzeExercise7::SlaveBegin(TTree* tree) {}

Bool_t AnalyzeExercise7::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  //******** Loop section *********
  //* You will probably want to put a GetEntry here. 
  GetEntry(entry);

  Double_t pt = TMath::Sqrt((*px)*(*px) + (*py)*(*py)); // Exercise 6
  Double_t theta = TMath::ATan2(pt,*pz);                // Exercise 7

  ptHist->Fill(pt);
  thetaHist->Fill(theta);

  return kTRUE;
}

void AnalyzeExercise7::SlaveTerminate() {}

void AnalyzeExercise7::Terminate()
{
  //******** Wrap-up section *********
  ptCanvas->cd();            // Exercise 6
  ptHist->Draw("e1"); 
  thetaCanvas->cd();         // Exercise 7
  thetaHist->Draw("e1"); 
}
