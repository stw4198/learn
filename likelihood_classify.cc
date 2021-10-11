#include "learn.h"

void likehood_classify(const char* infile, const char* component/*, int nbins*/){

  TFile *f = new TFile(infile);
  if(!f->IsOpen()){
    printf("File %s does not exist.\n",infile);
    return;
  }
  TTree *t_in = (TTree*)f->Get("data");
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
  
  int nentries = t_in->GetEntries();
  printf("There are %i reconstructed entries in %s\n",nentries,infile);

  int nbins = sqrt(nentries);
  
  TFile *output = new TFile(Form("%s_classified.root",component),"RECREATE");
  TTree *data = new TTree("data","low-energy detector triggered events");
  TTree *run_summary=new TTree("runSummary","mc run summary");

  double innerPE;
  double n9,n9_prev,nOff,n100,n100_prev;
  double good_pos,good_pos_prev;
  double closestPMT,closestPMT_prev;
  double drPrevr,dt_prev_us;
  int inner_hit,inner_hit_prev;
  double x,y,z,t;
  double u,v,w;
  double beta_one,beta_one_prev;
  double beta_two,beta_two_prev;
  double beta_three,beta_three_prev;
  double beta_four,beta_four_prev;
  double beta_five,beta_five_prev;
  double beta_six,beta_six_prev;
  double mc_energy;
  int mcid,subid;

  data->Branch("inner_hit",&inner_hit,"inner_hit/I");//inner detector    
  data->Branch("inner_hit_prev",&inner_hit_prev,"inner_hit_prev/I");//inner detector
  data->Branch("innerPE",&innerPE,"innerPE/D");
  data->Branch("n9",&n9,"n9/D");
  data->Branch("n9_prev",&n9_prev,"n9_prev/D");
  data->Branch("nOff",&nOff,"nOff/D");
  data->Branch("n100",&n100,"n100/D");
  data->Branch("n100_prev",&n100_prev,"n100_prev/D");
  data->Branch("good_pos",&good_pos,"good_pos/D");
  data->Branch("good_pos_prev",&good_pos_prev,"good_pos_prev/D");
  data->Branch("closestPMT",&closestPMT,"closestPMT/D");
  data->Branch("closestPMT_prev",&closestPMT_prev,"closestPMT_prev/D");
  data->Branch("drPrevr",&drPrevr,"drPrevr/D");
  data->Branch("dt_prev_us",&dt_prev_us,"dt_prev_us/D");
  data->Branch("x",&x,"x/D");
  data->Branch("y",&y,"y/D");
  data->Branch("z",&z,"z/D");
  data->Branch("t",&t,"t/D");
  data->Branch("u",&u,"u/D");
  data->Branch("v",&v,"v/D");
  data->Branch("w",&w,"w/D");
  data->Branch("beta_one",&beta_one,"beta_one/D"); 
  data->Branch("beta_two",&beta_two,"beta_two/D"); 
  data->Branch("beta_three",&beta_three,"beta_three/D"); 
  data->Branch("beta_four",&beta_four,"beta_four/D"); 
  data->Branch("beta_five",&beta_five,"beta_five/D"); 
  data->Branch("beta_six",&beta_six,"beta_six/D"); 
  data->Branch("beta_one_prev",&beta_one_prev,"beta_one_prev/D"); 
  data->Branch("beta_two_prev",&beta_two_prev,"beta_two_prev/D"); 
  data->Branch("beta_three_prev",&beta_three_prev,"beta_three_prev/D"); 
  data->Branch("beta_four_prev",&beta_four_prev,"beta_four_prev/D"); 
  data->Branch("beta_five_prev",&beta_five_prev,"beta_five_prev/D"); 
  data->Branch("beta_six_prev",&beta_six_prev,"beta_six_prev/D");
  data->Branch("mcid",&mcid,"mcid/I");
  data->Branch("subid",&subid,"subid/I");
  data->Branch("mc_energy",&mc_energy,"mc_energy/D");
  run_summary->Branch("nevents",&nevents,"nevents/I");

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
  
  TFile *singles_like = new TFile("singles_likelihoods.root");
  if(!singles_like->IsOpen()){
    printf("File singles_likelihoods.root does not exist.\n");
    return;
  }
  TH1D* ratio_like = (TH1D*)singles_like->Get("ratio_like");

  int binmax = ratio_like->FindLastBinAbove();
  double max_Lr = ratio_like->GetXaxis()->GetBinCenter(binmax);
  //int thresh = std::ceil(max_Lr);
  printf("Max Lr for singles = %f\n\n\n",max_Lr);//Setting Lr threshold to %i\n\n\n",max_Lr,thresh);
  
  for(int i=0; i<nentries; i++){
    t_in->GetEntry(i);
    if (i%100000==0){
      printf("Evaluating likelihoods: Event %d of %d\n",i,nentries);
    }
    if (t_in->GetLeaf("n100")->GetValue(0) > 0 and t_in->GetLeaf("closestPMT")->GetValue(0) > -499) {
      double n100_sig_bin = n100_signal->GetXaxis()->FindBin(t_in->GetLeaf("n100")->GetValue(0));
      double n100_sig_prob = n100_signal->GetBinContent(n100_sig_bin);
      double n100_bg_bin = n100_background->GetXaxis()->FindBin(t_in->GetLeaf("n100")->GetValue(0));
      double n100_bg_prob = n100_background->GetBinContent(n100_bg_bin);
      
      double n100_prev_sig_bin = n100_prev_signal->GetXaxis()->FindBin(t_in->GetLeaf("n100_prev")->GetValue(0));
      double n100_prev_sig_prob = n100_prev_signal->GetBinContent(n100_prev_sig_bin);
      double n100_prev_bg_bin = n100_prev_background->GetXaxis()->FindBin(t_in->GetLeaf("n100_prev")->GetValue(0));
      double n100_prev_bg_prob = n100_prev_background->GetBinContent(n100_prev_bg_bin);
      
      double dt_prev_us_sig_bin = dt_prev_us_signal->GetXaxis()->FindBin(t_in->GetLeaf("dt_prev_us")->GetValue(0));
      double dt_prev_us_sig_prob = dt_prev_us_signal->GetBinContent(dt_prev_us_sig_bin);
      double dt_prev_us_bg_bin = dt_prev_us_background->GetXaxis()->FindBin(t_in->GetLeaf("dt_prev_us")->GetValue(0));
      double dt_prev_us_bg_prob = dt_prev_us_background->GetBinContent(dt_prev_us_bg_bin);
      
      double drPrevr_sig_bin = drPrevr_signal->GetXaxis()->FindBin(t_in->GetLeaf("drPrevr")->GetValue(0));
      double drPrevr_sig_prob = drPrevr_signal->GetBinContent(drPrevr_sig_bin);
      double drPrevr_bg_bin = drPrevr_background->GetXaxis()->FindBin(t_in->GetLeaf("drPrevr")->GetValue(0));
      double drPrevr_bg_prob = drPrevr_background->GetBinContent(drPrevr_bg_bin);
      
      double closestPMT_sig_bin = closestPMT_signal->GetXaxis()->FindBin(t_in->GetLeaf("closestPMT")->GetValue(0));
      double closestPMT_sig_prob = closestPMT_signal->GetBinContent(closestPMT_sig_bin);
      double closestPMT_bg_bin = closestPMT_background->GetXaxis()->FindBin(t_in->GetLeaf("closestPMT")->GetValue(0));
      double closestPMT_bg_prob = closestPMT_background->GetBinContent(closestPMT_bg_bin);
      
      double sig_like = log(n100_sig_prob*n100_prev_sig_prob*dt_prev_us_sig_prob*drPrevr_sig_prob*closestPMT_sig_prob);
      double bg_like = log(n100_bg_prob*n100_prev_bg_prob*dt_prev_us_bg_prob*drPrevr_bg_prob*closestPMT_bg_prob);
      double r_like = sig_like-bg_like;

      if((sig_like != 0 && bg_like == 0) || (r_like>max_Lr)){
        x = t_in->GetLeaf("x")->GetValue(0);
        y = t_in->GetLeaf("y")->GetValue(0);
        z = t_in->GetLeaf("z")->GetValue(0);
        u = t_in->GetLeaf("u")->GetValue(0);
        v = t_in->GetLeaf("v")->GetValue(0);
        w = t_in->GetLeaf("w")->GetValue(0);
        t = t_in->GetLeaf("t")->GetValue(0);
        innerPE = t_in->GetLeaf("innerPE")->GetValue(0);
        n9 = t_in->GetLeaf("n9")->GetValue(0);
        n9_prev = t_in->GetLeaf("n9_prev")->GetValue(0);
        n100 = t_in->GetLeaf("n100")->GetValue(0);
        n100_prev = t_in->GetLeaf("n100_prev")->GetValue(0);
        nOff = t_in->GetLeaf("nOff")->GetValue(0);
        good_pos = t_in->GetLeaf("good_pos")->GetValue(0);
        good_pos_prev = t_in->GetLeaf("good_pos_prev")->GetValue(0);
        closestPMT = t_in->GetLeaf("closestPMT")->GetValue(0);
        closestPMT_prev = t_in->GetLeaf("closestPMT_prev")->GetValue(0);
        drPrevr = t_in->GetLeaf("drPrevr")->GetValue(0);
        dt_prev_us = t_in->GetLeaf("dt_prev_us")->GetValue(0);
        inner_hit = t_in->GetLeaf("inner_hit")->GetValue(0);
        inner_hit_prev = t_in->GetLeaf("inner_hit_prev")->GetValue(0);
        beta_one = t_in->GetLeaf("beta_one")->GetValue(0);
        beta_one_prev = t_in->GetLeaf("beta_one_prev")->GetValue(0);
        beta_two = t_in->GetLeaf("beta_two")->GetValue(0);
        beta_two_prev = t_in->GetLeaf("beta_two_prev")->GetValue(0);
        beta_three = t_in->GetLeaf("beta_three")->GetValue(0);
        beta_three_prev = t_in->GetLeaf("beta_three_prev")->GetValue(0);
        beta_four = t_in->GetLeaf("beta_four")->GetValue(0);
        beta_four_prev = t_in->GetLeaf("beta_four_prev")->GetValue(0);
        beta_five = t_in->GetLeaf("beta_five")->GetValue(0);
        beta_five_prev = t_in->GetLeaf("beta_five_prev")->GetValue(0);
        beta_six = t_in->GetLeaf("beta_six")->GetValue(0);
        beta_six_prev = t_in->GetLeaf("beta_six_prev")->GetValue(0);
        mc_energy = t_in->GetLeaf("mc_energy")->GetValue(0);
        subid = t_in->GetLeaf("subid")->GetValue(0);
        mcid = t_in->GetLeaf("mcid")->GetValue(0);
        data->Fill();
      }
      else{
        //reject event
      }
    }
  }
  
  output->cd();
  data->Write();
  run_summary->Fill();
  run_summary->Write();
  singles_like->Close();
  f->Close();
  
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
  
  double rate;
  
  for (int i = 0;i<components.size();i++){
    if(strncmp(component, components[i].c_str(),strlen(component))==0){
      rate = rates[i];
    }
  }

  printf("\n\n\nComponent = %s\n\n\n",component);
  printf("Expected interaction rate = %.9e per second\n",rate);
  double det_eff = data->GetEntries()/double(nevents);
  printf("%lli kept events\n",data->GetEntries());
  printf("%i MC events\n",nevents);
  printf("%i MC events\n",2*nevents);
  double det_rate = det_eff*rate;
  printf("Detection rate = %e per second if singles\n",det_rate);
  printf("Detection rate = %e per second if IBD or correlated\n",0.5*det_rate);
  printf("Detection rate = %e per day if singles\n",det_rate*86400);
  printf("Detection rate = %e per day if IBD or correlated\n",0.5*86400*det_rate);
  
  output->Close();

}
