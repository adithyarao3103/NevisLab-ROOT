#define AnalyzeExercise10_cxx

#include "AnalyzeExercise10.h"
#include <TH2.h>
#include <TStyle.h>
#include <TFile.h>

//******** Definition section *********

TH1* ptHist = nullptr;

TH1* thetaHist = nullptr;

void AnalyzeExercise10::Begin(TTree * /*tree*/)
{
  TString option = GetOption();

  //******** Initialization section *********
  ptHist = new TH1D("pt","Histogram of pt",100,0,35);
  ptHist->GetXaxis()->SetTitle("pt [GeV]");
  ptHist->GetYaxis()->SetTitle("number of events");

  thetaHist = new TH1D("theta","Histogram of Theta",100,0,.240);
  thetaHist->GetXaxis()->SetTitle("theta [radians]");
  thetaHist->GetYaxis()->SetTitle("number of events");
}

void AnalyzeExercise10::SlaveBegin(TTree* tree) {}

Bool_t AnalyzeExercise10::Process(Long64_t entry)
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

void AnalyzeExercise10::SlaveTerminate() {}

void AnalyzeExercise10::Terminate()
{
  //******** Wrap-up section *********
  TFile* outputfile = new TFile("analysis.root","recreate");
  ptHist->Write(); 
  thetaHist->Write();
  outputfile->Close();
}
