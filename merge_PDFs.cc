#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
#include <TTree.h>
#include <math.h>
//#include "likelihood.h"
#include <TH1D.h>
#include <TLeaf.h>

#include <vector>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <iostream>

//Likelihood,Analysis,Unbinned,Reactor,Dwell,Time

void merge_PDFs(const char* sig){

  std::vector<std::string> signal;
  std::vector<std::string> background;
  std::vector<std::string> components;
  std::vector<double> rates;
  std::vector<std::string> line_values;
  std::ifstream theFile ("rates.csv");
  std::string line;
  std::getline(theFile, line); //remove header
  
  while(std::getline(theFile, line))
  {
    std::string line_value;
    std::stringstream ss(line);
    while(std::getline(ss, line_value, ','))
    {
      line_values.push_back(line_value);
      //printf("line_value = %s\n",line_value.c_str());
    }
  }
  
  for (int i = 0; i < line_values.size(); i = i + 2) {
    components.push_back(line_values[i]);
    //printf("components[%i] = %s\n",i,line_values[i].c_str());
  }
  
  for (int i = 1; i < line_values.size(); i = i + 2) {
    rates.push_back(std::stod(line_values[i]));
    //printf("rates[%i] = %f\n",i,std::stod(line_values[i]));
  }
  
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

  const char* sig = "hartlepool";
  if (argc > 1) {sig = argv[1];}

  //const char* sig = argv[1]; //input file (FRED)
  //const char* outfile = argv[2]; //output file (likehoods)
  merge_PDFs(sig);
  // have component type/rate as an input?
  // need MC information for number of events simulated

}
