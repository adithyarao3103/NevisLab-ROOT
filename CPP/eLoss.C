void eLoss(){
     // Definitions
    TCanvas* c = nullptr;
    TH2D* hist = nullptr;

    // Initialisations
    c = new TCanvas();
    hist = new TH2D("hist", "zv vs eloss", 500, 0., 30, 500, 0., 120.);

    // Open file
    TFile* myFile = TFile::Open("DATA/experiment.root");

    // Create a TTreeReader
    TTreeReader myReader("tree1", myFile);

    // Point to TTreeReader to which branch (column) to read
    TTreeReaderValue<Float_t> ebeam(myReader, "ebeam");
    TTreeReaderValue<Float_t> px(myReader, "px");
    TTreeReaderValue<Float_t> py(myReader, "py");
    TTreeReaderValue<Float_t> pz(myReader, "pz");
    TTreeReaderValue<Float_t> zv(myReader, "zv");

    // Loop over all entries of ebeam
    while (myReader.Next()){
        Double_t emeas = TMath::Sqrt((*px)*(*px) + (*py)*(*py) + (*pz)*(*pz));
        Double_t eloss = *ebeam - emeas;
        hist->Fill(eloss, *zv);
    }

    // Wrap up
    hist->Draw();
    hist->GetXaxis()->SetTitle("E_{loss}");
    hist->GetYaxis()->SetTitle("zv");

    c->SaveAs("CPP/OUTPUTS/eloss.png");
    TFile file1("CPP/OUTPUTS/output.root","UPDATE");
    hist->Write();
    file1.Close();
}