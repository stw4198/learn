# LEARN
Likelihood Event Analysis of Reactor Neutrinos

Combine with machine learning for Machine LEARNing

### Dependencies
ROOT must be installed and sourced before compiling or using

### Compile

Use "make" to compile and "make clean" to remove binaries

### Use

To use, do ./learn [options]

LEARN has 4 main steps:
1) Generating probability density functions (PDFs) for signal/background components
2) Scaling and merging PDFs to create signal and background PDFs
3) Creating likelihoods based on signal and background PDFs, and determining likelihood ratio (log(L<sub>s</sub>/L<sub>b</sub>))
4) Evaluating the likelihoods to find optimal cut on likelihood ratio to suppress backgrounds

To generate PDFs, use<br>
./learn --pdf [input file] [component] [nbins:default 1000] [dTank: 22000 mm]

To scale and merge PDFs, use<br>
./learn --merge [signal:default hartlepool]

To create likelihoods, use<br>
./learn --like [input file] [component]

To Evaluate likelihoods and rates, use<br>
./learn --eval [input file] [component]

To see help with basic list of components, use<br>
./learn

Event rates and components are defined in 'rates.csv', which needs to be in the current working directory. Example files for different detector configurations are found in this repository.
