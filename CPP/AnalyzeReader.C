void AnalyzeReader() {
    // Definitions
    TCanvas* c = nullptr;
    TH1D* ebeamHist = nullptr;
    TH1D* ptHist = nullptr;
    TH1D* zvHist_withCut = nullptr;
    Int_t zvCount;

    // Initialisations
    c = new TCanvas();
    c->Divide(3,0);

    zvCount = 0;

    ebeamHist = new TH1D("ebeam", "Histogram for ebeam", 100, 149.2, 150.8);
    ptHist = new TH1D("pt", "Histogram for pt", 100, 0, 30);
    zvHist_withCut = new TH1D("zv", "Histogram for zv {zv < 20}", 100, 0, 30);

    // Open file
    TFile* myFile = TFile::Open("DATA/experiment.root");

    // Create a TTreeReader
    TTreeReader myReader("tree1", myFile);

    // Point to TTreeReader to which branch (column) to read
    TTreeReaderValue<Float_t> ebeam(myReader, "ebeam");
    TTreeReaderValue<Float_t> px(myReader, "px");
    TTreeReaderValue<Float_t> py(myReader, "py");
    TTreeReaderValue<Float_t> zv(myReader, "zv");

    // Loop over all entries of ebeam
    while (myReader.Next()){
        ebeamHist->Fill(*ebeam);
        Double_t pt = TMath::Sqrt((*px)*(*px) + (*py)*(*py));
        ptHist->Fill(pt);

        if ((*zv)<20){ //Applying a cut
            zvHist_withCut->Fill(*zv);
            zvCount++;
        }
    }

    // Wrap up
    c->cd(1);
    ebeamHist->Fit("gaus");
    gStyle->SetOptFit(0001);
    ebeamHist->Draw();

    c->cd(2);
    ptHist->Draw();

    c->cd(3);
    zvHist_withCut->Draw();

    std::cout<<"Number of zv<20: "<<zvCount;
}