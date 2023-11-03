#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;


// Global variables
//int matrix[N_MAX][M_MAX];
//int kernel[K_MAX][K_MAX];
//int finalMatrix[N_MAX][M_MAX];
int numRows, numCols, kernelRows, kernelCols, numThreads;
vector<vector<int>> inputMatrix;
vector<vector<int>> convolutionKernel;
vector<vector<int>> resultMatrix;

void readInput(string path);
void writeOutput(string path);
int singlePixelConvolution(int x, int y, int offset);
void performSequentialConvolution(int offset);
void performParallelConvolution(int offset, int start, int end);
void parallelizeConvolution(int offset);

bool compareFiles(const string& path1, const string& path2) {
    ifstream fin_t(path1);
    ifstream fin_v(path2);

    int x, y;
    while (fin_t >> x && fin_v >> y) {
        if (x != y) {
            throw exception();
        }
    }

    if (fin_t >> x || fin_v >> x) {
        throw exception();
    }
}

int main(int argc, char** argv) {
    // Number of threads to use (set to 0 for sequential execution)
    numThreads = atoi(argv[1]);
    //numThreads = 0;

    readInput("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1-c\\input.txt");

    int offset = (kernelRows - 1) / 2;

    if (numThreads == 0) {
        // Perform sequential convolution if the number of threads is 0
        performSequentialConvolution(offset);
    }
    else {
        // Perform parallel convolution if the number of threads is greater than 0
        parallelizeConvolution(offset);
    }


    if (numThreads == 0) {
        writeOutput("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1c\\output2.txt");
    }
    else {
        writeOutput("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1c\\output.txt");
        compareFiles("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1c\\output.txt", "C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1c\\output2.txt");
    }

    return 0;
}

// Function to read input from a file
void readInput(string path) {
    ifstream fin(path);

    // Read matrix dimensions from the input file
    fin >> numRows >> numCols;

    // Initialize inputMatrix and resultMatrix with the appropriate dimensions
    inputMatrix = vector<vector<int>>(numRows, vector<int>(numCols));
    resultMatrix = vector<vector<int>>(numRows, vector<int>(numCols));

    // Populate inputMatrix with values from the input file
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            fin >> inputMatrix[i][j];
        }
    }

    // Read kernel dimensions from the input file
    fin >> kernelRows >> kernelCols;

    // Initialize convolutionKernel with the appropriate dimensions
    convolutionKernel = vector<vector<int>>(kernelRows, vector<int>(kernelCols));

    // Populate convolutionKernel with values from the input file
    for (int i = 0; i < kernelRows; ++i) {
        for (int j = 0; j < kernelCols; ++j) {
            fin >> convolutionKernel[i][j];
        }
    }

    // Close the input file
    fin.close();
}

// Function to write output to a file
void writeOutput(string path) {
    ofstream fout(path);

    // Write resultMatrix to the output file
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            fout << resultMatrix[i][j] << " ";
        }
        fout << endl;
    }

    // Close the output file
    fout.close();
}

// Function for single pixel convolution
int singlePixelConvolution(int x, int y, int offset) {
    int output = 0;

    // Perform convolution for the given pixel
    for (int i = 0; i < kernelRows; ++i) {
        for (int j = 0; j < kernelCols; ++j) {
            int ii = x - offset + i;
            int jj = y - offset + j;

            // Ensure indices are within bounds
            ii = max(0, min(ii, numRows - 1));
            jj = max(0, min(jj, numCols - 1));

            // Update the convolution output
            output += inputMatrix[ii][jj] * convolutionKernel[i][j];
        }
    }

    return output;
}

// Function for sequential convolution
void performSequentialConvolution(int offset) {
    auto startTime = high_resolution_clock::now();

    // Iterate through each pixel and perform convolution
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            resultMatrix[i][j] = singlePixelConvolution(i, j, offset);
        }
    }

    // Measure elapsed time for sequential convolution
    auto endTime = high_resolution_clock::now();
    double elapsedTime = duration<double, milli>(endTime - startTime).count();

    cout << "Sequential Convolution Time: " << elapsedTime << " milliseconds" << endl;
}

// Function for parallel convolution
void performParallelConvolution(int offset, int start, int end) {
    // Iterate through a range of rows and perform parallel convolution
    for (int i = start; i < end; i++) {
        for (int j = 0; j < numCols; j++) {
            resultMatrix[i][j] = singlePixelConvolution(i, j, offset);
        }
    }
}

// Function to parallelize convolution using multiple threads
void parallelizeConvolution(int offset) {
    vector<thread> threads;

    // Calculate chunk size for each thread
    int chunkSize = numRows / numThreads;
    int remainder = numRows % numThreads;
    int start = 0, end = 0;

    // Measure elapsed time for parallel convolution
    auto startTime = high_resolution_clock::now();

    // Create threads and distribute the workload
    for (int i = 0; i < numThreads; i++) {
        start = end;
        end = start + chunkSize + (remainder-- > 0 ? 1 : 0);

        threads.emplace_back(performParallelConvolution, offset, start, end);
    }

    // Join threads to synchronize execution
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }

    // Measure elapsed time for parallel convolution
    auto endTime = high_resolution_clock::now();
    double elapsedTime = duration<double, milli>(endTime - startTime).count();

    cout << "Parallel Convolution Time: " << elapsedTime << " milliseconds" << endl;
}
