void run(){

  TFile *file_org = new TFile("HEEP_SF.root");

  vector<TString> etaregions = {
    "Barrel",
    "Endcap",
  };

  TFile *file_new = new TFile("HEEP_SF_SKFlatAnalyzer.root","RECREATE");
  for(unsigned int i=0; i<etaregions.size(); i++){
    TString etaregion = etaregions.at(i);

    cout << "["<<etaregion<<"]" << endl;

    TGraphAsymmErrors *gr_sf = (TGraphAsymmErrors *)file_org->Get("SF_Et_"+etaregion);


    int NX = gr_sf->GetN();

    double bins_x[NX+1];
    double sf_central[NX], sf_high[NX], sf_low[NX];
		for(int j=0; j<NX; j++){

			double x, x_low, x_high;
      double y, y_low, y_high;

			gr_sf->GetPoint(j, x, y);
      x_low = gr_sf->GetErrorXlow(j);
      x_high = gr_sf->GetErrorXhigh(j);
      y_low = gr_sf->GetErrorYlow(j);
      y_high = gr_sf->GetErrorYhigh(j);

      bins_x[j] = x-x_low;
      if(j==NX-1) bins_x[j+1] = x+x_high;

      sf_central[j] = y;
      sf_high[j] = y_high;
      sf_low[j] = y_low;

      //cout << x_low << "\t" << x << "\t" << x_high << "\t" << y_low << "\t" << y << "\t" << y_high << endl;
    

		}
    for(int j=0; j<NX+1; j++){
      cout << bins_x[j] << ", ";
    }
    cout << endl;

    TH1D *hist_sf = new TH1D("EGamma_SF2D_"+etaregion, "", NX, bins_x);
    TH1D *hist_sf_down = new TH1D("EGamma_SF2D_"+etaregion+"_down", "", NX, bins_x);

    for(int j=1; j<=hist_sf->GetXaxis()->GetNbins(); j++){
      hist_sf->SetBinContent(j,sf_central[j-1]);
      hist_sf->SetBinError(j,sf_high[j-1]);
      hist_sf_down->SetBinContent(j,sf_central[j-1]);
      hist_sf_down->SetBinError(j,sf_low[j-1]);
    }

    file_new->cd();
    hist_sf->Write();
    hist_sf_down->Write();


  }

  file_new->Close();




}
