// Stand-alone program based on AnalyzeExercise10.C
// Almost the same as AnalyzeExercise10.cxx, except we're
// being more rigorous about memory and using unique_ptr
// instead of normal pointers. 
// To compile this:
//   g++ `root-config --cflags --libs` AnalyzeExercise10_ptr.cxx -o AnalyzeExercise10_ptr

#include <TSelector.h>
#include <TFile.h>
#include <TTree.h>
#include <memory>

// Main program.
int main(int argc, char *argv[])
{
  // Open the file that the TSelector class will process.
  std::unique_ptr<TFile> inputfile( new TFile("experiment.root") );
  // Read tree1 from the input file.
  std::unique_ptr<TTree> tree1( (TTree*) inputfile->Get("tree1") ); 
  // Did we read in tree1?
  if  (tree1 != nullptr)
    {
      // Tell tree1 to process the class created by MakeSelector.
      tree1->Process("AnalyzeExercise10.C");
    }
}
