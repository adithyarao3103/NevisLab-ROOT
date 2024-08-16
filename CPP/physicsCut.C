void physicsCut() {
    // Definitions
    TCanvas* c = nullptr;
    TH2D* hist_bc = nullptr;
    TH2D* hist_ac = nullptr;

    // Initialisations
    c = new TCanvas("c", "c", 800, 400);
    c->Divide(2,0);
    hist_bc = new TH2D("hist", "chi2 vs theta before cut", 500, 0., 0.24, 500, 0., 20.);
    hist_ac = new TH2D("hist", "chi2 vs theta after cut", 500, 0., 0.18, 500, 0., 2.);

    // Open file
    TFile* myFile = TFile::Open("DATA/experiment.root");

    // Create a TTreeReader
    TTreeReader myReader("tree1", myFile);

    // Point to TTreeReader to which branch (column) to read
    TTreeReaderValue<Float_t> chi2(myReader, "chi2");
    TTreeReaderValue<Float_t> px(myReader, "px");
    TTreeReaderValue<Float_t> py(myReader, "py");
    TTreeReaderValue<Float_t> pz(myReader, "pz");

    // Loop over all entries of ebeam
    while (myReader.Next()){
        Double_t pt = TMath::Sqrt((*px)*(*px) + (*py)*(*py));
        Double_t theta = TMath::ATan2(pt, (*pz));
        hist_bc->Fill(theta, *chi2);

        if (*chi2 < 1.5 && theta < 0.15 ) { //Cut
            hist_ac->Fill(theta, *chi2);
        }
    }

    // Wrap up
    c->cd(1);
    hist_bc->Draw();
    hist_bc->GetXaxis()->SetTitle("Theta");
    hist_bc->GetYaxis()->SetTitle("chi2");
    
    c->cd(2);
    hist_ac->Draw();
    hist_ac->GetXaxis()->SetTitle("Theta");
    hist_ac->GetYaxis()->SetTitle("chi2");

    c->SaveAs("CPP/OUTPUTS/PhysicsCut.png");
    TFile file1("CPP/OUTPUTS/output.root","UPDATE");
    hist_bc->Write();
    hist_ac->Write();
    file1.Close();
}