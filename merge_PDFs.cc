#include "learn.h"

void merge_PDFs(const char* sig){

  std::vector<std::string> signal;
  std::vector<std::string> background;
  std::vector<std::string> components;
  std::vector<double> rates;
  std::vector<std::string> line_values;
  std::ifstream theFile ("rates.csv");
  if(!theFile.is_open()){
    printf("File rates.csv does not exist, please copy to working directory from learn\n");
    return;
  }
  std::string line;
  std::getline(theFile, line);
  
  while(std::getline(theFile, line))
  {
    std::string line_value;
    std::stringstream ss(line);
    while(std::getline(ss, line_value, ','))
    {
      line_values.push_back(line_value);
    }
  }
  
  for (int i = 0; i < line_values.size(); i = i + 2) {
    components.push_back(line_values[i]);
  }
  
  for (int i = 1; i < line_values.size(); i = i + 2) {
    rates.push_back(std::stod(line_values[i]));
  }
  
  if(strncmp(sig, "hartlepool",strlen(sig))==0){
    signal.push_back("hartlepool_1");
    signal.push_back("hartlepool_2");
    background.push_back("heysham_full");
    background.push_back("torness_full");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("geo");
    background.push_back("world");
    background.push_back("fn");
  }
  else if(strncmp(sig, "heysham_full",strlen(sig))==0){
    signal.push_back("heysham_full");
    background.push_back("torness_full");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("geo");
    background.push_back("world");
    background.push_back("fn");
  }
  else if(strncmp(sig, "heysham_2",strlen(sig))==0){
    signal.push_back("heysham_2");
    background.push_back("torness_full");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("geo");
    background.push_back("world");
    background.push_back("fn");
  }
  else if(strncmp(sig, "torness_full",strlen(sig))==0){
    signal.push_back("torness_full");
    background.push_back("heysham_2");
    background.push_back("singles");
    background.push_back("n17");
    background.push_back("li9");
    background.push_back("geo");
    background.push_back("world");
    background.push_back("fn");
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
  
  for(int i=0; i<components.size(); i++){
      if(std::find(signal.begin(), signal.end(), components[i]) != signal.end()){
      printf("Scaling signal component %s\n",components[i].c_str());
      TFile *like = new TFile(Form("%s_pdfs.root",components[i].c_str()));
      if(!like->IsOpen()){
        printf("File %s_pdfs.root does not exist.\n",components[i].c_str());
      return;
      }
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
      
      TH1D* beta_one = (TH1D*)like->Get("beta_one");
      beta_one->Scale(rates[i]/signal_rate);
      
      TH1D* beta_one_prev = (TH1D*)like->Get("beta_one_prev");
      beta_one_prev->Scale(rates[i]/signal_rate);
      
      TH1D* beta_two = (TH1D*)like->Get("beta_two");
      beta_two->Scale(rates[i]/signal_rate);
      
      TH1D* beta_two_prev = (TH1D*)like->Get("beta_two_prev");
      beta_two_prev->Scale(rates[i]/signal_rate);
      
      TH1D* beta_three = (TH1D*)like->Get("beta_three");
      beta_three->Scale(rates[i]/signal_rate);
      
      TH1D* beta_three_prev = (TH1D*)like->Get("beta_three_prev");
      beta_three_prev->Scale(rates[i]/signal_rate);
      
      TH1D* beta_four = (TH1D*)like->Get("beta_four");
      beta_four->Scale(rates[i]/signal_rate);
      
      TH1D* beta_four_prev = (TH1D*)like->Get("beta_four_prev");
      beta_four_prev->Scale(rates[i]/signal_rate);
      
      TH1D* beta_five = (TH1D*)like->Get("beta_five");
      beta_five->Scale(rates[i]/signal_rate);
      
      TH1D* beta_five_prev = (TH1D*)like->Get("beta_five_prev");
      beta_five_prev->Scale(rates[i]/signal_rate);
      
      TH1D* beta_six = (TH1D*)like->Get("beta_six");
      beta_six->Scale(rates[i]/signal_rate);
      
      TH1D* beta_six_prev = (TH1D*)like->Get("beta_six_prev");
      beta_six_prev->Scale(rates[i]/signal_rate);
      
      TFile *like_scale = new TFile(Form("%s_scaled_pdfs.root",components[i].c_str()),"RECREATE");
      n100->Write();
      n100_prev->Write();
      dt_prev_us->Write();
      drPrevr->Write();
      closestPMT->Write();
      beta_one->Write();
      beta_one_prev->Write();
      beta_two->Write();
      beta_two_prev->Write();
      beta_three->Write();
      beta_three_prev->Write();
      beta_four->Write();
      beta_four_prev->Write();
      beta_five->Write();
      beta_five_prev->Write();
      beta_six->Write();
      beta_six_prev->Write();
      like->Close();
      like_scale->Close();
    }
    else if(std::find(background.begin(), background.end(), components[i]) != background.end()){
      printf("Scaling background component %s\n",components[i].c_str());
      TFile *like = new TFile(Form("%s_pdfs.root",components[i].c_str()));
      if(!like->IsOpen()){
        printf("File %s_pdfs.root does not exist.\n",components[i].c_str());
      return;
      }
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
      
      TH1D* beta_one = (TH1D*)like->Get("beta_one");
      beta_one->Scale(rates[i]/background_rate);
      
      TH1D* beta_one_prev = (TH1D*)like->Get("beta_one_prev");
      beta_one_prev->Scale(rates[i]/background_rate);
      
      TH1D* beta_two = (TH1D*)like->Get("beta_two");
      beta_two->Scale(rates[i]/background_rate);
      
      TH1D* beta_two_prev = (TH1D*)like->Get("beta_two_prev");
      beta_two_prev->Scale(rates[i]/background_rate);
      
      TH1D* beta_three = (TH1D*)like->Get("beta_three");
      beta_three->Scale(rates[i]/background_rate);
      
      TH1D* beta_three_prev = (TH1D*)like->Get("beta_three_prev");
      beta_three_prev->Scale(rates[i]/background_rate);
      
      TH1D* beta_four = (TH1D*)like->Get("beta_four");
      beta_four->Scale(rates[i]/background_rate);
      
      TH1D* beta_four_prev = (TH1D*)like->Get("beta_four_prev");
      beta_four_prev->Scale(rates[i]/background_rate);
      
      TH1D* beta_five = (TH1D*)like->Get("beta_five");
      beta_five->Scale(rates[i]/background_rate);
      
      TH1D* beta_five_prev = (TH1D*)like->Get("beta_five_prev");
      beta_five_prev->Scale(rates[i]/background_rate);
      
      TH1D* beta_six = (TH1D*)like->Get("beta_six");
      beta_six->Scale(rates[i]/background_rate);
      
      TH1D* beta_six_prev = (TH1D*)like->Get("beta_six_prev");
      beta_six_prev->Scale(rates[i]/background_rate);
      
      TFile *like_scale = new TFile(Form("%s_scaled_pdfs.root",components[i].c_str()),"RECREATE");
      n100->Write();
      n100_prev->Write();
      dt_prev_us->Write();
      drPrevr->Write();
      closestPMT->Write();
      beta_one->Write();
      beta_one_prev->Write();
      beta_two->Write();
      beta_two_prev->Write();
      beta_three->Write();
      beta_three_prev->Write();
      beta_four->Write();
      beta_four_prev->Write();
      beta_five->Write();
      beta_five_prev->Write();
      beta_six->Write();
      beta_six_prev->Write();
      like->Close();
      like_scale->Close();
    }
  }
  
  //hadd signal and background components
    
  std::string sig_hadd = "hadd -f signal_pdfs.root";
  std::string bg_hadd = "hadd -f background_pdfs.root";

  for(int i=0;i<signal.size();i++){
    sig_hadd += " ";
    sig_hadd += signal[i];
    sig_hadd += "_scaled_pdfs.root";
  }
  
  for(int i=0;i<background.size();i++){
    bg_hadd += " ";
    bg_hadd += background[i];
    bg_hadd += "_scaled_pdfs.root";
  }
 
 printf("\nRunning command:\n%s\n\n",sig_hadd.c_str());
 system(sig_hadd.c_str());
 printf("\nRunning command:\n%s\n\n",bg_hadd.c_str());
 system(bg_hadd.c_str());
}
