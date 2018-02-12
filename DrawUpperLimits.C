#include <TROOT.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TFile.h"
#include "TLatex.h"
//#include "TDRStyle.h"

void DrawUpperLimits(TString LimitType) 
{

Double_t t1=0.74,t2=0.96;
Double_t t3=0.6,  t4=0.87;
Double_t t5=t3,  t6=0.81;

   gStyle -> SetTitleSize(0.045,"X");
   gStyle -> SetTitleSize(0.045,"Y");
   gStyle -> SetLabelSize(0.04,"X");
   gStyle -> SetLabelSize(0.045,"Y");
   gStyle -> SetTitleOffset(1.2,"Y");
   gStyle -> SetStripDecimals(kFALSE);
   gStyle -> SetPadTickX(1);
   gStyle -> SetPadTickY(1);
   gStyle -> SetOptTitle(0);
   gStyle -> SetOptFit(0);
   gStyle -> SetOptStat(0);
   gStyle -> SetStatX(0.64);
   gStyle -> SetStatY(0.9);
   gStyle -> SetStatY(0.9);
   gStyle -> SetStatW(0.3);
   gStyle -> SetStatH(0.15);


for(Int_t obji=6; obji<7 ;obji++){

TString nobj;
stringstream nj; nj << obji;
nobj=nj.str();


int wd=10;
cout.setf(ios::fixed);
TString inputfile;

if(LimitType=="Asymptotic"){inputfile="OutputLogFiles/asympLimit_mul"+nobj+".log";}
else if(LimitType=="FullCLs"){inputfile="MIlimit_N"+nobj+".txt";}
cout << inputfile<<endl;
//else{ErrorMessage();}
ifstream infile(inputfile);
ifstream myfile(inputfile);
int nlines = 0;
string line;
if (myfile.is_open()){while(!myfile.eof()){ getline(myfile,line); nlines++; } myfile.close();}
cout<<"nlines="<<nlines-1<<endl;
const int  n = nlines-1;
Double_t st[n], est[n],obsL[n], expL[n], m1s[n], p1s[n], m2s[n], p2s[n];   
cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout<<"@  Multiplicity >= "<<obji<<" @"<<endl;
cout<<"@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout<<"-------------------------------------------------------------------------"<<endl;
cout<<" N      STmin    Obs_UL	   -2Sig    -1Sig      Exp_UL   +1Sig     +2Sig "<<endl;
cout<<"-------------------------------------------------------------------------"<<endl;
if (infile.is_open())
    {
for(Int_t i = 0; i < n; i++)
      {
   infile >> st[i] >> obsL[i] >> m2s[i] >> m1s[i] >> expL[i] >> p1s[i] >> p2s[i];
   cout <<setprecision(0)<<obji<<setw(wd)<<st[i]<<setprecision(1)<<setprecision(2)<<setw(wd)<< obsL[i]<<setw(wd)<<m2s[i]<<setw(wd)<<m1s[i]<<setw(wd)<<expL[i]<<setw(wd)<<p1s[i]<<setw(wd)<<p2s[i]<<endl;
     est[i]=0.;
     
      double pb =2.26;
      st[i]  = st[i]/1000;
      m1s[i] = (expL[i] - m1s[i])/pb;
      m2s[i] = (expL[i] - m2s[i])/pb;
      p2s[i] = (p2s[i] - expL[i])/pb;
      p1s[i] = (p1s[i] - expL[i])/pb;
      obsL[i]= obsL[i]/pb;
      expL[i]= expL[i]/pb;

      }
   infile.close();
    }
//TStyle *tdrStyle=setTDRStyle();
//tdrStyle->cd();
//tdrStyle->SetPadLeftMargin(0.14);
//tdrStyle->SetTitleYOffset(1.6);

TCanvas * c1 = new TCanvas("c1"," Canvas ", 0,0,700,700);
 c1->SetLeftMargin(0.15);
 c1->SetRightMargin(0.04);
 c1->SetTopMargin(0.06);
 c1->SetBottomMargin(0.13);
 TGraphAsymmErrors *gr1s= new TGraphAsymmErrors(n,st,expL,est,est,m1s,p1s);
 TGraphAsymmErrors *gr2s= new TGraphAsymmErrors(n,st,expL,est,est,m2s,p2s);
 TGraphAsymmErrors *grex= new TGraphAsymmErrors(n,st,expL,est,est,est,est);
 TGraphAsymmErrors *grob= new TGraphAsymmErrors(n,st,obsL,est,est,est,est);


  gr2s->GetXaxis()->SetTitle("S_{T}^{min} [TeV]");
  gr2s->GetYaxis()->SetTitle("#sigma ( S_{T} > S_{T}^{min} ) #times A [fb]");
  gr2s->GetXaxis()->SetTitleOffset(1.2);
  gr2s->GetYaxis()->SetTitleOffset(1.50);
  gr2s->GetYaxis()->SetRangeUser(0.1,8000);
  gr2s->SetLineStyle(2);
  gr2s->SetLineWidth(2);
  gr2s -> GetXaxis()->SetRangeUser(1.8,8.2);
  //gr2s -> GetXaxis()->CenterTitle();
  //gr2s -> GetYaxis()->CenterTitle();
  gr1s->SetLineStyle(2);
  gr1s->SetLineWidth(2);
  gr2s->SetFillColor(kYellow);
  gr1s->SetFillColor(kGreen);
  grob->SetLineStyle(1);
  grob->SetLineColor(1);
  grob->SetLineWidth(2);
  grob->SetMarkerStyle(20);
  grob->SetMarkerSize(0.7);
  grex->SetLineStyle(2);
  grex->SetLineWidth(2);
  grex->SetLineColor(1);
  gr2s->DrawClone("E3AL");
  gr1s->DrawClone("E3Same");
  grob->DrawClone("PLSame");
  grex->DrawClone("LSame");
float tsize=0.035;
  TLatex *tex = new TLatex(t1,t2,"2.3 fb^{-1} (13 TeV)");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(tsize);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(t3,t4,"Upper Limits, 95% CL");
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(tsize);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(t5,t6,"Multiplicity, N #geq "+nobj);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(tsize);
  tex->SetLineWidth(2);
  tex->Draw();
  tex = new TLatex(0.2,t4,"CMS");
  tex->SetNDC();
  tex->SetTextFont(62);
  tex->SetTextSize(0.04);
  tex->SetLineWidth(2);
  tex->Draw();
  TLegend* leg = new TLegend(0.5922819,0.5933682,0.8724832,0.7905759);
//0.5419463,0.591623,0.8221477,0.7888307);
  leg->AddEntry(  grob, "Observed", "lp");
  leg->AddEntry(  grex, "Expected", "l");
  leg->AddEntry(  gr1s, "Expected #pm 1 #sigma", "lf");
  leg->AddEntry(  gr2s, "Expected #pm 2 #sigma", "lf");
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(tsize);
  leg->SetBorderSize(0);
  leg->Draw("");
  c1 -> SetLogy(); 
  c1->SaveAs("Plots/"+LimitType+"/MILimit_Mul"+nobj+"_"+LimitType+".pdf");
  }
}
//void DrawUpperLimits(){ ErrorMessage();} 
//void ErrorMessage(){
//  cout<<"\033[1;31m ERROR!!!, please run this code with one of following two options:\033[0m"<<endl;
//  cout<<"\033[1;32m a). root 'DrawUpperLimits.C(\"Asymptotic\")'\033[0m"<<endl;
//  cout<<"\033[1;32m b). root 'DrawUpperLimits.C(\"FullCLs\")'\033[0m"<<endl;
//  exit();
//} 
