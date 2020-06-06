#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MyAnalysis.C")
// Root > T->Process("MyAnalysis.C","some options")
// Root > T->Process("MyAnalysis.C+")
//

#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TLatex.h>

using namespace std;

void MyAnalysis::BuildEvent() {
   
   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Px[i], Muon_Py[i], Muon_Pz[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }
   
   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Px[i], Electron_Py[i], Electron_Pz[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso[i]);
      electron.SetCharge(Electron_Charge[i]);
      Electrons.push_back(electron);
   }
   
   Photons.clear();
   for (int i = 0; i < NPhoton; ++i) {
      MyPhoton photon(Photon_Px[i], Photon_Py[i], Photon_Pz[i], Photon_E[i]);
      photon.SetIsolation(Photon_Iso[i]);
      Photons.push_back(photon);
   }
   
   Jets.clear();
   for (int i = 0; i < NJet; ++i) {
      MyJet jet(Jet_Px[i], Jet_Py[i], Jet_Pz[i], Jet_E[i]);
      jet.SetBTagDiscriminator(Jet_btag[i]);
      jet.SetJetID(Jet_ID[i]);
      Jets.push_back(jet);
   }
   
   hadB.SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 4.8);
   lepB.SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 4.8);
   hadWq.SetXYZM(MChadronicWDecayQuark_px, MChadronicWDecayQuark_py, MChadronicWDecayQuark_pz, 0.0);
   hadWqb.SetXYZM(MChadronicWDecayQuarkBar_px, MChadronicWDecayQuarkBar_py, MChadronicWDecayQuarkBar_pz, 0.0);
   lepWl.SetXYZM(MClepton_px, MClepton_py, MClepton_pz, 0.0);
   lepWn.SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0.0);
   met.SetXYZM(MET_px, MET_py, 0., 0.);
   
   EventWeight *= weight_factor;
   
}

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
   h_Mmumu = new TH1F("Mmumu", "Invariant di-muon mass", 60, 60, 120);
   h_Mmumu->SetXTitle("m_{#mu#mu}");
   h_Mmumu->Sumw2();
   histograms.push_back(h_Mmumu);
   histograms_MC.push_back(h_Mmumu);
   
   h_NMuon = new TH1F("NMuon", "Number of muons", 7, 0, 7);
   h_NMuon->SetXTitle("No. Muons");
   h_NMuon->Sumw2();
   histograms.push_back(h_NMuon);
   histograms_MC.push_back(h_NMuon);
   
   h_InvarM=new TH1F("h_InvarM","IsoMu_p+IsoMu_m",40,0,200);
   h_InvarM->SetXTitle("Invariant Mass");
   h_InvarM->Sumw2();
   histograms_IM.push_back(h_InvarM);

   h_dRmumu=new TH1F("h_dRmumu","h_dRmumu",40,0,7);
   h_dRmumu->SetXTitle("Delta R");
   h_dRmumu->Sumw2();
   hist_exercise2.push_back(h_dRmumu);

   h_jetmul=new TH1F("h_jetmul","h_jetmul",10,0,10);
   h_jetmul->SetXTitle("jet multiplicity");
   h_jetmul->Sumw2();
   hist_exercise2.push_back(h_jetmul);

   h_pt_jet=new TH1F("h_pt_jet","h_pt_jet",40,0,800);
   h_pt_jet->SetXTitle("transverse momenta of jets");
   h_pt_jet->Sumw2();
   hist_exercise2.push_back(h_pt_jet);   

   h_pt_lepton=new TH1F("h_pt_lepton","h_pt_lepton",40,0,700);
   h_pt_lepton->SetXTitle("transverse momenta of leptons");
   h_pt_lepton->Sumw2();
   hist_exercise2.push_back(h_pt_lepton);

   h_lepton_Iso=new TH1F("h_lepton_Iso","h_lepton_ISo",40,0,30);
   h_lepton_Iso->SetXTitle("lepton isolation");
   h_lepton_Iso->Sumw2();
   hist_exercise2.push_back(h_lepton_Iso);

   h_btag=new TH1F("h_btag","h_btag",40,0,6);
   h_btag->SetXTitle("b-tagging discriminator");
   h_btag->Sumw2();
   hist_exercise2.push_back(h_btag);

   h_missEt=new TH1F("h_missEt","h_missEt",40,0,800);
   h_missEt->SetXTitle("missing transverse energy");
   h_missEt->Sumw2();
   hist_exercise2.push_back(h_missEt);

   h_bjet=new TH1F("h_bjet","h_bjet",10,0,10);
   h_bjet->SetXTitle("number of b-jet");
   h_bjet->Sumw2();
   hist_exercise2.push_back(h_bjet);


   
   //apply cut
   h_dRmumu_c=new TH1F("h_dRmumu","h_dRmumu",40,0,7);
   h_dRmumu_c->SetXTitle("Delta R");
   h_dRmumu_c->Sumw2();
   hist_exercise2_c.push_back(h_dRmumu_c);

   h_jetmul_c=new TH1F("h_jetmul","h_jetmul",10,0,10);
   h_jetmul_c->SetXTitle("jet multiplicity");
   h_jetmul_c->Sumw2();
   hist_exercise2_c.push_back(h_jetmul_c);

   h_pt_jet_c=new TH1F("h_pt_jet","h_pt_jet",40,0,800);
   h_pt_jet_c->SetXTitle("transverse momenta of jets");
   h_pt_jet_c->Sumw2();
   hist_exercise2_c.push_back(h_pt_jet_c);

   h_pt_lepton_c=new TH1F("h_pt_lepton","h_pt_lepton",40,0,700);
   h_pt_lepton_c->SetXTitle("transverse momenta of leptons");
   h_pt_lepton_c->Sumw2();
   hist_exercise2_c.push_back(h_pt_lepton_c);

   h_lepton_Iso_c=new TH1F("h_lepton_Iso","h_lepton_ISo",40,0,30);
   h_lepton_Iso_c->SetXTitle("lepton isolation");
   h_lepton_Iso_c->Sumw2();
   hist_exercise2_c.push_back(h_lepton_Iso_c);

   h_btag_c=new TH1F("h_btag","h_btag",40,0,6);
   h_btag_c->SetXTitle("b-tagging discriminator");
   h_btag_c->Sumw2();
   hist_exercise2_c.push_back(h_btag_c);

   h_bjet_c=new TH1F("h_bjet","h_bjet",10,0,10);
   h_bjet_c->SetXTitle("number of b-jet");
   h_bjet_c->Sumw2();
   hist_exercise2_c.push_back(h_bjet_c);



   //exercise3

   h_muon=new TH1F("h_muon","h_muon",40,0,600);
   h_muon->SetXTitle("muon Pt");
   h_muon->Sumw2();
   hist_exercise3.push_back(h_muon);

   h_trigger=new TH1F("h_trigger","h_trigger",40,0,600);
   h_trigger->SetXTitle("triggermuon_pt");
   h_trigger->Sumw2();
   hist_exercise3.push_back(h_trigger);

   h_acceptance=new TH1F("h_acceptance","h_acceptance",40,0,600);
   h_acceptance->SetXTitle("acceptance_pt");
   h_acceptance->Sumw2();
   hist_exercise3.push_back(h_acceptance);

   h_purity=new TH1F("h_purity","h_purity",40,0,600);
   h_purity->SetXTitle("purity");
   h_purity->Sumw2();
   hist_exercise3.push_back(h_purity);

   h_xsection=new TH1F("h_xsection","h_xsection",40,0,600);
   h_xsection->SetXTitle("cross section");
   h_xsection->Sumw2();
   hist_exercise3.push_back(h_xsection);

}

