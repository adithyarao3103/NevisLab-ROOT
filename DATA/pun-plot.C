{
Int_t n = 6;
Float_t x[n];
Float_t y[n];
Float_t ex[n];
Float_t ey[n];

for (Int_t i=0; i != n; i++)
{
  x[i] = 0.5*pow(10,i-1);
  ex[i] = 0.;

  y[i] = 3.*log(x[i] + 100.);
  ey[i] = 0.1*y[i];
}

   TCanvas *c1 = new TCanvas("c1", "c1",10,10,775,646);
   c1->Range(0.01,-3.85618,4.12408,10000.);
   c1->SetBorderSize(2);
   c1->SetLogx();
   c1->SetGridx();
   c1->SetGridy();
   c1->SetLeftMargin(0.119326);
   
   gre = new TGraphErrors(6,x,y,ex,ey);
   gre->SetName("PunPlot");
   gre->SetTitle("Number of charged atoms in 'Nights in the Gardens of Spain'");
   gre->SetFillColor(1);
   gre->SetMarkerColor(4);
   gre->SetMarkerStyle(21);
   gre->SetMarkerSize(1.3);
   gre->Draw("AP");
   c1->Modified();
   c1->cd();
}
}
