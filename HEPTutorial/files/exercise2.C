#include<iostream>
#include<vector>
#include<math.h>
#include<TLorentzVector.h>

void format_h(TH1F* h, int linecolor){
	h->SetLineWidth(3);
	h->SetLineColor(linecolor);
	}


void exercise2(){
	TCanvas *c1=new TCanvas("c1","data",600,400);
	
	auto jetmul=new TH1F("jetmul","Jet Multiplicity",200,-10,10);
	auto pt_jets=new TH1F("pt_jets","Transverse momenta of jets",200,-10,10);
	auto pt_lept=new TH1F("pt_letps","Transverse momenta of leptons",200,-10,10);
	auto lept_iso=new TH1F("lept_iso","Lepton Isolation",200,-10,10);
	auto btag=new TH1F("btag","b-tagging",200,-10,10);
	auto met_hist=new TH1F("met_hist","Missing transverse energy",200,-10,10);
	auto dR=new TH1F("dR","Angular distribution",200,-10,10);

	int a=0;
	for (auto hist : {jetmul,pt_jets,pt_lept,lept_iso,btag,met_hist,dR})
		format_h(hist,1+a++);
	
	TTree *events;

	//# of components
	float njet, jet_c, m, e;
	njet=469384;
	jet_c=126242;
	m=260828;
	e=396;
	
	//jet multiplicity
	TLeaf *l1=events->GetLeaf("NJet");
	for (int i1=0;i1<njet;i1++){
		jetmul->Fill(l1->GetValue(i1));}
	jetmul->Draw();
	c1->Update();

	//transverse momenta of jets
	TLeaf *l2_x=events->GetLeaf("Jet_Px");
	TLeaf *l2_y=events->GetLeaf("Jet_Py");
	for (int i2=0;i2<jet_c;i2++){
	        double px=l2_x->GetValue(i2);
       		double py=l2_y->GetValue(i2);
		double pt=sqrt(pow(px,2.)+pow(py,2.));
		pt_jets->Fill(pt);
	}
	pt_jets->Draw();
	c1->Update();
	
	//transverse momenta of leptons
	TLeaf *l3_mx=events->GetLeaf("Muon_Px");
	TLeaf *l3_my=events->GetLeaf("Muon_Py");
	TLeaf *l3_ex=events->GetLeaf("Electron_Px");
	TLeaf *l3_ey=events->GetLeaf("Electron_Py");
	for (int i3_m=0; i3_m<m;i3_m++){
		double px_m=l3_mx->GetValue(i3_m);
		double py_m=l3_my->GetValue(i3_m);
		double pt_m=sqrt(pow(px_m,2.)+pow(py_m,2.));
		pt_lept->Fill(pt_m);
	}
	for (int i3_e=0; i3_e<e;i3_e++){
		double px_e=l3_ex->GetValue(i3_e);
		double py_e=l3_ey->GetValue(i3_e);
		double pt_e=sqrt(pow(px_e,2.)+pow(py_e,2.));
		pt_lept->Fill(pt_e);
	}
	pt_lept->Draw();
	c1->Update();

	//lepton isolation
	TLeaf *l4_m=events->GetLeaf("Muon_Iso");
	TLeaf *l4_e=events->GetLeaf("Electron_Iso");
	for (int i4_m=0;i4_m<m;i4_m++){
		lept_iso->Fill(l4_m->GetValue(i4_m));
	}
	for (int i4_e=0;i4_e<e;i4_e++){
		lept_iso->Fill(l4_e->GetValue(i4_e));
	}
	lept_iso->Draw();
	c1->Update();

	//b-tagging
	TLeaf *l5=events->GetLeaf("Jet_btag");
	for (int i5=0;i5<jet_c;i5++){
		btag->Fill(l5->GetValue(i5));
	}
	btag->Draw();
	c1->Update();

	//missing transverse energy
	TLeaf *l6_x=events->GetLeaf("MET_px");
	TLeaf *l6_y=events->GetLeaf("MET_py");
	for (int i6=0;i6<njet;i6++){
		double met_x=l6_x->GetValue(i6);
		double met_y=l6_y->GetValue(i6);
		double met=sqrt(pow(met_x,2.)+pow(met_y,2.));
		met_hist->Fill(met);
	}
	met_hist->Draw();
	c1->Update();

	//angular distribution
	TLeaf *l7_mx=events->GetLeaf("Muon_Px");
	TLeaf *l7_my=events->GetLeaf("Muon_Py");
	TLeaf *l7_mz=events->GetLeaf("Muon_Pz");
	TLeaf *l7_me=events->GetLeaf("Muon_E");
	TLeaf *l7_ex=events->GetLeaf("Electron_Px");
	TLeaf *l7_ey=events->GetLeaf("Electron_Py");
	TLeaf *l7_ez=events->GetLeaf("Electron_Pz");
	TLeaf *l7_ee=events->GetLeaf("Electron_E");
	vector<TLorentzVector> Muon;
	for (int i7_m=0;i7_m<m;i7_m++){
	        float mx=l7_mx->GetValue(i7_m);
       		float my=l7_my->GetValue(i7_m);
 		float mz=l7_mz->GetValue(i7_m);
		float me=l7_me->GetValue(i7_m);
		TLorentzVector *tmp=new TLorentzVector(mx,my,mz,me);
		Muon.push_back(tmp);
	}
	int N_Muon=0;
	TLorentzVector *muon1,*muon2;
	for (vector<Muon>::iterator im=Muon.begin();im!=Muon.end();++im){
		++N_Muon;
		if (N_Muon==1) muon1=&(*im);
		if (N_Muon==2) muon2=&(*im);
	
		float dr_m=muon1->DeltaR(muon2);
	}
		dR->Fill(dr_m);
	}

	for (int i7_e=0;i7_e<e;i7_e++){
		float ex=l7_ex->GetValue(i7_e);
		float ey=l7_ey->GetValue(i7_e);
		float ez=l7_ez->GetValue(i7_e);
		float ee=l7_ee->GetValue(i7_e);
		TLorentzVector *Electron=new TLorentzVector(ex,ey,ez,ee);
		
	}
	int N_Electron=0;
	TLorentzVector *electron1,*electron2;
	for (vector<Electron>::iterator ie=Electron.begin();ie!=Electron.end();++ie){
		++N_Electron;
		if (N_Electron==1) electron1==&(*ie);
		if (N_Electron==2) electron2==&(*ie);
		float dr_e=electron1->DeltaR(electron2);
	
		dR->Fill(dr_e);
	}
	dR->Draw();
	c1->Update();

	c1->SaveAs("exercise2_data.pdf");
	c1->Close();
	c1->Print();
}	

