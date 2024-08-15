{
//=========Macro generated from canvas: cvs1/A test canvas
//=========  (Thu May 24 15:21:35 2001) by ROOT version3.00/06
   TCanvas *cvs1 = new TCanvas("cvs1", "A test canvas",100,100,808,617);
   cvs1->Range(0,0,1,1);
   cvs1->SetBorderSize(2);
   TCurlyLine *curlyline = new TCurlyLine(0.335821,0.524618,0.70398,0.529711,0.05,0.02);
   curlyline->Draw();
   TLine *line = new TLine(0.0957711,0.7691,0.335821,0.52292);
   line->Draw();
   line = new TLine(0.0957711,0.295416,0.334577,0.524618);
   line->Draw();
   line = new TLine(0.705224,0.531409,0.879353,0.792869);
   line->Draw();
   line = new TLine(0.70398,0.529711,0.881841,0.266553);
   line->Draw();
   TCurlyArc *curlyarc = new TCurlyArc(0.527363,0.5382,0.0696095,0,180,0.05,0.02);
   curlyarc->Draw();
   TLatex *tex = new TLatex(0.227612,0.655348,"q_{1}");
   tex->SetTextSize(0.05);
   tex->SetLineWidth(2);
   tex->Draw();
   tex = new TLatex(0.205224,0.368421,"q_{2}");
   tex->SetTextSize(0.05);
   tex->SetLineWidth(2);
   tex->Draw();
   cvs1->Modified();
   cvs1->cd();
}
