#define AnalyzeChi2_cxx

#include "AnalyzeChi2.h"
#include <TH2.h>
#include <TStyle.h>

//******** Definition section *********
TH1* chi2Hist = nullptr;

void AnalyzeChi2::Begin(TTree * /*tree*/)
{
  TString option = GetOption();

  //******** Initialization section *********
  chi2Hist = new TH1D("chi2","Histogram of Chi2",100,0,20);
}

void AnalyzeChi2::SlaveBegin(TTree *) {}

Bool_t AnalyzeChi2::Process(Long64_t entry)
{
  fReader.SetEntry(entry);

  //******** Loop section *********
  GetEntry(entry);
  chi2Hist->Fill(*chi2);

  return kTRUE;
}

void AnalyzeChi2::SlaveTerminate() {}

void AnalyzeChi2::Terminate()
{
  //******** Wrap-up section *********
  chi2Hist->Draw();
}
