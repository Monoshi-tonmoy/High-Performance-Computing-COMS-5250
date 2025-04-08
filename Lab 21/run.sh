#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --account=s2025.coms.525.1
#SBATCH --time=00:10:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=4  # Using 4 processes for example
#SBATCH --mem=1G
#SBATCH --job-name="MPI_Trapezoidal"
#SBATCH --output=mpi_trap_%j.out

module purge
module load intel/2024.2.0

echo "Compiling program..."
make clean
make

if [ ! -f "trap_mpi.exe" ]; then
    echo "Compilation failed!"
    exit 1
fi


for procs in 1 2 4 8; do
    echo "Running with $procs processes..."
    echo "1.718281828459045" > exact.txt 
    mpirun -np $procs ./trap_mpi.exe <<< "0 1 1000000"
    echo ""
done

echo "All runs completed"