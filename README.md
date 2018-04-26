# valleytronics_logic
A set of classes and libraries to Simulate Valleytronic Logic Gates and Computation

# Introduction
The purpose of this code is to create a portable and flexible test bench for developing
computer systems and other integrated circuits based on electronically controlled valleytronic
circuits as described by Ang et al. DOI: 10.1103/PhysRevB.96.245410

The current layout verifies reversibility of the logic gates and allows the construction of
arbitrary static circuits and some clocked circuits. Latches are beginning to be added, but creating 
latches that respect the valley states when being used to store bits has proven challenging.

The current library includes a C++ program that demonstrates the reversible logic along with an 8b adder.

# Compiling and Using
gates can be called from their member class c_valley, and logic can be called from c_vlogic. Architecture parameters
are stored in parameters.h and need to be included when using the valleytronics libraries, which should be linked to
the main file as presented in the example makefile

The adder executable can be built using

$ make clean adder

which will compile and link all necessary libraries and code. Running the code simply requires

$ ./adder $(Decimal Number 1) $(Decimal Number 2)

and it will return the binary of those numbers, along with the sum and valley outputs. It will then 
recover the original values from only the adder outputs. truth tables for the 2b adders and some of the
gates are also printed for completeness
