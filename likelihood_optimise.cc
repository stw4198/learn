#include <TROOT.h>
#include <TFile.h>
#include <TString.h>
#include <TTree.h>
#include <TH1D.h>
#include <TLeaf.h>
//Likelihood,Analysis,Unbinned,Reactor,Dwell,Time

void likehood_optimise(){

  // Component of interest
  TFile *f = new TFile("singles_likelihoods.root");
  
  TH1D* ratio_like = (TH1D*)f->Get("ratio_like");

  int binmax = ratio_like->FindLastBinAbove();//GetMaximumBin();
  double max_Lr = ratio_like->GetXaxis()->GetBinCenter(binmax);
  printf("Max Lr for singles = %f\n",max_Lr);

}

int main(int argc, char** argv){
  
  likehood_optimise();

}
