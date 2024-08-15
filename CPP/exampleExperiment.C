void exampleExperiment(){
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