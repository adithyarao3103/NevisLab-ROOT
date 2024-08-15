#include "ExampleEvent.h"
void MakeNtuple ()
{
  // You can run this macro with:
  //    root -l MakeNtuple.C
  // or
  //    root
  //    .x MakeNtuple.C

  // This macro reads in a ROOT Tree containing ExampleEvent objects
  // from a file, and creates an n-tuple from it.
  // To be able to read ExampleEvent objects, we need the ROOT
  // dictionary for the ExampleEvent class. This was previously
  // created (see BuildExampleEvent.sh), and we don't have to do that
  // again. But we do have to load the library that contains the
  // definition.

  gSystem->Load("libExampleEvent.so");

  // Open the input file.
  TFile* inputFile = new TFile("exampleEvents.root");
  if ( inputFile == 0 )
    {
      std::cout << "Error: file exampleEvents.root not found" << std::endl;
      return;
    }

  // Open the tree within the input file.
  TTree* exampleEventsTree;
  inputFile->GetObject("exampleEventsTree",exampleEventsTree);
  if ( exampleEventsTree == 0 )
    {
      std::cout << "Error: TTree exampleEventsTree not found" << std::endl;
      return;
    }

  // This tree has only one branch.
  TBranch* exampleEventsBranch;

  // In order to read a ROOT tree, we have to define a "dummy" object
  // that will hold the contents of the file. In this case, the
  // object is an ExampleEvent pointer. Note that, right now, that
  // pointer is set to 0.
  ExampleEvent* exampleEvent = 0;

  // Connect the above pointer with the branch.
  exampleEventsTree->SetBranchAddress("exampleEventsBranch", &exampleEvent, &exampleEventsBranch );

  // That defines how we'll read the tree.  Now we have to define how
  // we'll write the n-tuple.  It follows a similar logic as the above
  // tree definition, but with a different scheme for defining the
  // branches.
  TFile* outputFile = new TFile("exampleNtuple.root","recreate");
  TTree* ntuple = new TTree("exampleEventsNtuple","Selected variables from the ExampleEvents objects");

  // Allocate the variables we'll write.
  Int_t run;
  Int_t event;
  Double_t totalEnergy;
  Double_t muonEnergy;
  Bool_t singleMuon;
  Int_t numberOfMuons;
  Int_t numberOfParticles;

  // In an n-tuple, we assign each variable to its own branch.
  ntuple->Branch("run", &run, "run/I");
  ntuple->Branch("event", &event, "event/I");
  ntuple->Branch("totalEnergy",&totalEnergy,"totalEnergy/D");
  ntuple->Branch("muonEnergy",&muonEnergy,"muonEnergy/D");
  ntuple->Branch("singleMuon",&singleMuon,"singleMuon/O");
  ntuple->Branch("numberOfMuons",&numberOfMuons,"numberOfMuons/I");
  ntuple->Branch("numberOfParticles",&numberOfParticles,"numberOfParticles/I");

  // For each entry in the tree:
  Int_t numberOfEntries = exampleEventsTree->GetEntriesFast();
  for ( Int_t entry = 0; entry != numberOfEntries; ++entry )
    {
      // Get the ExampleEvent object from the file.
      exampleEventsTree->GetEntry(entry);

      // After the above statement, exampleEvent now points to an
      // ExampleEvent object.  Compute the variables we'll write to
      // the n-tuple.

      run = exampleEvent->GetRun();
      event = exampleEvent->GetEvent();

      totalEnergy = 0.;
      muonEnergy = 0.;
      singleMuon = kFALSE;
      numberOfMuons = 0;
      numberOfParticles = 0;

      // First, the leptons
      for ( Int_t i = 0; i != exampleEvent->GetNumberLeptons(); ++i )
	{
	  ++numberOfParticles;

	  Double_t px = exampleEvent->LeptonPx(i);
	  Double_t py = exampleEvent->LeptonPy(i);
	  Double_t pz = exampleEvent->LeptonPz(i);
	  Double_t energy = TMath::Sqrt( px*px + py*py + pz*pz );
	  totalEnergy += energy;

	  // Muons have some special processing, if there are any.
	  Int_t pdg = exampleEvent->LeptonPDG(i);
	  if ( pdg == 13  ||  pdg == -13 )
	    {
	      // The particle is a muon.
	      muonEnergy += energy;
	      ++numberOfMuons;
	    }
	}
      singleMuon = ( numberOfMuons == 1 );

      // Next, the photons.
      for ( Int_t i = 0; i != exampleEvent->GetNumberPhotons(); ++i )
	{
	  ++numberOfParticles;

	  Double_t px = exampleEvent->PhotonPx(i);
	  Double_t py = exampleEvent->PhotonPy(i);
	  Double_t pz = exampleEvent->PhotonPz(i);
	  Double_t energy = TMath::Sqrt( px*px + py*py + pz*pz );
	  totalEnergy += energy;
	}

      // Finally, the hadrons.
      for ( Int_t i = 0; i != exampleEvent->GetNumberHadrons(); ++i )
	{
	  ++numberOfParticles;

	  Double_t px = exampleEvent->HadronPx(i);
	  Double_t py = exampleEvent->HadronPy(i);
	  Double_t pz = exampleEvent->HadronPz(i);
	  Double_t energy = TMath::Sqrt( px*px + py*py + pz*pz );
	  totalEnergy += energy;
	}

      // Write all the n-tuple variables.
      ntuple->Fill();
    }

  // Make sure we've written the entire n-tuple to the output file,
  // then close all files.
  ntuple->Write();
  inputFile->Close();
  outputFile->Close();
}
