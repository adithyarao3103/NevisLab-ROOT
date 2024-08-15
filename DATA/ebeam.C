#ifdef __CLING__
#pragma cling optimize(0)
#endif
void ebeam()
{
//=========Macro generated from canvas: c1_n2/c1_n2
//=========  (Mon May  1 17:39:10 2023) by ROOT version 6.26/10
   TCanvas *c1_n2 = new TCanvas("c1_n2", "c1_n2",0,0,700,500);
   c1_n2->SetHighLightColor(2);
   c1_n2->Range(148.75,-702.7126,151.25,6324.413);
   c1_n2->SetFillColor(0);
   c1_n2->SetBorderMode(0);
   c1_n2->SetBorderSize(2);
   c1_n2->SetFrameBorderMode(0);
   c1_n2->SetFrameBorderMode(0);
   
   TH1D *hist1dim__1 = new TH1D("hist1dim__1","ebeam",100,149,151);
   hist1dim__1->SetBinContent(16,1);
   hist1dim__1->SetBinContent(20,1);
   hist1dim__1->SetBinContent(21,2);
   hist1dim__1->SetBinContent(22,1);
   hist1dim__1->SetBinContent(23,4);
   hist1dim__1->SetBinContent(24,10);
   hist1dim__1->SetBinContent(25,16);
   hist1dim__1->SetBinContent(26,38);
   hist1dim__1->SetBinContent(27,47);
   hist1dim__1->SetBinContent(28,59);
   hist1dim__1->SetBinContent(29,80);
   hist1dim__1->SetBinContent(30,124);
   hist1dim__1->SetBinContent(31,192);
   hist1dim__1->SetBinContent(32,252);
   hist1dim__1->SetBinContent(33,369);
   hist1dim__1->SetBinContent(34,500);
   hist1dim__1->SetBinContent(35,617);
   hist1dim__1->SetBinContent(36,836);
   hist1dim__1->SetBinContent(37,1025);
   hist1dim__1->SetBinContent(38,1371);
   hist1dim__1->SetBinContent(39,1612);
   hist1dim__1->SetBinContent(40,2001);
   hist1dim__1->SetBinContent(41,2371);
   hist1dim__1->SetBinContent(42,2844);
   hist1dim__1->SetBinContent(43,3182);
   hist1dim__1->SetBinContent(44,3554);
   hist1dim__1->SetBinContent(45,4212);
   hist1dim__1->SetBinContent(46,4393);
   hist1dim__1->SetBinContent(47,4879);
   hist1dim__1->SetBinContent(48,5016);
   hist1dim__1->SetBinContent(49,5294);
   hist1dim__1->SetBinContent(50,5212);
   hist1dim__1->SetBinContent(51,5354);
   hist1dim__1->SetBinContent(52,5292);
   hist1dim__1->SetBinContent(53,5035);
   hist1dim__1->SetBinContent(54,4824);
   hist1dim__1->SetBinContent(55,4416);
   hist1dim__1->SetBinContent(56,4001);
   hist1dim__1->SetBinContent(57,3563);
   hist1dim__1->SetBinContent(58,3198);
   hist1dim__1->SetBinContent(59,2764);
   hist1dim__1->SetBinContent(60,2374);
   hist1dim__1->SetBinContent(61,1980);
   hist1dim__1->SetBinContent(62,1697);
   hist1dim__1->SetBinContent(63,1302);
   hist1dim__1->SetBinContent(64,996);
   hist1dim__1->SetBinContent(65,866);
   hist1dim__1->SetBinContent(66,633);
   hist1dim__1->SetBinContent(67,438);
   hist1dim__1->SetBinContent(68,350);
   hist1dim__1->SetBinContent(69,232);
   hist1dim__1->SetBinContent(70,170);
   hist1dim__1->SetBinContent(71,130);
   hist1dim__1->SetBinContent(72,99);
   hist1dim__1->SetBinContent(73,56);
   hist1dim__1->SetBinContent(74,45);
   hist1dim__1->SetBinContent(75,32);
   hist1dim__1->SetBinContent(76,21);
   hist1dim__1->SetBinContent(77,9);
   hist1dim__1->SetBinContent(78,2);
   hist1dim__1->SetBinContent(79,4);
   hist1dim__1->SetBinContent(82,2);
   hist1dim__1->SetEntries(100000);
   hist1dim__1->SetDirectory(0);
   
   TPaveStats *ptstats = new TPaveStats(0.78,0.775,0.98,0.935,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *ptstats_LaTex = ptstats->AddText("hist1dim");
   ptstats_LaTex->SetTextSize(0.0368);
   ptstats_LaTex = ptstats->AddText("Entries = 100000 ");
   ptstats_LaTex = ptstats->AddText("Mean  =    150");
   ptstats_LaTex = ptstats->AddText("Std Dev   = 0.1498");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   hist1dim__1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(hist1dim__1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#000099");
   hist1dim__1->SetLineColor(ci);
   hist1dim__1->GetXaxis()->SetLabelFont(42);
   hist1dim__1->GetXaxis()->SetTitleOffset(1);
   hist1dim__1->GetXaxis()->SetTitleFont(42);
   hist1dim__1->GetYaxis()->SetLabelFont(42);
   hist1dim__1->GetYaxis()->SetTitleFont(42);
   hist1dim__1->GetZaxis()->SetLabelFont(42);
   hist1dim__1->GetZaxis()->SetTitleOffset(1);
   hist1dim__1->GetZaxis()->SetTitleFont(42);
   hist1dim__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.4346839,0.94,0.5653161,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   TText *pt_LaTex = pt->AddText("ebeam");
   pt->Draw();
   c1_n2->Modified();
   c1_n2->cd();
   c1_n2->SetSelected(c1_n2);
}