Bool_t MyAnalysis::Process(Long64_t entry) {
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MyAnalysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   
   ++TotalEvents;
   
   GetEntry(entry);
   
   if (TotalEvents % 10000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
   BuildEvent();
   
   double MuonPtCut = 25.;
   double MuonRelIsoCut = 0.10;
   
   //   cout << "Jets: " << endl;
   //   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //      cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID()
   //      << endl;
   //   }
   //   cout << "Muons: " << endl;
   //   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Electrons: " << endl;
   //   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Photons: " << endl;
   //   for (vector<MyPhoton>::iterator it = Photons.begin(); it != Photons.end(); ++it) {
   //      cout << "pt, eta, phi, iso: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->GetIsolation()
   //      << endl;
   //   }
   
   
   
   int N_IsoMuon = 0;
   MyMuon *muon1, *muon2,*IsoMu_p,*IsoMu_m;
   
   for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {
      if (jt->IsIsolated(MuonRelIsoCut)) {
         ++N_IsoMuon;
         if (N_IsoMuon == 1) muon1 = &(*jt);
         if (N_IsoMuon == 2) muon2 = &(*jt);
      }
   }
  
   h_NMuon->Fill(N_IsoMuon, EventWeight);
  

   //angular_distribution:exercise2 
   if (N_IsoMuon > 1 && triggerIsoMu24) {
      if (muon1->Pt()>MuonPtCut) {

         TLorentzVector mymuon1( muon1->Px(), muon1->Py(), muon1->Pz(), muon1->E());
         TLorentzVector mymuon2( muon2->Px(), muon2->Py(), muon2->Pz(), muon2->E());
         float dR = mymuon1.DeltaR(mymuon2); 
         h_dRmumu->Fill(dR,EventWeight);
         h_Mmumu->Fill((*muon1 + *muon2).M(), EventWeight);
      }

   }
   //apply cut: dR
   if (N_IsoMuon>1 && triggerIsoMu24){
	   if (muon1->Pt()>=35){
		   TLorentzVector mymuon_c1(muon1->Px(),muon1->Py(),muon1->Pz(),muon1->E());
		   TLorentzVector mymuon_c2(muon2->Px(),muon2->Py(),muon2->Pz(),muon2->E());
		   float dR_c=mymuon_c1.DeltaR(mymuon_c2);
		   h_dRmumu_c->Fill(dR_c,EventWeight);
		   }}
 
  //exercise1 
   float  InvarM =-1;
   if (N_IsoMuon>1 && (muon1->GetCharge()*muon2->GetCharge())<0 && triggerIsoMu24){
	   InvarM=(*muon1+*muon2).M();
   }
   h_InvarM->Fill(InvarM,EventWeight);
  

  //jet_multiplicity & transverse momenta of jets & b-tagging
   int N_jet = 0;
   MyJet *jet;

   for (vector<MyJet>::iterator jj = Jets.begin(); jj != Jets.end(); ++jj) {
              ++N_jet;
	      jet = &(*jj);
	      TLorentzVector myjet(jet->Px(), jet->Py(),jet->Pz(),jet->E());
	      double jet_pt=myjet.Pt();
              h_pt_jet->Fill(jet_pt, EventWeight);
              
	      float btag=jet->GetBTagDiscriminator();
	      h_btag->Fill(btag,EventWeight);
   }
  h_jetmul->Fill(N_jet, EventWeight);
  
  //apply cut: jet_multiplicity & transverse momenta of jets & btag
  int N_jet_c=0;
  MyJet *jet_c;
  for (vector<MyJet>::iterator jc=Jets.begin();jc !=Jets.end(); ++jc){
	 ++N_jet_c;
	 jet_c=&(*jc);
         if (N_jet_c>=5){
	 TLorentzVector myjet_c(jet_c->Px(), jet_c->Py(),jet_c->Pz(),jet_c->E());
         double jet_pt_c=myjet_c.Pt();
         h_pt_jet_c->Fill(jet_pt_c, EventWeight);
         float btag_c=jet_c->GetBTagDiscriminator();
         h_btag_c->Fill(btag_c,EventWeight);
         h_jetmul_c->Fill(N_jet_c,EventWeight);}}


  //number of b-jet
   int N_bjet=0;
   MyJet *bjet;

   for (vector<MyJet>::iterator jb=Jets.begin();jb != Jets.end();++jb){
	   bjet=&(*jb);
	   if (jet->GetBTagDiscriminator()>1.74) ++N_bjet;
   }
   h_bjet->Fill(N_bjet, EventWeight);

   //apply cut: number of b-jet
   int N_bjet_c=0;
   MyJet *bjet_c;
   for (vector<MyJet>::iterator jbc=Jets.begin();jbc !=Jets.end(); ++jbc){
		  bjet_c=&(*jbc);
		 if (jet->GetBTagDiscriminator()>1.74) ++N_bjet_c;
		 }
		if (N_bjet_c>=3) h_bjet_c->Fill(N_bjet_c,EventWeight); 


     
   //transverse momenta of leptons & lepton isolation & exercise3
   MyMuon *mymuon, *muon;
   for (vector<MyMuon>::iterator jm=Muons.begin();jm != Muons.end(); ++jm){
	   muon=&(*jm);
	   TLorentzVector mymuon(muon->Px(),muon->Py(),muon->Pz(),muon->E());
	   double muon_pt=mymuon.Pt();
	   h_pt_lepton->Fill(muon_pt,EventWeight);
           
           //apply cut
	   if (muon_pt>=35 && -2.4<mymuon.Eta()<2.4){ double muon_pt_c=muon_pt;
	   h_pt_lepton_c->Fill(muon_pt_c,EventWeight);}


	   float N_Iso_muon=muon->GetIsolation();
	   h_lepton_Iso->Fill(N_Iso_muon,EventWeight);

	   //apply cut
	   if (muon_pt>=35 && -2.4<mymuon.Eta()<2.4){
		   float N_Iso_muon_c=muon->GetIsolation();
		   h_lepton_Iso_c->Fill(N_Iso_muon_c,EventWeight);}
           
           
	   if (mymuon.Pt()>MuonPtCut && muon->IsIsolated(MuonRelIsoCut) && -2.4<mymuon.Eta()<2.4) h_muon->Fill(mymuon.Pt(),EventWeight);
	   if (mymuon.Pt()>MuonPtCut && muon->IsIsolated(MuonRelIsoCut) && -2.4<mymuon.Eta()<2.4 && triggerIsoMu24) h_trigger->Fill(mymuon.Pt(),EventWeight); 
           
           //acceptance
	   if (mymuon.Pt()>35 && muon->IsIsolated(MuonRelIsoCut) && -2.4<mymuon.Eta()<2.4 && triggerIsoMu24) h_acceptance->Fill(mymuon.Pt(),EventWeight);

	  
  }
    
   MyElectron *myelectron, *electron;
   for (vector<MyElectron>::iterator je=Electrons.begin();je !=Electrons.end();++je){
	   electron=&(*je);
	   TLorentzVector myelectron(electron->Px(),electron->Py(),electron->Pz(),electron->E());
	   double electron_pt=myelectron.Pt();
	   h_pt_lepton->Fill(electron_pt,EventWeight);

           //apply cut
	   if (electron_pt>=35 && -2.4<myelectron.Eta()<2.4){ double electron_pt_c=electron_pt;
		   h_pt_lepton_c->Fill(electron_pt_c,EventWeight);}
	   
	   float N_Iso_electron=electron->GetIsolation();
	   h_lepton_Iso->Fill(N_Iso_electron,EventWeight);
           
	   //apply cut
	   if (electron_pt>=35 && -2.4<myelectron.Eta()<2.4){
		   float N_Iso_electron_c=electron->GetIsolation();
		   h_lepton_Iso_c->Fill(N_Iso_electron_c,EventWeight);}
   }
   
   //cuts: pt>=35, # of jet>=5, # of b-jet>=3, eta(dR)<=2.4


   h_trigger->Divide(h_muon); 
   h_acceptance->Divide(h_muon);

   //purity
   h_purity->Multiply(h_acceptance,h_trigger,1,1);

   //cross section

   //missing transverse energy
   double missEt=met.Pt();
   h_missEt->Fill(missEt,EventWeight);


   return kTRUE;
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   TString option = GetOption();

   TFile *f=new TFile(Form("hist_%s.root", option.Data()),"RECREATE");
   h_InvarM->Write();
   h_NMuon->Write();
   h_Mmumu->Write();
   h_dRmumu->Write();
   h_jetmul->Write();
   h_pt_jet->Write();
   h_pt_lepton->Write();
   h_lepton_Iso->Write();
   h_btag->Write();
   h_missEt->Write();
   h_bjet->Write();
   h_dRmumu_c->Write();
   h_jetmul_c->Write();
   h_pt_jet_c->Write();
   h_pt_lepton_c->Write();
   h_lepton_Iso_c->Write();
   h_btag_c->Write();
   h_bjet_c->Write();

   f->Close();
   
}

void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   

}

