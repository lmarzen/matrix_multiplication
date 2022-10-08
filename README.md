### Parallel Matrix Multiplication Using OpenMP, Phtreads, and MPI 

This is a fork of https://github.com/mperlet/matrix_multiplication.
This fork implements another version of this benchmark that utilizes OpenMP target directives to offload data to a GPU.



The multiplication of two matrices is to be implemented as 

* a sequential program 
* an OpenMP shared memory program 
* an explicitly threaded program (using the pthread standard) 
* a message passing program using the MPI standard 

## Matrix multiplication
The aim is to multiply two matrices together.To multiply two matrices, the number of columns of the first matrix has to match the number of lines of the second matrix. The calculation of the matrix solution has independent steps, it is possible to parallelize the calculation.


## Results

    * * * * * * * 100x100 Matrix
    with sequential    0m0.019s
    with omp           0m0.035s
    with omp_gpu       0m0.235s
    
    * * * * * * * 1000x1000 Matrix
    with sequential    0m2.302s
    with omp           0m1.808s
    with omp_gpu       0m1.713s
    
    * * * * * * * 5000x5000 Matrix
    with sequential    11m13.876s
    with omp           2m16.492s
    with omp_gpu       0m46.481s
    