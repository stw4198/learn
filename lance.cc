//#include "pdf_gen.cc"
//#include "merge_PDFs.cc"
//#include "likelihood.cc"
//#include "likelihood_classify.cc"

#include "lance.h"

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

int main(int argc, char** argv){

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
    
      const char* file = argv[2];
      const char* component = argv[3];
      if (argc > 4) {nbins = std::stoi(argv[4]);}
      if (argc > 5) {dTank = std::stoi(argv[5]);}

      printf("\nMaking PDFs for %s\n\n\n",component);
  
      printf("nbins = %i\n",nbins);
      printf("dTank = %i mm\n\n\n",dTank);

      pdf_gen(file,component,nbins,dTank);   
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
      printf("No component entered\n");
      return -1;
    }
    else{
      const char* file = argv[2];
      const char* component = argv[3];

      printf("\nEvaluating likelihoods for %s\n\n\n",component);
  
      likehood_classify(file,component);
      }
  }
  
  else{
    printf("\n\n\nWelcome to LANCE (Likelihood analysis of AntiNeutrino Coincidence Events)\n\n\n");
    printf("There are four stages to this analysis\n\n");
    printf("1) Creating PDFs\nDo ./lance --pdf [input file] [component] [nbins:default 1000] [dTank: 22000 mm]\n\n");
    printf("2) Scaling and merging PDFs\nDo ./lance --merge [signal:default hartlepool]\n\n");
    printf("3) Creating likelihoods\nDo ./lance --like [input file] [component]\n\n");
    printf("4) Evaluating likelihoods and rates\nDo ./lance --eval [input file] [component]\n\n");
    printf("\nComponent options are:\nbig\nsmall\nworld\ngeo\nli9\nn17\nsingles\nheysham\nheysham2\ntorness\n");
  }

}
