#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
#include <TColor.h>
#include <math.h>


void stack_like(){

    //TFile* f1 = new TFile("../JA_data/likelihood_ratio_3.root");
  
  TString folder = "../likelihood_test/";
  
  TFile *big = new TFile(/*folder+*/"big_likelihoods.root");
  TFile *small = new TFile(/*folder+*/"small_likelihoods.root");
  TFile *singles = new TFile(/*folder+*/"singles_likelihoods.root");
  TFile *geo = new TFile(/*folder+*/"geo_likelihoods.root");
  TFile *world = new TFile(/*folder+*/"world_likelihoods.root");
  TFile *li9 = new TFile(/*folder+*/"li9_likelihoods.root");
  TFile *n17 = new TFile(/*folder+*/"n17_likelihoods.root");
  TFile *fn = new TFile("fn_likelihoods.root");
  
  TH1D * ratio_b = (TH1D*)big->Get("ratio_like");
  TH1D * ratio_s = (TH1D*)small->Get("ratio_like");
  TH1D * ratio_c = (TH1D*)singles->Get("ratio_like");
  TH1D * ratio_g = (TH1D*)geo->Get("ratio_like");
  TH1D * ratio_w = (TH1D*)world->Get("ratio_like");
  TH1D * ratio_n = (TH1D*)n17->Get("ratio_like");
  TH1D * ratio_l = (TH1D*)li9->Get("ratio_like");
  TH1F * ratio_f = (TH1F*)fn->Get("ratio_like");


  THStack * stack = new THStack("stack","log(likelihood) ratio");
  TLegend *legend = new TLegend(0.85,0.5,0.98,0.98);
  ratio_b->SetLineColor(2);
  ratio_s->SetLineColor(3);
  ratio_c->SetLineColor(1);
  ratio_g->SetLineColor(4);
  ratio_w->SetLineColor(5);
  ratio_n->SetLineColor(6);
  ratio_l->SetLineColor(7);
  ratio_f->SetLineColor(8);
  ratio_b->SetLineWidth(2);
  ratio_s->SetLineWidth(2);
  ratio_c->SetLineWidth(2);
  ratio_g->SetLineWidth(2);
  ratio_w->SetLineWidth(2);
  ratio_n->SetLineWidth(2);
  ratio_l->SetLineWidth(2);
  ratio_f->SetLineWidth(2);
  legend->AddEntry(ratio_b,"Big Hartlepool");
  legend->AddEntry(ratio_s,"Small Hartlepool");
  legend->AddEntry(ratio_c,"Singles");
  legend->AddEntry(ratio_w,"World");
  legend->AddEntry(ratio_g,"Geoneutrinos");
  legend->AddEntry(ratio_n,"Nitrogen - 17");
  legend->AddEntry(ratio_l,"Lithium - 9");
  legend->AddEntry(ratio_f,"Fast Neutrons");
  stack->Add(ratio_c);
  stack->Add(ratio_g);
  stack->Add(ratio_w);
  stack->Add(ratio_n);
  stack->Add(ratio_l);
  stack->Add(ratio_s);
  stack->Add(ratio_b);
  stack->Add(ratio_f);
  TCanvas * c1 = new TCanvas("c1");
  int binmax = ratio_c->FindLastBinAbove();//GetMaximumBin();
  double max_Lr = ratio_c->GetXaxis()->GetBinCenter(binmax);
  printf("Max Lr for singles = %f\n",max_Lr);
  TLine * l = new TLine(max_Lr,0,max_Lr,0.2105);
  stack->Draw("NOSTACK HIST");
  stack->GetXaxis()->SetTitle("\\mathscr{L}_{R}");
  stack->GetYaxis()->SetTitle("Normalised events");
  stack->GetYaxis()->SetTitleOffset(1.3);
  l->SetLineWidth(3);
  l->Draw();
  legend->Draw();
  c1->SaveAs(/*folder+*/"likelihood_ratio.png");


}
