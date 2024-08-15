#define AnalyzeHistogram_cxx

#include "AnalyzeHistogram.h"
#include <TH2.h>
#include <TStyle.h>

//******** Definition section *********
TH1* chi2Hist = nullptr;

void AnalyzeHistogram::Begin(TTree * /*tree*/)
{
  TString option = GetOption();

  //******** Initialization section *********
  chi2Hist = new TH1F("chi2","Histogram of Chi2",100,0,20);
  chi2Hist->GetXaxis()->SetTitle("chi2");
  chi2Hist->GetYaxis()->SetTitle("number of events");
}

void AnalyzeHistogram::SlaveBegin(TTree* tree) {}

Bool_t AnalyzeHistogram::Process(Long64_t entry)
{
  //******** Loop section *********
  //* You will probably want to put a GetEntry here. 
  tree1->GetEntry(entry);
  chi2Hist->Fill(chi2);

  return kTRUE;
}

void AnalyzeHistogram::SlaveTerminate() {}

void AnalyzeHistogram::Terminate()
{
  //******** Wrap-up section *********
  chi2Hist->Draw();
}
