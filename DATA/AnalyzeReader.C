// A replacement for Analyze.h and Analyze.C that uses TTreeReader
// instead of a TSelector created by MakeSelector.

// To run this in command-line ROOT, you can just run:
// > root AnalyzeReader.C

// Define a function to read our TTree. For the example command above
// to work, the name of the function must match the name of file, so
// we define AnalyzeReader() inside AnalyzeReader.C.

void AnalyzeReader() {

  //******** Definition section *********

  //******** Initialization section *********

  // Open the file containing the tree.
  TFile* myFile = TFile::Open("experiment.root");

  // Create a TTreeReader for the TTree "tree1" in 'myFile'.
  TTreeReader myReader("tree1", myFile);

  // Tell the TTreeReader which	branches (or columns) we'll read.
  // Because TTreeReaderValue behaves like a pointer, to access the
  // contents of the variable 'ebeam' I have to use pointer syntax;
  // e.g., "auto energy = *ebeam;".

  TTreeReaderValue<Float_t> ebeam(myReader, "ebeam");

  // Loop over all the entries of the TTree.
  while (myReader.Next()) {
    
    //******** Loop section *********

  }

  //******** Wrap-up section *********
}
