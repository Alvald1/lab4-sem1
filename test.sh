#!/bin/bash

# Optimization flags to test
optimization_flags=(-Og -O0 -O1 -O2 -O3 -Ofast)

# Datasets to test
datasets=(10000 20000 30000 40000 50000 60000 70000 80000 90000 100000)

# Create a directory to store the results
mkdir -p results_lib

# Loop through each dataset
for dataset in "${datasets[@]}"
do
    # Loop through each optimization flag
    for flag in "${optimization_flags[@]}"
    do
        # Create a subdirectory for each dataset and optimization level
        mkdir -p results_lib/out_$dataset/$flag

        # Compile the program with the current optimization flag
        make OPTIM=$flag

        # Run the program and save the results in the corresponding subdirectory
        for i in {1..100}
        do
            cat datasets/$dataset.txt | ./bin_clean > results_lib/out_$dataset/$flag/$i.txt
        done
    done
done
