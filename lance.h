#ifndef LANCE_H
#define LANCE_H

#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TLeaf.h>
#include <sstream>
#include <fstream>

void pdf_gen(const char* file, const char* component, int nbins, int dTank);
void merge_PDFs(const char* sig);
void likehood_classify(const char* infile, const char* component/*, int nbins*/);
void likehood(const char* infile, const char* component/*, int nbins*/);

#endif
