#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
#include <TTree.h>
#include <math.h>
//#include "likelihood.h"
#include <TH1D.h>
#include <TLeaf.h>

//Likelihood,Analysis,Unbinned,Reactor,Dwell,Time

void merge_PDFs(const char* sig){

  //read in pdfs
  //big, small, world, geo, li9, n17, singles
  std::vector<std::string> signal;
  std::vector<std::string> background;
  
  std::vector<std::string/*const char* */> components = {"big","small","li9","n17","world","geo","singles","heysham","heysham_bg","heysham2","heysham2_bg","torness","torness_bg"};
  
  // char* sig = "hartlepool"; //set as input
  
  if(strncmp(sig, "hartlepool",10)==0){
    signal.push_back("big");
    signal.push_back("small");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("geo");
    background.push_back("world");
  }
  else if(strncmp(sig, "heysham",10)==0){
    signal.push_back("heysham");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("heysham_bg");
  }
  else if(strncmp(sig, "heysham2",10)==0){
    signal.push_back("heysham2");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("heysham2_bg");
  }
  else if(strncmp(sig, "torness",10)==0){
    signal.push_back("torness");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("torness_bg");
  }
    
  double big_rate = 9.531e-5;
  double small_rate = 7.126e-5;
  double li9_rate = 7.97e-6;
  double n17_rate = 8.01e-6;
  double world_rate = 4.382e-6;
  double geo_rate = 7.013e-7;
  double singles_rate = 1.96e8;
  double heysham_rate = 5.295e-6;
  double heysham_bg_rate = 2.106e-5;
  double heysham2_rate = 2.648e-6;
  double heysham2_bg_rate = 2.106e-5;
  double torness_rate = 1.945e-6;
  double torness_bg_rate = 2.106e-5;
    
  //set proper rates -> read from csv?
  
  std::vector<double> rates = {big_rate,small_rate,li9_rate,n17_rate,world_rate,geo_rate,singles_rate,heysham_rate,heysham_bg_rate,heysham2_rate,heysham2_bg_rate,torness_rate,torness_bg_rate};
  
  //return everything above here to use in analysis
  
  //loop over components. if component[i] in signal, add rate[i] to signal rate. repeat for background
  //loop over components and read in histograms, scale by rate[i]/signal(background) rate.
  //write new file for components and merge all signal and background pdfs
  
  double signal_rate = 0;
  double background_rate = 0;
  
  for(int i=0;i<components.size();i++){
    if(std::find(signal.begin(), signal.end(), components[i]) != signal.end()){
      signal_rate+=rates[i];
      printf("Component %s in signal\n",components[i].c_str());
    }
    else if(std::find(background.begin(), background.end(), components[i]) != background.end()){
      background_rate+=rates[i];
      printf("Component %s in background\n",components[i].c_str());
    }
    else{
      printf("Component %s not in signal or background\n",components[i].c_str());
    }
  }
  
  printf("Signal rate = %e per second\nBackground rate = %e per second\n",signal_rate,background_rate);
  
  int nbins = /*signal.size()**/200;
  
  //read in signal pdfs
  for(int i=0; i<components.size(); i++){
  
  //need to isolate signal and background
    if(std::find(signal.begin(), signal.end(), components[i]) != signal.end()){
      printf("Scaling signal component %s\n",components[i].c_str());
      TFile *like = new TFile(Form("%s_pdfs.root",signal[i].c_str()));
      TH1D* n100 = (TH1D*)like->Get("n100");
      n100->Scale(rates[i]/signal_rate);
      TH1D* n100_prev = (TH1D*)like->Get("n100_prev");
      n100_prev->Scale(rates[i]/signal_rate);
      TH1D* dt_prev_us = (TH1D*)like->Get("dt_prev_us");
      dt_prev_us->Scale(rates[i]/signal_rate);
      TH1D* drPrevr = (TH1D*)like->Get("drPrevr");
      drPrevr->Scale(rates[i]/signal_rate);
      TH1D* closestPMT = (TH1D*)like->Get("closestPMT");
      closestPMT->Scale(rates[i]/signal_rate);
      TFile *like_scale = new TFile(Form("%s_scaled_pdfs.root",components[i].c_str()),"RECREATE");
      n100->Write();
      n100_prev->Write();
      dt_prev_us->Write();
      drPrevr->Write();
      closestPMT->Write();
      like->Close();
      like_scale->Close();
    }
    else if(std::find(background.begin(), background.end(), components[i]) != background.end()){
      printf("Scaling background component %s\n",components[i].c_str());
      TFile *like = new TFile(Form("%s_pdfs.root",components[i].c_str()));
      TH1D* n100 = (TH1D*)like->Get("n100");
      n100->Scale(rates[i]/background_rate);
      TH1D* n100_prev = (TH1D*)like->Get("n100_prev");
      n100_prev->Scale(rates[i]/background_rate);
      TH1D* dt_prev_us = (TH1D*)like->Get("dt_prev_us");
      dt_prev_us->Scale(rates[i]/background_rate);
      TH1D* drPrevr = (TH1D*)like->Get("drPrevr");
      drPrevr->Scale(rates[i]/background_rate);
      TH1D* closestPMT = (TH1D*)like->Get("closestPMT");
      closestPMT->Scale(rates[i]/background_rate);
      TFile *like_scale = new TFile(Form("%s_scaled_pdfs.root",components[i].c_str()),"RECREATE");
      n100->Write();
      n100_prev->Write();
      dt_prev_us->Write();
      drPrevr->Write();
      closestPMT->Write();
      like->Close();
      like_scale->Close();
    }
  }
  
  //hadd signal and background components

}

int main(int argc, char** argv){

  const char* sig = argv[1]; //input file (FRED)
  //const char* outfile = argv[2]; //output file (likehoods)
  merge_PDFs(sig);
  // have component type/rate as an input?
  // need MC information for number of events simulated

}
