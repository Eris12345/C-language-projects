#include <iostream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
using namespace std;
/* initializes the given matrix as a NULL (ZERO) matrix
* (In the NULL (ZERO) matrix all elements are 0) */
__global__ void initNullGPU(
	int *devMatrix, int numR, int numC) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x * gridDim.y + y;
	if (x < numR && y < numC)
		devMatrix[offset] = 0;
}
/* initializes all the elements of the given matrix with the given value */
__global__ void initValueGPU(
	int *devMatrix, int numR, int numC, int value) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x * gridDim.y + y;
	if (x < numR && y < numC)
		devMatrix[offset] = value;
}
/* initializes the given square matrix as an IDENTITY matrix
* (In the IDENTITY matrix all diagonal elements are 1) */
__global__ void initIdentityGPU(
	int *devMatrix, int numR, int numC) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x * gridDim.y + y;
	if (x < numR && y < numC)
		if (x == y)
			devMatrix[offset] = 1;
		else
			devMatrix[offset] = 0;
}
/* initializes the upper triangular matrix with the given value
* (In the UPPER TRIANGULAR matrix all the elements in the upper
* triangular segment have the same value) */
__global__ void initUpperTriangularValueGPU(
	int *devMatrix, int numR, int numC, int value) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x * gridDim.y + y;
	if (x < numR && y < numC)
		if (x > y)
			devMatrix[offset] = 0;
		else
			devMatrix[offset] = value;
}
/* initializes the given scalar matrix with the given value
* (In the SCALAR matrix all diagonal elements have the same value) */
__global__ void initScalarValueGPU(
	int *devMatrix, int numR, int numC, int value) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x * gridDim.y + y;

	if (x < numR && y < numC)
		if (x == y)
			devMatrix[offset] = value;
		else
			devMatrix[offset] = 0;
}
/* adds the given left and right matrices onto the result matrix. */
__global__ void addGPU(
	int *devMatrixLeft, int *devMatrixRight, int *devMatrixResult,
	int numR, int numC) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offset = x * gridDim.y + y;
	if (x < numR && y < numC)
		devMatrixResult[offset] = devMatrixLeft[offset] + devMatrixRight[offset];
}
/* calculates and returns the transpose of the given matrix. */
__global__ void transposeGPU(
	int *devMatrix, int *devTranspose,
	int numR, int numC) {
	int x = blockIdx.x;
	int y = blockIdx.y;
	int offsetMatrix = x * gridDim.y + y;
	int offsetTranspose = y * gridDim.x + x;
	if (x < numR && y < numC)
		devTranspose[offsetTranspose] = devMatrix[offsetMatrix];
}
class Matrix {
	int *hostMatrix; //matrix as a one-dimensional array
	int numRows,
		numCols;
public:
	Matrix(int numR, int numC);
	Matrix(const Matrix& m);
		Matrix& operator=(const Matrix& right);
	~Matrix();
	friend ostream& operator<<(ostream& out, const Matrix& right);
	//member functions to initialize the matrix:
	void initNull();
	void initValue(int value);
	void initIdentity();
	void initUpperTriangularValue(int value);
	void initScalarValue(int value);
	Matrix operator+(const Matrix& right);
	friend Matrix transpose(const Matrix& matrix);
};

