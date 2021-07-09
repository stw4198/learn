#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TLeaf.h>

#include "lance.h"

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
  
  printf("There are %i MC events\n",nevents);
  
  int nentries = t->GetEntries();
  printf("There are %i entries in %s\n",nentries,file);
  
  int nkept = 0;
  
  TH1D* n100 = new TH1D("n100","n100",nbins,0,1000);
  TH1D* n100_prev = new TH1D("n100_prev","n100_prev",nbins,0,1000);
  TH1D* dt_prev_us = new TH1D("dt_prev_us","dt_prev_us",nbins,0,2000);
  TH1D* drPrevr = new TH1D("drPrevr","drPrevr",nbins,0,dTank);
  TH1D* closestPMT = new TH1D("closestPMT","closestPMT",nbins,0,dTank);
  
  for(int i=0; i<nentries; i++){
    t->GetEntry(i);
    if (i%100000==0){
      printf("Generating PDFs: Event %d of %d\n",i,nentries);
    }
    if ( t->GetLeaf("n100")->GetValue(0) > 0 and t->GetLeaf("closestPMT")->GetValue(0) > 0 and t->GetLeaf("dt_prev_us")->GetValue(0) > 0 and t->GetLeaf("dt_prev_us")->GetValue(0) < 2000) {
	    nkept++;
	    n100->Fill(t->GetLeaf("n100")->GetValue(0));
	    n100_prev->Fill(t->GetLeaf("n100_prev")->GetValue(0));
	    dt_prev_us->Fill(t->GetLeaf("dt_prev_us")->GetValue(0));
	    drPrevr->Fill(t->GetLeaf("drPrevr")->GetValue(0));
	    closestPMT->Fill(t->GetLeaf("closestPMT")->GetValue(0));
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
  like->Close();

}
