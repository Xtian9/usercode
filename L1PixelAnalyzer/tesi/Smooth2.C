void Smooth (TString sel, double frac_true_err ) {

  // -C8 : maximum quality factor 1.1314+-0.00503415 at LR > 0.4
  // -M8 : maximum quality factor 1.03056+-0.00499927 at LR > 1.4
  // -C6 : maximum quality factor 1.18157+-0.00673922 at LR > 0.8
  // -M6 : maximum quality factor 1.01414+-0.00240137 at LR > 1.2
  // MEt : maximum quality factor 1.00301+-0.00088719 at LR > 0.8
  // -MEtSig : maximum quality factor 1.01873+-0.00367832 at LR > 1.4
  // -CorrSumEt : maximum quality factor 1.02956+-0.00487776 at LR > 1.4
  // GoodHt : maximum quality factor 1.05092+-0.00244139 at LR > 0.4
  // M45bestall : maximum quality factor 1.03104+-0.00370672 at LR > 1
  // -Chi2mass : maximum quality factor 1.13193+-0.00467282 at LR > 0.4
  // Chi2extall : maximum quality factor 1.07473+-0.00716133 at LR > 1.4
  // Mbbnoh : maximum quality factor 2.17059+-0.0321631 at LR > 0.8
  // DPbbnoh : maximum quality factor 1.30261+-0.0105512 at LR > 0.8
  // SumHED4 : maximum quality factor 1.08131+-0.00809236 at LR > 1.4
  // SumHED6 : maximum quality factor 1.09023+-0.0160105 at LR > 1.8
  // DP12 : maximum quality factor 2.29376+-0.0270215 at LR > 0.4
  // MEtDPM : maximum quality factor 1+-0.1 at LR > 0
  // -MEtDP1 : maximum quality factor 1.06697+-0.00357291 at LR > 0.4
  // MEtDP2 : maximum quality factor 1+-0.1 at LR > 0
  // -M45best : maximum quality factor 1.02626+-0.00341181 at LR > 1.2
  // -M_others : maximum quality factor 1.11418+-0.00859052 at LR > 1.4
  // -Et6 : maximum quality factor 1.02596+-0.00268856 at LR > 1
  
  const int nbins = 50;
  
  const int nvars=25;
  TString var[nvars] = { "C8", "M8", "C6", "M6", "MEt", "MEtSig", "CorrSumEt", "GoodHt", 
			 "Hbestcomb", "Chi2mass", "Mbbnoh", "DPbbnoh", 
			 "SumHED4", "SumHED6", "MEtDPM", "MEtDP1", "MEtDP2",
			 "M_others", "Et6", "Scprod", "Thdeta", "M5", "M3best", "Mwbest", 
			 "TTMS1" }

  TString pippo[nvars];
  TString pippotot[nvars];
  TString pippotth[nvars];
  TString pippototS[nvars];
  TString pippotthS[nvars];
  for ( int i=0; i<nvars; i++ ) { 
    pippo[i] = var[i]+sel; 
    pippotot[i]=var[i]+sel+"_bgr";
    pippotth[i]=var[i]+sel+"_sig";
    pippototS[i]=var[i]+sel+"_bgrS";
    pippotthS[i]=var[i]+sel+"_sigS";
  }
  
  const int nqcdsamples=8;
  TFile * QCD[nqcdsamples];     
  QCD[0] = new TFile("./root/TDAna_QCD30-50_tk3.root");
  QCD[1] = new TFile("./root/TDAna_QCD50-80_tk3.root");
  QCD[2] = new TFile("./root/TDAna_QCD80-120_tk3.root");
  QCD[3] = new TFile("./root/TDAna_QCD120-170_tk3.root");
  QCD[4] = new TFile("./root/TDAna_QCD170-230_tk3.root");
  QCD[5] = new TFile("./root/TDAna_QCD230-300_tk3.root");
  QCD[6] = new TFile("./root/TDAna_QCD300-380_tk3.root");
  QCD[7] = new TFile("./root/TDAna_QCD380incl_tk3.root");
  double QCDxs[nqcdsamples] = { 155929000., 20938850., 2949713., 499656., 100995.,  23855., 6391., 2821.};
  double NQCD[nqcdsamples] = { 86000., 78000., 104000., 96000., 100000., 102000., 112000., 102000.};


  const int nwsamples=11;
  TFile * W[nwsamples];
  W[0] = new TFile ("./root/TDAna_W0w_tk3.root");
  W[1] = new TFile ("./root/TDAna_W10w_tk3.root");
  W[2] = new TFile ("./root/TDAna_W11w_tk3.root");
  W[3] = new TFile ("./root/TDAna_W20w_tk3.root");
  W[4] = new TFile ("./root/TDAna_W21w_tk3.root");
  W[5] = new TFile ("./root/TDAna_W30w_tk3.root");
  W[6] = new TFile ("./root/TDAna_W31w_tk3.root");
  W[7] = new TFile ("./root/TDAna_W40w_tk3.root");
  W[8] = new TFile ("./root/TDAna_W41w_tk3.root");
  W[9] = new TFile ("./root/TDAna_W50w_tk3.root");
  W[10] = new TFile ("./root/TDAna_W51w_tk3.root");
  double Wxs[nwsamples] = { 45000., 9200., 250., 2500., 225., 590., 100., 125., 40., 85., 40. };
  double NW[nwsamples] = { 88000., 40000., 100530., 99523., 105255., 79000., 
			   88258., 83038., 30796., 59022., 41865. };

  TFile * TTH = new TFile("./root/TDAna_ttH_120_tk3.root");
  double TTHxs = 0.667 ;
  double NTTH = 1000000.; // 62000.; // 1652000.; // 62000.;

  const int nttsamples=5;
  TFile * TT[nttsamples];
  TT[0] = new TFile("./root/TDAna_TT0_tk3.root");
  TT[1] = new TFile("./root/TDAna_TT1_tk3.root");
  TT[2] = new TFile("./root/TDAna_TT2_tk3.root");
  TT[3] = new TFile("./root/TDAna_TT3_tk3.root");
  TT[4] = new TFile("./root/TDAna_TT4_tk3.root");
  // double TTxs[5] = { 619., 176., 34.,  6., 1.5 };  // from web
  double TTxs[nttsamples] = { 434., 162., 43., 10., 1.9 };     // from note
  double NTT[nttsamples] = { 57900., 66000., 98159., 14768., 5304. };

  double Lumfactor = 100000; // 100/fb of luminosity assumed in histograms

  TH1D * Histo_TOT[nvars];
  TH1D * Histo_TTH[nvars];
  TH1D * Histo_TOTS[nvars];
  TH1D * Histo_TTHS[nvars];
  for ( int i=0; i<nvars; i++ ) {
    cout << i << endl;
    TH1D * H = dynamic_cast<TH1D*>(TTH->Get(pippo[i]));
    double minx=H->GetBinLowEdge(1);
    double maxx=nbins*H->GetBinWidth(1);
    Histo_TOT[i] = new TH1D ( pippotot[i],pippotot[i], nbins, minx, maxx );
    Histo_TTH[i] = new TH1D ( pippotth[i],pippotth[i], nbins, minx, maxx );
    Histo_TOTS[i] = new TH1D ( pippototS[i],pippototS[i], nbins, minx, maxx );
    Histo_TTHS[i] = new TH1D ( pippotthS[i],pippotthS[i], nbins, minx, maxx );
  }

  cout << "Starting loop on variables needing smoothing" << endl;

  // Loop on variables 
  // -----------------
  for ( int ivar=0; ivar<nvars; ivar++ ) {

    // Extract sum histograms with the right normalization and errors
    // --------------------------------------------------------------
    double totWW[nwsamples][nbins]={0.};
    double totW[nbins]={0.};
    double s2_totW[nbins]={0.};
    double totNW[nwsamples][nbins]={0.};
    for ( int i=0; i<nwsamples; i++ ) {
      //cout << "Processing W file #" << i << " ..." << endl;
      TH1D * Histo = dynamic_cast<TH1D*>(W[i]->Get(pippo[ivar]));
      TH1D * HistoW = dynamic_cast<TH1D*>(W[i]->Get(pippo[ivar]+"W"));
      // For W, we need also total entries in histograms to add a
      // Poisson fluke contribution to total errors from matrix:
      // ----------------------------------------------------------
      TH1D * HistoN = dynamic_cast<TH1D*>(W[i]->Get(pippo[ivar]+"N"));    
      for ( int ibin=1; ibin<=nbins; ibin++ ) {
	double t=Histo->GetBinContent(ibin);
	double s2t=HistoW->GetBinContent(ibin);
	double n=HistoN->GetBinContent(ibin);
	totWW[i][ibin-1]+=t*Wxs[i]/NW[i]*Lumfactor;
	s2_totW[ibin-1]+=s2t*pow(Wxs[i]/NW[i]*Lumfactor,2);
	totNW[i][ibin-1]+=n;
      }
    }
    // Once grandtotals of weights are computed for each bin, we can
    // add to the total s2 the Poisson contribution 1/sqrt(N) * T
    // -------------------------------------------------------------
    for ( int i=0; i<nwsamples; i++ ) {
      for ( int ibin=1; ibin<=nbins; ibin++ ) {
	totW[ibin-1]+=totWW[i][ibin-1];
	if ( totNW[i][ibin-1]>0 ) {
	  s2_totW[ibin-1]+=pow(totWW[i][ibin-1],2)/totNW[i][ibin-1];
	}
      }
    }
    
    double totWQCD[nqcdsamples][nbins]={0.};
    double totQCD[nbins]={0.};
    double s2_totQCD[nbins]={0.};
    double totNQCD[nqcdsamples][nbins]={0.};
    for ( int i=0; i<nqcdsamples; i++ ) {
      //cout << "Processing QCD file #" << i << " ..." << endl;
      TH1D * Histo = dynamic_cast<TH1D*>(QCD[i]->Get(pippo[ivar]));
      TH1D * HistoW = dynamic_cast<TH1D*>(QCD[i]->Get(pippo[ivar]+"W"));
      // For QCD, we need also total entries in histograms to add a
      // Poisson fluke contribution to total errors from matrix:
      // ----------------------------------------------------------
      TH1D * HistoN = dynamic_cast<TH1D*>(QCD[i]->Get(pippo[ivar]+"N"));    
      for ( int ibin=1; ibin<=nbins; ibin++ ) {
	double t=Histo->GetBinContent(ibin);
	double s2t=HistoW->GetBinContent(ibin);
	double n=HistoN->GetBinContent(ibin);
	totWQCD[i][ibin-1]+=t*QCDxs[i]/NQCD[i]*Lumfactor;
	s2_totQCD[ibin-1]+=s2t*pow(QCDxs[i]/NQCD[i]*Lumfactor,2);
	totNQCD[i][ibin-1]+=n;
      }
    }
    // Once grandtotals of weights are computed for each bin, we can
    // add to the total s2 the Poisson contribution 1/sqrt(N) * T
    // -------------------------------------------------------------
    for ( int i=0; i<nqcdsamples; i++ ) {
      for ( int ibin=1; ibin<=nbins; ibin++ ) {
	totQCD[ibin-1]+=totWQCD[i][ibin-1];
	if ( totNQCD[i][ibin-1]>0 ) {
	  s2_totQCD[ibin-1]+=pow(totWQCD[i][ibin-1],2)/totNQCD[i][ibin-1];
	}
      }
    }
    
    double totTT[nbins]={0.};
    double s2_totTT[nbins]={0.};
    for ( int i=0; i<nttsamples; i++ ) {
      //cout << "Processing TT file #" << i << " ..." << endl;
      TH1D * Histo = dynamic_cast<TH1D*>(TT[i]->Get(pippo[ivar]));
      for ( int ibin=1; ibin<=nbins; ibin++ ) {
	double t=Histo->GetBinContent(ibin);
	totTT[ibin-1]+=t*TTxs[i]/NTT[i]*Lumfactor;
	s2_totTT[ibin-1]+=t*pow(TTxs[i]/NTT[i]*Lumfactor,2);
      }
    }
    double totTTH[nbins]={0.};
    double s2_totTTH[nbins]={0.};
    //cout << "Processing TTH file " << " ..." << endl;
    TH1D * Histo = dynamic_cast<TH1D*>(TTH->Get(pippo[ivar]));
    for ( int ibin=1; ibin<=nbins; ibin++ ) {
      double t=Histo->GetBinContent(ibin);
      totTTH[ibin-1]+=t*TTHxs/NTTH*Lumfactor;
      s2_totTTH[ibin-1]+=t*pow(TTHxs/NTTH*Lumfactor,2);
    }
    
    // OK now fill total histograms
    // ----------------------------
    double total_sig=0.;
    double total_bgr=0.;
    double grandtot[nbins]={0.};
    double grandtote[nbins]={0.};
    for ( int ibin=1; ibin<=nbins; ibin++ ) {
      Histo_TTH[ivar]->SetBinContent(ibin,totTTH[ibin-1]);
      Histo_TTH[ivar]->SetBinError(ibin,sqrt(s2_totTTH[ibin-1]));
      Histo_TTHS[ivar]->SetBinContent(ibin,totTTH[ibin-1]);
      Histo_TTHS[ivar]->SetBinError(ibin,sqrt(s2_totTTH[ibin-1]));
      grandtot[ibin-1] = totQCD[ibin-1]+totTT[ibin-1]+totW[ibin-1];
      grandtote[ibin-1]= sqrt(s2_totQCD[ibin-1]+s2_totTT[ibin-1]+s2_totW[ibin-1]);
      Histo_TOT[ivar]->SetBinContent(ibin,grandtot[ibin-1]);
      Histo_TOT[ivar]->SetBinError(ibin,grandtote[ibin-1]);
      Histo_TOTS[ivar]->SetBinContent(ibin,grandtot[ibin-1]);
      Histo_TOTS[ivar]->SetBinError(ibin,grandtote[ibin-1]);
      total_sig+=totTTH[ibin-1];
      total_bgr+=grandtot[ibin-1];
    }

    // Preliminary: we set to zero bins with less than 0.01% of the integral
    // ---------------------------------------------------------------------
    for ( int ibin=0; ibin<nbins; ibin++ ) {
      if ( grandtot[ibin]/total_bgr<0.0001 ) grandtot[ibin]=0.;
    }
    // Pre-pre-smoothing: kill bins with abnormally large errors, 
    // replace with average of neighbors
    // ----------------------------------------------------------
    double averror=0.;
    double nav=0.;
    for ( int ibin=0; ibin<nbins; ibin++ ) {
      if ( grandtot[ibin]>0 && grandtote[ibin]>0 ) {
	averror+=grandtote[ibin]/grandtot[ibin];
	nav++;
      }
    }
    if ( nav>0 ) {
      averror=averror/nav;
      double err;
      double nlterr[100]={0.};
      double max67pc;
      int i67=-1;
      for ( int i=0; i<100 && i67==-1; i++ ) {
	err=2*averror/100.*(double)i;
	for ( int ibin=0; ibin<nbins; ibin++ ) {
	  if ( grandtot[ibin]>0 && grandtote[ibin]>0 ) {
	    if ( grandtote[ibin]/grandtot[ibin]<err ) nlterr[i]++;
	  }
	}
	nlterr[i]=nlterr[i]/nav;
	if ( nlterr[i]>frac_true_err ) {
	  max67pc=err;
	  i67=i;
	}
      }
      cout << "var#" << ivar<< " averror=" << averror << " nav=" <<nav << " max67pc=" << max67pc << endl; 

      // Ok now we know which bins to disregard. Let us correct them:
      // ------------------------------------------------------------
      int inext;
      int iprev;
      for ( int ibin=0; ibin<nbins; ibin++ ) {
	if ( grandtot[ibin]>0. && grandtote[ibin]>0. ) {
	  if ( grandtote[ibin]/grandtot[ibin]>2*max67pc ) { // consider this bin for smoothing
	    if ( ibin==0 ) {
	      inext=0;
	      // look at the three next ones
	      // ---------------------------
	      for ( int jbin=ibin+1; jbin<ibin+4 && inext==0; jbin++ ) {
		if ( grandtot[jbin]>0. && grandtote[jbin]>0. ) {
		  if ( grandtote[jbin]/grandtot[jbin]<2*max67pc ) inext=jbin;
		}
	      }
	      if ( inext==0 ) inext=1;
	      iprev=inext;	 
	    } else if ( ibin<nbins-1 && ibin>0 ) {
	      iprev=ibin-1;
	      inext=0;
	      // look at the three next ones
	      // ---------------------------
	      for ( int jbin=ibin+1; jbin<ibin+4 && jbin<nbins && inext==0; jbin++ ) {
		if ( grandtot[jbin]>0. && grandtote[jbin]>0. ) {
		  if ( grandtote[jbin]/grandtot[jbin]<2*max67pc ) inext=jbin;
		}
	      }
	      if ( inext==0 ) inext=iprev;
	    } else if ( ibin==nbins-1 ) {
	      iprev=ibin-1;
	      inext=ibin-1;
	    } 
	    // Compute new value of bin, taking into account the prescription that
	    // when averaging, an average of x and zero is given value zero.
	    // Also, do not replace bins which are consistent with their neighbors 
	    // within the errors in the average of the latter
	    // ------------------------------------------------------------------
	    if ( grandtot[iprev]>0. && grandtot[inext]>0. ) {
	      double av = (grandtot[iprev]+grandtot[inext])/2;
	      double s_av = sqrt((pow(grandtote[iprev],2)+pow(grandtote[inext],2))/4.);
	      if ( fabs(grandtot[ibin]-av)>s_av ) {
		grandtot[ibin]=av;
		grandtote[ibin]=s_av;
	      }
	    } else {
	      grandtot[ibin]=0.;
	    grandtote[ibin]=sqrt((pow(grandtote[iprev],2)+pow(grandtote[inext],2))/4.);
	    }
	  }
	} 
      }
    }
    double total_bgr_s=0.;
    for ( int ibin=1; ibin<=nbins; ibin++ ) {
      total_bgr_s+=grandtot[ibin-1];
      Histo_TOTS[ivar]->SetBinContent(ibin,grandtot[ibin-1]);
      Histo_TOTS[ivar]->SetBinError(ibin,grandtote[ibin-1]);
    } 
    
    // Now do the regular smoothing
    // ----------------------------
    //Histo_TOTS[ivar]->Smooth(1);
    //Histo_TTHS[ivar]->Smooth(1);
    double sumtot=0.;
    double sumtth=0.;
    double sumtotS=0.;
    double sumtthS=0.;
    for ( int ibin=1; ibin<=nbins; ibin++ ) {
      sumtotS+=Histo_TOTS[ivar]->GetBinContent(ibin);
      sumtthS+=Histo_TTHS[ivar]->GetBinContent(ibin);
      sumtot+=Histo_TOT[ivar]->GetBinContent(ibin);
      sumtth+=Histo_TTH[ivar]->GetBinContent(ibin);
    }
    if ( sumtotS>0 ) Histo_TOTS[ivar]->Scale(1./sumtotS);
    if ( sumtthS>0 ) Histo_TTHS[ivar]->Scale(1./sumtthS);
    if ( sumtot>0 ) Histo_TOT[ivar]->Scale(1./sumtot);
    if ( sumtth>0 ) Histo_TTH[ivar]->Scale(1./sumtth);

} // end of ivar loop

cout << "Done, now plotting and writing histos." << endl;

// File where smoothed histos are stored
// -------------------------------------
TString fname;
  fname="functionfile" + sel + ".root";
  TFile * Smoothed = new TFile(fname,"RECREATE");
  Smoothed->cd();

  TCanvas * b1 = new TCanvas ("b1", "Kinematics comparison", 600, 600 );
  b1->Divide(2,4);
  for ( int ivar=0; ivar<8; ivar++ ) {
    b1->cd(ivar+1);
    Histo_TOTS[ivar]->SetMinimum(0.);
    Histo_TOTS[ivar]->Draw();
    Histo_TTHS[ivar]->SetLineColor(kBlue);
    Histo_TTHS[ivar]->Draw("PESAME");
  }
  b1->Print("./ps/Smooth_svsb_1.ps");
  TCanvas * b2 = new TCanvas ("b2", "Kinematics comparison", 600, 600 );
  b2->Divide(2,4);
  for ( int ivar=8; ivar<16; ivar++ ) {
    b2->cd(ivar-7);
    Histo_TOTS[ivar]->SetMinimum(0.);
    Histo_TOTS[ivar]->Draw();
    Histo_TTHS[ivar]->SetLineColor(kBlue);
    Histo_TTHS[ivar]->Draw("PESAME");
  }
  b2->Print("./ps/Smooth_svsb_2.ps");
  TCanvas * b3 = new TCanvas ("b3", "Kinematics comparison", 600, 600 );
  b3->Divide(2,4);
  for ( int ivar=16; ivar<nvars; ivar++ ) {
    b3->cd(ivar-15);
    Histo_TOTS[ivar]->SetMinimum(0.);
    Histo_TOTS[ivar]->Draw();
    Histo_TTHS[ivar]->SetLineColor(kBlue);
    Histo_TTHS[ivar]->Draw("PESAME");
  }
  b3->Print("./ps/Smooth_svsb_3.ps");

  TCanvas * c1 = new TCanvas ("c1", "Kinematics comparison", 600, 600 );
  c1->Divide(2,4);
  for ( int ivar=0; ivar<8; ivar++ ) {
    c1->cd(ivar+1);
    Histo_TOT[ivar]->SetMinimum(0.);
    Histo_TOT[ivar]->SetLineColor(kRed);
    Histo_TOT[ivar]->Draw("PE");    
    Histo_TOTS[ivar]->Draw("PESAME");
    Histo_TOT[ivar]->Write();
    Histo_TTH[ivar]->Write();
    Histo_TOTS[ivar]->Write();
    Histo_TTHS[ivar]->Write();
  }
  c1->Print("./ps/Smooth_check_1.ps");
  TCanvas * c2 = new TCanvas ("c2", "Kinematics comparison", 600, 600 );
  c2->Divide(2,4);
  for ( int ivar=8; ivar<16; ivar++ ) {
    c2->cd(ivar-7);
    Histo_TOT[ivar]->SetMinimum(0.);
    Histo_TOT[ivar]->SetLineColor(kRed);
    Histo_TOT[ivar]->Draw("PE");    
    Histo_TOTS[ivar]->Draw("PESAME");
    Histo_TOT[ivar]->Write();
    Histo_TTH[ivar]->Write();
    Histo_TOTS[ivar]->Write();
    Histo_TTHS[ivar]->Write();
  }
  c2->Print("./ps/Smooth_check_2.ps");
  TCanvas * c3 = new TCanvas ("c3", "Kinematics comparison", 600, 600 );
  c3->Divide(2,4);
  for ( int ivar=16; ivar<nvars; ivar++ ) {
    c3->cd(ivar-15);
    Histo_TOT[ivar]->SetMinimum(0.);
    Histo_TOT[ivar]->SetLineColor(kRed);
    Histo_TOT[ivar]->Draw("PE");    
    Histo_TOTS[ivar]->Draw("PESAME");
    Histo_TOT[ivar]->Write();
    Histo_TTH[ivar]->Write();
    Histo_TOTS[ivar]->Write();
    Histo_TTHS[ivar]->Write();
  }
  c3->Print("./ps/Smooth_check_3.ps");

  Smoothed->Close();

}
