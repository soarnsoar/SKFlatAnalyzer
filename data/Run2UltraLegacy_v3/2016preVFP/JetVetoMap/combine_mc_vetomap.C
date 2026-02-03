int combine_mc_vetomap(){
    // Open input file
    TFile* fin = TFile::Open("hotjets-UL16.root", "READ");
    if (!fin || fin->IsZombie()) return 0;

    // Get histograms
    TH2D* h_ul16 = (TH2D*) fin->Get("h2hot_ul16_plus_hbm2_hbp12_qie11");
    TH2D* h_mc   = (TH2D*) fin->Get("h2hot_mc");
    if (!h_ul16 || !h_mc) return 0;


    // Clone and add
    TH2D* h_sum = (TH2D*) h_ul16->Clone(
        "h2hot_ul16_plus_hbm2_hbp12_qie11_plus_mc"
    );
    h_sum->SetTitle("h2hot_ul16_plus_hbm2_hbp12_qie11_plus_mc");
    h_sum->Add(h_mc);

    // Write to output file
    TFile* fout = TFile::Open("hotjets-UL16_add_mc.root", "RECREATE");
    h_sum->Write();
    fout->Close();

    fin->Close();
    return 0;
}
