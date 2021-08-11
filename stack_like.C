#include <TCanvas.h>
#include <TFile.h>
#include <TString.h>
#include <TROOT.h>
#include <TH1D.h>
#include <THStack.h>
#include <TLegend.h>
#include <TLine.h>
#include <TColor.h>
#include <math.h>


void stack_like(){

  //TFile *h1 = new TFile("hartlepool_1_likelihoods.root");
  //TFile *h2 = new TFile("hartlepool_2_likelihoods.root");
  //TFile *singles = new TFile("singles_likelihoods.root");
  TFile *geo = new TFile("geo_likelihoods.root");
  TFile *world = new TFile("world_likelihoods.root");
  TFile *li9 = new TFile("li9_likelihoods.root");
  TFile *n17 = new TFile("n17_likelihoods.root");
  //TFile *fn = new TFile("fn_likelihoods.root");
  TFile *hey = new TFile("heysham_2_likelihoods.root");
  TFile *tor = new TFile("torness_full_likelihoods.root");
  
  //TH1D * ratio_b = (TH1D*)h1->Get("ratio_like");
  //TH1D * ratio_s = (TH1D*)h2->Get("ratio_like");
  //TH1D * ratio_c = (TH1D*)singles->Get("ratio_like");
  TH1D * ratio_g = (TH1D*)geo->Get("ratio_like");
  TH1D * ratio_w = (TH1D*)world->Get("ratio_like");
  TH1D * ratio_n = (TH1D*)n17->Get("ratio_like");
  TH1D * ratio_l = (TH1D*)li9->Get("ratio_like");
  //TH1D * ratio_f = (TH1D*)fn->Get("ratio_like");
  TH1D * ratio_h = (TH1D*)hey->Get("ratio_like");
  TH1D * ratio_t = (TH1D*)tor->Get("ratio_like");
  
  //ratio_b->Scale(1./ratio_b->GetMaximum());
  //ratio_s->Scale(1./ratio_s->GetMaximum());
  //ratio_c->Scale(1./ratio_c->GetMaximum());
  ratio_g->Scale(1./ratio_g->GetMaximum());
  ratio_w->Scale(1./ratio_w->GetMaximum());
  ratio_n->Scale(1./ratio_n->GetMaximum());
  ratio_l->Scale(1./ratio_l->GetMaximum());
  //ratio_f->Scale(1./ratio_f->GetMaximum());
  ratio_h->Scale(1./ratio_h->GetMaximum());
  ratio_t->Scale(1./ratio_t->GetMaximum());

  THStack * stack = new THStack("stack","log(likelihood) ratio");
  TLegend *legend = new TLegend(0.85,0.5,0.98,0.98);
  
  //ratio_b->SetLineColor(2);
  //ratio_s->SetLineColor(3);
  //ratio_c->SetLineColor(1);
  ratio_g->SetLineColor(4);
  ratio_w->SetLineColor(5);
  ratio_n->SetLineColor(6);
  ratio_l->SetLineColor(7);
  //ratio_f->SetLineColor(8);
  ratio_h->SetLineColor(28);
  ratio_t->SetLineColor(11);
  
  //ratio_b->SetLineWidth(2);
  //ratio_s->SetLineWidth(2);
  //ratio_c->SetLineWidth(2);
  ratio_g->SetLineWidth(2);
  ratio_w->SetLineWidth(2);
  ratio_n->SetLineWidth(2);
  ratio_l->SetLineWidth(2);
  //ratio_f->SetLineWidth(2);
  ratio_h->SetLineWidth(2);
  ratio_t->SetLineWidth(2);
  
  //legend->AddEntry(ratio_b,"Hartlepool 1");
  //legend->AddEntry(ratio_s,"Hartlepool 2");
  //legend->AddEntry(ratio_c,"Singles");
  legend->AddEntry(ratio_w,"World");
  legend->AddEntry(ratio_g,"Geoneutrinos");
  legend->AddEntry(ratio_n,"Nitrogen - 17");
  legend->AddEntry(ratio_l,"Lithium - 9");
  //legend->AddEntry(ratio_f,"Fast Neutrons");
  legend->AddEntry(ratio_h,"Heysham");
  legend->AddEntry(ratio_t,"Torness");
  
  //stack->Add(ratio_c);
  stack->Add(ratio_g);
  stack->Add(ratio_w);
  stack->Add(ratio_n);
  stack->Add(ratio_l);
  //stack->Add(ratio_s);
  //stack->Add(ratio_b);
  //stack->Add(ratio_f);
  stack->Add(ratio_h);
  stack->Add(ratio_t);
  
  TCanvas * c1 = new TCanvas("c1");
  //int binmax = ratio_c->FindLastBinAbove();
  //double max_Lr = ratio_c->GetXaxis()->GetBinCenter(binmax);
  //printf("Max Lr for singles = %f\n",max_Lr);
  //TLine * l = new TLine(max_Lr,0,max_Lr,1);
  stack->Draw("NOSTACK HIST");
  stack->GetXaxis()->SetTitle("\\mathscr{L}_{R}");
  stack->GetYaxis()->SetTitle("Normalised events");
  stack->GetYaxis()->SetTitleOffset(1.3);
  //l->SetLineWidth(3);
  //l->Draw();
  legend->Draw();
  c1->SaveAs("likelihood_ratio.png");


}
