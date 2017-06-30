# Script to run swig standalone without CMake on Linux / Mac
# Generates the swig python3 wrappers in a sub folder called "output"
# Pre-requisites: swig in the path (e.g. /usr/local/bin/swig)

# Generate example map
../../../build/bin/makeExamples -o map

# Generate model IR
../../../build/bin/compile -imap ELL_step10.map -cfn Step10 -m clockStep -of ELL_step10.ll

# Generate swig interface and header
../../../build/bin/compile -imap ELL_step10.map -cmn ELL_step10 -cfn Step10 -m clockStep -o swig -of ELL_step10.i

# Run swig
mkdir -p output
swig -python -c++ -Fmicrosoft -py3 -outdir output -c++ \
-I../../../interfaces/common/include \
-I../../../interfaces/common \
-I../../../libraries/emitters/include \
-o output/ELL_step10PYTHON_wrap.cxx \
ELL_step10.i
