#include <stdio.h>
void treeMacro(){
	TH1::AddDirectory(kFALSE);
	
	cout << "loading Files..." << endl;
	TFile * bgFile = new TFile("background.root");
	TFile * sigFile = new TFile("signal.root");

	TTree * bgTree = (TTree*)bgFile->Get("btree");
	// TTree * bgTree = dynamic_cast<TTree*> bgFile->Get("btree");
	TTree * sigTree = (TTree*)sigFile->Get("stree");

	TH1F * bg_pT = new TH1F("bg_pT","p_T [GeV]",50,0,110);
	TH1F * sig_pT = new TH1F("sig_pT","p_T [GeV]",50,0,110);

	TH1F * bg_energy = new TH1F("bg_energy","E [GeV]",100,0,1000);
	TH1F * sig_energy = new TH1F("sig_energy","E [GeV]",100,0,1000);

	TH1F * bg_eta = new TH1F("bg_eta","#eta",20,-6.5,6.5);
	TH1F * sig_eta = new TH1F("sig_eta","#eta",20,-6.5,6.5);

	TH1F * bg_phi = new TH1F("bg_phi","#phi",20,-3.2,3.2);
	TH1F * sig_phi = new TH1F("sig_phi","#phi",20,-3.2,3.2);


	std::vector<TTree*> trees={bgTree,sigTree};
	

	std::vector<TH1F*> pT_hists= {bg_pT,sig_pT};
	std::vector<TH1F*> energy_hists= {bg_energy,sig_energy};
	std::vector<TH1F*> eta_hists= {bg_eta,sig_eta};
	std::vector<TH1F*> phi_hists= {bg_phi,sig_phi};

	
	for(int i=0;i<2;i++){
		TBranch *branchPX = trees[i]->GetBranch("px");
		TBranch *branchPY = trees[i]->GetBranch("py");
		TBranch *branchPZ = trees[i]->GetBranch("pz");
		TBranch *branchE = trees[i]->GetBranch("E");
		
		Double_t px,py,pz,E;
		branchPX->SetAddress(&px);
		branchPY->SetAddress(&py);
		branchPZ->SetAddress(&pz);
		branchE->SetAddress(&E);

		Int_t NEntries=trees[i]->GetEntries();
		
		for (int j=0; j < NEntries; j++) {
			branchPX->GetEntry(j);
			branchPY->GetEntry(j);
			branchPZ->GetEntry(j);
			branchE->GetEntry(j);
			TLorentzVector p = TLorentzVector(px,py,pz,E);
			if(i==0){
				bg_pT->Fill(p.Pt());
				bg_energy->Fill(p.E());
				bg_eta->Fill(p.Eta());
				bg_phi->Fill(p.Phi());		
			}else{
				sig_pT->Fill(p.Pt());
				sig_energy->Fill(p.E());
				sig_eta->Fill(p.Eta());
				sig_phi->Fill(p.Phi());		
			}
		}
	}
	TCanvas * c_pT = new TCanvas("pT","pT",600,600);
	c_pT->SetLogy();
	bg_pT->SetLineColor(kRed);
	bg_pT->SetFillColor(kRed);
	bg_pT->Draw("H");
	sig_pT->SetLineColor(kBlue);
	sig_pT->SetFillColor(kBlue);
	sig_pT->Draw("HSAME");
	c_pT->Print("pT.eps");
	TCanvas * c_energy = new TCanvas("energy","energy",600,600);
	c_energy->SetLogy();
	bg_energy->SetLineColor(kRed);
	bg_energy->SetFillColor(kRed);
	bg_energy->Draw("H");
	sig_energy->SetLineColor(kBlue);
	sig_energy->SetFillColor(kBlue);
	sig_energy->Draw("HSAME");
	c_energy->Print("energy.eps");
	TCanvas * c_eta = new TCanvas("eta","eta",600,600);
	c_eta->SetLogy();
	bg_eta->SetLineColor(kRed);
	bg_eta->SetFillColor(kRed);
	bg_eta->Draw("H");
	sig_eta->SetLineColor(kBlue);
	sig_eta->SetFillColor(kBlue);
	sig_eta->Draw("HSAME");
	c_eta->Print("eta.eps");
	TCanvas * c_phi = new TCanvas("phi","phi",600,600);
	c_phi->SetLogy();
	bg_phi->SetLineColor(kRed);
	bg_phi->SetFillColor(kRed);
	bg_phi->Draw("H");
	sig_phi->SetLineColor(kBlue);
	sig_phi->SetFillColor(kBlue);
	sig_phi->Draw("HSAME");
	c_phi->Print("phi.eps");


	
	// exit(0);
	
}
	// TBranch *bg_branchPX = bgTree->GetBranch("px");
	// TBranch *bg_branchPY = bgTree->GetBranch("py");
	// TBranch *bg_branchPZ = bgTree->GetBranch("pz");
	// TBranch *bg_branchE = bgTree->GetBranch("E");
	
	// Double_t px,py,pz,E;
	// bg_branchPX->SetAddress(&px);
	// bg_branchPY->SetAddress(&py);
	// bg_branchPZ->SetAddress(&pz);
	// bg_branchE->SetAddress(&E);
		
	// for (int i = 0; i < bgTree->GetEntries(); ++i) {
	// 	bg_branchPX->GetEntry(i);
	// 	bg_branchPY->GetEntry(i);
	// 	bg_branchPZ->GetEntry(i);
	// 	bg_branchE->GetEntry(i);
	// 	TLorentzVector p = TLorentzVector(px,py,pz,E);
	// 	bg_pT->Fill(p.Pt());
	// 	bg_energy->Fill(p.E());
	// 	bg_eta->Fill(p.Eta());
	// 	bg_phi->Fill(p.Phi());		
	// }


	// TBranch *sig_branchPX = sigTree->GetBranch("px");
	// TBranch *sig_branchPY = sigTree->GetBranch("py");
	// TBranch *sig_branchPZ = sigTree->GetBranch("pz");
	// TBranch *sig_branchE = sigTree->GetBranch("E");
	
	// Double_t px,py,pz,E;
	// sig_branchPX->SetAddress(&px);
	// sig_branchPY->SetAddress(&py);
	// sig_branchPZ->SetAddress(&pz);
	// sig_branchE->SetAddress(&E);
		
	// for (int i = 0; i < sigTree->GetEntries(); ++i) {
	// 	sig_branchPX->GetEntry(i);
	// 	sig_branchPY->GetEntry(i);
	// 	sig_branchPZ->GetEntry(i);
	// 	sig_branchE->GetEntry(i);
	// 	TLorentzVector p = TLorentzVector(px,py,pz,E);
		// sig_pT->Fill(p.Pt());
		// sig_energy->Fill(p.E());
		// sig_eta->Fill(p.Eta());
		// sig_phi->Fill(p.Phi());		
	// }
