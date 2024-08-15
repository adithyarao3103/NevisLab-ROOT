#include <vector>
void PlotGraphs()
{
  // You can run this macro with:
  //    root -l PlotGraphs.C
  // or
  //    root
  //    .x PlotGraphs.C

  // What's the point of making the students suffer if you haven't
  // suffered yourself, at least a little bit? So here's how I
  // solved the problems of making plots from the histograms in
  // folders.root.

  // Note that this deviates from what I asked the students to do: I
  // asked them to generate these plots in separate exercises, but I'm
  // doing all three in a single program. This helps discourage the
  // too-clever ones from simply copying my code.

  // First, open the file.
  TString fileName = "folders.root";
  TFile* inputFile = new TFile( fileName );

  // The folders in which we'll navigate. I could do this with an
  // array, but I like vectors. I don't even have to use a vector of
  // TStrings, but (a) it makes it easier if I ever decide to add more
  // folders to the file; (b) it defines the folder names near the top
  // of the program, where I can see them if I need to change them.
  std::vector< TString > folder(3);
  folder[0] = "example1";
  folder[1] = "example2";
  folder[2] = "example3";

  // Fiddle with the file and folder names to get the absolute path to
  // each folder within the file.
  for ( Int_t i = 0; i != folder.size(); ++i )
    {
      folder[i] = fileName + ":/" + folder[i];
    }

  ////////////////////////////////////
  // 
  // Plot 1

  // Now let's go to a particular directory.
  TDirectory* example1 = inputFile->GetDirectory( folder[0] );
  if ( example1 == 0 )
    {
      std::cout << "Fatal error: folder " << folder[0] << " does not exist." << std::endl;
      return;
    }
  example1->cd();

  // For the first folder example, I know there are exactly six
  // histograms.  I could use the fancier technique that I use in
  // example3; in fact, I'd prefer to do so.  But let's keep it simple
  // for the first example.
  Int_t numberOfHistograms = 6;

  // Create the vectors that will hold the information to be displayed on the plot.
  std::vector< Double_t > xValue( numberOfHistograms );
  std::vector< Double_t > yValue( numberOfHistograms );
  std::vector< Double_t > xError( numberOfHistograms );
  std::vector< Double_t > yError( numberOfHistograms );

  // A gaussian function to fit the histograms. One more time: not
  // all of physics is fit with gaussian distributions! I'm using
  // them here because they're a simple example!
  TF1 myFunction("myFunction","gaus");

  // For each histogram in the folder:
  for ( Int_t i = 0; i != numberOfHistograms; ++i )
    {
      // We have to derive the name of the histogram as stored in the
      // folder. String manipulation in C++ can be a little tricky.
      // Fortunately, ROOT's TString class is defined in such a way
      // that if you add a number to a string, it appends the text
      // version of that number to the end of the string.
      TString name = "hist";
      name += i;

      // Get an object with this name from the current directory in the file.
      TH1* histogram;
      example1->GetObject(name,histogram);

      // What if there's some kind of problem; for example, the object
      // with the name "hist456" may not be a histogram after all, or
      // maybe it doesn't exist. In either case, the value of the
      // histogram pointer will be 0.
      if ( histogram == 0 )
	{
	  std::cout << "Error: histogram '" << name << "' not found" << std::endl;
	  continue; // go to the next cycle of the loop
	}

      // How do we get the value of x given this histogram? In this
      // case, I've given the students no other way other than to
      // display each histogram, look at the description, and derive
      // the following formula.
      xValue[i] = 0.5*pow(10,i-1);

      // For all the plots, there is no error in x.
      xError[i] = 0;

      // The value and error in y comes from the histograms.
      // Actually, I've constructed the histograms so that you can bet
      // these values from the mean and RMS of the histograms. But
      // let's use a gaussian fit. Before fitting, set the initial
      // values of the gaussian function from the histogram statistics.
      myFunction.SetParameters( histogram->GetMaximum(),
				histogram->GetMean(),
				histogram->GetRMS() );
      // "Q" means quiet; otherwise we get text printed for every fit.
      // "N" means do not plot the function after we're done.
      histogram->Fit("myFunction","QN");

      yValue[i] = myFunction.GetParameter(1);
      yError[i] = myFunction.GetParameter(2);
    }

  // Create a canvas on which to draw the graph.

  // How did I figure out all the options and values to put on the
  // graph? It was a combination of two things:

  // 1) I looked in $ROOTSYS/tutorials and hunted around for a simple
  // example of TGraphErrors. I found one in
  // $ROOTSYS/tutorials/graphs/gerrors.C.

  // 2) After creating an initial graph, I saved it as a .C file.
  // Then I looked at the commands, copied them, and adjusted the
  // settings.

  TCanvas* canvas1 = new TCanvas("canvas1", "canvas1",20,20,775,646);
  canvas1->Range(0.01,-3.85618,4.12408,10000.);
  canvas1->SetBorderSize(2);
  canvas1->SetLogx();
  canvas1->SetGridx();
  canvas1->SetGridy();
  canvas1->SetLeftMargin(0.119326);
  canvas1->cd();

  // We want to create the graph with error bars. We have a problem;
  // I stored the numbers in the form std::vector<Double_t>, but the
  // ROOT web site says that TGraphErrors needs Double_t*, which is
  // the pointer to the first element of an array.

  // There's a C++ trick that let's us get at the underlying array
  // within a vector: if v is of type std::vector<T>, then v.data() is
  // the same as a pointer to the first element of an array of T.
  TGraphErrors* graph1 
    = new TGraphErrors( numberOfHistograms, xValue.data(), yValue.data(), 
                                            xError.data(), yError.data() );

  graph1->SetName("PunPlot");
  graph1->SetTitle("Number of charged atoms in 'Nights in the Gardens of Spain'");
  graph1->SetFillColor(1);
  graph1->SetMarkerColor(4);
  graph1->SetMarkerStyle(21);
  graph1->SetMarkerSize(1.3);

  // Define xAxis and yAxis. We're going to re-use these variables later.
  TAxis* xAxis = 0;
  TAxis* yAxis = 0;

  // Set the axis labels. Note the use of TLatex on the y-axis title.
  xAxis = graph1->GetXaxis();
  xAxis->SetTitle("t [secs]");
  xAxis->CenterTitle( kTRUE );
  xAxis->SetTitleOffset( 1.2 );

  yAxis = graph1->GetYaxis();
  yAxis->SetTitle("#frac{n_{ions}}{d#left(Falla#right)}");
  yAxis->CenterTitle( kTRUE );
  yAxis->SetTitleOffset( 1.2 );

  // Draw the graph on the canvas.
  graph1->Draw("AP");
  canvas1->Update();


  ////////////////////////////////////
  // 
  // Plot 2

  // On to the next folder.
  TDirectory* example2 = inputFile->GetDirectory( folder[1] );
  if ( example2 == 0 )
    {
      std::cout << "Fatal error: folder " << folder[1] << " does not exist." << std::endl;
      return;
    }
  example2->cd();

  // Reset the arrays.
  xValue.clear();
  xError.clear();
  yValue.clear();
  yError.clear();

  // For the second example, the correspondence between the histograms
  // and the x-values is in a TTree. I told the students to use
  // histogramList->MakeSelector() to create the code to read the tree.
  // But since I know what I'm doing (OK, you can stop laughing now)
  // I'll just read the tree directly.

  TTree* histogramList;
  example2->GetObject("histogramList",histogramList);
  if ( histogramList == 0 )
    {
      std::cout << "Error: TTree histogramList not found" << std::endl;
    }
  else
    {
      Int_t numberOfEntries = histogramList->GetEntriesFast();

      // Define the branches of the tree.
      TBranch* histogramNumberBranch;
      TBranch* xBranch;

      // The variables we'll read from those branches.
      Int_t histogramNumber;
      Double_t x;

      // Connect the variables with the branches.
      histogramList->SetBranchAddress("histNumber", &histogramNumber, &histogramNumberBranch );
      histogramList->SetBranchAddress("x", &x, &xBranch );

      // For each entry in the tree...
      for ( Int_t i = 0; i != numberOfEntries; ++i )
	{
	  // Get the i-th entry in the tree. Because of the
	  // "SetBranchAddress" calls above, this will automatically
	  // set the values of histogramNumber and x.
	  histogramList->GetEntry(i);

	  // Derive the histogram name.
	  TString name = "hist";
	  name += histogramNumber;
	  
	  // Fetch the histogram.
	  TH1* histogram;
	  example2->GetObject(name,histogram);
	  if ( histogram == 0 )
	    {
	      std::cout << "Error: histogram '" << name << "' not found" << std::endl;
	      continue; // go to the next cycle of the loop
	    }

	  // Fit the histogram.
	  myFunction.SetParameters( histogram->GetMaximum(),
				    histogram->GetMean(),
				    histogram->GetRMS() );
	  histogram->Fit("myFunction","QN");

	  // Add the results to the end of the list of numbers.
	  xValue.push_back( x );
	  xError.push_back( 0 );
	  yValue.push_back( myFunction.GetParameter(1) );
	  yError.push_back( myFunction.GetParameter(2) );
	}

      // Create a canvas on which to draw the graph.

      TCanvas* canvas2 = new TCanvas("canvas2", "canvas2",40,40,775,646);
      canvas2->Range(0.01,-3.85618,4.12408,10000.);
      canvas2->SetBorderSize(2);
      canvas2->SetLeftMargin(0.119326);
      canvas2->cd();

      // Create the graph.
      TGraphErrors* graph2 
	= new TGraphErrors( xValue.size(), &xValue[0], &yValue[0], &xError[0], &yError[0] );

      graph2->SetName("Example2Plot");
      graph2->SetTitle("Results of fits to example2 histograms");
      graph2->SetFillColor(1);
      graph2->SetMarkerColor(4);
      graph2->SetMarkerStyle(21);
      graph2->SetMarkerSize(1.3);

      // Set the axis labels.
      xAxis = graph2->GetXaxis();
      xAxis->SetTitle("x; units unknown");
      xAxis->CenterTitle( kTRUE );
      xAxis->SetTitleOffset( 1.2 );

      yAxis = graph2->GetYaxis();
      yAxis->SetTitle("value from fit");
      yAxis->CenterTitle( kTRUE );
      yAxis->SetTitleOffset( 1.2 );

      // Draw the graph on the canvas.
      graph2->Draw("AP");
      canvas2->Update();
    }


  ////////////////////////////////////
  // 
  // Plot 3

  // The final folder.
  TDirectory* example3 = inputFile->GetDirectory( folder[2] );
  if ( example3 == 0 )
    {
      std::cout << "Fatal error: folder " << folder[2] << " does not exist." << std::endl;
      return;
    }
  example3->cd();

  // Reset the arrays.
  xValue.clear();
  xError.clear();
  yValue.clear();
  yError.clear();

  // For the third example, there's no particular guide to the
  // histogram names. Let's start by getting a list of everything in
  // the folder. I had to hunt a bit through the web pages and the
  // tutorials, but this seems to be the way to go through all the
  // objects in the folder:
  TIter next( example3->GetListOfKeys() );
  TKey* key = 0;
  while ( ( key = (TKey*) next() ) )
    {
      TH1* histogram = (TH1*) key->ReadObj();
      // Is this object a histogram?
      if ( histogram != 0 )
	{
	  // It's a histogram.  We only want to look at those
	  // histogram whose names begin with the text
	  // "plotAfterCuts".
	  TString name = histogram->GetName();
	  if ( name.BeginsWith("plotAfterCuts") )
	    {
	      // We're going to work with this histogram.  The value
	      // of x is contained in the histogram title.
	      TString title = histogram->GetTitle();

	      // How do we convert the text into a number?
	      // Fortunately, there's already a TString method that
	      // does just that.
	      Double_t x = title.Atof();

	      // Fit the histogram.
	      myFunction.SetParameters( histogram->GetMaximum(),
					histogram->GetMean(),
					histogram->GetRMS() );
	      histogram->Fit("myFunction","QN");

	      // Add the results to the end of the list of numbers.
	      xValue.push_back( x );
	      xError.push_back( 0 );
	      yValue.push_back( myFunction.GetParameter(1) );
	      yError.push_back( myFunction.GetParameter(2) );
	    }
	} // if the object is a histogram
    } // for each object in the folder

      // Create a canvas on which to draw the graph.
  TCanvas* canvas3 = new TCanvas("canvas3", "canvas3",60,60,775,646);
  canvas3->Range(0.01,-3.85618,4.12408,10000.);
  canvas3->SetBorderSize(2);
  canvas3->SetLeftMargin(0.119326);
  canvas3->cd();

  // Create the graph.
  TGraphErrors* graph3 
    = new TGraphErrors( xValue.size(), &xValue[0], &yValue[0], &xError[0], &yError[0] );

  graph3->SetName("Example3Plot");
  graph3->SetTitle("Results of fits to example3 after-cut histograms");
  graph3->SetFillColor(1);
  graph3->SetMarkerColor(4);
  graph3->SetMarkerStyle(21);
  graph3->SetMarkerSize(1.3);

  // Set the axis labels.
  xAxis = graph3->GetXaxis();
  xAxis->SetTitle("x; units unknown");
  xAxis->CenterTitle( kTRUE );
  xAxis->SetTitleOffset( 1.2 );

  yAxis = graph3->GetYaxis();
  yAxis->SetTitle("value from fit");
  yAxis->CenterTitle( kTRUE );
  yAxis->SetTitleOffset( 1.2 );

  // Draw the graph on the canvas.
  graph3->Draw("AP");
  canvas3->Update();
}

