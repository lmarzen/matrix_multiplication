CC=clang
CFLAGS= -Wall -fopenmp
LIBS=src/matrix.c
TUNE= -O3

TARGET=nvptx64
LDFLAGS=-L/usr/lib

all: sequential omp omp_gpu thread2 mpi

sequential:
		$(CC) $(TUNE) $(CFLAGS) -o bin/seq $(LIBS) src/sequential.c

omp:
		$(CC) $(TUNE) $(CFLAGS) -o bin/omp $(LIBS) src/omp.c

omp_gpu:
		$(CC) $(TUNE) $(CFLAGS) -o bin/omp_gpu src/omp_gpu.c -fopenmp-targets=$(TARGET) $(LDFLAGS)

thread:
		$(CC) $(TUNE) $(CFLAGS) -pthread -o bin/thread $(LIBS) src/thread.c

thread2:
		$(CC) $(TUNE) $(CFLAGS) -pthread -o bin/thread2 $(LIBS) src/thread2.c

mpi:
		OMPI_CC=$(CC) mpicc $(TUNE) $(CFLAGS) -o bin/mpi $(LIBS) src/mpi.c
