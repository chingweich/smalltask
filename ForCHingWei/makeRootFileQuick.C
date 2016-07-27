#include <Riostream.h>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>
#include <cstdlib>
#include "TTree.h"
#include "TH1D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLine.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TPaveText.h"
#include "fstream"
#include "TGraph.h"
#define nXm 8

void makeRootFileQuick(){
	fstream file1("xsec_MonoHTheoryATLAS_New.txt");
	double x1[8],y1[8];
	for(int i=0;i<8;i++){
		file1>>x1[i]>>y1[i];
	}
	double x2[8],y2[8];
	fstream file2("xsec_MonoHTheoryCMS_New.txt");
	for(int i=0;i<8;i++){
		file2>>x2[i]>>y2[i];
	}
	
	TGraph* tg1=new TGraph(8,x1,y1);
	TGraph* tg2=new TGraph(8,x2,y2);
	TFile* outFile= new TFile("lineA.root","recreate");
	tg1->Write();
	outFile->Close();
	
	TFile* outFile2= new TFile("lineC.root","recreate");
	tg2->Write();
	outFile2->Close();
}