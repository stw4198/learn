#include<stdio.h>
#include<string>
#include<cstring>
#include<vector>
#include<algorithm>
#include<iostream>

std::vector<const char*> input_select(int argc,char** argv)
{
    std::vector<const char*> inputs;
    std::vector<const char*> func;
    std::vector<const char*> in;
    // input options
    std::vector<const char*> functions = {"--help","--pdf","--merge","--like","--eval","--energy","--veto"};
    std::vector<const char*> input_options = {"file","component","signal","rPMT","dTank","nbins","nX","file path"};
    std::vector<const char*> input_flags = {"-f","-c","-s","-rpmt","-dtank","-nbins","-nx","-path"};
    const char* file = ""; const char* component = ""; const char* signal = "";
    const char* rPMT = "9000"; const char* dTank = "22"; const char* nbins = "1000"; const char* nx = "100"; const char* path =".";
    //printf("File = %s\nComponent = %s\nSignal = %s\nrPMT = %s mm\ndTank = %s m\nnbins = %s\nnX = %s ns\nfile path = %s\n",file,component,signal,rPMT,dTank,nbins,nx,path);
    // check for inputs
    inputs.push_back(""); inputs.push_back(file); inputs.push_back(component); inputs.push_back(signal); inputs.push_back(rPMT);
    inputs.push_back(dTank); inputs.push_back(nbins); inputs.push_back(nx); inputs.push_back(path);
    if(argc==1){
        printf("No Inputs\nPlease select one function. Options are\n");
        for(int i=0;i<functions.size();i++){printf("%s\n",functions[i]);}
        printf("Input options are\n");
        for(int i=0;i<input_options.size();i++){printf("%s: %s\n",input_flags[i],input_options[i]);}
        return inputs;
    }
    else if(argc>1)
    {
        // separate function input from other inputs
        for(int i=1;i<argc;i++){
            if(strstr(argv[i],"--")){
                func.push_back(argv[i]);
            }
            else{
                in.push_back(argv[i]);
            }
        }
        // check number of functions called
        if(func.size()>1){
            printf("Multiple functions selected. Please select one (using --)\nOptions are:\n");
            for(int i=0;i<functions.size();i++){printf("%s\n",functions[i]);}
            return inputs;
        }
        else if(func.size()<1){
            printf("No function selected. Please select one (using --)\nOptions are:\n");
            //printf("Function input %s not recognised\nOptions are:\n",func[0]);
            for(int i=0;i<functions.size();i++){printf("%s\n",functions[i]);}
            return inputs;
        }
        // check function is valid option
        int func_found = 0;
        for(int i=0;i<functions.size();i++){
            if(strstr(functions[i],func[0]) && strlen(functions[i])==strlen(func[0])){
                func_found++;
            }
        }
        if(func_found==0){
            printf("Function input %s not recognised\nOptions are:\n",func[0]);
            for(int i=0;i<functions.size();i++){printf("%s\n",functions[i]);}
            return inputs;
        }
        else{
            //printf("%s function selected\n",func[0]);
            // separate input flags and values
            for(int i=0;i<in.size();i++){
                if(!strstr(in[i],"-")){
                    continue;
                }
                else if(!strcmp(in[i],"-f")){
                    //printf("Input file = %s\n",in[i+1]);
                    file = in[i+1];
                }
                else if(!strcmp(in[i],"-c")){
                    //printf("Component = %s\n",in[i+1]);
                    component = in[i+1];
                }
                else if(!strcmp(in[i],"-s")){
                    //printf("Signal = %s\n",in[i+1]);
                    signal = in[i+1];
                }
                else if(!strcmp(in[i],"-rpmt")){
                    //printf("rPMT = %s mm\n",in[i+1]);
                    rPMT = in[i+1];
                }
                else if(!strcmp(in[i],"-dtank")){
                    //printf("dTank = %s m\n",in[i+1]);
                    dTank = in[i+1];
                }
                else if(!strcmp(in[i],"-nbins")){
                    //printf("nbins = %s\n",in[i+1]);
                    nbins = in[i+1];
                }
                else if(!strcmp(in[i],"-nx")){
                    //printf("nx = %s\n",in[i+1]);
                    nx = in[i+1];
                }
                else if(!strcmp(in[i],"-path")){
                    //printf("File path = %s\n",in[i+1]);
                    path = in[i+1];
                }
                else{
                    printf("Input %s not recognised\n",in[i]);
                }
            }
        }
    }

    // if(!strcmp(file,"")){
    //     printf("No file input\nUse -f [file]\n");
    //     return inputs;
    // }
    // else if(strcmp(signal,"")){
    //     printf("No file input\nUse -f [file]\n");
    //     return 0;
    // }

    //printf("\n\nValues:\nFunction = %s\nFile = %s\nComponent = %s\nSignal = %s\nrPMT = %s mm\ndTank = %s m\nnbins = %s\nnX = %s ns\nfile path = %s\n",func[0],file,component,signal,rPMT,dTank,nbins,nx,path);
    inputs.clear();
    inputs.push_back(func[0]); inputs.push_back(file); inputs.push_back(component); inputs.push_back(signal); inputs.push_back(rPMT);
    inputs.push_back(dTank); inputs.push_back(nbins); inputs.push_back(nx); inputs.push_back(path);
    //printf("\n\nValues:\nFunction = %s\nFile = %s\nComponent = %s\nSignal = %s\nrPMT = %s mm\ndTank = %s m\nnbins = %s\nnX = %s ns\nfile path = %s\n",func[0],file,component,signal,rPMT,dTank,nbins,nx,path);
    return inputs;
}

// int main(int argc,char** argv){
//     std::vector<const char*> inputs = input_select(argc,argv);
//     const char* function = inputs[0];
//     const char* file = inputs[1];
//     const char* component = inputs[2];
//     const char* signal = inputs[3];
//     const char* rPMT = inputs[4];
//     const char* dTank = inputs[5];
//     const char* nbins = inputs[6];
//     const char* nx = inputs[7];
//     const char* file_path = inputs[8];

//     printf("Inputs:\nFunction = %s\nFile = %s\nComponent = %s\nSignal = %s\nrPMT = %s mm\ndTank = %s m\nnbins = %s\nnX = %s ns\nfile path = %s\n",function,file,component,signal,rPMT,dTank,nbins,nx,file_path);
//     if(!strcmp(file,"")){
//         printf("No file input\nUse -f [file]\n");
//         return 0;
//     }
//     return 0;
// }