Matrix::Matrix(int numR, int numC) {
	numRows = numR;
	numCols = numC;
	hostMatrix = new int[numRows * numCols];
}

	Matrix::Matrix(const Matrix& m) {
	numRows = m.numRows;
	numCols = m.numCols;
	hostMatrix = new int[numRows * numCols];
	memcpy(hostMatrix, m.hostMatrix, sizeof(int) * numRows * numCols);
}
  Matrix& Matrix :: operator=(const Matrix& right) {
	  if (this != &right) {
		  delete[] hostMatrix;
		  numRows = right.numRows;
		  numCols = right.numCols;
		  hostMatrix = new int[numRows * numCols];
		  memcpy(hostMatrix, right.hostMatrix, sizeof(int) * numRows * numCols);
	  }
	  return (*this);
  }
  Matrix :: ~Matrix() {
	  delete[] hostMatrix;
  }
  ostream& operator<<(ostream& out, const Matrix& right) {
	  int r, c, offset = 0;
	  out << "A " << right.numRows << " by " << right.numCols << " matrix:\n";
	  for (r = 0; r < right.numRows; r++) {
		  out << "| ";
		  for (c = 0; c < right.numCols - 1; c++)
			  out << right.hostMatrix[offset++] << " ";
		  out << right.hostMatrix[offset++] << " |\n";
	  }
	  return out;
  }
  /* initializes the given matrix as a NULL (ZERO) matrix
  * (In the NULL (ZERO) matrix all elements are 0) */
  void Matrix::initNull() {
	  int *devMatrix;
	  cudaMalloc((void**)&devMatrix, sizeof(int) * numRows * numCols);
	  dim3 grid(numRows, numCols);
	  initNullGPU << <grid, 1 >> > (devMatrix, numRows, numCols);
	  cudaMemcpy(hostMatrix, devMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	  cudaFree(devMatrix);
  }
  /* initializes all the elements of the given matrix with the given value */
  void Matrix::initValue(int value) {
	  int *devMatrix;
	  cudaMalloc((void**)&devMatrix, sizeof(int) * numRows * numCols);
	  dim3 grid(numRows, numCols);
	  initValueGPU << <grid, 1 >> > (devMatrix, numRows, numCols, value);
	  cudaMemcpy(hostMatrix, devMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	  cudaFree(devMatrix);
  }

	/* initializes the given square matrix as an IDENTITY matrix
	* (In the IDENTITY matrix all diagonal elements are 1) */
	void Matrix::initIdentity() {
	int *devMatrix;
	cudaMalloc((void**)&devMatrix, sizeof(int) * numRows * numCols);
	dim3 grid(numRows, numCols);
	initIdentityGPU << <grid, 1 >> > (devMatrix, numRows, numCols);
	cudaMemcpy(hostMatrix, devMatrix,
		sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	cudaFree(devMatrix);
}
  /* initializes the upper triangular matrix with the given value
  * (In the UPPER TRIANGULAR matrix all the elements in the upper
  * triangular segment have the same value) */
  void Matrix::initUpperTriangularValue(int value) {
	  int *devMatrix;
	  cudaMalloc((void**)&devMatrix, sizeof(int) * numRows * numCols);
	  dim3 grid(numRows, numCols);
	  initUpperTriangularValueGPU << <grid, 1 >> > (devMatrix, numRows, numCols, value);
	  cudaMemcpy(hostMatrix, devMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	  cudaFree(devMatrix);
  }
  /* initializes the given scalar matrix with the given value
  * (In the SCALAR matrix all diagonal elements have the same value) */
  void Matrix::initScalarValue(int value) {
	  int *devMatrix;
	  cudaMalloc((void**)&devMatrix, sizeof(int) * numRows * numCols);
	  dim3 grid(numRows, numCols);
	  initScalarValueGPU << <grid, 1 >> > (devMatrix, numRows, numCols, value);
	  cudaMemcpy(hostMatrix, devMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	  cudaFree(devMatrix);
  }
  Matrix Matrix :: operator+(const Matrix& right) {
	  if (numRows != right.numRows ||
		  numCols != right.numCols) {
		  cerr << "Error: invalid sizes in matrix addition.\n";
		  cerr << "Left matrix object is returned.\n";
		  return (*this);
	  }
	  Matrix result(numRows, numCols);
	  int *devMatrixLeft,
		  *devMatrixRight,
		  *devMatrixResult;
	  cudaMalloc((void**)&devMatrixLeft, sizeof(int) * numRows * numCols);
	  cudaMalloc((void**)&devMatrixRight, sizeof(int) * numRows * numCols);
	  cudaMalloc((void**)&devMatrixResult, sizeof(int) * numRows * numCols);
	  cudaMemcpy(devMatrixLeft, hostMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyHostToDevice);
	  cudaMemcpy(devMatrixRight, right.hostMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyHostToDevice);
 
	  dim3 grid(numRows, numCols);
	addGPU << <grid, 1 >> > (devMatrixLeft, devMatrixRight, devMatrixResult,
		numRows, numCols);
	cudaMemcpy(result.hostMatrix, devMatrixResult,
		sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	cudaFree(devMatrixLeft);
	cudaFree(devMatrixRight);
	cudaFree(devMatrixResult);
	return result;
  }
  /* calculates and returns the transpose of the given matrix. */
  Matrix transpose(const Matrix& matrix) {
	  int numRows = matrix.numRows;
	  int numCols = matrix.numCols;
	  Matrix result(numCols, numRows);
	  int *devMatrix, *devTranspose;
	  cudaMalloc((void**)&devMatrix, sizeof(int) * numRows * numCols);
	  cudaMalloc((void**)&devTranspose, sizeof(int) * numRows * numCols);
	  cudaMemcpy(devMatrix, matrix.hostMatrix,
		  sizeof(int) * numRows * numCols, cudaMemcpyHostToDevice);
	  dim3 grid(numRows, numCols);
	  transposeGPU << <grid, 1 >> > (devMatrix, devTranspose, numRows, numCols);
	  cudaMemcpy(result.hostMatrix, devTranspose,
		  sizeof(int) * numRows * numCols, cudaMemcpyDeviceToHost);
	  cudaFree(devMatrix);
	  cudaFree(devTranspose);
	  return result;
  }
  int main(void) {
	  Matrix a(3, 5), b(3, 5), c(3, 5), d(5, 3), e(4, 4);
	  a.initValue(2);
	  b.initValue(3);
	  cout << "a: \n" << a << endl;
	  cout << "b: \n" << b << endl;
	  c = a + b;
	  cout << "a + b = c: \n" << c << endl;
	  d.initNull();
	  cout << "null matrix d: \n" << d << endl;
	  e.initIdentity();
	  cout << "identity matrix e: \n" << e << endl;
	  e.initUpperTriangularValue(7);
	  cout << "upper triangular matrix e: \n" << e << endl;
	  e = transpose(e);
	  cout << "transpose of e: \n" << e << endl;
	  e.initScalarValue(9);
	  cout << "scalar matrix e: \n" << e << endl;
	  return 0;
  }
