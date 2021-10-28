#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TLeaf.h>
#include <iostream>
#include <TF1.h>
#include <TH2.h>

void energy(const char* infile, const char* outfile){

  double ecut = 6.;
  double ecut2 = 1.;

  gROOT->SetBatch(kTRUE);

  TFile *f = new TFile(infile);
  TTree *t_in = (TTree*)f->Get("data");
  TTree *run = (TTree*)f->Get("runSummary");

  int nentries = t_in->GetEntries();

  t_in->Draw("mc_energy:n100>>prompt","subid == 0 && n100>0");
  TH1 *prompt = (TH1*)gDirectory->Get("prompt");
  prompt->Fit("pol1","Q");
  TF1 *fitresult = prompt->GetFunction("pol1");
  double p0 = fitresult->GetParameter(0);
  double p1 = fitresult->GetParameter(1);
  TString prompt_cut = Form("subid==0 && %f + %f*n100 < %f",p0,p1,ecut);
  t_in->Draw("n100>>prompt_cut",prompt_cut);
  
  int subid,n100,mcid,mcid_2;
  double E,mc_energy;

  int removed = 0;

  for(int i=1; i<nentries; i++){
      t_in->GetEntry(i-1);
      subid = t_in->GetLeaf("subid")->GetValue(0);
      mcid = t_in->GetLeaf("mcid")->GetValue(0);
      n100 = t_in->GetLeaf("n100")->GetValue(0);
      mc_energy = t_in->GetLeaf("mc_energy")->GetValue(0);
      E = p0 + p1*n100;
      printf("Event %i: mcid = %i, subid = %i, E = %f, mc_energy = %f\n",i-1,mcid,subid,E,mc_energy);
      t_in->GetEntry(i);
      if(E>100){
          subid = t_in->GetLeaf("subid")->GetValue(0);
          mcid_2 = t_in->GetLeaf("mcid")->GetValue(0);
          removed++;
      }
      else if((E>ecut or E<ecut2) && subid==0){
          //remove event
          printf("Remove prompt entry %i\n",i-1);
          subid = t_in->GetLeaf("subid")->GetValue(0);
          mcid_2 = t_in->GetLeaf("mcid")->GetValue(0);
          removed++;
          if(subid==1 && mcid==mcid_2){
              //remove
              printf("Remove delayed entry %i\n",i);
              removed++;
          }
      }
  }
  printf("Removed %i out of % i entries\n",removed+1,nentries);
}

int main(int argc, char** argv){

  const char* infile = argv[1];
  const char* outfile = "test";//argv[2];
  energy(infile,outfile);

}
