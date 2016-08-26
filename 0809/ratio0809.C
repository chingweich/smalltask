#include <TLegend.h>
#include <vector>
#include <iostream>
#include <fstream>
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
#include <TClonesArray.h>
#include <fstream>
#include <cmath>
#include <TSystem.h>
#include <string>
#include <sstream>
#include "../0808/setNCUStyle.C"
#include<TH2.h>
#include "TLine.h"
#include "TF1.h"
#include"TGraphAsymmErrors.h"
#include "TLatex.h"

void ratio0809(){
	TFile *f1, *f2;
	f1=TFile::Open("../0803/output.root");
	f2=TFile::Open("../0808/output.root");
	
	
	int massA[6]={300,400,500,600,700,800};
	
	TH2D* th1[4];
	th1[0]=(TH2D*) f1->FindObjectAny("exp");
	th1[1]=(TH2D*) f1->FindObjectAny("obs");
	th1[2]=(TH2D*) f2->FindObjectAny("exp");
	th1[3]=(TH2D*) f2->FindObjectAny("obs");
	
	th1[0]->Divide(th1[2]);
	th1[1]->Divide(th1[3]);
	
	for(int j=0;j<6;j++){
		
		th1[0]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th1[1]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th1[2]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
		th1[3]->GetYaxis()->SetBinLabel(j+1,Form("%d",massA[j]));
	}
	
	for(int i=0;i<4;i++){
		th1[i]->SetXTitle("m_{Zp}[GeV]");
		th1[i]->SetYTitle("m_{A0}[GeV]");
		//th2[i]->SetMarkerSize(2);
		//th1[i]->SetMinimum(0.8);
	}
	
	TCanvas* c1,*c2;
	TStyle* ts =setNCUStyle();
	ts->SetPadRightMargin(0.12);
	c1 = new TCanvas("c1","",889,768);
	
	
	TPad *p1 = new TPad("p1","",0,0.09,1,0.89);
   p1->Draw();
   p1->cd();
   th1[1]->SetMaximum(1.01);
   th1[1]->SetMinimum(0.78);
   th1[1]->Draw("TEXT,same  colz");
   p1->Update();
   Double_t x1,y1,x2,y2;
   gPad->GetRange(x1,y1,x2,y2);

   c1->cd();
   TPad *p2 = new TPad("p2","",0,0.12,1,0.92);
   p2->SetFillStyle(0);
   p2->SetFillColor(0);
   p2->Draw();
   p2->cd();
   
   
   	TLatex * latex = new TLatex();
    latex->SetNDC();
    //latex->SetTextSize(0.05);
    latex->SetTextAlign(12); // align left
    latex->SetNDC(kTRUE);                                                                                                                        
	latex->SetTextSize(0.06);    
	latex->SetTextFont(42);
    latex->DrawLatex(0.15, 0.92, Form("CMS                                        %.1f fb^{-1} ( 13 TeV )", 2.32));
   
	th1[0]->SetXTitle("");
	//th1[1]->SetYTitle("");
	//th2[3]->SetXTitle("");
	//th2[3]->SetYTitle("");
   gStyle->SetPaintTextFormat(" 4.3f ");
   
   p2->Range(x1,y1,x2,y2);
   th1[0]->Draw("TEXTSAME");
   
   c1->Print("ratio.pdf");
  c1->SaveAs("ratio.png");
}