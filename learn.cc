#include "learn.h"

bool make_pdf(std::vector<std::string> p)
{
  for( auto v : p )
    if( v == "--pdf" )
      return true;
  return false;
}

bool merge(std::vector<std::string> p)
{
  for( auto v : p )
    if( v == "--merge" )
      return true;
  return false;
}

bool likelihood(std::vector<std::string> p)
{
  for( auto v : p )
    if( v == "--like" )
      return true;
  return false;
}

bool classify(std::vector<std::string> p)
{
  for( auto v : p )
    if( v == "--eval" )
      return true;
  return false;
}

bool veto(std::vector<std::string> p)
{
  for( auto v : p )
    if( v == "--veto" )
      return true;
  return false;
}

int main(int argc, char** argv){

  std::string argv_str(argv[0]);
  std::string base = argv_str.substr(0, argv_str.find_last_of("/"));
  const char* path = base.c_str();

  std::vector<std::string> args(argv+1, argv+argc);

  if(make_pdf(args)){
    if(argc<3){
      printf("No input file or component entered\n");
      return -1;
    }
    else if(argc<4){
      printf("No component entered\n");
      return -1;
    }
    else{
      int nbins = 1000; //look at Freedman-Diaconis rule or use root n
      int dTank = 22000;
      int rPMT = 9000;
    
      const char* file = argv[2];
      const char* component = argv[3];
      if (argc > 4) {rPMT = std::stoi(argv[4]);}
      if (argc > 5) {dTank = std::stoi(argv[5]);}
      if (argc > 6) {nbins = std::stoi(argv[6]);}

      printf("\nMaking PDFs for %s\n\n\n",component);
  
      printf("rPMT = %i mm\n",rPMT);
      printf("dTank = %i mm\n",dTank);
      printf("nbins = %i\n\n\n",nbins);

      pdf_gen(file,component,nbins,1.2*dTank,rPMT);   
      } 
  }
  
  else if(merge(args)){
    const char* sig = "hartlepool";
    if (argc > 2) {sig = argv[2];}
  
    printf("\nScaling and merging PDFs\nSignal = %s\n\n\n",sig);

    merge_PDFs(sig);
  }

  else if(likelihood(args)){
    if(argc<3){
      printf("No input file or component entered\n");
      return -1;
    }
    else if(argc<4){
      printf("No component entered\n");
      return -1;
    }
    else{
      const char* file = argv[2];
      const char* component = argv[3];

      printf("\nMaking likelihoods for %s\n\n\n",component);

      likehood(file,component);
      }
  }

  else if(classify(args)){
    if(argc<3){
      printf("No input file or component entered\n");
      return -1;
    }
    else if(argc<4){
      printf("No tank size entered\n");
      return -1;
    }
    else{
      const char* file = argv[2];
      const char* component = argv[3];

      printf("\nApplying veto for %s\n\n\n",component);
  
      likehood_classify(file,component);
      }
  }

  else if(veto(args)){
    if(argc<3){
      printf("No input file or component entered\n");
      return -1;
    }
    else if(argc<4){
      printf("No tank size entered\n");
      return -1;
    }
    else if(argc<5){
      printf("No component entered\n");
      return -1;
    }
    else{
      const char* file = argv[2];
      const char* tank = argv[3];
      const char* component = argv[4];

      printf("\nEvaluating dwell time for %s in %s m tank\n\n\n",component,tank);
      const char* command = Form("python3 %s/veto.py %s %s %s",path,file,tank,component);
      std::system (command);
      }
  }
  
  else{
    printf("\n\n\nWelcome to LEARN (Likelihood Event Analysis of Reactor Neutrinos)\n\n\n");
    printf("There are four stages to this analysis\n\n");
    printf("1) Creating PDFs\nDo ./learn --pdf [input file] [component] [nbins:default 1000] [dTank: 22000 mm]\n\n");
    printf("2) Scaling and merging PDFs\nDo ./learn --merge [signal:default hartlepool]\n\n");
    printf("3) Creating likelihoods\nDo ./learn --like [input file] [component]\n\n");
    printf("4) Evaluating likelihoods and rates\nDo ./learn --eval [input file] [component]\n\n");
    printf("5) Data reduction\nNot currently integrated into LEARN\n\n");
    printf("6) Evaluating dwell times\nDo ./learn --veto [results csv file] [tank size] [component]\n\n");
    
    std::vector<std::string> components;
    std::vector<double> rates;
    std::vector<std::string> line_values;
    std::ifstream theFile ("rates.csv");
    if(!theFile.is_open()){
      printf("File rates.csv does not exist, please copy to working directory from learn to see list of components and rates\n");
      return -1;
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
    
    printf("Component options and rates are set in rates.csv\nThey are currently defined as:\n");
    for (int i = 0; i < components.size(); i++) {
      printf("%s: %.4e per second\n",components[i].c_str(),rates[i]);
    }
  
    
  }

}
