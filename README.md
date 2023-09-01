# CaloCalibandPerformance
Repository for Calorimeter calibration and performance study.

1. DrawJESvsEta.C: This macro draws the jet energy scale (JES) for single charged and neutral pions jets (Figure 38 in the public note).

2. PlotCaloEnergyDistribution.C: This macro draws the distribution for the FOCAL-E only calibrated energy, FOCAL-H only calibrated energy, and for FOCAL-E + FOCAL-H calibrated energy for both charged pions and electrons with 500 GeV energy. You have to set the flag $doElectrons$ to true or false whether you want to draw electrons or pions respectively. Figure 5 in the public note.

3. PlotDetResolution.C: This macro draws the total energy response (FOCAL-E + FOCAL-H) for charged pions and electrons with uniform energy for both the spaghetti HCAL and the sandwich HCAL. Mainly it draws the average $\Delta E$ vs $E_{\mathrm{MC}}$ the energy of the particle (electron or pion). You have to set the flag $doElectrons$ to true or false whether you want to draw electrons or pions respectively for both FOCAL-H setups. Figure 6 and 8 in the public note. This macro will also draw the energy resolution of both the spaghetti and the Sandwich calorimeters for charged pions and also the energy resolution for electrons. Figure 7 left panel.

4. PlotResolutionEta.C: This macro does many thing, but the main this is it draws the energy resolution of the spaghetti calorimeter vs $\eta$ for charged pions, and make the ratios of these resolution over the general one created from macro 3. Figure 7 right panel in the public note.
