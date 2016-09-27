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

void DMDrawerBase(string model){
	bool masspointMissing=1;
	if(model.find("DMSpin0")!= std::string::npos)masspointMissing=0;
	
	setNCUStyle(true);
	c1 = new TCanvas("c1","",1360,768);
	
	int MSC[7]={10,20,50,100,200,300,500};
	int MDM[7]={1,10,20,50,100,150,200};
	
	vector<string> h_name;
	h_name.push_back("genMET_true");
	h_name.push_back("Higgs_pt");
	h_name.push_back("b0_pt");
	h_name.push_back("b1_pt");
	h_name.push_back("deltaR");
	//h_name.push_back("Mt");
	
	for(int i=0;i<7;i++){
		TFile* tf1[7];
		TH1D* th1[7];
		for(int j=0;j<7;j++){
			if(MSC[i]==MDM[j]*2)tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i]-5,MDM[j]));
			else tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i],MDM[j]));
		}
		
		
		TLegend *leg = new TLegend(0.75, 0.58, 0.96, 0.92);
  
		leg->SetBorderSize(0);
		leg->SetFillColor(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		
		for(unsigned int k=0;k<h_name.size();k++){
			leg->Clear();
			double temp=0;
			for(int j=0;j<7;j++){
				
				if(i==4 && j==4 && masspointMissing)continue;
				if(i==4 && j==5  && masspointMissing)continue;
				if(i==4 && j==6  && masspointMissing)continue;
				
				th1[j]=(TH1D*)tf1[j]->Get(Form("%s",h_name[k].data()));
				
				th1[j]->SetLineColor(j+1);
				th1[j]->SetLineWidth(2);
				
				if(th1[j]->GetMaximum()>temp)temp=th1[j]->GetMaximum();
				
			}
			//cout<<temp<<endl;
			
			for(int j=0;j<7;j++){
				
				if(i==4 && j==4 && masspointMissing)continue;
				if(i==4 && j==5  && masspointMissing)continue;
				if(i==4 && j==6  && masspointMissing)continue;
				
				th1[j]->SetMaximum(temp*1.1);
				if(h_name[k].find("deltaR")!= std::string::npos)th1[j]->SetMaximum(temp*1.5);
				if(j!=0)th1[j]->Draw("same");
				else th1[j]->Draw();
				leg->AddEntry(th1[j],Form("MDM=%d",MDM[j]));
			}
			leg->Draw("same");
			
			if(k==0)c1->Print(Form("plots/%s/MSC%d.pdf(",model.data(),MSC[i]));
			else if(k== h_name.size()-1)c1->Print(Form("plots/%s/MSC%d.pdf)",model.data(),MSC[i]));
			else c1->Print(Form("plots/%s/MSC%d.pdf",model.data(),MSC[i]));
		}
	}
	
	cout<<"MSC finish!"<<endl;
	
	
	for(int i=0;i<7;i++){
		TFile* tf1[7];
		TH1D* th1[7];
		for(int j=0;j<7;j++){
			if(MSC[j]==MDM[i]*2)tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[j]-5,MDM[i]));
			else tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[j],MDM[i]));
		}
		
		
		TLegend *leg = new TLegend(0.75, 0.58, 0.96, 0.92);
  
		leg->SetBorderSize(0);
		leg->SetFillColor(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		
		for(unsigned int k=0;k<h_name.size();k++){
			leg->Clear();
			double temp=0;
			for(int j=0;j<7;j++){
				
				if(i==6 && j==4  && masspointMissing)continue;
				if(i==4 && j==4  && masspointMissing)continue;
				if(i==5 && j==4  && masspointMissing)continue;
				
				th1[j]=(TH1D*)tf1[j]->Get(Form("%s",h_name[k].data()));
				
				th1[j]->SetLineColor(j+1);
				th1[j]->SetLineWidth(2);
				
				if(th1[j]->GetMaximum()>temp)temp=th1[j]->GetMaximum();
				
			}
			
			for(int j=0;j<7;j++){
				
				if(i==6 && j==4  && masspointMissing)continue;
				if(i==4 && j==4  && masspointMissing)continue;
				if(i==5 && j==4  && masspointMissing)continue;
				
				th1[j]->SetMaximum(temp*1.1);
				if(h_name[k].find("deltaR")!= std::string::npos)th1[j]->SetMaximum(temp*1.5);
				if(j!=0)th1[j]->Draw("same");
				else th1[j]->Draw();
				leg->AddEntry(th1[j],Form("MSC=%d",MSC[j]));
			}
			leg->Draw("same");
			
			if(k==0)c1->Print(Form("plots/%s/MDM%d.pdf(",model.data(),MSC[i]));
			else if(k== h_name.size()-1)c1->Print(Form("plots/%s/MDM%d.pdf)",model.data(),MSC[i]));
			else c1->Print(Form("plots/%s/MDM%d.pdf",model.data(),MSC[i]));
		}
	}
	
}

void DMCompare(){
	setNCUStyle(true);
	c1 = new TCanvas("c1","",1360,768);
	
	
	int MSC[7]={10,20,50,100,200,300,500};
	int MDM[7]={1,10,20,50,100,150,200};
	
	vector<string> h_name;
	h_name.push_back("genMET_true");
	h_name.push_back("Higgs_pt");
	h_name.push_back("b0_pt");
	h_name.push_back("b1_pt");
	h_name.push_back("deltaR");
	
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
				if(MSC[i]==MDM[j]*2)tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i]-5,MDM[j]));
				else tf1[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i],MDM[j]));
				th1[j]=(TH1D*)tf1[j]->Get(Form("%s",h_name[k].data()));
				model ="DMSpin0";
				if(MSC[i]==MDM[j]*2)tf2[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i]-5,MDM[j]));
				else tf2[j]=TFile::Open(Form("output/%s_MSC%d_MDM%d.root",model.data(),MSC[i],MDM[j]));
				th2[j]=(TH1D*)tf2[j]->Get(Form("%s",h_name[k].data()));
				
				th1[j]->SetLineWidth(2);
				th2[j]->SetLineWidth(2);
				
				if(MSC[i]==MDM[j]*2)th1[j]->SetTitle(Form("MSC%d_MDM%d",MSC[i]-5,MDM[j]));
				else th1[j]->SetTitle(Form("MSC%d_MDM%d",MSC[i],MDM[j]));
				
				th2[j]->SetLineColor(2);
				
				th1[j]->SetMaximum(th1[j]->GetMaximum()>th2[j]->GetMaximum()?th1[j]->GetMaximum()*1.1:th2[j]->GetMaximum()*1.1);
				
				th1[j]->Draw("");
				th2[j]->Draw("same");
				
				TLegend *leg = new TLegend(0.75, 0.58, 0.96, 0.92);
  
		leg->SetBorderSize(0);
		leg->SetFillColor(0);
		leg->SetFillStyle(0);
		leg->SetTextSize(0.04);
		
				leg->AddEntry(th1[j],"Scalar");
				leg->AddEntry(th2[j],"Spin0");
				leg->Draw("same");
				
				if(i==0 &&j==0) c1->Print(Form("plots/%s.pdf(",h_name[k].data()));
				else if(i==6 &&j==6) c1->Print(Form("plots/%s.pdf)",h_name[k].data()));
				else  c1->Print(Form("plots/%s.pdf",h_name[k].data()));
			}
		}
		
		
	}
	
	
	
}

void DMDrawer(){
	DMDrawerBase("Scalar");
	DMDrawerBase("DMSpin0");
	DMCompare();
}