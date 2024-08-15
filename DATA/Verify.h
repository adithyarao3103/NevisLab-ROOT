//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May  5 18:15:34 2006 by ROOT version 5.10/00
// from TTree tree1/Reconstruction ntuple
// found on file: experiment.root
//////////////////////////////////////////////////////////

#ifndef Verify_h
#define Verify_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

class Verify {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leave types
   Int_t           event;
   Float_t         ebeam;
   Float_t         px;
   Float_t         py;
   Float_t         pz;
   Float_t         zv;
   Float_t         chi2;

   // List of branches
   TBranch        *b_event;   //!
   TBranch        *b_ebeam;   //!
   TBranch        *b_px;   //!
   TBranch        *b_py;   //!
   TBranch        *b_pz;   //!
   TBranch        *b_zv;   //!
   TBranch        *b_chi2;   //!

   Verify(TTree *tree=0);
   virtual ~Verify();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Verify_cxx
Verify::Verify(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("experiment.root");
      if (!f) {
         f = new TFile("experiment.root");
      }
      tree = (TTree*)gDirectory->Get("tree1");

   }
   Init(tree);
}

Verify::~Verify()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Verify::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Verify::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->IsA() != TChain::Class()) return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Verify::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses of the tree
   // will be set. It is normaly not necessary to make changes to the
   // generated code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running with PROOF.

   // Set branch addresses
   if (tree == 0) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event",&event);
   fChain->SetBranchAddress("ebeam",&ebeam);
   fChain->SetBranchAddress("px",&px);
   fChain->SetBranchAddress("py",&py);
   fChain->SetBranchAddress("pz",&pz);
   fChain->SetBranchAddress("zv",&zv);
   fChain->SetBranchAddress("chi2",&chi2);
   Notify();
}

Bool_t Verify::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. Typically here the branch pointers
   // will be retrieved. It is normaly not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed.

   // Get branch pointers
   b_event = fChain->GetBranch("event");
   b_ebeam = fChain->GetBranch("ebeam");
   b_px = fChain->GetBranch("px");
   b_py = fChain->GetBranch("py");
   b_pz = fChain->GetBranch("pz");
   b_zv = fChain->GetBranch("zv");
   b_chi2 = fChain->GetBranch("chi2");

   return kTRUE;
}

void Verify::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Verify::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Verify_cxx
