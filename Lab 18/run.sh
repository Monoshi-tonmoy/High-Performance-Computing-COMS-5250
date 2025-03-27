#!/bin/bash
#SBATCH --partition=instruction       # partition to use
#SBATCH --account=s2025.coms.525.1    # account to use
#SBATCH --time=00:50:00               # walltime limit (HH:MM:SS)
#SBATCH --nodes=1                     # number of nodes
#SBATCH --ntasks-per-node=36          # 36 processor core(s) per node 
#SBATCH --mem=16G                     # maximum memory per node
#SBATCH --job-name="Simpson_Parallel" # job name
#SBATCH --output=simpson_job_%j.out   # standard output file

# LOAD MODULES AND COMPILE
module load gcc

echo "Compiling program..."
make clean
make

if [ ! -f "simpson.exe" ]; then
    echo "Compilation failed!"
    exit 1
fi

# PARAMETERS
N=16777216  # Divisible by 1,2,4,8,16
a=0.0
b=1.0

# RUN WITH DIFFERENT THREAD COUNTS
for threads in 1 2 4 8 16; do
    echo "Running with $threads threads"
    
    # Run and save output to thread-specific file
    ./simpson.exe $threads $N > "output_$threads.txt" 2>&1
    
    # Print timing results from the output file
    echo "Results for $threads threads:"
    tail -n 5 "output_$threads.txt"
    echo ""
done

echo "All runs completed. Outputs saved as output_[threads].txt"
