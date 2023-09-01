#include "include/paperPlotsHeader.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TCut.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TTree.h"
#include "TStyle.h"
#include "TPad.h"

void PlotCaloEnergyDistribution()
{

  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  bool doElectrons = true;
  float textSize = 0.04;

  const float eta_min = 3.5;
  const float eta_max = 5.5;

  const float scaleHCAL = 1. / 17600;
  const float scaleECAL = 1. / 7200;

  std::cout << "scaleHCAL " << scaleHCAL << " scaleECAL " << scaleECAL << " ratio: " << scaleECAL / scaleHCAL << std::endl;
  TString expr;
  expr.Form("Theta[0]>%f&&Theta[0]<%f", 2. * TMath::ATan(TMath::Exp(-eta_max)), 2. * TMath::ATan(TMath::Exp(-eta_min)));
  TCut thetacut(expr.Data());

  expr.Form("%f*TotalEnergy[12]>%f", scaleHCAL, 0.15);
  TCut Ecut(expr.Data());

  TFile *inputFile = doElectrons ? TFile::Open("Data/MCInfoResults_Electrons_Spaghetti_500GeV.root") : TFile::Open("Data/MCInfoResults_PiPlus_Spaghetti_500GeV.root");

  TTree *MCInfo = (TTree *)gFile->Get("MCInfo");

  TCanvas *c1 = new TCanvas("c1", "c1: EM vs HCAL", 500, 500);
  // c1->Divide(2, 1);
  c1->cd(1);
  expr.Form("%f*TotalEnergy[12]:%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10])>>hHCalvsECal(100,0,600,100,0,700)", scaleHCAL, scaleECAL);
  MCInfo->Draw(expr.Data(), thetacut, "colz");

  TH2F *hHCalvsECal = dynamic_cast<TH2F *>(gDirectory->Get("hHCalvsECal"));
  hHCalvsECal->SetName("hHCalvsECal");
  hHCalvsECal->SetTitle("HCalvsECal");
  hHCalvsECal->GetXaxis()->SetTitle("#alpha * ECal");
  hHCalvsECal->GetYaxis()->SetTitle("#beta * HCal");
  hHCalvsECal->GetYaxis()->SetTitleOffset(1.55);

  // c1->cd(2);
  // TH2F *hHCalECalvsECal = new TH2F("hHCalECalvsECal", "hHCalECalvsECal", 40, 0, 500, 40, 0, 1300);
  // expr.Form("%f*TotalEnergy[12]+%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10]):%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10])>>hHCalECalvsECal", scaleHCAL, scaleECAL, scaleECAL);
  // MCInfo->Draw(expr.Data(), thetacut, "colz");

  // TH2F *hHCalECalvsECal = dynamic_cast<TH2F*> (gDirectory->Get("hHCalECalvsECal"));
  // hHCalECalvsECal->SetName("hHCalECalvsECal");
  // hHCalECalvsECal->GetXaxis()->SetTitle("Scale * ECal");
  // hHCalECalvsECal->GetYaxis()->SetTitle("Scale * ECal + #alpha HCal");
  // hHCalECalvsECal->GetYaxis()->SetTitleOffset(1.55);
  // hHCalECalvsECal->Draw("colz");

  TCanvas *c2 = new TCanvas("c2", "c2: combined", 500, 500);
  expr.Form("%.15f*TotalEnergy[12]+%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10])>>hHCalECal(250,0,1000)", scaleHCAL, scaleECAL);
  MCInfo->Draw(expr.Data(), thetacut);

  TH1F *hHCalECal = dynamic_cast<TH1F *>(gDirectory->Get("hHCalECal"));
  hHCalECal->SetName("hHCalECal");
  hHCalECal->GetXaxis()->SetTitle("#alpha * #it{E}_{em} + #beta #it{E}_{had}");
  hHCalECal->Sumw2();
  auto f1 = new TF1("f1", "crystalball", 0, 1000);
  // f1->SetParameters(hHCalECal->GetMaximum(), hHCalECal->GetMean(), 0.02 * 500, 0.6, 1.5);
  f1->SetParameters(hHCalECal->GetMaximum(), hHCalECal->GetMean(), 0.1 * 500, 0.6, 1.5);
  hHCalECal->Fit("f1", "", "", 0, 1000);

  TCanvas *c3 = new TCanvas("c3", "c3: EM vs HCal", 500, 500);
  expr.Form("%f*TotalEnergy[12]+%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10]):%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10])/(%f*TotalEnergy[12]) >>hHCalECalvsECaloHCal", scaleHCAL, scaleECAL, scaleECAL, scaleHCAL);
  MCInfo->Draw(expr.Data(), thetacut, "colz");

  TH2F *hHCalECalvsECaloHCal = dynamic_cast<TH2F *>(gDirectory->Get("hHCalECalvsECaloHCal"));
  hHCalECalvsECaloHCal->SetName("hHCalECalvsECaloHCal");
  hHCalECalvsECaloHCal->GetYaxis()->SetTitle("#alpha * #it{E}_{em} + #beta #it{E}_{had}");
  hHCalECalvsECaloHCal->GetXaxis()->SetTitle("ECal/^{}HCal");

  TCanvas *c4 = new TCanvas("c4", "c4: ECal and HCal Raw", 600, 600);
  c4->cd();

  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetLogy();

  gPad->SetRightMargin(0.035);
  gPad->SetTopMargin(0.02);

  expr.Form("(%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10]) + %f*TotalEnergy[12] )>>hEnergyTotalECALandHCAL(250,0,1000)", scaleECAL, scaleHCAL);
  MCInfo->Draw(expr.Data(), thetacut);
  expr.Form("%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10]) >> hEnergyECALonly(250,0,1000)", scaleECAL);
  MCInfo->Draw(expr.Data(), thetacut, "same");

  expr.Form("(%f*TotalEnergy[12] )>>hEnergyHCALonly(250,0,1000)", scaleHCAL);
  MCInfo->Draw(expr.Data(), thetacut, "same");

  auto hAll = dynamic_cast<TH1F *>(gDirectory->Get("hEnergyTotalECALandHCAL"));
  hAll->SetName("ECALHCAL_Spaghetti_noECAL_3x3");
  hAll->SetTitle("FOCAL-E + FOCAL-H");
  hAll->GetYaxis()->SetTitle("Yield");
  hAll->GetXaxis()->SetTitle("Energy (GeV)");
  hAll->Sumw2();
  hAll->SetLineColor(kBlack);
  hAll->SetMarkerColor(kBlack);
  hAll->GetYaxis()->SetRangeUser(3e-1, 1e4);

  auto f2 = new TF1("f2", "crystalball", 0, 1000);
  f2->SetParameters(hAll->GetMaximum(), hAll->GetMean(), 0.1 * 500, 0.6, 1.5);
  f2->SetLineColor(kRed);
  hAll->Fit(f2, "", "", 0., 1000.);
  // hAll->Fit("gaus", "R+", "R+", 400, 600);
  hAll->Draw();
  auto hECAL = dynamic_cast<TH1F *>(gDirectory->Get("hEnergyECALonly"));
  hECAL->SetTitle("FOCAL-E Only");
  hECAL->Sumw2();
  hECAL->SetLineColor(kMagenta + 1);
  hECAL->SetMarkerColor(kMagenta + 1);
  hECAL->Draw("same");
  auto hHCAL = dynamic_cast<TH1F *>(gDirectory->Get("hEnergyHCALonly"));
  hHCAL->SetTitle("FOCAL-H Only");
  hHCAL->Sumw2();
  hHCAL->SetLineColor(kBlue);
  hHCAL->SetMarkerColor(kBlue);
  hHCAL->Draw("same");

  TLegend *leg = new TLegend(0.61, 0.735, 0.91, 0.94);
  leg->SetTextSizePixels(15);
  leg->SetLineWidth(0);
  leg->SetFillStyle(0);
  leg->SetTextSize(0.04);
  leg->AddEntry(hAll, "FOCAL-E + FOCAL-H");
  leg->AddEntry(f2, "Crystal Ball fit", "l");
  leg->AddEntry(hECAL, "FOCAL-E Only");
  leg->AddEntry(hHCAL, "FOCAL-H Only");
  leg->Draw();

  drawLatexAdd(Form("ALICE simulation, Single %s", doElectrons ? "e^{-}" : "#pi^{+}"), 0.17, 0.95 - 1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kFALSE);
  drawLatexAdd("FoCal upgrade", 0.17, 0.95 - 2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kFALSE);
  drawLatexAdd(Form("3.4 < #it{#eta}_{%s} < 5.5", doElectrons ? "e^{-}" : "#pi^{+}"), 0.17, 0.95 - 3 * 1.1 * textSize, textSize, kFALSE, kFALSE, kFALSE);
  drawLatexAdd(Form("#it{E}_{%s} = 500 GeV", doElectrons ? "e^{-}" : "#pi^{+}"), 0.17, 0.95 - 4.1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kFALSE);

  c4->SaveAs(Form("figures/Edoposit_%s_Large.pdf", doElectrons ? "electrons" : "PiPlus"));

  TCanvas *c5 = new TCanvas("c5", "c5: ECal and HCal Raw", 500, 500);
  c5->cd();
  TCut HCALeCut(Form("(%f*TotalEnergy[12] )>400", scaleHCAL));
  TCut ECALeCut(Form("%f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10]) < 300 && %f*(TotalEnergy[0]+TotalEnergy[2]+TotalEnergy[4]+TotalEnergy[6]+TotalEnergy[8]+TotalEnergy[10]) > 240", scaleECAL, scaleECAL));
  MCInfo->Draw("700*TMath::Tan(Theta)*TMath::Sin(Phi):700*TMath::Tan(Theta)*TMath::Cos(Phi) >> XYPos(500,-50,50,500,-50,50)", HCALeCut && thetacut);
  auto XYPos = dynamic_cast<TH2F *>(gDirectory->Get("XYPos"));
  XYPos->Draw("colz");
}
