// A short program to make a silly plot.
// 26-May-2024 WGS

void TwoPoints() {
   TCanvas *c1 = new TCanvas("c1","A Simple Two-point Plot",200,10,700,500);

   c1->SetGrid();

   const Int_t n = 2;
   Double_t x[n] = { 0.2, 2.0 };
   Double_t y[n] = { 10., 2.0 };
   TGraph *gr = new TGraph(n,x,y);
   gr->SetMarkerColor(4);
   gr->SetMarkerStyle(20);
   gr->SetMarkerSize(2);
   gr->SetTitle("A couple of anecdotal points");
   gr->GetXaxis()->SetTitle("ROOT tutorials (arbitrary units)");
   gr->GetYaxis()->SetTitle("Physics results (arbitrary units)");
   gr->Draw("AP");

   // TCanvas::Update() draws the frame, after which one can change it
   c1->Update();
   c1->GetFrame()->SetBorderSize(12);
   c1->Modified();
}
