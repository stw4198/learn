# LEARN
Likelihood Event Analysis of Reactor Neutrinos

### Dependencies
ROOT must be installed and sourced before compiling or using. Developed using ROOT 6.18

### Compile

Use "make" to compile and "make clean" to remove binaries. Source LEARN.sh to export paths

### Use

Use "learn" to see input options. Use "learn --help" to print analysis steps.

There are several stages to this analysis

1) Creating PDFs: "learn --pdf -f [input file] -c [component]"

2) Scaling and merging PDFs: "learn --merge -s [signal]"

3) Creating likelihoods: "learn --like -f [input file] -c [component]"

4) Evaluating likelihoods and rates: "learn --eval -f [input file] -c [component name]"

5) Data reduction
Not currently integrated into LEARN

6) Evaluating dwell times (energy cut): "learn --energy -s [signal]"

7) Evaluating dwell times (no energy cut): "learn --veto -s [signal]"

Event rates and components are defined in 'rates.csv', which needs to be in the current working directory. Example files for different detector configurations are found in this repository.
