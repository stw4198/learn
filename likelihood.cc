#include "lance.h"

void likehood(const char* infile, const char* component/*, int nbins*/){

  TFile *f = new TFile(infile);
  if(!f->IsOpen()){
    printf("File %s does not exist.\n",infile);
    return;
  }
  TTree *t = (TTree*)f->Get("data");
  TTree *run = (TTree*)f->Get("runSummary");
  
  int nfiles = run->GetEntries();
  printf("%i files merged together\n",nfiles);
  
  int nevents = 0;
  int events;
  for(int i=0;i<nfiles;i++){
    run->GetEntry(i);
    events = run->GetLeaf("nEvents")->GetValue(0);
    nevents += events;
  }
  
  printf("There are %i MC events\n",nevents);
  
  int nentries = t->GetEntries();
  printf("There are %i entries in %s\n",nentries,infile);

  TFile *out=new TFile(Form("%s_likelihoods.root",component),"RECREATE");

  int nbins = sqrt(nentries);

  TH1D* signal_like = new TH1D("signal_like","signal_like",nbins,0,0);
  TH1D* background_like = new TH1D("background_like","background_like",nbins,0,0);
  TH1D* ratio_like = new TH1D("ratio_like","ratio_like",nbins,0,0);

  //signal pdfs
  TFile* signal = new TFile("signal_pdfs.root");
  if(!signal->IsOpen()){
    printf("File signal_pdfs.root does not exist.\n");
    return;
  }
  TH1D* n100_signal = (TH1D*)signal->Get("n100");
  TH1D* n100_prev_signal = (TH1D*)signal->Get("n100_prev");
  TH1D* dt_prev_us_signal = (TH1D*)signal->Get("dt_prev_us");
  TH1D* drPrevr_signal = (TH1D*)signal->Get("drPrevr");
  TH1D* closestPMT_signal = (TH1D*)signal->Get("closestPMT");
  //background pdfs
  TFile * background = new TFile("background_pdfs.root");
  if(!background->IsOpen()){
    printf("File background_pdfs.root does not exist.\n");
    return;
  }
  TH1D* n100_background = (TH1D*)background->Get("n100");
  TH1D* n100_prev_background = (TH1D*)background->Get("n100_prev");
  TH1D* dt_prev_us_background = (TH1D*)background->Get("dt_prev_us");
  TH1D* drPrevr_background = (TH1D*)background->Get("drPrevr");
  TH1D* closestPMT_background = (TH1D*)background->Get("closestPMT");
  
  for(int i=0; i<nentries; i++){
    t->GetEntry(i);
    if (i%100000==0){
      printf("Creating likelihoods: Event %d of %d\n",i,nentries);
    }
    if ( t->GetLeaf("n100")->GetValue(0) > 0 and t->GetLeaf("closestPMT")->GetValue(0) > 0 and t->GetLeaf("dt_prev_us")->GetValue(0) > 0 and t->GetLeaf("dt_prev_us")->GetValue(0) < 2000) {
      double n100_sig_bin = n100_signal->GetXaxis()->FindBin(t->GetLeaf("n100")->GetValue(0));
      double n100_sig_prob = n100_signal->GetBinContent(n100_sig_bin);
      double n100_bg_bin = n100_background->GetXaxis()->FindBin(t->GetLeaf("n100")->GetValue(0));
      double n100_bg_prob = n100_background->GetBinContent(n100_bg_bin);
      double n100_prev_sig_bin = n100_prev_signal->GetXaxis()->FindBin(t->GetLeaf("n100_prev")->GetValue(0));
      double n100_prev_sig_prob = n100_prev_signal->GetBinContent(n100_prev_sig_bin);
      double n100_prev_bg_bin = n100_prev_background->GetXaxis()->FindBin(t->GetLeaf("n100_prev")->GetValue(0));
      double n100_prev_bg_prob = n100_prev_background->GetBinContent(n100_prev_bg_bin);
      double dt_prev_us_sig_bin = dt_prev_us_signal->GetXaxis()->FindBin(t->GetLeaf("dt_prev_us")->GetValue(0));
      double dt_prev_us_sig_prob = dt_prev_us_signal->GetBinContent(dt_prev_us_sig_bin);
      double dt_prev_us_bg_bin = dt_prev_us_background->GetXaxis()->FindBin(t->GetLeaf("dt_prev_us")->GetValue(0));
      double dt_prev_us_bg_prob = dt_prev_us_background->GetBinContent(dt_prev_us_bg_bin);
      double drPrevr_sig_bin = drPrevr_signal->GetXaxis()->FindBin(t->GetLeaf("drPrevr")->GetValue(0));
      double drPrevr_sig_prob = drPrevr_signal->GetBinContent(drPrevr_sig_bin);
      double drPrevr_bg_bin = drPrevr_background->GetXaxis()->FindBin(t->GetLeaf("drPrevr")->GetValue(0));
      double drPrevr_bg_prob = drPrevr_background->GetBinContent(drPrevr_bg_bin);
      double closestPMT_sig_bin = closestPMT_signal->GetXaxis()->FindBin(t->GetLeaf("closestPMT")->GetValue(0));
      double closestPMT_sig_prob = closestPMT_signal->GetBinContent(closestPMT_sig_bin);
      double closestPMT_bg_bin = closestPMT_background->GetXaxis()->FindBin(t->GetLeaf("closestPMT")->GetValue(0));
      double closestPMT_bg_prob = closestPMT_background->GetBinContent(closestPMT_bg_bin);
      double sig_like = log(n100_sig_prob*n100_prev_sig_prob*dt_prev_us_sig_prob*drPrevr_sig_prob*closestPMT_sig_prob);
      double bg_like = log(n100_bg_prob*n100_prev_bg_prob*dt_prev_us_bg_prob*drPrevr_bg_prob*closestPMT_bg_prob);
      {if( std::isinf(sig_like) == true){sig_like=0;}else{}}
      {if( std::isinf(bg_like) == true){bg_like=0;}else{}}
      double r_like = sig_like-bg_like;
      signal_like->Fill(sig_like);
      background_like->Fill(bg_like);
      ratio_like->Fill(r_like);
    }
  }
  
  ratio_like->Scale(1/ratio_like->GetEntries());
  signal_like->Scale(1/signal_like->GetEntries());
  background_like->Scale(1/background_like->GetEntries());
  
  out->cd();
  signal_like->Write();
  background_like->Write();
  ratio_like->Write();
  out->Close();
  f->Close();

}
