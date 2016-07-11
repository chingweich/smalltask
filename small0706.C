#include <TLegend.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TH1F.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"
#include "TStyle.h"
#include "untuplizer.h"
#include <TClonesArray.h>
#include <fstream>
#include <cmath>
#include <TSystem.h>
#include <string>
#include <sstream>
#include "../HHbbbbAnalyzer/setNCUStyle.C"
#include<TH2.h>
#include "TLine.h"
#include "TF1.h"
#include"TGraphAsymmErrors.h"
#include "TLatex.h"


void small0706Base(string inputDir,string outputName){
	TCanvas* c1,*c2;
	setNCUStyle();
	c1 = new TCanvas("c1","",1150,768);
	
	int massZ[8]={600,800,1000,1200,1400,1700,2000,2500};
	int inputZ[8]={2,4,6,8,10,13,16,21};
	int massA[6]={300,400,500,600,700,800};
	
	TH2D* th2[4];
	th2[0]=new TH2D("expected","expected",8,0,8,6,0,6);
	th2[1]=new TH2D("observed","observed",8,0,8,6,0,6);
	
	th2[2]=new TH2D("expected","expected",8,0,8,6,0,6);
	th2[3]=new TH2D("observed","observed",8,0,8,6,0,6);
	
	TFile* tf1;
	
	tf1=TFile::Open("ScanPlot_fixgz.root");
	TH2F * th2f2=(TH2F *)tf1->FindObjectAny("xsec2");
	
	
	for(int i=0;i<4;i++){
		th2[i]->SetXTitle("m_{Zp}[GeV]");
		th2[i]->SetYTitle("m_{A0}[GeV]");
		th2[i]->SetMarkerSize(2);
	}
	
	for(int i=0;i<8;i++){
		for(int j=0;j<6;j++){
				
				TFile* tf1;
				TTree* tree;
				tf1=TFile::Open(Form("%s/higgsCombineTest_Asymptotic_%d_%dGeV_MonoHbb_13TeV.root",inputDir.data(),massZ[i],massA[j]));
				if(!tf1)continue;
				//TDirectory * dir;
				//dir = (TDirectory*)tf1->Get(Form("higgsCombineTest_Asymptotic_%d_%dGeV_MonoHbb_13TeV.root",massZ[i],massA[j]));
				
				tf1->GetObject("limit",tree);
				TreeReader data(tree);
				//data.Print();
				for(Long64_t jEntry=0; jEntry<data.GetEntriesFast() ;jEntry++){
						data.GetEntry(jEntry);
						Float_t  quantileExpected = data.GetFloat("quantileExpected");
						Double_t  limit = data.GetDouble("limit");
						if(quantileExpected==0.5)th2[0]->Fill(i,j,limit);
						if(quantileExpected==-1)th2[1]->Fill(i,j,limit);
						
						if(quantileExpected==0.5)th2[2]->Fill(i,j,limit*th2f2->GetBinContent(inputZ[i],j+2));
						if(quantileExpected==-1)th2[3]->Fill(i,j,limit*th2f2->GetBinContent(inputZ[i],j+2));
				}
				
		}
	}
	
	for(int i=0;i<8;i++){
		
		th2[0]->GetXaxis()->SetBinLabel(i+1,Form("%d",massZ[i]));
		th2[1]->GetXaxis()->SetBinLabel(i+1,Form("%d",massZ[i]));
		th2[2]->GetXaxis()->SetBinLabel(i+1,Form("%d",massZ[i]));
		th2[3]->GetXaxis()->SetBinLabel(i+1,"");
	}
	for(int j=0;j<6;j++){
		
		th2[0]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th2[1]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th2[2]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th2[3]->GetYaxis()->SetBinLabel(j+1,"");
	}
	th2[0]->Draw("colz,text");
	c1->Print("expected.pdf");
	th2[1]->Draw("colz,text");
	c1->Print("observed.pdf");
	
	
	c1->Clear();
	
	TPad *p1 = new TPad("p1","",0,0.09,1,0.89);
   p1->Draw();
   p1->cd();
   th2[0]->Draw("colzTEXT");
   p1->Update();
   Double_t x1,y1,x2,y2;
   gPad->GetRange(x1,y1,x2,y2);

   c1->cd();
   TPad *p2 = new TPad("p2","",0,0.12,1,0.92);
   p2->SetFillStyle(0);
   p2->SetFillColor(0);
   p2->Draw();
   p2->cd();
   
   for(int i=0;i<2;i++){
		th2[i]->SetTitle("");
		th2[i+2]->SetTitle("");
	}
	th2[1]->SetXTitle("");
	th2[1]->SetYTitle("");
	th2[3]->SetXTitle("");
	th2[3]->SetYTitle("");
   gStyle->SetPaintTextFormat(" 4.5f ");
   
   p2->Range(x1,y1,x2,y2);
   th2[1]->Draw("TEXTSAME");
	
	TLatex * latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.05);
    latex->SetTextAlign(12); // align left
    latex->SetNDC(kTRUE);                                                                                                                        
	latex->SetTextFont(62);
    latex->DrawLatex(0.18, 0.92, Form("CMS Preliminary   #sqrt{s} = 13 TeV    #intL = %.1f fb^{-1}", 2.32));
    //latex->DrawLatex(0.18, 0.885, );
	
	c1->Print(Form("plot/%s.pdf",outputName.data()));
	
}

