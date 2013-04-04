#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TROOT.h"
#include "THStack.h"
#include "TPaveText.h"
#include "TLegend.h"
#include "TMarker.h"
#include <iostream>
#include "Common/setTDRStyle_modified.C"

const double nsig_barrel  = 60.;
const double nbkg_barrel  = 28884.;
const double nsig_endcap  = 35.;
const double nbkg_endcap  = 35392.;

void significance(TString method="BDT",TString region="barrel") {
  
  double nsig, nbkg;
  if(region=="barrel") {
    nsig = nsig_barrel;
    nbkg = nbkg_barrel;
  } else if (region=="endcaps") {
    nsig = nsig_endcap;
    nbkg = nbkg_endcap;
  } else  {cout<<"wrong input"<<endl; exit(-1);}

  cout << "processing " << method << " for " << region << endl;

  TString name = method + "_" + region;

  TString fnameA = "TMVA_" + region + ".root";
  TFile* inputA = TFile::Open(fnameA);

  gDirectory->Cd(fnameA+":/Method_"+method+"/"+method);
  gDirectory->pwd();
  TH1F* tmva_s = (TH1F*)gROOT->FindObject(TString("MVA_"+method+"_S_high"));
  TH1F* tmva_b = (TH1F*)gROOT->FindObject(TString("MVA_"+method+"_B_high"));

  const int rb =100;
  tmva_s->Rebin(rb);
  tmva_b->Rebin(rb);

  int nbins   = tmva_s -> GetNbinsX();
  double xmin = tmva_s -> GetBinLowEdge(1);
  double xmax = tmva_s -> GetBinLowEdge(nbins+1);

  double normS = tmva_s -> Integral(1,nbins);
  double normB = tmva_b -> Integral(1,nbins);
  tmva_s->Scale(nsig/normS);
  tmva_b->Scale(nbkg/normB);
  normS = tmva_s -> Integral(1,nbins);
  normB = tmva_b -> Integral(1,nbins);

  double sumS(0), sumB(0), signi(0); 

  printf("check bins: %d  %f %f %f %f \n", nbins, xmin, xmax, sumS, normS);

  TH1F* effS = new TH1F("effS","effS",nbins,xmin,xmax);
  TH1F* effB = new TH1F("effB","effB",nbins,xmin,xmax);
  TH1F* rejB = new TH1F("rejB","rejB",nbins,xmin,xmax);
  TH1F* sign = new TH1F("sign","sign",nbins,xmin,xmax);

  TH2F* roc  = new TH2F("roc","roc",nbins,0,1.02,nbins,0,1.02);

  for(int i=0; i<nbins+1; i++) {

    sumS  = tmva_s -> Integral(i,nbins);
    sumB  = tmva_b -> Integral(i,nbins);

    rejB->SetBinContent(i, 1.-sumB);
    effS->SetBinContent(i, normS?sumS/normS:0);
    effB->SetBinContent(i, normB?sumB/normB:0);
    rejB->SetBinContent(i, normB?1.-sumB/normB:1);

    roc->Fill(normS?sumS/normS:0,normB?1.-sumB/normB:1);

    signi = sumS/sqrt(sumS + sumB);
    sign->SetBinContent(i, signi);

  }

  int sig_max_bin = sign->GetMaximumBin(); 
  double sig_max_mva = effS->GetBinCenter(sig_max_bin);
  double sig_max = sign->GetBinContent(sig_max_bin);
  double sig_max_effS = effS->GetBinContent(sig_max_bin);
  double sig_max_effB = effB->GetBinContent(sig_max_bin);
  //printf("maximum significance: %f bin:%d mva:%f %f %f \n", sig_max, sig_max_bin, sig_max_mva, sig_max_effS, sig_max_effB);
 char ss[100];
 sprintf(ss, "%s,  max. significance: %3.1f, %s>%5.4f, #epsilon_{S}=%4.3f, #epsilon_{B}=%5.4f",region.Data(),sig_max,method.Data(), sig_max_mva, sig_max_effS, sig_max_effB);



  //setTDRStyle(false);
  gStyle->SetOptStat(kFALSE);
  gStyle->SetFillColor(0);

  TCanvas c;
  c.SetGrid();
  effS->SetTitle("");
  effS->GetYaxis()->SetTitle("#epsilon_{S}   |   1-#epsilon_{B}  ");
  effS->GetXaxis()->SetTitle(method+ " >     ");
  effS->SetLineColor(kBlue);
  effS->Draw("c");
  rejB->SetLineColor(kRed);
  rejB->Draw("same c");
  c.Update();  

  Float_t rightmax = 1.02*sign->GetMaximum();
  Float_t scale = gPad->GetUymax()/rightmax;
  sign->SetLineColor(8);
  sign->Scale(scale);
  sign->SetLineWidth(3);

  sign->Draw("same c");


  //draw an axis on the right side
  TGaxis *axis = new TGaxis(gPad->GetUxmax(),gPad->GetUymin(),
  	  gPad->GetUxmax(), gPad->GetUymax(),0,rightmax,510,"+L");
   axis->SetLineColor (8);
   axis->SetLabelColor(8);
   axis->SetTextColor (8);
   axis->SetTitle("Significance");
   axis->Draw();

   TPaveText *tp = new TPaveText(0.2,0.9,0.9,0.95,"brNDC");
   tp->SetBorderSize(0);
   tp->AddText(ss);
   tp->Draw("same");
   
   TLine* tl = new TLine(sig_max_mva,0,sig_max_mva, gPad->GetUymax());
   tl->SetLineStyle(4);
   tl->Draw("same");

   c.SaveAs(TString("plots/"+name+"_eff.gif"));

   TCanvas c2;
   roc->SetTitle("");
   roc->GetXaxis()->SetTitle("#epsilon_{S}");
   roc->GetYaxis()->SetTitle("1-#epsilon_{B}");
   roc->SetMarkerStyle(7);
   roc->Draw();
   tp->Draw();
   TMarker* tm = new TMarker(sig_max_effS,1.-sig_max_effB, 28);
   tm->SetMarkerSize(1.5);
   tm->Draw("same");

   c2.SaveAs(TString("plots/"+name+"_roc.gif"));

   inputA->Close();
}