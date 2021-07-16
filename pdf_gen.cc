#include "learn.h"

void pdf_gen(const char* file, const char* component, int nbins, int dTank){

  TFile *f = new TFile(file);
  if(!f->IsOpen()){
    printf("File %s does not exist.\n",file);
    return;
  }
  TTree *t = (TTree*)f->Get("data");
  TTree *run = (TTree*)f->Get("runSummary");
  
  TFile *like = new TFile(Form("%s_pdfs.root",component),"RECREATE");
   
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
  printf("There are %i reconstructed entries in %s\n",nentries,file);
  
  int nkept = 0;
  
  TH1D* n100 = new TH1D("n100","n100",nbins,0,1000);
  TH1D* n100_prev = new TH1D("n100_prev","n100_prev",nbins,0,1000);
  TH1D* dt_prev_us = new TH1D("dt_prev_us","dt_prev_us",nbins,0,4000);
  TH1D* drPrevr = new TH1D("drPrevr","drPrevr",nbins,0,dTank);
  TH1D* closestPMT = new TH1D("closestPMT","closestPMT",nbins,0,dTank);
  TH1D* beta_one = new TH1D("beta_one","beta_one",nbins,-0.3,1.1);
  TH1D* beta_one_prev = new TH1D("beta_one_prev","beta_one_prev",nbins,-0.3,1.1);
  TH1D* beta_two = new TH1D("beta_two","beta_two",nbins,-0.3,1.1);
  TH1D* beta_two_prev = new TH1D("beta_two_prev","beta_two_prev",nbins,-0.3,1.1);
  TH1D* beta_three = new TH1D("beta_three","beta_three",nbins,-0.3,1.1);
  TH1D* beta_three_prev = new TH1D("beta_three_prev","beta_three_prev",nbins,-0.3,1.1);
  TH1D* beta_four = new TH1D("beta_four","beta_four",nbins,-0.3,1.1);
  TH1D* beta_four_prev = new TH1D("beta_four_prev","beta_four_prev",nbins,-0.3,1.1);
  TH1D* beta_five = new TH1D("beta_five","beta_five",nbins,-0.3,1.1);
  TH1D* beta_five_prev = new TH1D("beta_five_prev","beta_five_prev",nbins,-0.3,1.1);
  TH1D* beta_six = new TH1D("beta_six","beta_six",nbins,-0.3,1.1);
  TH1D* beta_six_prev = new TH1D("beta_six_prev","beta_six_prev",nbins,-0.3,1.1);
  
  for(int i=0; i<nentries; i++){
    t->GetEntry(i);
    if (i%100000==0){
      printf("Generating PDFs: Event %d of %d\n",i,nentries);
    }
    if (t->GetLeaf("n100")->GetValue(0) > 0 and t->GetLeaf("closestPMT")->GetValue(0) > -499) {
	    nkept++;
	    n100->Fill(t->GetLeaf("n100")->GetValue(0));
	    n100_prev->Fill(t->GetLeaf("n100_prev")->GetValue(0));
	    dt_prev_us->Fill(t->GetLeaf("dt_prev_us")->GetValue(0));
	    drPrevr->Fill(t->GetLeaf("drPrevr")->GetValue(0));
	    closestPMT->Fill(t->GetLeaf("closestPMT")->GetValue(0));
	    beta_one->Fill(t->GetLeaf("beta_one")->GetValue(0));
	    beta_one_prev->Fill(t->GetLeaf("beta_one_prev")->GetValue(0));
	    beta_two->Fill(t->GetLeaf("beta_two")->GetValue(0));
	    beta_two_prev->Fill(t->GetLeaf("beta_two_prev")->GetValue(0));
	    beta_three->Fill(t->GetLeaf("beta_three")->GetValue(0));
	    beta_three_prev->Fill(t->GetLeaf("beta_three_prev")->GetValue(0));
	    beta_four->Fill(t->GetLeaf("beta_four")->GetValue(0));
	    beta_four_prev->Fill(t->GetLeaf("beta_four_prev")->GetValue(0));
	    beta_five->Fill(t->GetLeaf("beta_five")->GetValue(0));
	    beta_five_prev->Fill(t->GetLeaf("beta_five_prev")->GetValue(0));
	    beta_six->Fill(t->GetLeaf("beta_six")->GetValue(0));
	    beta_six_prev->Fill(t->GetLeaf("beta_six_prev")->GetValue(0));
    }
  }
  
  printf("Kept %i events\n",nkept);
  
  n100->Scale(1/n100->GetEntries());
  n100->Write();
  n100_prev->Scale(1/n100_prev->GetEntries());
  n100_prev->Write();
  dt_prev_us->Scale(1/dt_prev_us->GetEntries());
  dt_prev_us->Write();
  drPrevr->Scale(1/drPrevr->GetEntries());
  drPrevr->Write();
  closestPMT->Scale(1/closestPMT->GetEntries());
  closestPMT->Write();
  beta_one->Scale(1/beta_one->GetEntries());
  beta_one->Write();
  beta_one_prev->Scale(1/beta_one_prev->GetEntries());
  beta_one_prev->Write();
  beta_two->Scale(1/beta_two->GetEntries());
  beta_two->Write();
  beta_two_prev->Scale(1/beta_two_prev->GetEntries());
  beta_two_prev->Write();
  beta_three->Scale(1/beta_three->GetEntries());
  beta_three->Write();
  beta_three_prev->Scale(1/beta_three_prev->GetEntries());
  beta_three_prev->Write();
  beta_four->Scale(1/beta_four->GetEntries());
  beta_four->Write();
  beta_four_prev->Scale(1/beta_four_prev->GetEntries());
  beta_four_prev->Write();
  beta_five->Scale(1/beta_five->GetEntries());
  beta_five->Write();
  beta_five_prev->Scale(1/beta_five_prev->GetEntries());
  beta_five_prev->Write();
  beta_six->Scale(1/beta_six->GetEntries());
  beta_six->Write();
  beta_six_prev->Scale(1/beta_six_prev->GetEntries());
  beta_six_prev->Write();
  like->Close();

}
