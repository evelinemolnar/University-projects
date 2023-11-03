#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <chrono>

using namespace std;
using namespace std::chrono;

class MyBarrier {
private:
    mutex m;
    condition_variable cv;
    int counter;
    int waiting;
    int thread_count;

public:
    MyBarrier(int count) : thread_count(count), counter(0), waiting(0) {}

    void wait() {
        unique_lock<mutex> lk(m);
        ++counter;
        ++waiting;
        cv.wait(lk, [&] {return counter >= thread_count; });
        cv.notify_one();
        --waiting;
        if (waiting == 0) {
            counter = 0;
        }
        lk.unlock();
    }
};

const int N_MAX = 10000;
const int M_MAX = 10000;
const int K_MAX = 6;

int N, M, n, m, p;

vector<vector<int>> matrix;
vector<vector<int>> kernel;

void readInput(string path) {
    ifstream fin(path);

    fin >> N >> M;
    matrix = vector<vector<int>>(N, vector<int>(M));

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < M; ++j)
            fin >> matrix[i][j];

    fin >> n >> m;
    kernel = vector<vector<int>>(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            fin >> kernel[i][j];

    fin.close();
}

void writeOutput(string path, const vector<vector<int>>& mat) {
    ofstream fout(path);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            fout << mat[i][j] << " ";
        fout << endl;
    }

    fout.close();
}

void performSequentialConvolution(int offset) {
    vector<int> previousLine, currentLine;
    previousLine = matrix[0];
    currentLine = matrix[0];

    vector<int> buffer;

    auto startTime = high_resolution_clock::now();
    for (int i = 0; i < N; i++) {
        buffer.clear();
        for (int j = 0; j < M; j++) {
            int output = applyConvolution(previousLine, j, 0) +
                applyConvolution(currentLine, j, 1) +
                applyConvolution(matrix[min(N - 1, i + 1)], j, 2);
            buffer.push_back(output);
        }

        matrix[i] = buffer;
        previousLine = currentLine;
        currentLine = matrix[min(N - 1, i + 1)];    //outlines
    }

    auto endTime = high_resolution_clock::now();
    double difference = duration<double, milli>(endTime - startTime).count();
    cout << difference << " ms" << endl;
}

void performParallelConvolution(MyBarrier& barrier, int offset, int start, int end) {
    vector<int> previousLine, currentLine;

    if (start > 0)
        previousLine = matrix[start - 1];
    else
        previousLine = matrix[start];   //outline

    currentLine = matrix[start];

    vector<int> previousLineBuffer, nextLineBuffer;
    previousLineBuffer.clear();
    nextLineBuffer.clear();

    for (int i = start; i < end; i++) {
        for (int j = 0; j < M; j++) {
            int output = applyConvolution(previousLine, j, 0) +
                applyConvolution(currentLine, j, 1) +
                applyConvolution(matrix[min(N - 1, i + 1)], j, 2);

            if (i == end - 1)
                nextLineBuffer.push_back(output);
            else if (i == start)
                previousLineBuffer.push_back(output);
            else
                matrix[i][j] = output;
        }

        previousLine = currentLine;
        currentLine = matrix[min(N - 1, i + 1)];
    }

    barrier.wait();

    matrix[start] = previousLineBuffer;
    matrix[end - 1] = nextLineBuffer;
}

void performParallelization(MyBarrier& barrier, int offset) {
    vector<thread> threads;
    int start = 0, end = 0;
    int chunk = N / p;
    int rest = N % p;

    auto startTime = high_resolution_clock::now();

    for (size_t i = 0; i < p; i++) {
        start = end;
        end = start + chunk;
        if (rest > 0) {
            end++;
            rest--;
        }
        thread thr = thread(performParallelConvolution, ref(barrier), offset, start, end);
        threads.push_back(std::move(thr));
    }

    for (auto& th : threads) {
        if (th.joinable())
            th.join();
    }

    auto endTime = high_resolution_clock::now();
    double difference = duration<double, milli>(endTime - startTime).count();
    cout << difference << " ms" << endl;
}

void compareFiles(string path_t, string path_v) {
    ifstream fin_t(path_t);
    ifstream fin_v(path_v);

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
    p = 0; 
    MyBarrier barrier{ p };
    readInput("input.txt");

    int offset = (n - 1) / 2;

    if (p == 0) {
        performSequentialConvolution(offset);
    }
    else {
        performParallelization(barrier, offset);
    }

    /*writeOutput("output.txt", matrix);

    if (p == 0) {
        writeOutput("valid.txt", matrix);
    } else {
        checkCompliance("output.txt", "valid.txt");
    }*/
    return 0;
}

int applyConvolution(vector<int>& values, int j, int kernelRow) {
    return values[max(j - 1, 0)] * kernel[kernelRow][0] +
        values[j] * kernel[kernelRow][1] +
        values[min(M - 1, j + 1)] * kernel[kernelRow][2];
}
