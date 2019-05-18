void fittingMacro(){
	TH1::AddDirectory(ROOT::kFALSE);
	gROOT->SetStyle("Plain");
	gStyle->SetOptFit(1111);
	
	TFile file = TFile("data.root");

	TCanvas * c= new TCanvas("combined","combined",400,300);

	TH1F * h= (TH1F*) file.Get("combined");
	TF1 * f_bg= new TF1("f_bg","[0]+[1]*x+[2]*exp(-[3]*x)");
	f_bg->SetParNames("#alpha","#beta","#gamma","#delta");
	f_bg->SetParameters(30,-0.06,800,0.01);
	f_bg->SetLineColor(kRed);
	f_bg->SetLineStyle(kDashed);

	h->Draw("E2");
	h->Fit("f_bg");	
	// f_bg->Draw("alpsame");
	double * bg_pars=f_bg->GetParameters();

	
	TF1 * f_sig = new TF1("f_sig","gaus(0)");
	f_sig->SetParNames("N","#mu","#sigma");


	TH1F * h1 = h->Clone();
	
	TF1 *f_sb= new TF1("f_sb","[0]+[1]*x+[2]*exp(-[3]*x)+[4]*exp(-0.5*((x-[5])/[6])**2)",0,300);
	// TF1 * f_sb= new TF1("f_sb","f_bg+f_sig",0,300);
	f_sb->SetParNames("#alpha","#beta","#gamma","#delta","N","#mu","#sigma");
	f_sb->SetParameters(bg_pars[0],bg_pars[1],bg_pars[2],bg_pars[3],0.004,173,10);
	// f_sb->SetParameters(*bg_pars++,*bg_pars++,*bg_pars++,*bg_pars++,0.004,173,10);
	f_sb->SetLineColor(kBlue);
	h1->Fit("f_sb");
	// h->Fit("f_bg","SAME");
	for(int i=0;i<4;i++){
		f_bg->SetParameter(i,f_sb->GetParameter(i));
	}
	f_bg->Draw("lSAME");
	
	double * sb_pars=f_sb->GetParameters();
	// h->DrawClone("E1");
	// f_bg->DrawClone("lsame");
	// f_sb->DrawClone("lsame");
	
	

	cout << "ChiSquared BG-Only: " << f_bg->GetChisquare()<<endl;
	cout << "ChiSquared Sig+BG: " << f_sb->GetChisquare()<<endl;

	c->Print("combined.eps");

	// exit(0);
}
