void plottingFunction(){
    TF1 *f = new TF1("func1", "sin(x)/x", 0, 10);
    TCanvas *c1 = new TCanvas();
    f->Draw();
    c1->Draw();
}

void excercise1(){
    TF2 *f = new TF2("func2", "sin(x)*sin(y)/(x*y)", -10, 10, -10, 10);
    TCanvas *c1 = new TCanvas();
    f->Draw("surf1");
    c1->Draw();
}

void histogram(){
    TH1D *h = new TH1D("hist1", "Example Histogram", 100, -3, 3);
    h->FillRandom("gaus", 10000);
    TCanvas *c1 = new TCanvas();
    h->Draw();
    c1->Draw();
}

void customHistogram(){
    TF1 *myFun = new  TF1("myFun", "sin(x)", 0, TMath::Pi());
    TH1D *h = new TH1D("hist1", "Custom Histogram", 100, 0, TMath::Pi());
    h->FillRandom("myFun", 10000);
    TCanvas *c1 = new TCanvas();
    h->Draw("e");
    c1->Draw();
}

void fittingHistToGaus(){
    TH1D *h = new TH1D("hist1", "Histogram", 100, -3, 3);
    h->FillRandom("gaus", 10000);
    h->Fit("gaus");
    TCanvas *c1 = new TCanvas();
    h->Draw();
    gStyle->SetOptFit(0001); // To display the fit results
    c1->Draw();
}

void fittingHistogramCustom(){
    TFile* file1 =  TFile::Open("DATA/histogram.root");
    TH1D* h1 = (TH1D*)file1->Get("hist2");
    TF1* myFunc = new TF1("myFunc", "gaus(0) + gaus(3)", 0, 14) ;
    myFunc->SetParameters(5., 2., 1., 1., 10., 1.);
    // myFunc->Draw();
    h1->Fit("myFunc");
    h1->Draw();
}