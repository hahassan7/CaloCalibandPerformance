#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLine.h"
#include "TStyle.h"
#include "TProfile.h"
#include "TLegend.h"
#include "include/paperPlotsHeader.h"

float textSize = 0.07;
float textSizeLabels = 0.08;

void PlotResolutionEta()
{

    bool doElectrons = false;
    bool doEnergy = true;
    float maxEnergy = doEnergy ? 1200 : 70.;
    float nBins = doEnergy ? 24 : 14;

    bool doGauss = false;

    float maxResHist = doElectrons ? 0.12 : 0.35;

    TString etaRange[] = {"3.5 < #it{#eta}_{#pi^{+}} < 4.0", "4.0 < #it{#eta}_{#pi^{+}} < 4.5", "4.5 < #it{#eta}_{#pi^{+}} < 5.0", "5.0 < #it{#eta}_{#pi^{+}} < 5.5"};

    TString ResTitle = doEnergy ? "Resoltion;#it{E}_{MC} (GeV);#sigma(#it{E})/#it{E}" : "Resoltion;Truth #it{p}_{T} (GeV/#it{c});#sigma(#it{p}_{T})/#it{p}_{T}";
    TString MeanDETitle = doEnergy ? "Mean #Delta #it{E} versus #it{E}_{MC};#it{E}_{MC} (GeV);<#Delta#it{E}>" : "Mean #Delta #it{p}_{T} versus Truth #it{p}_{T};Truth #it{p}_{T} (GeV);<#Delta#it{p}_{T}>";

    Color_t colors[4] = {kBlack, kRed, kGreen + 2, kBlue};

    TString DETitle = doEnergy ? "(#it{E}_{Clust} #font[122]{-} #it{E}_{MC})/#it{E}_{MC} for Sandwich HCAL;#it{E}_{MC} (GeV);(#it{E}_{Clust} #font[122]{-} #it{E}_{MC})/#it{E}_{MC}" : "(Clust #it{p}_{T} #font[122]{-} Truth #it{p}_{T})/Truth#it{p}_{T} for Sandwich HCAL;#it{p}_{T} (GeV/#it{c});(Clust #it{p}_{T} #font[122]{-} Truth#it{p}_{T})/Truth#it{p}_{T}";

    TFile *fileSpaghetti = doElectrons ? TFile::Open("Data/AnalysisClusters_BoxElectrons_Spaghetti.root") : TFile::Open("Data/AnalysisClusters_BoxPiPlus_Spaghetti.root");
    TFile *fileSandwich = doElectrons ? TFile::Open("Data/AnalysisClusters_BoxElectrons_Sandwich.root") : TFile::Open("Data/AnalysisClusters_BoxPiPlus_Sandwich.root");

    TH2D *hClustEPartEOverEreal_Spaghetti[4];
    TH2D *hClustEPartEOverEreal_Sandwich[4];
    TProfile *prof_hClustEPartEOverEreal_Spaghetti[4];
    TProfile *prof_hClustEPartEOverEreal_Sandwich[4];

    TH1D *hMeanDeltaE_Spaghetti[4];
    TH1D *hMeanDeltaE_Sandwich[4];
    TH1D *hResolution_Spaghetti[4];
    TH1D *hResolution_Sandwich[4];

    for (int ibin = 0; ibin < 4; ibin++)
    {
        hClustEPartEOverEreal_Spaghetti[ibin] = doEnergy ? (TH2D *)fileSpaghetti->Get(Form("hClustERealEVsRealOverReal_EtaBin%d", ibin)) : (TH2D *)fileSpaghetti->Get(Form("hClustPRealPVsRealOverReal_EtaBin%d", ibin));
        // hClustEPartEOverEreal_Spaghetti[ibin]->SetTitle(Form("%s%s", etaRange[ibin].Data(), ";E_{MC} (GeV);(E_{Clust} - E_{MC})/E_{MC}"));
        hClustEPartEOverEreal_Spaghetti[ibin]->SetTitle(Form("%s%s", etaRange[ibin].Data(), ";#it{p}_{T}^{MC} (GeV/#it{c});(#it{p}_{T}^{Clust} - #it{p}_{T}^{MC})/#it{p}_{T}^{MC}"));
        hClustEPartEOverEreal_Spaghetti[ibin]->GetXaxis()->SetRangeUser(0, maxEnergy);
        prof_hClustEPartEOverEreal_Spaghetti[ibin] = (TProfile *)hClustEPartEOverEreal_Spaghetti[ibin]->ProfileX(Form("prof_hClustEPartEOverEreal_Spaghetti_EtaBin%d", ibin));
        hClustEPartEOverEreal_Sandwich[ibin] = doEnergy ? (TH2D *)fileSandwich->Get(Form("hClustERealEVsRealOverReal_EtaBin%d", ibin)) : (TH2D *)fileSandwich->Get(Form("hClustPRealPVsRealOverReal_EtaBin%d", ibin));
        // hClustEPartEOverEreal_Sandwich[ibin]->SetTitle(Form("%s%s", etaRange[ibin].Data(), ";E_{MC} (GeV);(E_{Clust} - E_{MC})/E_{MC}"));
        hClustEPartEOverEreal_Sandwich[ibin]->SetTitle(Form("%s%s", etaRange[ibin].Data(), ";#it{p}_{T}^{MC} (GeV/#it{c});(#it{p}_{T}^{Clust} - #it{p}_{T}^{MC})/#it{p}_{T}^{MC}"));
        hClustEPartEOverEreal_Sandwich[ibin]->GetXaxis()->SetRangeUser(0, maxEnergy);
        prof_hClustEPartEOverEreal_Sandwich[ibin] = (TProfile *)hClustEPartEOverEreal_Sandwich[ibin]->ProfileX(Form("prof_hClustEPartEOverEreal_Sandwich_EtaBin%d", ibin));

        hMeanDeltaE_Spaghetti[ibin] = new TH1D(Form("hMeanDeltaE_Spaghetti_EtaBin_%d", ibin), MeanDETitle.Data(), nBins, 0, maxEnergy);
        hMeanDeltaE_Spaghetti[ibin]->GetXaxis()->SetRangeUser(0, maxEnergy);
        hMeanDeltaE_Spaghetti[ibin]->SetLineWidth(2);
        hMeanDeltaE_Sandwich[ibin] = new TH1D(Form("hMeanDeltaE_Sandwich_EtaBin_%d", ibin), MeanDETitle.Data(), nBins, 0, maxEnergy);
        hMeanDeltaE_Sandwich[ibin]->GetXaxis()->SetRangeUser(0, maxEnergy);
        hMeanDeltaE_Sandwich[ibin]->SetLineWidth(2);

        hResolution_Spaghetti[ibin] = new TH1D(Form("hResolution_Spaghetti_EtaBin_%d", ibin), ResTitle.Data(), nBins, 0, maxEnergy);
        hResolution_Spaghetti[ibin]->GetYaxis()->SetRangeUser(1e-4, maxResHist);
        hResolution_Sandwich[ibin] = new TH1D(Form("hResolution_Sandwich_EtaBin_%d", ibin), ResTitle.Data(), nBins, 0, maxEnergy);
        hResolution_Sandwich[ibin]->GetYaxis()->SetRangeUser(1e-4, maxResHist);
    }

    TFile *ResFits = TFile::Open("Data/ResolutionFits_PiPlus.root");
    TH1D *ResDetSpaghetti = (TH1D *)ResFits->Get("hResolution_Spaghetti");
    TH1D *ResDetSandwich = (TH1D *)ResFits->Get("hResolution_Sandwich");

    TCanvas *c1 = new TCanvas("c1", "c1: response slice Spaghetti", 1200, 1200);
    c1->Divide(doEnergy ? 5 : 3, 5);

    TCanvas *c2 = new TCanvas("c2", "c2: response slice Sandwich", 1200, 1200);
    c2->Divide(doEnergy ? 5 : 3, 5);

    TLine *UnityLine = new TLine(0, 0, maxEnergy, 0);
    UnityLine->SetLineWidth(2);
    UnityLine->SetLineColor(kBlack);
    UnityLine->SetLineStyle(2);

    TCanvas *c3 = new TCanvas("c3", "Energy deposited HCAL Spaghetti", 800, 600);
    c3->Divide(2, 2);

    TCanvas *c4 = new TCanvas("c4", "Energy deposited HCAL Sandwich", 800, 600);
    c4->Divide(2, 2);

    TCanvas *cResSpaghetti = new TCanvas("cResSpaghetti", "Energy Resolution Spaghetti", 800, 600);
    cResSpaghetti->SetCanvasSize(800, 600);
    cResSpaghetti->cd();
    gPad->SetMargin(0., 0., 0., 0.);
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TPad *pad1 = new TPad("pad1", "pad1", 0, 0.35, 1, 1.0);
    pad1->SetBottomMargin(0);
    pad1->SetTicky();
    pad1->SetTickx();
    pad1->SetTopMargin(0.025);
    pad1->SetRightMargin(0.04);
    pad1->SetLeftMargin(0.11);
    pad1->Draw();
    pad1->cd();
    cResSpaghetti->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0, 0.00, 1, 0.35);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.29);
    pad2->SetRightMargin(0.04);
    pad2->SetLeftMargin(0.11);
    pad2->SetTicky();
    pad2->SetTickx();
    pad2->SetGridy();
    pad2->Draw();
    pad2->cd();

    TCanvas *cResSandwich = new TCanvas("cResSandwich", "Energy Resolution Sandwich", 800, 600);
    cResSandwich->cd();
    gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
    TPad *pad3 = new TPad("pad3", "pad3", 0, 0.3, 1, 1.0);
    pad3->SetBottomMargin(0);
    pad3->SetTicky();
    pad3->SetTickx();
    pad3->Draw();
    pad3->cd();
    cResSandwich->cd();
    TPad *pad4 = new TPad("pad4", "pad4", 0, 0.00, 1, 0.3);
    pad4->SetTopMargin(0);
    pad4->SetBottomMargin(0.2);
    pad4->SetTicky();
    pad4->SetTickx();
    pad4->SetGridy();
    pad4->Draw();
    pad4->cd();

    TLegend *leg = new TLegend(0.15, 0.5, 0.47, 0.93);
    leg->SetLineWidth(0);

    for (int ieta = 0; ieta < 4; ieta++)
    {
        for (Int_t ibin = 1; ibin <= nBins; ibin++)
        {
            c1->cd(ibin);
            gPad->SetLogy();
            auto eresp_Spaghetti = (TH1F *)hClustEPartEOverEreal_Spaghetti[ieta]->ProjectionY(Form("eresp_Spaghetti_EtaBin_%d_%d", ieta, ibin), ibin, ibin);
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
            eresp_Spaghetti->SetLineColor(ieta + 1);
            eresp_Spaghetti->Draw("same");

            auto f1 = new TF1("f1", "crystalball", -1, 1);
            f1->SetLineColor(ieta + 1);
            f1->SetLineWidth(1);
            if (doElectrons)
            {
                f1->SetParameters(eresp_Spaghetti->GetMaximum(), -0.1, 0.019, 0.6, 1.5);
            }
            else
            {
                f1->SetParameters(eresp_Spaghetti->GetMaximum(), eresp_Spaghetti->GetMean(), 0.1, 0.6, 1.5);
            }
            eresp_Spaghetti->Fit("f1", "", "same", -0.9, 1.);

            if (eresp_Spaghetti->GetEntries())
            {
                hMeanDeltaE_Spaghetti[ieta]->SetBinContent(ibin, eresp_Spaghetti->GetFunction("f1")->GetParameter(1));
                hMeanDeltaE_Spaghetti[ieta]->SetBinError(ibin, eresp_Spaghetti->GetFunction("f1")->GetParError(1));

                hResolution_Spaghetti[ieta]->SetBinContent(ibin, eresp_Spaghetti->GetFunction("f1")->GetParameter(2));
                hResolution_Spaghetti[ieta]->SetBinError(ibin, eresp_Spaghetti->GetFunction("f1")->GetParError(2));
            }
            else
            {
                hMeanDeltaE_Spaghetti[ieta]->SetBinContent(ibin, 0.);
                hMeanDeltaE_Spaghetti[ieta]->SetBinError(ibin, 0.);

                hResolution_Spaghetti[ieta]->SetBinContent(ibin, 0.);
                hResolution_Spaghetti[ieta]->SetBinError(ibin, 0.);
            }

            c2->cd(ibin);
            gPad->SetLogy();

            auto eresp_Sandwich = (TH1F *)hClustEPartEOverEreal_Sandwich[ieta]->ProjectionY(Form("eresp_Sandwich_EtaBin_%d_%d", ieta, ibin), ibin, ibin);
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
            eresp_Sandwich->SetLineColor(ieta + 1);

            // eresp_Spaghetti->GetYaxis()->SetRangeUser(0, std::max(eresp_Spaghetti->GetMaximum(), eresp_Sandwich->GetMaximum()));
            eresp_Spaghetti->GetYaxis()->SetRangeUser(1e-4, std::max(eresp_Spaghetti->GetMaximum(), eresp_Sandwich->GetMaximum()));

            auto f2 = new TF1("f2", "crystalball", -1, 1);
            f2->SetLineColor(ieta + 1);
            f2->SetLineWidth(1);
            if (doElectrons)
            {
                f2->SetParameters(eresp_Sandwich->GetMaximum(), -0.1, 0.02, 0.6, 1.6);
            }
            else
            {
                f2->SetParameters(eresp_Sandwich->GetMaximum(), eresp_Sandwich->GetMean(), 0.1, 0.6, 1.5);
            }
            eresp_Sandwich->Fit("f2", "", "same", -0.9, 1.);

            if (eresp_Sandwich->GetEntries())
            {
                hMeanDeltaE_Sandwich[ieta]->SetBinContent(ibin, eresp_Sandwich->GetFunction("f2")->GetParameter(1));
                hMeanDeltaE_Sandwich[ieta]->SetBinError(ibin, eresp_Sandwich->GetFunction("f2")->GetParError(1));

                hResolution_Sandwich[ieta]->SetBinContent(ibin, eresp_Sandwich->GetFunction("f2")->GetParameter(2));
                hResolution_Sandwich[ieta]->SetBinError(ibin, eresp_Sandwich->GetFunction("f2")->GetParError(2));
            }
            else
            {
                hMeanDeltaE_Sandwich[ieta]->SetBinContent(ibin, 0.);
                hMeanDeltaE_Sandwich[ieta]->SetBinError(ibin, 0.);

                hResolution_Sandwich[ieta]->SetBinContent(ibin, 0.);
                hResolution_Sandwich[ieta]->SetBinError(ibin, 0.);
            }
        }

        c3->cd(ieta + 1);
        gPad->SetTicky();
        gPad->SetTickx();
        hClustEPartEOverEreal_Spaghetti[ieta]->Draw("colz,same");
        hMeanDeltaE_Spaghetti[ieta]->Draw("E1,same");
        prof_hClustEPartEOverEreal_Spaghetti[ieta]->SetLineColor(kRed);
        prof_hClustEPartEOverEreal_Spaghetti[ieta]->SetLineWidth(2);
        prof_hClustEPartEOverEreal_Spaghetti[ieta]->Draw("E1,same");
        UnityLine->Draw("same");
        c4->cd(ieta + 1);
        gPad->SetTicky();
        gPad->SetTickx();
        hClustEPartEOverEreal_Sandwich[ieta]->Draw("colz,same");
        hMeanDeltaE_Sandwich[ieta]->Draw("E1,same");
        prof_hClustEPartEOverEreal_Sandwich[ieta]->SetLineColor(kRed);
        prof_hClustEPartEOverEreal_Sandwich[ieta]->SetLineWidth(2);
        prof_hClustEPartEOverEreal_Sandwich[ieta]->Draw("E1,same");
        UnityLine->Draw("same");

        pad1->cd();

        if (ieta == 0)
        {
            gPad->SetTickx();
            gPad->SetTicky();
            TH2D *ResFrame = new TH2D("ResFrame", "", 1200, 0, maxEnergy, 2000, 1e-4, maxResHist);
            SetStyleHistoTH2ForGraphs(ResFrame, "#it{E}_{part} (GeV)", "Res", 0.95 * textSizeLabels, textSizeLabels, 0.85 * textSizeLabels, textSizeLabels, 0.65, 0.71, 510, 510, 42, 62);
            ResFrame->SetTitle(ResTitle);
            ResFrame->Draw();
        }
        hResolution_Spaghetti[ieta]->SetLineColor(colors[ieta]);
        hResolution_Spaghetti[ieta]->SetMarkerColor(colors[ieta]);
        hResolution_Spaghetti[ieta]->SetMarkerStyle(8);
        hResolution_Spaghetti[ieta]->SetLineWidth(2);
        hResolution_Spaghetti[ieta]->GetYaxis()->SetTitleSize(textSizeLabels);
        hResolution_Spaghetti[ieta]->GetYaxis()->SetTitleOffset(0.65);
        hResolution_Spaghetti[ieta]->GetYaxis()->SetLabelSize(textSizeLabels * 0.85);
        // hResolution_Spaghetti[ieta]->GetYaxis()->CenterTitle();
        // hResolution_Spaghetti[ieta]->GetYaxis()->SetNdivisions(505);
        hResolution_Spaghetti[ieta]->Draw("same");

        leg->AddEntry(hResolution_Spaghetti[ieta], Form("%s", etaRange[ieta].Data()));
        TF1 *fres_Spaghetti = new TF1("fres_Spaghetti", "TMath::Sqrt([0]*[0]/x+[1]*[1])", 0, 1200);
        fres_Spaghetti->SetLineColor(ieta + 1);
        fres_Spaghetti->SetLineWidth(1);
        fres_Spaghetti->SetParameters(0.3, 0.01);
        // hResolution_Spaghetti[ieta]->Fit(fres_Spaghetti, "same");
        pad2->cd();

        if (ieta == 0)
        {
            gPad->SetTickx();
            gPad->SetTicky();
            TH2D *RatioFrame = new TH2D("RatioFrame", "", 1200, 0, maxEnergy, 2000, 0.45, 1.55);
            SetStyleHistoTH2ForGraphs(RatioFrame, "#it{E}_{part} (GeV)", "Res", 0.9 * textSizeLabels * 1.9, textSizeLabels * 1.9, 0.9 * textSizeLabels * 1.9, textSizeLabels * 1.9, 0.88, 0.39, 510, 510, 42, 62);
            RatioFrame->SetTitle(ResTitle);
            RatioFrame->GetYaxis()->SetTitle("Ratio");
            RatioFrame->GetYaxis()->CenterTitle();
            RatioFrame->GetXaxis()->SetTickLength(0.08);
            RatioFrame->Draw();
        }

        TH1D *ratio_Spaghetti = (TH1D *)hResolution_Spaghetti[ieta]->Clone(Form("ratio_Spaghetti_EtaBin_%d", ieta));
        // ratio_Spaghetti->Divide(fres_Spaghetti);
        ratio_Spaghetti->Divide(ResDetSpaghetti->GetFunction("fres_Spaghetti"));
        ratio_Spaghetti->GetYaxis()->SetRangeUser(0.45, 1.55);
        // ratio_Spaghetti->GetYaxis()->SetTitle("(Resolution)/(Total Fit)");
        ratio_Spaghetti->GetYaxis()->SetTitle("Ratio");
        ratio_Spaghetti->GetYaxis()->SetTitleSize(0.14);
        ratio_Spaghetti->GetYaxis()->SetTitleOffset(0.38);
        ratio_Spaghetti->GetYaxis()->SetLabelSize(0.13);
        ratio_Spaghetti->GetYaxis()->CenterTitle();
        ratio_Spaghetti->GetXaxis()->SetTitleSize(0.14);
        ratio_Spaghetti->GetXaxis()->SetTitleOffset(0.81);
        ratio_Spaghetti->GetXaxis()->SetLabelSize(0.13);
        ratio_Spaghetti->GetXaxis()->SetLabelOffset(0.0);
        ratio_Spaghetti->GetXaxis()->SetTickLength(0.08);
        ratio_Spaghetti->GetYaxis()->SetNdivisions(509);
        ratio_Spaghetti->Draw("same");

        pad3->cd();
        gPad->SetTickx();
        gPad->SetTicky();
        hResolution_Sandwich[ieta]->SetLineColor(ieta + 1);
        hResolution_Sandwich[ieta]->SetMarkerColor(ieta + 1);
        hResolution_Sandwich[ieta]->SetLineWidth(2);
        hResolution_Sandwich[ieta]->GetYaxis()->SetTitleSize(0.05);
        hResolution_Sandwich[ieta]->GetYaxis()->SetTitleOffset(1.0);
        hResolution_Sandwich[ieta]->GetYaxis()->SetLabelSize(0.05);
        hResolution_Sandwich[ieta]->GetYaxis()->CenterTitle();
        hResolution_Sandwich[ieta]->Draw("same");
        TF1 *fres_Sandwich = new TF1("fres_Sandwich", "TMath::Sqrt([0]*[0]/x+[1]*[1])", 0, 1200);
        fres_Sandwich->SetLineColor(ieta + 1);
        fres_Sandwich->SetLineWidth(1);
        fres_Sandwich->SetParameters(0.3, 0.01);
        // hResolution_Sandwich[ieta]->Fit(fres_Sandwich, "same");
        pad4->cd();
        TH1D *ratio_Sandwich = (TH1D *)hResolution_Sandwich[ieta]->Clone(Form("ratio_Sandwich_EtaBin_%d", ieta));
        // ratio_Sandwich->Divide(fres_Sandwich);
        ratio_Sandwich->Divide(ResDetSandwich->GetFunction("fres_Sandwich"));
        ratio_Sandwich->GetYaxis()->SetRangeUser(0.45, 1.55);
        ratio_Sandwich->GetYaxis()->SetTitle("Ratio");
        // ratio_Sandwich->GetYaxis()->SetTitle("(Resolution)/(Total Fit)");
        ratio_Sandwich->GetYaxis()->SetTitleSize(0.08);
        ratio_Sandwich->GetYaxis()->SetTitleOffset(0.6);
        ratio_Sandwich->GetYaxis()->SetLabelSize(0.12);
        ratio_Sandwich->GetYaxis()->CenterTitle();
        ratio_Sandwich->GetXaxis()->SetTitleSize(0.09);
        ratio_Sandwich->GetXaxis()->SetTitleOffset(0.94);
        ratio_Sandwich->GetXaxis()->SetLabelSize(0.11);
        ratio_Sandwich->GetXaxis()->SetLabelOffset(0.0);
        ratio_Sandwich->GetYaxis()->SetNdivisions(509);
        ratio_Sandwich->Draw("same");
    }
    pad1->cd();
    leg->Draw();

    drawLatexAdd("#bf{ALICE simulation, Single #pi^{+}}", 0.93, 0.96 - 1 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#bf{FoCal upgrade}", 0.93, 0.96 - 2 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);
    drawLatexAdd("#bf{3.4 < #it{#eta}_{#pi^{+}} < 5.5}", 0.93, 0.96 - 3 * 1.1 * textSize, textSize, kFALSE, kFALSE, kTRUE);

    if (!doElectrons)
    {
        cResSpaghetti->SaveAs("figures/Eresolution_Eta_Spaghetti.pdf");
    }

    pad3->cd();
    leg->Draw();
}