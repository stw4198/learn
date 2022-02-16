#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TLeaf.h>
#include <iostream>
#include <TF1.h>
#include <TH2.h>

std::vector<double> energy_write(const char* infile, const char* fitfile, const char* outfile, double e_lower, double e_upper){

  double ecut = e_upper;
  double ecut2 = e_lower;
  std::vector<double> energy_cut;

  gROOT->SetBatch(kTRUE);
  gROOT->ProcessLine( "gErrorIgnoreLevel = 1001;");

  TFile *ffit = new TFile(fitfile);
  if(!ffit->IsOpen()){
    printf("File %s does not exist.\n",fitfile);
    energy_cut.push_back(0);
    energy_cut.push_back(0);
    printf("Removed 0 out of 0 entries\n");
    return(energy_cut);
  }
  TTree *tfit = (TTree*)ffit->Get("data");

  TFile *f = new TFile(infile);
  if(!f->IsOpen()){
    printf("File %s does not exist.\n",infile);
    energy_cut.push_back(0);
    energy_cut.push_back(0);
    printf("Removed 0 out of 0 entries\n");
    return(energy_cut);
  }
  TTree *t_in = (TTree*)f->Get("data");
  TTree *run = (TTree*)f->Get("runSummary");

  int nentries = t_in->GetEntries();
  if (nentries==0){
      energy_cut.push_back(0);
      energy_cut.push_back(0);
      printf("Removed 0 out of %i entries\n",nentries);
      return(energy_cut);
  }

  tfit->Draw("mc_energy:n100>>prompt","subid == 0 && mc_energy>1");
  TH1 *prompt = (TH1*)gDirectory->Get("prompt");
  prompt->Fit("pol1","Q");
  TF1 *fitresult = prompt->GetFunction("pol1");
  double p0 = fitresult->GetParameter(0);
  double p1 = fitresult->GetParameter(1);
  
  int subid,n100,mcid,mcid_2;
  double E,mc_energy,innerPE;
  int nevents;

  TFile *output = new TFile(outfile,"RECREATE");
  TTree *data = new TTree("data","low-energy detector triggered events");
  TTree *run_summary=new TTree("runSummary","mc run summary");

  data->Branch("subid",&subid,"subid/I");
  data->Branch("mcid",&mcid,"mcid/I");
  data->Branch("n100",&n100,"n100/I");
  data->Branch("mc_energy",&mc_energy,"mc_energy/D");
  data->Branch("innerPE",&innerPE,"innerPE/D");
  run_summary->Branch("nevents",&nevents,"nevents/I");

  int removed = 0;

  for(int i=1; i<nentries; i++){
      t_in->GetEntry(i-1);
      subid = t_in->GetLeaf("subid")->GetValue(0);
      mcid = t_in->GetLeaf("mcid")->GetValue(0);
      n100 = t_in->GetLeaf("n100")->GetValue(0);
      innerPE = t_in->GetLeaf("innerPE")->GetValue(0);
      mc_energy = t_in->GetLeaf("mc_energy")->GetValue(0);
      E = p0 + p1*n100;
      t_in->GetEntry(i);
      if(E>100){
          subid = t_in->GetLeaf("subid")->GetValue(0);
          mcid_2 = t_in->GetLeaf("mcid")->GetValue(0);
          removed++;
      }
      else if((E>ecut or E<ecut2) && subid==0){
          subid = t_in->GetLeaf("subid")->GetValue(0);
          mcid_2 = t_in->GetLeaf("mcid")->GetValue(0);
          removed++;
          if(subid==1 && mcid==mcid_2){
              removed++;
          }
      }
      else{
        data->Fill();
      }
  }
  run->GetEntry(0);
  nevents = run->GetLeaf("nevents")->GetValue();
  output->cd();
  data->Write();
  run_summary->Fill();
  run_summary->Write();
  output->Close();
  printf("Removed %i out of %i entries\n",removed+1,nentries);
  energy_cut.clear();
  energy_cut.push_back(removed);
  energy_cut.push_back(nentries);
  return(energy_cut);
}

int main(int argc, char** argv){

  const char* infile = argv[1];
  const char* fitfile = argv[2];
  const char* outfile = argv[3];
  double e_lower = std::stod(argv[4]);
  double e_upper = std::stod(argv[5]);
  std::vector<double> energy_cut = energy_write(infile,fitfile,outfile,e_lower,e_upper);

}
