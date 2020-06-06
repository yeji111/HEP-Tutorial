#include "MyAnalysis.h"
#include "Plotter.h"
#include <iostream>
#include <TChain.h>
#include <TGraphAsymmErrors.h>
#include <string>

int main() {
   
   float lumi = 50.;
   
   MyAnalysis *A = new MyAnalysis();
   TChain* ch = new TChain("events");
   ch->Add("files/data.root");
   ch->Process(A,"data");
   
   MyAnalysis *B = new MyAnalysis();
   TChain* ch2 = new TChain("events");
   ch2->Add("files/ttbar.root");
   ch2->Process(B,"ttbar");
   
   MyAnalysis *C = new MyAnalysis();
   TChain* ch3 = new TChain("events");
   ch3->Add("files/wjets.root");
   ch3->Process(C,"wjets");
   
   MyAnalysis *D = new MyAnalysis();
   TChain* ch4 = new TChain("events");
   ch4->Add("files/dy.root");
   ch4->Process(D,"dy");
   
   MyAnalysis *E = new MyAnalysis();
   TChain* ch5 = new TChain("events");
   ch5->Add("files/ww.root");
   ch5->Process(E,"ww");

   MyAnalysis *F = new MyAnalysis();
   TChain* ch6 = new TChain("events");
   ch6->Add("files/wz.root");
   ch6->Process(F,"wz");

   MyAnalysis *G = new MyAnalysis();
   TChain* ch7 = new TChain("events");
   ch7->Add("files/zz.root");
   ch7->Process(G,"zz");

   MyAnalysis *H = new MyAnalysis();
   TChain* ch8 = new TChain("events");
   ch8->Add("files/qcd.root");
   ch8->Process(H,"qcd");
   
   MyAnalysis *I = new MyAnalysis();
   TChain* ch9 = new TChain("events");
   ch9->Add("files/single_top.root");
   ch9->Process(I,"single_top");

	Plotter P;
	P.SetData(A->histograms, std::string("Data"));
	P.AddBg(B->histograms, std::string("TTbar"));
	P.AddBg(C->histograms, std::string("Wjets"));
	P.AddBg(D->histograms, std::string("DY"));
	P.AddBg(E->histograms, std::string("WW"));
	P.AddBg(F->histograms, std::string("WZ"));
	P.AddBg(G->histograms, std::string("ZZ"));
	P.AddBg(H->histograms, std::string("QCD"));
	P.AddBg(I->histograms, std::string("single Top"));
   
	P.Plot(string("results.pdf"));
   
	Plotter P_MC;
	P_MC.AddBg(B->histograms_MC, std::string("TTbar"));
	P_MC.AddBg(C->histograms_MC, std::string("Wjets"));
	P_MC.AddBg(D->histograms_MC, std::string("DY"));
	P_MC.AddBg(E->histograms_MC, std::string("WW"));
	P_MC.AddBg(F->histograms_MC, std::string("WZ"));
	P_MC.AddBg(G->histograms_MC, std::string("ZZ"));
	P_MC.AddBg(H->histograms_MC, std::string("QCD"));
	P_MC.AddBg(I->histograms_MC, std::string("single Top"));
	P_MC.Plot(string("results_MC.pdf"));
 

	Plotter P_IM;
       P_IM.SetData(A->histograms_IM, std::string("Data"));
       P_IM.AddBg(B->histograms_IM, std::string("TTbar"));
       P_IM.AddBg(C->histograms_IM, std::string("Wjets"));
       P_IM.AddBg(D->histograms_IM, std::string("DY"));
       P_IM.AddBg(E->histograms_IM, std::string("WW"));
       P_IM.AddBg(F->histograms_IM, std::string("WZ"));
       P_IM.AddBg(G->histograms_IM, std::string("ZZ"));
       P_IM.AddBg(H->histograms_IM, std::string("QCD"));
       P_IM.AddBg(I->histograms_IM, std::string("single Top"));

       P_IM.Plot(string("results_IM.pdf"));

	 Plotter P_ex2;
       P_ex2.SetData(A->hist_exercise2, std::string("Data"));
       P_ex2.AddBg(B->hist_exercise2, std::string("TTbar"));
       P_ex2.AddBg(C->hist_exercise2, std::string("Wjets"));
       P_ex2.AddBg(D->hist_exercise2, std::string("DY"));
       P_ex2.AddBg(E->hist_exercise2, std::string("WW"));
       P_ex2.AddBg(F->hist_exercise2, std::string("WZ"));
       P_ex2.AddBg(G->hist_exercise2, std::string("ZZ"));
       P_ex2.AddBg(H->hist_exercise2, std::string("QCD"));
       P_ex2.AddBg(I->hist_exercise2, std::string("single Top"));

       P_ex2.Plot(string("exercise2.pdf"));

       Plotter P_ex3;
       P_ex3.SetData(A->hist_exercise3, std::string("Data"));
       P_ex3.AddBg(B->hist_exercise3, std::string("TTbar"));
       P_ex3.AddBg(C->hist_exercise3, std::string("Wjets"));
       P_ex3.AddBg(D->hist_exercise3, std::string("DY"));
       P_ex3.AddBg(E->hist_exercise3, std::string("WW"));
       P_ex3.AddBg(F->hist_exercise3, std::string("WZ"));
       P_ex3.AddBg(G->hist_exercise3, std::string("ZZ"));
       P_ex3.AddBg(H->hist_exercise3, std::string("QCD"));
       P_ex3.AddBg(I->hist_exercise3, std::string("single Top"));

       P_ex3.Plot(string("exercise3.pdf"));
       

                Plotter P_ex2_c;
       P_ex2_c.SetData(A->hist_exercise2_c, std::string("Data"));
       P_ex2_c.AddBg(B->hist_exercise2_c, std::string("TTbar"));
       P_ex2_c.AddBg(C->hist_exercise2_c, std::string("Wjets"));
       P_ex2_c.AddBg(D->hist_exercise2_c, std::string("DY"));
       P_ex2_c.AddBg(E->hist_exercise2_c, std::string("WW"));
       P_ex2_c.AddBg(F->hist_exercise2_c, std::string("WZ"));
       P_ex2_c.AddBg(G->hist_exercise2_c, std::string("ZZ"));
       P_ex2_c.AddBg(H->hist_exercise2_c, std::string("QCD"));
       P_ex2_c.AddBg(I->hist_exercise2_c, std::string("single Top"));

       P_ex2_c.Plot(string("exercise2_c.pdf"));

}

