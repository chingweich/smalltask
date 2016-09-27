#include <TLegend.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <TH1D.h>
#include <TH2D.h>
#include <TRandom.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TGraphAsymmErrors.h>
#include <TH1F.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TROOT.h>
#include "TImage.h"
#include "TSystem.h"
#include "TStyle.h"
#include <TClonesArray.h>
#include <fstream>
#include <cmath>
#include <TSystem.h>
#include <string>
#include <sstream>
#include"setNCUStyle.C"

TCanvas* c1;



void DMCompare(){
	setNCUStyle(true);
	c1 = new TCanvas("c1","",1360,768);
	
	
	int MSC[7]={10,20,50,100,200,300,500};
	int MDM[7]={1,10,20,50,100,150,200};
	
	vector<string> h_name;
	h_name.push_back("genMET_true");
	
	
	for(unsigned int k=0;k<h_name.size();k++){
		
		for(int i=0;i<7;i++){
		TFile* tf1[7];
		TH1D* th1[7];
		
		TFile* tf2[7];
		TH1D* th2[7];
			for(int j=0;j<7;j++){
				
				if(i==4 && j==4 )continue;
				if(i==4 && j==5  )continue;
				if(i==4 && j==6 )continue;
				
				
				string model ="Scalar";
				model ="DMSpin0";
				if(MSC[i]==MDM[j]*2)tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i]-5,MDM[j]));
				else tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i],MDM[j]));
				th1[j]=(TH1D*)tf1[j]->Get(Form("%s",h_name[k].data()));
				
				 tf2[j]=TFile::Open(Form("output2/MonoH_%d_%d_0.4_1.0_805.root",MSC[i],MDM[j]));
				 if (!tf2[j] || !tf2[j]->IsOpen())continue;
				th2[j]=(TH1D*)tf2[j]->Get(Form("%s",h_name[k].data()));
				
				
				
				th1[j]->SetLineWidth(2);
				th2[j]->SetLineWidth(2);
				
				if(MSC[i]==MDM[j]*2)th1[j]->SetTitle(Form("MSC%d_MDM%d",MSC[i]-5,MDM[j]));
				else th1[j]->SetTitle(Form("MSC%d_MDM%d",MSC[i],MDM[j]));
				
				th2[j]->SetLineColor(2);
				
				th1[j]->Scale(1/th1[j]->Integral());
				th2[j]->Scale(1/th2[j]->Integral());
				
				th1[j]->SetMaximum(th1[j]->GetMaximum()>th2[j]->GetMaximum()?th1[j]->GetMaximum()*1.1:th2[j]->GetMaximum()*1.1);
				
				
				
				th1[j]->Draw("");
				th2[j]->Draw("same");
				
				TLegend *leg = new TLegend(0.75, 0.58, 0.96, 0.92);
  
		leg->SetBorderSize(0);
		leg->SetFillColor(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		
				leg->AddEntry(th1[j],"DMsimp_s_spin0");
				leg->AddEntry(th2[j],"DMsimp_s_spin0_ph");
				leg->Draw("same");
				
				if(i==0 &&j==1) c1->Print(Form("plots2/%s.pdf(",h_name[k].data()));
				else if(i==6 &&j==6) c1->Print(Form("plots2/%s.pdf)",h_name[k].data()));
				else  c1->Print(Form("plots2/%s.pdf",h_name[k].data()));
			}
		}
		
		
	}
	
	
	
}

void DMDrawer2(){
	
	DMCompare();
}