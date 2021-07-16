#include "learn.h"

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
  
  printf("There were %i MC events simulated\n",nevents);
  
  int nentries = t->GetEntries();
  printf("There are %i reconstructed entries in %s\n",nentries,infile);

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
  TH1D* beta_one_signal = (TH1D*)signal->Get("beta_one");
  TH1D* beta_one_prev_signal = (TH1D*)signal->Get("beta_one_prev");
  TH1D* beta_two_signal = (TH1D*)signal->Get("beta_two");
  TH1D* beta_two_prev_signal = (TH1D*)signal->Get("beta_two_prev");
  TH1D* beta_three_signal = (TH1D*)signal->Get("beta_three");
  TH1D* beta_three_prev_signal = (TH1D*)signal->Get("beta_three_prev");
  TH1D* beta_four_signal = (TH1D*)signal->Get("beta_four");
  TH1D* beta_four_prev_signal = (TH1D*)signal->Get("beta_four_prev");
  TH1D* beta_five_signal = (TH1D*)signal->Get("beta_five");
  TH1D* beta_five_prev_signal = (TH1D*)signal->Get("beta_five_prev");
  TH1D* beta_six_signal = (TH1D*)signal->Get("beta_six");
  TH1D* beta_six_prev_signal = (TH1D*)signal->Get("beta_six_prev");
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
  TH1D* beta_one_background = (TH1D*)background->Get("beta_one");
  TH1D* beta_one_prev_background = (TH1D*)background->Get("beta_one_prev");
  TH1D* beta_two_background = (TH1D*)background->Get("beta_two");
  TH1D* beta_two_prev_background = (TH1D*)background->Get("beta_two_prev");
  TH1D* beta_three_background = (TH1D*)background->Get("beta_three");
  TH1D* beta_three_prev_background = (TH1D*)background->Get("beta_three_prev");
  TH1D* beta_four_background = (TH1D*)background->Get("beta_four");
  TH1D* beta_four_prev_background = (TH1D*)background->Get("beta_four_prev");
  TH1D* beta_five_background = (TH1D*)background->Get("beta_five");
  TH1D* beta_five_prev_background = (TH1D*)background->Get("beta_five_prev");
  TH1D* beta_six_background = (TH1D*)background->Get("beta_six");
  TH1D* beta_six_prev_background = (TH1D*)background->Get("beta_six_prev");
  
  for(int i=0; i<nentries; i++){
    t->GetEntry(i);
    if (i%100000==0){
      printf("Creating likelihoods: Event %d of %d\n",i,nentries);
    }
    if (t->GetLeaf("n100")->GetValue(0) > 0 and t->GetLeaf("closestPMT")->GetValue(0) > -499) {
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
      
      double beta_one_sig_bin = beta_one_signal->GetXaxis()->FindBin(t->GetLeaf("beta_one")->GetValue(0));
      double beta_one_sig_prob = beta_one_signal->GetBinContent(beta_one_sig_bin);
      double beta_one_bg_bin = beta_one_background->GetXaxis()->FindBin(t->GetLeaf("beta_one")->GetValue(0));
      double beta_one_bg_prob = beta_one_background->GetBinContent(beta_one_bg_bin);
      
      double beta_one_prev_sig_bin = beta_one_prev_signal->GetXaxis()->FindBin(t->GetLeaf("beta_one_prev")->GetValue(0));
      double beta_one_prev_sig_prob = beta_one_prev_signal->GetBinContent(beta_one_prev_sig_bin);
      double beta_one_prev_bg_bin = beta_one_prev_background->GetXaxis()->FindBin(t->GetLeaf("beta_one_prev")->GetValue(0));
      double beta_one_prev_bg_prob = beta_one_prev_background->GetBinContent(beta_one_prev_bg_bin);
      
      double beta_two_sig_bin = beta_two_signal->GetXaxis()->FindBin(t->GetLeaf("beta_two")->GetValue(0));
      double beta_two_sig_prob = beta_two_signal->GetBinContent(beta_two_sig_bin);
      double beta_two_bg_bin = beta_two_background->GetXaxis()->FindBin(t->GetLeaf("beta_two")->GetValue(0));
      double beta_two_bg_prob = beta_two_background->GetBinContent(beta_two_bg_bin);
      
      double beta_two_prev_sig_bin = beta_two_prev_signal->GetXaxis()->FindBin(t->GetLeaf("beta_two_prev")->GetValue(0));
      double beta_two_prev_sig_prob = beta_two_prev_signal->GetBinContent(beta_two_prev_sig_bin);
      double beta_two_prev_bg_bin = beta_two_prev_background->GetXaxis()->FindBin(t->GetLeaf("beta_two_prev")->GetValue(0));
      double beta_two_prev_bg_prob = beta_two_prev_background->GetBinContent(beta_two_prev_bg_bin);
      
      double beta_three_sig_bin = beta_three_signal->GetXaxis()->FindBin(t->GetLeaf("beta_three")->GetValue(0));
      double beta_three_sig_prob = beta_three_signal->GetBinContent(beta_three_sig_bin);
      double beta_three_bg_bin = beta_three_background->GetXaxis()->FindBin(t->GetLeaf("beta_three")->GetValue(0));
      double beta_three_bg_prob = beta_three_background->GetBinContent(beta_three_bg_bin);
      
      double beta_three_prev_sig_bin = beta_three_prev_signal->GetXaxis()->FindBin(t->GetLeaf("beta_three_prev")->GetValue(0));
      double beta_three_prev_sig_prob = beta_three_prev_signal->GetBinContent(beta_three_prev_sig_bin);
      double beta_three_prev_bg_bin = beta_three_prev_background->GetXaxis()->FindBin(t->GetLeaf("beta_three_prev")->GetValue(0));
      double beta_three_prev_bg_prob = beta_three_prev_background->GetBinContent(beta_three_prev_bg_bin);
      
      double beta_four_sig_bin = beta_four_signal->GetXaxis()->FindBin(t->GetLeaf("beta_four")->GetValue(0));
      double beta_four_sig_prob = beta_four_signal->GetBinContent(beta_four_sig_bin);
      double beta_four_bg_bin = beta_four_background->GetXaxis()->FindBin(t->GetLeaf("beta_four")->GetValue(0));
      double beta_four_bg_prob = beta_four_background->GetBinContent(beta_four_bg_bin);
      
      double beta_four_prev_sig_bin = beta_four_prev_signal->GetXaxis()->FindBin(t->GetLeaf("beta_four_prev")->GetValue(0));
      double beta_four_prev_sig_prob = beta_four_prev_signal->GetBinContent(beta_four_prev_sig_bin);
      double beta_four_prev_bg_bin = beta_four_prev_background->GetXaxis()->FindBin(t->GetLeaf("beta_four_prev")->GetValue(0));
      double beta_four_prev_bg_prob = beta_four_prev_background->GetBinContent(beta_four_prev_bg_bin);
      
      double beta_five_sig_bin = beta_five_signal->GetXaxis()->FindBin(t->GetLeaf("beta_five")->GetValue(0));
      double beta_five_sig_prob = beta_five_signal->GetBinContent(beta_five_sig_bin);
      double beta_five_bg_bin = beta_five_background->GetXaxis()->FindBin(t->GetLeaf("beta_five")->GetValue(0));
      double beta_five_bg_prob = beta_five_background->GetBinContent(beta_five_bg_bin);
      
      double beta_five_prev_sig_bin = beta_five_prev_signal->GetXaxis()->FindBin(t->GetLeaf("beta_five_prev")->GetValue(0));
      double beta_five_prev_sig_prob = beta_five_prev_signal->GetBinContent(beta_five_prev_sig_bin);
      double beta_five_prev_bg_bin = beta_five_prev_background->GetXaxis()->FindBin(t->GetLeaf("beta_five_prev")->GetValue(0));
      double beta_five_prev_bg_prob = beta_five_prev_background->GetBinContent(beta_five_prev_bg_bin);
      
      double beta_six_sig_bin = beta_six_signal->GetXaxis()->FindBin(t->GetLeaf("beta_six")->GetValue(0));
      double beta_six_sig_prob = beta_six_signal->GetBinContent(beta_six_sig_bin);
      double beta_six_bg_bin = beta_six_background->GetXaxis()->FindBin(t->GetLeaf("beta_six")->GetValue(0));
      double beta_six_bg_prob = beta_six_background->GetBinContent(beta_six_bg_bin);
      
      double beta_six_prev_sig_bin = beta_six_prev_signal->GetXaxis()->FindBin(t->GetLeaf("beta_six_prev")->GetValue(0));
      double beta_six_prev_sig_prob = beta_six_prev_signal->GetBinContent(beta_six_prev_sig_bin);
      double beta_six_prev_bg_bin = beta_six_prev_background->GetXaxis()->FindBin(t->GetLeaf("beta_six_prev")->GetValue(0));
      double beta_six_prev_bg_prob = beta_six_prev_background->GetBinContent(beta_six_prev_bg_bin);
      
      double sig_like = log(n100_sig_prob*n100_prev_sig_prob*dt_prev_us_sig_prob*drPrevr_sig_prob*closestPMT_sig_prob);//*beta_one_sig_prob*beta_one_prev_sig_prob*beta_two_sig_prob*beta_two_prev_sig_prob*beta_three_sig_prob*beta_three_prev_sig_prob*beta_four_sig_prob*beta_four_prev_sig_prob*beta_five_sig_prob*beta_five_prev_sig_prob*beta_six_sig_prob*beta_six_prev_sig_prob);
      double bg_like = log(n100_bg_prob*n100_prev_bg_prob*dt_prev_us_bg_prob*drPrevr_bg_prob*closestPMT_bg_prob);//*beta_one_bg_prob*beta_one_prev_bg_prob*beta_two_bg_prob*beta_two_prev_bg_prob*beta_three_bg_prob*beta_three_prev_bg_prob*beta_four_bg_prob*beta_four_prev_bg_prob*beta_five_bg_prob*beta_five_prev_bg_prob*beta_six_bg_prob*beta_six_prev_bg_prob);
      {if( std::isinf(sig_like) == true){sig_like=0;}else{}}
      {if( std::isinf(bg_like) == true){bg_like=0;}else{}}
      double r_like = sig_like-bg_like;
      signal_like->Fill(sig_like);
      background_like->Fill(bg_like);
      ratio_like->Fill(r_like);
    }
  }
  
  ratio_like->Scale(1/ratio_like->Integral());
  signal_like->Scale(1/signal_like->Integral());
  background_like->Scale(1/background_like->Integral());
  
  out->cd();
  signal_like->Write();
  background_like->Write();
  ratio_like->Write();
  out->Close();
  f->Close();

}