void small0706Compare(string inputDir[],string outputName){
	TCanvas* c1,*c2;
	setNCUStyle();
	c1 = new TCanvas("c1","",1150,768);
	
	int massZ[8]={600,800,1000,1200,1400,1700,2000,2500};
	int inputZ[8]={2,4,6,8,10,13,16,21};
	int massA[6]={300,400,500,600,700,800};
	
	TH2D* th2[4];
	th2[0]=new TH2D("expected","expected",8,0,8,6,0,6);
	th2[1]=new TH2D("observed","observed",8,0,8,6,0,6);
	
	th2[2]=new TH2D("expected","expected",8,0,8,6,0,6);
	th2[3]=new TH2D("observed","observed",8,0,8,6,0,6);
	
	TFile* tf1;
	
	tf1=TFile::Open("ScanPlot_fixgz.root");
	TH2F * th2f2=(TH2F *)tf1->FindObjectAny("xsec2");
	
	
	for(int i=0;i<4;i++){
		th2[i]->SetXTitle("m_{Zp}[GeV]");
		th2[i]->SetYTitle("m_{A0}[GeV]");
		th2[i]->SetMarkerSize(2);
	}
	
	for(int i=0;i<8;i++){
		for(int j=0;j<6;j++){
				
				TFile* tf1,* tf2;
				TTree* tree,*tree2;
				tf1=TFile::Open(Form("%s/higgsCombineTest_Asymptotic_%d_%dGeV_MonoHbb_13TeV.root",inputDir[0].data(),massZ[i],massA[j]));
				tf2=TFile::Open(Form("%s/higgsCombineTest_Asymptotic_%d_%dGeV_MonoHbb_13TeV.root",inputDir[1].data(),massZ[i],massA[j]));
				//if(!tf2 || !tf2->IsOpen())continue;
				if(!tf1 || !tf1->IsOpen()){
					
				}
				if (!tf2 || !tf2->IsOpen()){
					tf2=TFile::Open(Form("%s/higgsCombineTest_Asymptotic_%d_%dGeV_MonoHbb_13TeV.root",inputDir[0].data(),massZ[i],massA[j]));
				}
				//if(!tf1)continue;
				//TDirectory * dir;
				//dir = (TDirectory*)tf1->Get(Form("higgsCombineTest_Asymptotic_%d_%dGeV_MonoHbb_13TeV.root",massZ[i],massA[j]));
				
				tf1->GetObject("limit",tree);
				tf2->GetObject("limit",tree2);
				TreeReader data(tree);
				TreeReader data2(tree2);
				//data.Print();
				bool isData1=0;
				Double_t  limit[2]={0,0};
				int jEntryMax=data.GetEntriesFast();
				if(data.GetEntriesFast()==0){
					limit[0]=1000;
					jEntryMax=data2.GetEntriesFast();
				}
				if(i==3 &&j==1)cout<<"jMax="<<jEntryMax<<endl;
				for(Long64_t jEntry=0; jEntry< jEntryMax;jEntry++){
						data.GetEntry(jEntry);
						data2.GetEntry(jEntry);
						Float_t  quantileExpected = data.GetFloat("quantileExpected");
						
						
						if(data.GetEntriesFast()==0) quantileExpected = data2.GetFloat("quantileExpected");
						if(data.GetEntriesFast()!=0)limit[0]= data.GetDouble("limit");
						limit[1]= data2.GetDouble("limit");
						
						if(i==3 &&j==1){
							cout<<limit[0]<<","<<limit[1]<<","<<quantileExpected<<endl;
							}
						
						if(quantileExpected==0.5){
							
							
							th2[0]->Fill(i,j,limit[0]<limit[1]?limit[0]:limit[1]);
							isData1=limit[0]<limit[1]?1:0;
							
							th2[2]->Fill(i,j,(limit[0]<limit[1]?limit[0]:limit[1])*th2f2->GetBinContent(inputZ[i],j+2));
						}
						if(quantileExpected==-1){
							if(isData1)th2[1]->Fill(i,j,limit[0]);
							else th2[1]->Fill(i,j,limit[1]);
							
							if(isData1)th2[3]->Fill(i,j,limit[0]*th2f2->GetBinContent(inputZ[i],j+2));
							else th2[3]->Fill(i,j,limit[1]*th2f2->GetBinContent(inputZ[i],j+2));
						}
						
				}
				
		}
	}
	
	for(int i=0;i<8;i++){
		
		th2[0]->GetXaxis()->SetBinLabel(i+1,Form("%d",massZ[i]));
		th2[1]->GetXaxis()->SetBinLabel(i+1,Form("%d",massZ[i]));
		th2[2]->GetXaxis()->SetBinLabel(i+1,Form("%d",massZ[i]));
		th2[3]->GetXaxis()->SetBinLabel(i+1,"");
	}
	for(int j=0;j<6;j++){
		
		th2[0]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th2[1]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th2[2]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th2[3]->GetYaxis()->SetBinLabel(j+1,"");
	}
	th2[0]->Draw("colz,text");
	c1->Print("expected.pdf");
	th2[1]->Draw("colz,text");
	c1->Print("observed.pdf");
	
	
	c1->Clear();
	
	TPad *p1 = new TPad("p1","",0,0.09,1,0.89);
   p1->Draw();
   p1->cd();
   th2[0]->Draw("colzTEXT");
   p1->Update();
   Double_t x1,y1,x2,y2;
   gPad->GetRange(x1,y1,x2,y2);

   c1->cd();
   TPad *p2 = new TPad("p2","",0,0.12,1,0.92);
   p2->SetFillStyle(0);
   p2->SetFillColor(0);
   p2->Draw();
   p2->cd();
   
   for(int i=0;i<2;i++){
		th2[i]->SetTitle("");
		th2[i+2]->SetTitle("");
	}
	th2[1]->SetXTitle("");
	th2[1]->SetYTitle("");
	th2[3]->SetXTitle("");
	th2[3]->SetYTitle("");
   gStyle->SetPaintTextFormat(" 4.5f ");
   
   p2->Range(x1,y1,x2,y2);
   th2[1]->Draw("TEXTSAME");
	
	TLatex * latex = new TLatex();
    latex->SetNDC();
    latex->SetTextSize(0.05);
    latex->SetTextAlign(12); // align left
    latex->SetNDC(kTRUE);                                                                                                                        
	latex->SetTextFont(62);
    latex->DrawLatex(0.18, 0.92, Form("CMS Preliminary   #sqrt{s} = 13 TeV    #intL = %.1f fb^{-1}", 2.32));
    //latex->DrawLatex(0.18, 0.885, );
	
	c1->Print(Form("plot/%s.pdf",outputName.data()));
	
}


void small0706(){
	small0706Base("boost","boosted");
	small0706Base("ResolvedRootfiles","resolvedRootfiles");
	string in[2]={"boost","ResolvedRootfiles"};
	
	small0706Compare(in,"compare");
	
}




