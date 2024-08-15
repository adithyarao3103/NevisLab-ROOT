//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue May 19 17:01:00 2009 by ROOT version 5.22/00
// from TTree histogramList/A 'map' of histograms and associated values of x.
// found on file: folders.root
//////////////////////////////////////////////////////////

#ifndef histogramList_h
#define histogramList_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class histogramList {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Char_t          histogramName[5];
   Double_t        x;

   // List of branches
   TBranch        *b_histogramName;   //!
   TBranch        *b_x;   //!

   histogramList(TTree *tree=0);
   virtual ~histogramList();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef histogramList_cxx
histogramList::histogramList(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("folders.root");
      if (!f) {
         f = new TFile("folders.root");
         f->cd("folders.root:/distributions");
      }
      tree = (TTree*)gDirectory->Get("histogramList");

   }
   Init(tree);
}

histogramList::~histogramList()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t histogramList::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t histogramList::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void histogramList::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("histogramName", histogramName, &b_histogramName);
   fChain->SetBranchAddress("x", &x, &b_x);
   Notify();
}

Bool_t histogramList::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void histogramList::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t histogramList::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef histogramList_cxx
