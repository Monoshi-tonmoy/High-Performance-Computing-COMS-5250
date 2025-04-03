#!/bin/bash
#SBATCH --partition=instruction
#SBATCH --account=s2025.coms.525.1
#SBATCH --time=00:30:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=36
#SBATCH --mem=16G
#SBATCH --job-name="Adaptive_Quadrature"
#SBATCH --output=adaptive_job_%j.out

module load gcc

echo "Compiling program..."
make clean
make

if [ ! -f "adaptive.exe" ]; then
    echo "Compilation failed!"
    exit 1
fi


THREADS_LIST=(1 2 4 8 16)
TOL_LIST=(1e-4 1e-5 1e-6 1e-7)


SUMMARY_FILE="adaptive_results.csv"
echo "Threads,Tolerance,Integral,Error,Time(sec)" > "${SUMMARY_FILE}"


for threads in "${THREADS_LIST[@]}"; do
    for tol in "${TOL_LIST[@]}"; do
        echo "Running with ${threads} threads and TOL=${tol}"
        

        START_TIME=$SECONDS
        OUTPUT=$(./adaptive.exe ${threads} ${tol})
        ELAPSED=$(( SECONDS - START_TIME ))
        

        INTEGRAL=$(echo "${OUTPUT}" | grep "I =" | awk '{print $3}')
        ERROR=$(echo "${OUTPUT}" | grep "err =" | awk '{print $3}')
        

        echo "${threads},${tol},${INTEGRAL},${ERROR},${ELAPSED}" >> "${SUMMARY_FILE}"
        
        echo "Completed in ${ELAPSED} seconds"
        echo ""
    done
done

echo "All runs completed. Results saved in ${SUMMARY_FILE}"