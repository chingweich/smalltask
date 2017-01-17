#include <TFile.h>
#include <TLine.h>
#include <TTree.h>
#include <TBranch.h>
#include <TH2.h>
#include <TCanvas.h>
#include <TColor.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TMath.h>
#include <TFrame.h>
#include <TLatex.h>
//#include "../macro/mkPlotsLivia/CMS_lumi.C"
#include <iostream>
#include <vector>


void makePlots(){
	Float_t lumi = 2.3;	
	TString latexCMSname = "CMS";
	TLatex *l1b = new TLatex(0.11,0.90,latexCMSname);
 l1b->SetTextSize(0.040);
 l1b->SetTextAlign(12);
 l1b->SetNDC(kTRUE);
 l1b->SetTextFont(62);
 
 TString latexlumi = Form("%1.1f fb^{-1}",lumi);
 TString latexenergy = " (13 TeV)";
 TString latexname = latexlumi+latexenergy;
  TLatex *l2b = new TLatex(0.725,0.95,latexname);
 l2b->SetTextSize(0.034);
 l2b->SetTextAlign(12);
 l2b->SetNDC(kTRUE);
 l2b->SetTextFont(42);

 TString thestring = "Z'#rightarrow DM+h(b#bar{b})";
 TString add2hdm   = "(2HDM)";
  TLatex *l3b = new TLatex(0.11,0.86,thestring);
 l3b->SetTextSize(0.031);
 l3b->SetTextAlign(12);
 l3b->SetNDC(kTRUE);
 l3b->SetTextFont(42);
 
 TLatex *l4b = new TLatex(0.11,0.83,add2hdm);
 l4b->SetTextSize(0.031);
 l4b->SetTextAlign(12);
 l4b->SetNDC(kTRUE);
 l4b->SetTextFont(42);
 
 TFile * tf1=TFile::Open("fix2dStyle.root");
 TH1D* obslimits=(TH1D*)tf1->Get("obs");
 TH1D* limits=(TH1D*)tf1->Get("colz");
 TH1D* explimits=(TH1D*)tf1->Get("exp");
 
 limits->GetXaxis()->SetTitle("m_{Z'} [GeV]");
 limits->GetYaxis()->SetTitle("m_{A} [GeV]");
 limits->GetZaxis()->SetTitle("#sigma_{95\% CL} / #sigma_{th}");
 limits->SetTitle("");
 limits->SetMaximum(3000);
 limits->SetMarkerSize(1.6);

 limits->GetYaxis()->SetTitleOffset(1.3);
 limits->GetZaxis()->SetTitleOffset(0.75);
 // size of axis labels
 limits->GetXaxis()->SetTitleSize(0.04);
 limits->GetYaxis()->SetTitleSize(0.04);
 limits->GetZaxis()->SetTitleSize(0.035);
 limits->GetXaxis()->SetLabelSize(0.05);
 limits->GetYaxis()->SetLabelSize(0.05); 
 limits->GetZaxis()->SetLabelSize(0.025);

 // set the lables for the Xaxis (mZp)
 limits->GetXaxis()->SetBinLabel(1,"600");
 limits->GetXaxis()->SetBinLabel(2,"800");
 limits->GetXaxis()->SetBinLabel(3,"1000");
 limits->GetXaxis()->SetBinLabel(4,"1200");
 limits->GetXaxis()->SetBinLabel(5,"1400");
 limits->GetXaxis()->SetBinLabel(6,"1700");
 limits->GetXaxis()->SetBinLabel(7,"2000");
 limits->GetXaxis()->SetBinLabel(8,"2500");

 // set the lables for the Yaxis (mA0)
 limits->GetYaxis()->SetBinLabel(1,"300");
 limits->GetYaxis()->SetBinLabel(2,"400");
 limits->GetYaxis()->SetBinLabel(3,"500");
 limits->GetYaxis()->SetBinLabel(4,"600");
 limits->GetYaxis()->SetBinLabel(5,"700");
 limits->GetYaxis()->SetBinLabel(6,"800");
 
 explimits->GetXaxis()->SetTitle("m_{Z'} [GeV]");
 explimits->GetYaxis()->SetTitle("m_{A} [GeV]");
 explimits->GetZaxis()->SetTitle("#sigma_{95\% CL} / #sigma_{th}");
 explimits->SetTitle("");
 explimits->SetMaximum(3000);
 explimits->SetMarkerSize(1.6);

 explimits->GetYaxis()->SetTitleOffset(1.3);
 explimits->GetZaxis()->SetTitleOffset(0.75);
 // size of axis labels
 explimits->GetXaxis()->SetTitleSize(0.04);
 explimits->GetYaxis()->SetTitleSize(0.04);
 explimits->GetZaxis()->SetTitleSize(0.035);
 explimits->GetXaxis()->SetLabelSize(0.05);
 explimits->GetYaxis()->SetLabelSize(0.05); 
 explimits->GetZaxis()->SetLabelSize(0.025);

 // set the lables for the Xaxis (mZp)
 explimits->GetXaxis()->SetBinLabel(1,"600");
 explimits->GetXaxis()->SetBinLabel(2,"800");
 explimits->GetXaxis()->SetBinLabel(3,"1000");
 explimits->GetXaxis()->SetBinLabel(4,"1200");
 explimits->GetXaxis()->SetBinLabel(5,"1400");
 explimits->GetXaxis()->SetBinLabel(6,"1700");
 explimits->GetXaxis()->SetBinLabel(7,"2000");
 explimits->GetXaxis()->SetBinLabel(8,"2500");

 // set the lables for the Yaxis (mA0)
 explimits->GetYaxis()->SetBinLabel(1,"300");
 explimits->GetYaxis()->SetBinLabel(2,"400");
 explimits->GetYaxis()->SetBinLabel(3,"500");
 explimits->GetYaxis()->SetBinLabel(4,"600");
 explimits->GetYaxis()->SetBinLabel(5,"700");
 explimits->GetYaxis()->SetBinLabel(6,"800");
 
  TCanvas * cboth = new TCanvas("cboth","",550,550);
 cboth->cd();
 gStyle->SetOptStat(0);
 gStyle->SetPaintTextFormat("2.1f");
 gStyle->SetPalette(57);
 gStyle->SetFrameLineWidth(3);
 gStyle->SetPadRightMargin(0.109);
 //gStyle->SetPadLeftMargin(0.13);
 //cboth->SetLeftMargin(0.1);
 //cboth->SetRightMargin(0.1);


 Double_t pad1_x1 = 0.01; 
 Double_t pad1_x2 = 0.98;
 Double_t pad1_y1 = 0.03;
 Double_t pad1_y2 = 1.00;
 Double_t pad2_x1 = pad1_x1;
 Double_t pad2_x2 = pad1_x2;
 Double_t pad2_y1 = pad1_y1-0.03;
 Double_t pad2_y2 = pad1_y2-0.03;


 //TPad* p1 = new TPad("p1","",0,0.12,0.95,0.98);
 //TPad* p1 = new TPad("p1","",0,0.09,0.95,0.89); //x1,y1,x2,y2
 //TPad* p1 = new TPad("p1","",0.02,0.03,0.98,0.95); //x1,y1,x2,y2
 TPad* p1 = new TPad("p1","",pad1_x1,pad1_y1,pad1_x2,pad1_y2); //x1,y1,x2,y2
 p1->Draw();
 p1->cd();
 p1->SetLogz();


 explimits->Draw(" text"); 
 limits->Draw(" COLz same"); 
 explimits->Draw(" text same"); 
 //obslimits->Draw("TEXT SAME");

 //latex.DrawLatex(0.08,5.7,thestring);
 p1->Update();

 Double_t x1,y1,x2,y2;
 p1->GetRange(x1,y1,x2,y2);

 cboth->cd();
 TPad* p2 = new TPad("p2","",pad2_x1,pad2_y1,pad2_x2,pad2_y2); //x1,y1,x2,y2
 p2->SetFillStyle(0);
 p2->SetFillColor(0);
 p2->Draw();
 p2->cd();
 p2->Range(x1,y1,x2,y2);
 gStyle->SetFrameLineWidth(3);
 TFrame *f = (TFrame*)cboth->FindObject("TFrame");
 Double_t px1 = f->GetX1();
 Double_t px2 = f->GetX2();
 Double_t py1 = f->GetY1()+0.23;
 Double_t py2 = f->GetY2()+0.23;

 obslimits->SetMarkerSize(1.6);
 obslimits->GetXaxis()->SetTitle("");
 obslimits->GetYaxis()->SetTitle("");
 obslimits->SetTitle("");
 obslimits->GetXaxis()->SetBinLabel(1,"");
 obslimits->GetXaxis()->SetBinLabel(2,"");
 obslimits->GetXaxis()->SetBinLabel(3,"");
 obslimits->GetXaxis()->SetBinLabel(4,"");
 obslimits->GetXaxis()->SetBinLabel(5,"");
 obslimits->GetXaxis()->SetBinLabel(6,"");
 obslimits->GetXaxis()->SetBinLabel(7,"");
 obslimits->GetXaxis()->SetBinLabel(8,"");
 obslimits->GetYaxis()->SetBinLabel(1,"");
 obslimits->GetYaxis()->SetBinLabel(2,"");
 obslimits->GetYaxis()->SetBinLabel(3,"");
 obslimits->GetYaxis()->SetBinLabel(4,"");
 obslimits->GetYaxis()->SetBinLabel(5,"");
 obslimits->GetYaxis()->SetBinLabel(6,"");

 //limits->Draw("TEXT SAME"); 
 obslimits->Draw("TEXT SAME");
 p1->Update();

 // redraw the frame around the histogram
 TLine l;
 l.SetLineWidth(3);
 l.DrawLine(px1,py2,px2,py2);
 l.DrawLine(px2,py1,px2,py2);
 l.DrawLine(px1,py1,px2,py1);
 l.DrawLine(px1,py1,px1,py2);

 //CMS_lumi(cboth,false,0);
 l1b->Draw("same");
 l2b->Draw("same");
 l3b->Draw("same");
 l4b->Draw("same");
 cboth->cd();
// cboth->SaveAs(Form("%s/limits2D_2HDM_ExpAndObs.png",outDir.Data()));
 cboth->SaveAs("plot/limits2D_2HDM_ExpAndObs.pdf");
 delete cboth;
}