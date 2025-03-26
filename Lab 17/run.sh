#!/bin/bash

# Copy/paste this job script into a text file and submit with the command:
#    sbatch thefilename
# job standard output will go to the file slurm-%j.out (where %j is the job ID)

#SBATCH --partition=instruction       # partition to use
#SBATCH --account=s2025.coms.525.1    # account to use
#SBATCH --time=00:50:00   # walltime limit (HH:MM:SS)
#SBATCH --nodes=1   # number of nodes
#SBATCH --ntasks-per-node=36   # 36 processor core(s) per node 
#SBATCH --mem=16G   # maximum memory per node
#SBATCH --job-name="HCP"

# LOAD MODULES, INSERT CODE, AND RUN YOUR PROGRAMS HERE


module load gcc


echo "Compiling program..."
make clean
make


if [ ! -f "main.exe" ]; then
    echo "Compilation failed!"
    exit 1
fi


N=500
K=50


mkdir -p thread_outputs


for threads in 1 2 4 8 16; do
    echo "Running with $threads threads"
    
    output_dir="thread_outputs/threads_$threads"
    mkdir -p "$output_dir"
    

    ./main.exe $threads $N $K > "$output_dir/run_output.txt" 2>&1
    
    mv output_*.txt "$output_dir/" 2>/dev/null
    
    echo "Outputs saved to $output_dir/"
    echo ""
done
