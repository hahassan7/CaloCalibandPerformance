#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"
#include "TLegend.h"
#include "TProfile.h"
#include "TStyle.h"
#include "TGraphErrors.h"
#include "include/paperPlotsHeader.h"

double textSize = 0.04;
double textSizeLabels = 0.05;

void PlotDetResolution()
{

    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);

    bool doElectrons = true;
    bool doEnergy = true;
    float maxEnergy = doEnergy ? 1200 : 70.;
    float nBins = doEnergy ? 24 : 14;

    bool drawElectronRes = true;
    bool doGauss = false;

    float maxResHist = doElectrons ? 0.12 : 0.5;

    TString ResTitle = doEnergy ? "Resoltion;#it{E}_{MC} (GeV);#sigma(#it{E})/#it{E}" : "Resoltion;Truth #it{p}_{T} (GeV/#it{c});#sigma(#it{p}_{T})/#it{p}_{T}";
    TString MeanDETitle = doEnergy ? "Mean #Delta #it{E} versus #it{E}_{MC};#it{E}_{MC} (GeV);<#Delta #it{E}>" : "Mean #Delta #it{p}_{T} versus Truth #it{p}_{T};Truth #it{p}_{T} (GeV);<#Delta #it{p}_{T}>";

    TString DETitle_Sandwich = doEnergy ? "(#it{E}_{tot} #font[122]{-} #it{E}_{MC})/#it{E}_{MC} for Sandwich HCAL;#it{E}_{MC} (GeV);(#it{E}_{tot} #font[122]{-} #it{E}_{MC})/#it{E}_{MC}" : "(Clust #it{p}_{T} #font[122]{-} Truth #it{p}_{T})/Truth#it{p}_{T} for Sandwich HCAL;#it{p}_{T} (GeV/#it{c});(Clust #it{p}_{T} #font[122]{-} Truth#it{p}_{T})/Truth#it{p}_{T}";
    TString DETitle_Spaghetti = doEnergy ? "(#it{E}_{tot} #font[122]{-} #it{E}_{MC})/#it{E}_{MC} for Spaghetti HCAL;#it{E}_{MC} (GeV);(#it{E}_{tot} #font[122]{-} #it{E}_{MC})/#it{E}_{MC}" : "(Clust #it{p}_{T} #font[122]{-} Truth #it{p}_{T})/Truth#it{p}_{T} for Spaghetti HCAL;#it{p}_{T} (GeV/#it{c});(Clust #it{p}_{T} #font[122]{-} Truth#it{p}_{T})/Truth#it{p}_{T}";

    TFile *fileSpaghetti = doElectrons ? TFile::Open("Data/AnalysisClusters_BoxElectrons_Spaghetti.root") : TFile::Open("Data/AnalysisClusters_BoxPiPlus_Spaghetti.root");
    TFile *fileSandwich = doElectrons ? TFile::Open("Data/AnalysisClusters_BoxElectrons_Sandwich.root") : TFile::Open("Data/AnalysisClusters_BoxPiPlus_Sandwich.root");

    TH2D *hClustEPartEOverEreal_Spaghetti = doEnergy ? (TH2D *)fileSpaghetti->Get("hClustERealEVsRealOverReal") : (TH2D *)fileSpaghetti->Get("hClustPRealPVsRealOverReal");
    hClustEPartEOverEreal_Spaghetti->SetTitle(DETitle_Spaghetti.Data());
    hClustEPartEOverEreal_Spaghetti->GetXaxis()->SetRangeUser(0, maxEnergy);
    TProfile *prof_hClustEPartEOverEreal_Spaghetti = (TProfile *)hClustEPartEOverEreal_Spaghetti->ProfileX("prof_hClustEPartEOverEreal_Spaghetti");
    TH2D *hClustEPartEOverEreal_Sandwich = doEnergy ? (TH2D *)fileSandwich->Get("hClustERealEVsRealOverReal") : (TH2D *)fileSandwich->Get("hClustPRealPVsRealOverReal");
    hClustEPartEOverEreal_Sandwich->SetTitle(DETitle_Sandwich.Data());
    hClustEPartEOverEreal_Sandwich->GetXaxis()->SetRangeUser(0, maxEnergy);
    TProfile *prof_hClustEPartEOverEreal_Sandwich = (TProfile *)hClustEPartEOverEreal_Sandwich->ProfileX("prof_hClustEPartEOverEreal_Sandwich");

    TH1D *hMeanDeltaE_Spaghetti = new TH1D("hMeanDeltaE_Spaghetti", MeanDETitle.Data(), nBins, 0, maxEnergy);
    hMeanDeltaE_Spaghetti->GetXaxis()->SetRangeUser(0, maxEnergy);
    hMeanDeltaE_Spaghetti->SetLineWidth(2);
    TH1D *hMeanDeltaE_Sandwich = new TH1D("hMeanDeltaE_Sandwich", MeanDETitle.Data(), nBins, 0, maxEnergy);
    hMeanDeltaE_Sandwich->GetXaxis()->SetRangeUser(0, maxEnergy);
    hMeanDeltaE_Sandwich->SetLineWidth(2);

    TH1D *hResolution_Spaghetti = new TH1D("hResolution_Spaghetti", ResTitle.Data(), nBins, 0, maxEnergy);
    hResolution_Spaghetti->GetYaxis()->SetRangeUser(0, maxResHist);
    TH1D *hResolution_Sandwich = new TH1D("hResolution_Sandwich", ResTitle.Data(), nBins, 0, maxEnergy);
    hResolution_Sandwich->GetYaxis()->SetRangeUser(0, maxResHist);

    TH1D *hResolution_Spaghetti_dist = new TH1D("hResolution_Spaghetti_dist", ResTitle.Data(), nBins, 0, maxEnergy);
    hResolution_Spaghetti_dist->GetYaxis()->SetRangeUser(0, maxResHist);
    TH1D *hResolution_Sandwich_dist = new TH1D("hResolution_Sandwich_dist", ResTitle.Data(), nBins, 0, maxEnergy);
    hResolution_Sandwich_dist->GetYaxis()->SetRangeUser(0, maxResHist);

    TH1D *hResolution_Spaghetti_gauss = new TH1D("hResolution_Spaghetti_gauss", ResTitle.Data(), nBins, 0, maxEnergy);
    hResolution_Spaghetti_gauss->GetYaxis()->SetRangeUser(0, maxResHist);
    TH1D *hResolution_Sandwich_gauss = new TH1D("hResolution_Sandwich_gauss", ResTitle.Data(), nBins, 0, maxEnergy);
    hResolution_Sandwich_gauss->GetYaxis()->SetRangeUser(0, maxResHist);

    TCanvas *c1 = new TCanvas("c1", "c1: response slice", 1200, 1200);
    c1->Divide(doEnergy ? 5 : 3, 5);

    for (Int_t ibin = 1; ibin <= nBins; ibin++)
    {
        c1->cd(ibin);
        gPad->SetLogy();
        auto eresp_Spaghetti = (TH1F *)hClustEPartEOverEreal_Spaghetti->ProjectionY(Form("eresp_Spaghetti_%d", ibin), ibin, ibin);
        eresp_Spaghetti->Rebin();
        // eresp_Spaghetti->Rebin();
        // eresp_Spaghetti->Rebin();
        eresp_Spaghetti->Scale(1. / eresp_Spaghetti->Integral());
        if (doEnergy)
        {
            eresp_Spaghetti->SetTitle(Form("(ClustE - TruthE)/TruthE for %d < E < %d", (ibin - 1) * 50, (ibin)*50));
        }
        else
        {
            eresp_Spaghetti->SetTitle(Form("(Clust#it{p}_{T} - Truth#it{p}_{T})/Truth#it{p}_{T} for %d < #it{p}_{T} < %d", (ibin - 1) * 5, (ibin)*5));
        }
        eresp_Spaghetti->SetLineColor(kRed);
        eresp_Spaghetti->Draw();
        auto eresp_Sandwich = (TH1F *)hClustEPartEOverEreal_Sandwich->ProjectionY(Form("eresp_Sandwich_%d", ibin), ibin, ibin);
        eresp_Sandwich->Rebin();
        eresp_Sandwich->Scale(1. / eresp_Sandwich->Integral());
        if (doEnergy)
        {
            eresp_Sandwich->SetTitle(Form("(ClustE - TruthE)/TruthE for %d < E < %d", (ibin - 1) * 50, (ibin)*50));
        }
        else
        {
            eresp_Sandwich->SetTitle(Form("(Clust#it{p}_{T} - Truth#it{p}_{T})/Truth#it{p}_{T} for %d < #it{p}_{T} < %d", (ibin - 1) * 5, (ibin)*5));
        }
        eresp_Sandwich->SetLineColor(kBlue);

        // eresp_Spaghetti->GetYaxis()->SetRangeUser(0, std::max(eresp_Spaghetti->GetMaximum(), eresp_Sandwich->GetMaximum()));
        eresp_Spaghetti->GetYaxis()->SetRangeUser(1e-4, std::max(eresp_Spaghetti->GetMaximum(), eresp_Sandwich->GetMaximum()));

        auto f1 = new TF1("f1", "crystalball", -1, 1);
        f1->SetLineWidth(1);
        if (doElectrons)
        {
            f1->SetParameters(eresp_Spaghetti->GetMaximum(), -0.1, 0.019, 0.6, 1.5);
        }
        else
        {
            f1->SetParameters(eresp_Spaghetti->GetMaximum(), eresp_Spaghetti->GetMean(), 0.08, 0.6, 1.5);
        }

        auto f2 = new TF1("f2", "crystalball", -1, 1);
        f2->SetLineColor(kBlue);
        f2->SetLineWidth(1);
        if (doElectrons)
        {
            f2->SetParameters(eresp_Sandwich->GetMaximum(), -0.02, 0.02, 0.6, 1.6);
        }
        else
        {
            f2->SetParameters(eresp_Sandwich->GetMaximum(), eresp_Sandwich->GetMean(), 0.15, 0.6, 1.5);
        }

        eresp_Spaghetti->Fit("f1", "", "same", -0.6, 1.);
        eresp_Sandwich->Fit("f2", "", "same", -0.6, 1.);

        hMeanDeltaE_Spaghetti->SetBinContent(ibin, eresp_Spaghetti->GetFunction("f1")->GetParameter(1));
        hMeanDeltaE_Spaghetti->SetBinError(ibin, eresp_Spaghetti->GetFunction("f1")->GetParError(1));

        hMeanDeltaE_Sandwich->SetBinContent(ibin, eresp_Sandwich->GetFunction("f2")->GetParameter(1));
        hMeanDeltaE_Sandwich->SetBinError(ibin, eresp_Sandwich->GetFunction("f2")->GetParError(1));

        hResolution_Spaghetti->SetBinContent(ibin, eresp_Spaghetti->GetFunction("f1")->GetParameter(2));
        hResolution_Spaghetti->SetBinError(ibin, eresp_Spaghetti->GetFunction("f1")->GetParError(2));

        hResolution_Sandwich->SetBinContent(ibin, eresp_Sandwich->GetFunction("f2")->GetParameter(2));
        hResolution_Sandwich->SetBinError(ibin, eresp_Sandwich->GetFunction("f2")->GetParError(2));

        if (doGauss)
        {
            auto Gauss1 = new TF1("Gauss1", "gaus", -1, 1);
            Gauss1->SetParameters(f1->GetParameter(0), f1->GetParameter(1), f1->GetParameter(2));
            auto Gauss2 = new TF1("Gauss2", "gaus", -1, 1);
            Gauss2->SetParameters(f2->GetParameter(0), f2->GetParameter(1), f2->GetParameter(2));

            eresp_Spaghetti->Fit("Gauss1", "R+", "same", -1., 1.);
            eresp_Sandwich->Fit("Gauss2", "R+", "same", -1., 1.);

            hResolution_Spaghetti_gauss->SetBinContent(ibin, eresp_Spaghetti->GetFunction("Gauss1")->GetParameter(2));
            hResolution_Spaghetti_gauss->SetBinError(ibin, eresp_Spaghetti->GetFunction("Gauss1")->GetParError(2));

            hResolution_Sandwich_gauss->SetBinContent(ibin, eresp_Sandwich->GetFunction("Gauss2")->GetParameter(2));
            hResolution_Sandwich_gauss->SetBinError(ibin, eresp_Sandwich->GetFunction("Gauss2")->GetParError(2));

            hResolution_Spaghetti_dist->SetBinContent(ibin, eresp_Spaghetti->GetStdDev());
            hResolution_Spaghetti_dist->SetBinError(ibin, eresp_Spaghetti->GetStdDevError());

            hResolution_Sandwich_dist->SetBinContent(ibin, eresp_Sandwich->GetStdDev());
            hResolution_Sandwich_dist->SetBinError(ibin, eresp_Sandwich->GetStdDevError());
        }
    }

    TLine *UnityLine = new TLine(0, 0, maxEnergy, 0);
    UnityLine->SetLineWidth(2);
    UnityLine->SetLineColor(kBlack);
    UnityLine->SetLineStyle(2);

    TLegend *legEdep = new TLegend(0.37, 0.62, 0.87, 0.74);
    // TLegend *legEdep = new TLegend(0.1, 0.9, 0.4, 1.0);
    legEdep->SetLineWidth(0);

    TCanvas *cResponseSpaghetti = new TCanvas("cResponseSpaghetti", "Energy deposited Spaghetti HCAL", 650, 650);
    cResponseSpaghetti->cd();

    SetStyleHistoTH2ForGraphs(hClustEPartEOverEreal_Spaghetti, "E_{part} (GeV)", "JES", 0.9 * textSize, textSize, 0.9 * textSize, textSize, 0.92, 1.2, 510, 510, 42, 62);
    hClustEPartEOverEreal_Spaghetti->SetTitle(DETitle_Sandwich.Data());

    gPad->SetTickx();
    gPad->SetTicky();
    // hClustEPartEOverEreal_Spaghetti->GetYaxis()->SetTitleOffset(1.35);
    hClustEPartEOverEreal_Spaghetti->Draw("colz");
    // hMeanDeltaE_Spaghetti->SetLineColor(kMagenta + 1);
    hMeanDeltaE_Spaghetti->SetLineColor(kRed);
    hMeanDeltaE_Spaghetti->SetMarkerColor(kRed);
    hMeanDeltaE_Spaghetti->SetMarkerStyle(8);
    hMeanDeltaE_Spaghetti->SetLineWidth(3);
    hMeanDeltaE_Spaghetti->Draw("E1,same");
    prof_hClustEPartEOverEreal_Spaghetti->SetLineColor(kMagenta + 1);
    prof_hClustEPartEOverEreal_Spaghetti->SetMarkerColor(kMagenta + 1);
    // prof_hClustEPartEOverEreal_Spaghetti->SetLineColor(kOrange);
    // prof_hClustEPartEOverEreal_Spaghetti->SetMarkerColor(kOrange);
    prof_hClustEPartEOverEreal_Spaghetti->SetMarkerStyle(8);
    prof_hClustEPartEOverEreal_Spaghetti->SetLineWidth(3);
    prof_hClustEPartEOverEreal_Spaghetti->Draw("E1,same");
    UnityLine->Draw("same");
    legEdep->AddEntry(hMeanDeltaE_Spaghetti, "Mean: Crystal Ball fit");
    legEdep->AddEntry(prof_hClustEPartEOverEreal_Spaghetti, "Mean: distribution");
    legEdep->SetTextFont(62);
    legEdep->SetTextSize(textSize);
    // legEdep->SetFillStyle(1001);
    // legEdep->SetFillColor(kWhite);
    legEdep->Draw();

    drawLatexAdd(Form("#bf{ALICE simulation, Single %s}", doElectrons ? "e^{-}" : "#pi^{+}"), 0.86, 0.88 - 1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#bf{FoCal upgrade}", 0.86, 0.88 - 2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd(Form("#bf{3.4 < #it{#eta}_{%s} < 5.5}", doElectrons ? "e^{-}" : "#pi^{+}"), 0.86, 0.88 - 3 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);

    gPad->RedrawAxis();
    gPad->RedrawAxis("G");

    cResponseSpaghetti->SaveAs(Form("figures/Eresponse%s_Spaghetti_Bold.pdf", doElectrons ? "" : "_HCAL"));

    TCanvas *cResponseSandwich = new TCanvas("cResponseSandwich", "Energy deposited Sandwich HCAL", 650, 650);
    cResponseSandwich->cd();

    SetStyleHistoTH2ForGraphs(hClustEPartEOverEreal_Sandwich, "E_{part} (GeV)", "JES", 0.9 * textSize, textSize, 0.9 * textSize, textSize, 0.92, 1.2, 510, 510, 42, 62);
    hClustEPartEOverEreal_Sandwich->SetTitle(DETitle_Sandwich.Data());

    gPad->SetTickx();
    gPad->SetTicky();
    // hClustEPartEOverEreal_Sandwich->GetYaxis()->SetTitleOffset(1.35);
    hClustEPartEOverEreal_Sandwich->Draw("colz");
    // hMeanDeltaE_Sandwich->SetLineColor(kMagenta + 1);
    hMeanDeltaE_Sandwich->SetLineColor(kRed);
    hMeanDeltaE_Sandwich->SetMarkerColor(kRed);
    hMeanDeltaE_Sandwich->SetMarkerStyle(8);
    hMeanDeltaE_Sandwich->SetLineWidth(3);
    hMeanDeltaE_Sandwich->Draw("E1,same");
    prof_hClustEPartEOverEreal_Sandwich->SetLineColor(kMagenta + 1);
    prof_hClustEPartEOverEreal_Sandwich->SetMarkerColor(kMagenta + 1);
    // prof_hClustEPartEOverEreal_Sandwich->SetLineColor(kOrange);
    // prof_hClustEPartEOverEreal_Sandwich->SetMarkerColor(kOrange);
    prof_hClustEPartEOverEreal_Sandwich->SetMarkerStyle(8);
    prof_hClustEPartEOverEreal_Sandwich->SetLineWidth(3);
    prof_hClustEPartEOverEreal_Sandwich->Draw("E1,same");
    UnityLine->Draw("same");
    legEdep->Draw();

    drawLatexAdd(Form("#bf{ALICE simulation, Single %s}", doElectrons ? "e^{-}" : "#pi^{+}"), 0.86, 0.88 - 1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#bf{FoCal upgrade}", 0.86, 0.88 - 2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd(Form("#bf{3.4 < #it{#eta}_{%s} < 5.5}", doElectrons ? "e^{-}" : "#pi^{+}"), 0.86, 0.88 - 3 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);

    gPad->RedrawAxis();
    gPad->RedrawAxis("G");

    cResponseSandwich->SaveAs(Form("figures/Eresponse%s_Sandwich_Bold.pdf", doElectrons ? "" : "_HCAL"));

    TCanvas *cResolution = new TCanvas("cResolution", "Energy Resolution", 800, 600);
    cResolution->SetCanvasSize(800, 600);
    cResolution->cd();
    gPad->SetTopMargin(0.02);
    gPad->SetRightMargin(0.04);
    gPad->SetLeftMargin(0.11);
    gPad->SetTickx();
    gPad->SetTicky();

    TH2D *ResFrame = new TH2D("ResFrame", "", 1200, 0, maxEnergy, 2000, 0, 0.35);
    SetStyleHistoTH2ForGraphs(ResFrame, "#it{E}_{part} (GeV)", "Res", 0.95 * textSizeLabels, textSizeLabels, 0.95 * textSizeLabels, textSizeLabels, 0.95, 1.15, 510, 510, 42, 62);
    ResFrame->SetTitle(ResTitle);
    ResFrame->Draw();
    hResolution_Spaghetti->SetLineColor(kRed + 1);
    hResolution_Spaghetti->SetLineWidth(2);
    hResolution_Spaghetti->SetMarkerStyle(8);
    hResolution_Spaghetti->SetMarkerColor(kRed + 1);
    hResolution_Spaghetti->Draw("same");

    hResolution_Sandwich->SetLineColor(kBlue);
    hResolution_Sandwich->SetLineWidth(2);
    hResolution_Sandwich->SetMarkerStyle(8);
    hResolution_Sandwich->SetMarkerColor(kBlue);
    hResolution_Sandwich->Draw("same");
    // hResolution_Spaghetti->Draw("same");

    TH1D *ResDetSpaghetti;
    if (drawElectronRes)
    {
        TFile *ResFits = TFile::Open("Data/ResolutionFits_Electrons.root");
        ResDetSpaghetti = (TH1D *)ResFits->Get("hResolution_Spaghetti");
        ResDetSpaghetti->SetLineColor(kBlack);
        ResDetSpaghetti->SetLineWidth(2);
        ResDetSpaghetti->SetMarkerStyle(8);
        ResDetSpaghetti->SetMarkerColor(kBlack);
        ResDetSpaghetti->GetFunction("fres_Spaghetti")->SetLineColor(kBlack);
        ResDetSpaghetti->GetFunction("fres_Spaghetti")->SetLineStyle(2);
        ResDetSpaghetti->GetFunction("fres_Spaghetti")->SetLineWidth(3);
        ResDetSpaghetti->Draw("same");
    }

    if (doGauss)
    {

        hResolution_Spaghetti_dist->SetLineColor(kGreen);
        hResolution_Spaghetti_dist->SetLineWidth(2);
        hResolution_Spaghetti_dist->Draw("same");

        hResolution_Spaghetti_gauss->SetLineColor(kBlack);
        hResolution_Spaghetti_gauss->SetLineWidth(2);
        hResolution_Spaghetti_gauss->Draw("same");

        hResolution_Sandwich_dist->SetLineColor(kMagenta + 1);
        hResolution_Sandwich_dist->SetLineWidth(2);
        hResolution_Sandwich_dist->Draw("same");

        hResolution_Sandwich_gauss->SetLineColor(kOrange);
        hResolution_Sandwich_gauss->SetLineWidth(2);
        hResolution_Sandwich_gauss->Draw("same");
    }

    if (doGauss)
    {
        TLegend *legRes = new TLegend();
        legRes->AddEntry(hResolution_Spaghetti, "Spaghetti Crystall sigma");
        legRes->AddEntry(hResolution_Spaghetti_dist, "Spaghetti StdDev dist");
        legRes->AddEntry(hResolution_Spaghetti_gauss, "Spaghetti Gauss sigma");

        legRes->AddEntry(hResolution_Sandwich, "Sandwich Crystall sigma");
        legRes->AddEntry(hResolution_Sandwich_dist, "Sandwich StdDev dist");
        legRes->AddEntry(hResolution_Sandwich_gauss, "Sandwich Gauss sigma");

        legRes->Draw();
    }
    else
    {

        TLegend *legResolution = GetAndSetLegend2(0.39, 0.5 - 3 * 1.0 * textSize, 0.64, 0.82, textSize, 1, "", 42, 0.35);

        TF1 *fres_Spaghetti = new TF1("fres_Spaghetti", "TMath::Sqrt([0]*[0]/x+[1]*[1])", 0, 1000);
        fres_Spaghetti->SetParameters(0.3, 0.01);
        fres_Spaghetti->SetLineColor(kRed + 1);
        fres_Spaghetti->SetLineStyle(2);
        fres_Spaghetti->SetLineWidth(3);
        hResolution_Spaghetti->Fit(fres_Spaghetti, "same");
        // TLatex *ltx_Spa = new TLatex(0.29, 0.65, Form("ECal + Spaghetti HCal (#pi^{+}), fit:  #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{E} + %.2f^{2}}", fres_Spaghetti->GetParameter(0), fres_Spaghetti->GetParameter(1)));
        // ltx_Spa->SetTextColor(kRed + 1);
        // ltx_Spa->SetNDC();
        // ltx_Spa->SetTextSizePixels(19);
        // ltx_Spa->Draw();

        legResolution->AddEntry(hResolution_Spaghetti, "FOCAL-E + FOCAL-H Spaghetti (#pi^{+})", "lp");
        legResolution->AddEntry(fres_Spaghetti, Form("fit:  #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{#it{E}} + %.2f^{2}}", fres_Spaghetti->GetParameter(0), fres_Spaghetti->GetParameter(1)), "l");

        TF1 *fres_Sandwich = new TF1("fres_Sandwich", "TMath::Sqrt([0]*[0]/x+[1]*[1])", 0, 1000);
        fres_Sandwich->SetLineColor(kBlue);
        fres_Sandwich->SetParameters(0.3, 0.01);
        fres_Sandwich->SetLineStyle(2);
        fres_Sandwich->SetLineWidth(3);
        hResolution_Sandwich->Fit(fres_Sandwich, "same");
        // TLatex *ltx_Sand = new TLatex(0.29, 0.57, Form("ECal + Sandwich HCal (#pi^{+}), fit:  #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{E} + %.2f^{2}}", fres_Sandwich->GetParameter(0), fres_Sandwich->GetParameter(1)));
        // ltx_Sand->SetTextColor(kBlue);
        // ltx_Sand->SetNDC();
        // ltx_Sand->SetTextSizePixels(19);
        // ltx_Sand->Draw();

        legResolution->AddEntry(hResolution_Sandwich, "FOCAL-E + FOCAL-H Sandwich (#pi^{+})", "lp");
        legResolution->AddEntry(fres_Sandwich, Form("fit:  #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{#it{E}} + %.2f^{2}}", fres_Sandwich->GetParameter(0), fres_Sandwich->GetParameter(1)), "l");

        if (drawElectronRes)
        {
            // TLatex *ltx_Spa_e = new TLatex(0.29, 0.49, Form("ECal + Spaghetti HCal (e^{-} ), fit:  #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{E} + %.2f^{2}}", ResDetSpaghetti->GetFunction("fres_Spaghetti")->GetParameter(0), ResDetSpaghetti->GetFunction("fres_Spaghetti")->GetParameter(1)));
            // ltx_Spa_e->SetTextColor(kBlack);
            // ltx_Spa_e->SetNDC();
            // ltx_Spa_e->SetTextSizePixels(19);
            // ltx_Spa_e->Draw();

            legResolution->AddEntry(ResDetSpaghetti, "FOCAL-E + FOCAL-H (e^{-} )", "lp");
            legResolution->AddEntry(ResDetSpaghetti->GetFunction("fres_Spaghetti"), Form("fit:  #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{#it{E}} + %.2f^{2}}", ResDetSpaghetti->GetFunction("fres_Spaghetti")->GetParameter(0), ResDetSpaghetti->GetFunction("fres_Spaghetti")->GetParameter(1)), "l");
        }

        legResolution->Draw();
    }

    drawLatexAdd("#bf{ALICE simulation, Single #pi^{+},e^{-}}", 0.92, 0.96 - 1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#bf{FoCal upgrade}", 0.92, 0.96 - 2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#bf{3.4 < #it{#eta} < 5.5}", 0.92, 0.96 - 3 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);

    bool doTestBeamComp = false;
    if (doTestBeamComp)
    {
        std::array<double, 8> EnergyBins = {60.000000, 80.000000, 100.000000, 150.000000, 200.000000, 250.000000, 300.000000, 350.000000};
        std::array<double, 8> EnRes = {0.221731, 0.202234, 0.180107, 0.154607, 0.138218, 0.126473, 0.120935, 0.116489};
        std::array<double, 8> Energy_Err = {0.0};
        // std::array<double, 8> Energy_Errh = {10.000000, 10.000000, 25.000000, 25.000000, 25.000000, 25.000000, 25.000000, 25.000000};
        // std::array<double, 8> Energy_Errl = {10.000000, 10.000000, 10.000000, 25.000000, 25.000000, 25.000000, 25.000000, 25.000000};
        std::array<double, 8> EnRes_Err = {0.002615, 0.00169999, 0.00152800, 0.001043, 0.00085199, 0.00169799, 0.00113799, 0.00089500};

        // TGraphAsymmErrors *graphResTB = new TGraphAsymmErrors(8, EnergyBins.data(), EnRes.data(), Energy_Errl.data(), Energy_Errh.data(), EnRes_Err.data(), EnRes_Err.data());

        TGraphErrors *graphResTB = new TGraphErrors(8, EnergyBins.data(), EnRes.data(), Energy_Err.data(), EnRes_Err.data());
        graphResTB->SetLineColor(kBlack);
        graphResTB->SetLineWidth(2);
        graphResTB->Draw("E0,same");

        TF1 *fres_Testbeam = new TF1("fres_Testbeam", "TMath::Sqrt([0]*[0]/x+[1]*[1])", 0, 1200);
        fres_Testbeam->SetParameters(0.3, 0.01);
        fres_Testbeam->SetLineColor(kBlack);
        graphResTB->Fit(fres_Testbeam, "same");
        fres_Testbeam->Draw("same");
        TLatex *ltx_TB = new TLatex(0.23, 0.55, Form("Testbeam HCAL fit (#pi^{+}): #sigma(#it{E})/#it{E} = #sqrt{#frac{%.2f^{2}}{E} + %.2f^{2}}", fres_Testbeam->GetParameter(0), fres_Testbeam->GetParameter(1)));
        ltx_TB->SetTextColor(kBlack);
        ltx_TB->SetNDC();
        ltx_TB->SetTextSizePixels(25);
        ltx_TB->Draw();
    }

    if (!doElectrons)
    {
        cResolution->SaveAs("figures/Eresolution_Comparison_All_Legends.pdf");
    }

    bool saveOutput = false;
    if (saveOutput)
    {
        TFile *fileoutput = new TFile("ResolutionFits.root", "RECREATE");
        fileoutput->cd();
        hResolution_Spaghetti->Write();
        hResolution_Sandwich->Write();
    }
}
/*
//__________________________________________________________________________________________________________

void drawLatexAdd(TString latextext, Double_t textcolumn, Double_t textrow, Double_t textSizePixel, Bool_t setFont = kFALSE, Bool_t setFont2 = kFALSE, Bool_t alignRight = kFALSE, Color_t textcolor = kBlack, Float_t angle = 0., Bool_t alignBottomRight = kFALSE)
{
    TLatex *latexDummy = new TLatex(textcolumn, textrow, latextext);
    SetStyleTLatex(latexDummy, textSizePixel, 4, textcolor);
    if (setFont)
        latexDummy->SetTextFont(62);
    if (setFont2)
        latexDummy->SetTextFont(43);
    if (alignRight)
        latexDummy->SetTextAlign(31);
    if (alignBottomRight)
        latexDummy->SetTextAlign(33);
    if (angle != 0.)
        latexDummy->SetTextAngle(angle);
    latexDummy->SetTextColor(textcolor);
    latexDummy->Draw();
}

//__________________________________________________________________________________________________________
void SetStyleTLatex(
    TLatex *text,
    Size_t textSize,
    Width_t lineWidth,
    Color_t textColor = 1,
    Font_t textFont = 42,
    Bool_t kNDC = kTRUE,
    Short_t align = 11)
{
    if (kNDC)
    {
        text->SetNDC();
    }
    text->SetTextFont(textFont);
    text->SetTextColor(textColor);
    text->SetTextSize(textSize);
    text->SetLineWidth(lineWidth);
    text->SetTextAlign(align);
}
*/