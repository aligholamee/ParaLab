/*
*	In His Exalted Name
*	Vector Addition - Sequential Code
*	Ahmad Siavashi, Email: siavashi@aut.ac.ir
*	21/05/2018
*/
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <cuda_runtime.h>
#include "device_launch_parameters.h"
#include <math.h>

#pragma comment(lib, "winmm.lib")
void fillVector(int * v, size_t n);
void addVector(int * a, int *b, int *c, size_t n);
void printVector(int * v, size_t n);
cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size);
int *dev_a = 0;
int *dev_b = 0;
int *dev_c = 0;
cudaError_t cudaStatus;
__device__ const unsigned int vectorSize = 1023 * 513;

int main()
{

	const bool isCudaMode = true;

	int *a = new int[vectorSize];
	int *b = new int[vectorSize];
	int *c = new int[vectorSize];


	fillVector(a, vectorSize);
	fillVector(b, vectorSize);

	cudaEvent_t start, stop;
	float elapsed_time;

	cudaEventCreate(&start);
	cudaEventCreate(&stop);
	cudaEventRecord(start, 0);

	if (isCudaMode) {
		addWithCuda(c, a, b, vectorSize);
		cudaEventRecord(stop, 0);
		cudaEventSynchronize(stop);
	}
	else
	{
		addVector(a, b, c, vectorSize);
	}

	//end_time = clock
	cudaEventElapsedTime(&elapsed_time, start, stop);
	printf("Elapsed time is %lf\n", elapsed_time);
	//printVector(c, vectorSize);
	system("pause");
	return EXIT_SUCCESS;
}

// Fills a vector with data
void fillVector(int * v, size_t n) {
	int i;
	for (i = 0; i < n; i++) {
		v[i] = i;
	}
}

// Adds two vectors
void addVector(int * a, int *b, int *c, size_t n) {
	int i;

	for (i = 0; i < n; i++) {
		c[i] = a[i] + b[i];
	}
}

// Prints a vector to the stdout.
void printVector(int * v, size_t n) {
	int i;
	
	printf("[-] Vector elements: ");
	for (i = 0; i < n; i++) {
		printf("%d, ", v[i]);
	}
	printf("\b\b  \n");
}

__global__ void addKernel(int *c, const int *a, const int *b)
{
	int g_tId = threadIdx.x + blockDim.x * blockIdx.x;
	unsigned int warpId = threadIdx.x / warpSize;

	if ( g_tId < vectorSize) {
		c[g_tId] = a[g_tId] + b[g_tId];
		printf("thread id %d , warp Id %d , block id %d\n", g_tId, warpId,blockIdx.x);
	}
}

cudaError_t addWithCuda(int *c, const int *a, const int *b, unsigned int size) {
	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		printf("cudaSetDevice failed! Do you have a CUDA-capable GPU installed?");
		return cudaStatus;
	}
	cudaStatus = cudaMalloc((void**)&dev_c, size * sizeof(int));
	if (cudaStatus != cudaSuccess) {
		printf("cudaMalloc failed!");
		return cudaStatus;
	}
	cudaStatus = cudaMalloc((void**)&dev_a, size * sizeof(int));
	if (cudaStatus != cudaSuccess) {
		printf("cudaMalloc failed!");
		return cudaStatus;
	}
	cudaStatus = cudaMalloc((void**)&dev_b, size * sizeof(int));
	if (cudaStatus != cudaSuccess) {
		printf("cudaMalloc failed!");
		return cudaStatus;
	}
	cudaStatus = cudaMemcpy(dev_a, a, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		printf("cudaMemcpy failed!");
		return cudaStatus;
	}
	cudaStatus = cudaMemcpy(dev_b, b, size * sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		printf("cudaMemcpy failed!");
		return cudaStatus;
	}
	addKernel << <  ceil(size / 1024), 1024 >> >(dev_c, dev_a, dev_b);
	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		printf("addKernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		return cudaStatus;
	}
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		printf("cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
		return cudaStatus;
	}
	cudaStatus = cudaMemcpy(c, dev_c, size * sizeof(int), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) {
		printf("cudaMemcpy failed!");
		return cudaStatus;
	}
	cudaFree(dev_c);
	cudaFree(dev_a);
	cudaFree(dev_b);
	return cudaStatus;
}