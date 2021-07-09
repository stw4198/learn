# LANCE
Likelihood analysis of AntiNeutrino Coincidence Events

### Dependencies
ROOT must be installed and sourced before compiling or using

### Compile

Use "make" to compile and "make clean" to remove binaries

### Use

To use, do ./lance [options]

LANCE has 4 main steps:
1) Generating probability density functions (PDFs) for signal/background components
2) Scaling and merging PDFs to create signal and background PDFs
3) Creating likelihoods based on signal and background PDFs, and determining likelihood ratio (log(L<sub>s</sub>/L<sub>b</sub>))
4) Evaluating the likelihoods to find optimal cut on likelihood ratio to suppress backgrounds

To generate PDFs, use<br>
./lance --pdf [input file] [component] [nbins:default 1000] [dTank: 22000 mm]

To scale and merge PDFs, use<br>
./lance --merge [signal:default hartlepool]

To create likelihoods, use<br>
./lance --like [input file] [component]

To Evaluate likelihoods and rates, use<br>
./lance --eval [input file] [component]

To see help with basic list of components, use<br>
./lance

Event rates and components are defined in 'rates.csv', which needs to be in the current working directory. Example files for different detector configurations are found in this repository.
