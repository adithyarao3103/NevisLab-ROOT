void execute_cpad(){

    TCanvas* c_pad = new TCanvas();
    c_pad->Divide(2,2);

    TFile* experiment = new TFile("DATA/experiment.root");
    TTree* tree1 = (TTree*)experiment->Get("tree1");
    tree1->Print();

    c_pad->cd(1);
    tree1->Draw("pz:zv"); //ScatterPlot showing correlation

    c_pad->cd(2);
    tree1->Draw("zv", "zv<20"); //Cuts

    c_pad->cd(3);
    tree1->Draw("ebeam", "zv<20"); //Cuts can be applied to any variable

    c_pad->cd(4);
    tree1->Draw("ebeam","px>10 && zv<20") ; //Cuts can be merged with AND and OR

    c_pad->Draw();
}

void execute_vector(){
    std::vector<TCanvas*> canvases;
    int count = -1;

    TFile* experiment = new TFile("DATA/experiment.root");
    TTree* tree1 = (TTree*)experiment->Get("tree1");
    tree1->Print();

    canvases.push_back(new TCanvas()); count++;
    tree1->Draw("pz:zv"); //ScatterPlot showing correlation
    canvases[count]->Draw();

    canvases.push_back(new TCanvas()); count++;
    tree1->Draw("zv", "zv<20"); //Cuts
    canvases[count]->Draw();

    canvases.push_back(new TCanvas()); count++;
    tree1->Draw("ebeam", "zv<20"); //Cuts can be applied to any variable
    canvases[count]->Draw();

    canvases.push_back(new TCanvas()); count++;
    tree1->Draw("ebeam","px>10 && zv<20") ; //Cuts can be merged with AND and OR
    canvases[count]->Draw();
}