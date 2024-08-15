// A program to create a tree of ExampleEvent records for the two-day
// ROOT tutorial.

// 22-May-2009 <seligman@nevis.columbia.edu>

#include "ExampleEvent.h"

#include <TFile.h>
#include <TTree.h>

int main ( int argc, char** argv )
{
  // Open the output file, overwriting any file that might have been
  // there previously.
  TFile* outputFile = new TFile("exampleEvents.root","recreate");

  // Create a TTree to hold ExampleEvent objects.
  TTree* t1 = new TTree("exampleEventsTree","A tree of example event objects");
  ExampleEvent* exampleEvent = 0;
  t1->Branch("exampleEventsBranch",&exampleEvent);

  // Start with a new ExampleEvent object.
  exampleEvent = new ExampleEvent();

  // Create a few of these objects, writing each one to the output
  // tree.
  Int_t numberExampleEvents = 50000;
  for ( Int_t i = 0; i != numberExampleEvents; ++i )
    {
      // Fill the example event with dummy information.
      exampleEvent->Build();

      // Write it to the tree.
      t1->Fill();
    }

  // When we're done, write the tree and close the output file.
  t1->Write();
  outputFile->Close();

  return 0;
}
