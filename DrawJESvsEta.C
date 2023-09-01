#include "TFile.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLatex.h"
#include "include/paperPlotsHeader.h"

double textSize = 0.05;

void DrawJESvsEta()
{
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    int JESMinX = 0;
    int JESMaxX = 1200;

    Color_t colors[3] = {kBlue + 2, kRed + 1, kBlack};
    Color_t colorsMC[3] = {kBlack, kGreen + 2, kBlue + 2};
    Style_t marker[3] = {20, 21, 33};
    Style_t markerMC[3] = {33, 34, 21}; // 24, 25, 27
    Size_t markerS[3] = {2, 2, 2}; // 2.4

    // TFile *resultsFile_Ch = TFile::Open("AnalysisClusters_BoxPiPlus_Spaghetti.root");
    // TFile *resultsFile_Ch = TFile::Open("~/AnalysisClusters_BoxPiPlus_Sandwich_ktalgorithm.root");
    TFile *resultsFile_Ch = TFile::Open("Data/AnalysisClusters_BoxPiPlus_Sandwich.root");
    TFile *resultsFile_Ne = TFile::Open("Data/AnalysisClusters_BoxNeutralPions_Sandwich.root");

    TH2D *hLeadingJetFractionVsEnergy_Eta0_Ch = (TH2D *)resultsFile_Ch->Get("hJetEnergyFracVsEnergy_R06_eta0");
    TH2D *hLeadingJetFractionVsEnergy_Eta1_Ch = (TH2D *)resultsFile_Ch->Get("hJetEnergyFracVsEnergy_R06_eta1");
    // TH2D *hLeadingJetFractionVsEnergy_Eta0_Ch = (TH2D *)resultsFile_Ch->Get("hJetPTFracVsPT_R06_eta0");
    // TH2D *hLeadingJetFractionVsEnergy_Eta1_Ch = (TH2D *)resultsFile_Ch->Get("hJetPTFracVsPT_R06_eta1");

    // TH2D *hLeadingJetFractionVsEnergy_Eta2 = (TH2D *)resultsFile->Get("hJetEnergyFracVsEnergy_eta2");

    TH2D *hLeadingJetFractionVsEnergy_Eta0_Ne = (TH2D *)resultsFile_Ne->Get("hJetEnergyFracVsEnergy_R06_eta0");
    TH2D *hLeadingJetFractionVsEnergy_Eta1_Ne = (TH2D *)resultsFile_Ne->Get("hJetEnergyFracVsEnergy_R06_eta1");
    // TH2D *hLeadingJetFractionVsEnergy_Eta0_Ne = (TH2D *)resultsFile_Ne->Get("hJetPTFracVsPT_R06_eta0");
    // TH2D *hLeadingJetFractionVsEnergy_Eta1_Ne = (TH2D *)resultsFile_Ne->Get("hJetPTFracVsPT_R06_eta1");

    TProfile *prof_EnergyFractionVsEnergy_Eta0_Ch = (TProfile *)hLeadingJetFractionVsEnergy_Eta0_Ch->ProfileX("prof_EnergyFractionVsEnergy_Eta0_Ch");
    prof_EnergyFractionVsEnergy_Eta0_Ch->SetTitle("Leading jet energy fraction vs pions energy vs eta;#it{E}_{MC};JES");
    prof_EnergyFractionVsEnergy_Eta0_Ch->SetLineColor(kBlack);
    prof_EnergyFractionVsEnergy_Eta0_Ch->SetMarkerStyle(21);
    prof_EnergyFractionVsEnergy_Eta0_Ch->SetMarkerColor(kBlack);
    TProfile *prof_EnergyFractionVsEnergy_Eta1_Ch = (TProfile *)hLeadingJetFractionVsEnergy_Eta1_Ch->ProfileX("prof_EnergyFractionVsEnergy_Eta1_Ch");
    prof_EnergyFractionVsEnergy_Eta1_Ch->SetLineColor(kRed);
    prof_EnergyFractionVsEnergy_Eta1_Ch->SetMarkerStyle(20);
    prof_EnergyFractionVsEnergy_Eta1_Ch->SetMarkerColor(kRed);

    // TProfile *prof_EnergyFractionVsEnergy_Eta2 = (TProfile *)hLeadingJetFractionVsEnergy_Eta2->ProfileX("prof_EnergyFractionVsEnergy_Eta2");
    // prof_EnergyFractionVsEnergy_Eta2->SetLineColor(kBlue);

    TProfile *prof_EnergyFractionVsEnergy_Eta0_Ne = (TProfile *)hLeadingJetFractionVsEnergy_Eta0_Ne->ProfileX("prof_EnergyFractionVsEnergy_Eta0_Ne");
    prof_EnergyFractionVsEnergy_Eta0_Ne->SetLineColor(kBlue);
    prof_EnergyFractionVsEnergy_Eta0_Ne->SetMarkerStyle(21);
    prof_EnergyFractionVsEnergy_Eta0_Ne->SetMarkerColor(kBlue);

    TProfile *prof_EnergyFractionVsEnergy_Eta1_Ne = (TProfile *)hLeadingJetFractionVsEnergy_Eta1_Ne->ProfileX("prof_EnergyFractionVsEnergy_Eta1_Ne");
    prof_EnergyFractionVsEnergy_Eta1_Ne->SetLineColor(kGreen);
    prof_EnergyFractionVsEnergy_Eta1_Ne->SetMarkerStyle(20);
    prof_EnergyFractionVsEnergy_Eta1_Ne->SetMarkerColor(kGreen);

    TCanvas *c1 = new TCanvas("c1", "Leading jet energy fraction", 2 * 600, 2 * 410);
    DrawPaperCanvasSettings(c1, 0.081, 0.03, 0.018, 0.11);
    c1->cd();

    TH2D *jesframe = new TH2D("jesframe", "", 1200, JESMinX, JESMaxX, 2000, -0.55, 0.1);
    SetStyleHistoTH2ForGraphs(jesframe, "#it{E}_{part} (GeV)", "JES", 0.85 * textSize * 1.1, textSize * 1.1, 0.85 * textSize * 1.1, textSize * 1.1, 0.93, 0.75, 510, 510, 42, 62);

    prof_EnergyFractionVsEnergy_Eta0_Ch->GetYaxis()->SetRangeUser(-0.6, 0.);
    prof_EnergyFractionVsEnergy_Eta0_Ch->Draw("same");
    prof_EnergyFractionVsEnergy_Eta1_Ch->Draw("same");
    // prof_EnergyFractionVsEnergy_Eta2->Draw("same");

    prof_EnergyFractionVsEnergy_Eta0_Ne->Draw("same");
    prof_EnergyFractionVsEnergy_Eta1_Ne->Draw("same");

    TLegend *leg2 = GetAndSetLegend2(0.12, 0.88 - 3 * 1.0 * textSize, 0.25, 0.95, textSize, 1, "", 42, 0.35);
    DrawSetMarker(prof_EnergyFractionVsEnergy_Eta0_Ch, marker[0], markerS[0] * 1.2, colors[0], colors[0]);
    DrawSetMarker(prof_EnergyFractionVsEnergy_Eta1_Ch, marker[1], markerS[1] * 1.2, colors[1], colors[1]);
    DrawSetMarker(prof_EnergyFractionVsEnergy_Eta0_Ne, markerMC[0], markerS[0] * 1.2, colorsMC[0], colorsMC[0]);
    DrawSetMarker(prof_EnergyFractionVsEnergy_Eta1_Ne, markerMC[1], markerS[1] * 1.2, colorsMC[1], colorsMC[1]);

    jesframe->Draw("axis");

    prof_EnergyFractionVsEnergy_Eta0_Ch->Draw("same");
    prof_EnergyFractionVsEnergy_Eta1_Ch->Draw("same");
    prof_EnergyFractionVsEnergy_Eta0_Ne->Draw("same");
    prof_EnergyFractionVsEnergy_Eta1_Ne->Draw("same");
    leg2->AddEntry(prof_EnergyFractionVsEnergy_Eta0_Ch, "#pi^{+}:  4.0 < #it{#eta} < 4.5", "p");
    leg2->AddEntry(prof_EnergyFractionVsEnergy_Eta1_Ch, "#pi^{+}:  4.5 < #it{#eta} < 4.9", "p");
    leg2->AddEntry(prof_EnergyFractionVsEnergy_Eta0_Ne, "#pi^{0}:  4.0 < #it{#eta} < 4.5", "p");
    leg2->AddEntry(prof_EnergyFractionVsEnergy_Eta1_Ne, "#pi^{0}:  4.5 < #it{#eta} < 4.9", "p");

    leg2->Draw("same");
    drawLatexAdd("ALICE simulation, Single #pi^{+}, #pi^{0}", 0.94, 0.965 - 1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("FoCal upgrade", 0.94, 0.965 - 2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("jets, anti-#it{k}_{T}, #it{R} = 0.6, 4.0 < #it{#eta}_{jet} < 4.9", 0.94, 0.965 - 3 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#Delta#it{E} = (#it{E}_{det} #font[122]{-} #it{E}_{part})/#it{E}_{part}", 0.43, 0.5 - 5.2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);

    c1->SaveAs("figures/SinglePion_JES_R06.pdf");

    TCanvas *c2 = new TCanvas("c2", "Leading jet energy resolution");
    c2->cd();
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.025);

    gPad->SetTickx();
    gPad->SetTicky();

    TH1D *hResolution_Eta0_Ch = new TH1D("hResolution_Eta0_Ch", "Energy resolution", 24, 0, 120);
    hResolution_Eta0_Ch->SetTitle("Leading jet energy resolution vs pions energy vs eta;#it{E}_{MC};JER");
    hResolution_Eta0_Ch->SetLineColor(kBlack);
    hResolution_Eta0_Ch->SetMarkerStyle(21);
    hResolution_Eta0_Ch->SetMarkerColor(kBlack);

    TH1D *hResolution_Eta1_Ch = new TH1D("hResolution_Eta1_Ch", "Energy resolution", 24, 0, 120);
    hResolution_Eta1_Ch->SetLineColor(kRed);
    hResolution_Eta1_Ch->SetMarkerStyle(20);
    hResolution_Eta1_Ch->SetMarkerColor(kRed);

    TH1D *hResolution_Eta0_Ne = new TH1D("hResolution_Eta0_Ne", "Energy resolution", 24, 0, 120);
    hResolution_Eta0_Ne->SetLineColor(kBlue);
    hResolution_Eta0_Ne->SetMarkerStyle(21);
    hResolution_Eta0_Ne->SetMarkerColor(kBlue);

    TH1D *hResolution_Eta1_Ne = new TH1D("hResolution_Eta1_Ne", "Energy resolution", 24, 0, 120);
    hResolution_Eta1_Ne->SetLineColor(kGreen);
    hResolution_Eta1_Ne->SetMarkerStyle(20);
    hResolution_Eta1_Ne->SetMarkerColor(kGreen);

    for (Int_t ibin = 1; ibin <= 24; ibin++)
    {
        TH1D *JES_Eta0_Ch = hLeadingJetFractionVsEnergy_Eta0_Ch->ProjectionY(Form("JES_Eta0_Ch_%d", ibin), ibin, ibin);
        hResolution_Eta0_Ch->SetBinContent(ibin, JES_Eta0_Ch->GetStdDev());
        hResolution_Eta0_Ch->SetBinError(ibin, JES_Eta0_Ch->GetStdDevError());

        TH1D *JES_Eta1_Ch = hLeadingJetFractionVsEnergy_Eta1_Ch->ProjectionY(Form("JES_Eta1_Ch_%d", ibin), ibin, ibin);
        hResolution_Eta1_Ch->SetBinContent(ibin, JES_Eta1_Ch->GetStdDev());
        hResolution_Eta1_Ch->SetBinError(ibin, JES_Eta1_Ch->GetStdDevError());

        TH1D *JES_Eta0_Ne = hLeadingJetFractionVsEnergy_Eta0_Ne->ProjectionY(Form("JES_Eta0_Ne_%d", ibin), ibin, ibin);
        hResolution_Eta0_Ne->SetBinContent(ibin, JES_Eta0_Ne->GetStdDev());
        hResolution_Eta0_Ne->SetBinError(ibin, JES_Eta0_Ne->GetStdDevError());

        TH1D *JES_Eta1_Ne = hLeadingJetFractionVsEnergy_Eta1_Ne->ProjectionY(Form("JES_Eta1_Ne_%d", ibin), ibin, ibin);
        hResolution_Eta1_Ne->SetBinContent(ibin, JES_Eta1_Ne->GetStdDev());
        hResolution_Eta1_Ne->SetBinError(ibin, JES_Eta1_Ne->GetStdDevError());
    }

    hResolution_Eta0_Ch->GetYaxis()->SetRangeUser(0, 0.4);
    hResolution_Eta0_Ch->Draw();
    hResolution_Eta1_Ch->Draw("same");
    hResolution_Eta0_Ne->Draw("same");
    hResolution_Eta1_Ne->Draw("same");

    TLatex *ltx_Sand_Ch_Res = new TLatex(45, 0.37, "Charged Pions");
    ltx_Sand_Ch_Res->SetTextColor(kBlack);
    ltx_Sand_Ch_Res->Draw();

    TLatex *ltx_Sand_Ne_Res = new TLatex(800, 0.37, "Neutral Pions");
    ltx_Sand_Ne_Res->SetTextColor(kBlack);
    ltx_Sand_Ne_Res->Draw();
}