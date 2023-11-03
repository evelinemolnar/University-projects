import java.io.*;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;

import static java.lang.Math.max;
import static java.lang.Math.min;

public class Main {
    private static int N;
    private static int M;
    private static int n;
    private static int m;
    private static int numThreads;
    private static int[][] matrix;
    private static int[][] kernel;

    private static CyclicBarrier barrier;

    public static void read(String path) {
        try (BufferedReader br = new BufferedReader(new FileReader(path))) {
            N = Integer.parseInt(br.readLine());
            M = Integer.parseInt(br.readLine());

            matrix = new int[N][M];

            for (int i = 0; i < N; i++) {
                String[] line = br.readLine().split(" ");
                for (int j = 0; j < M; j++) {
                    matrix[i][j] = Integer.parseInt(line[j]);
                }
            }

            n = Integer.parseInt(br.readLine());
            m = Integer.parseInt(br.readLine());

            kernel = new int[n][m];

            for (int i = 0; i < n; i++) {
                String[] line = br.readLine().split(" ");
                for (int j = 0; j < m; j++) {
                    kernel[i][j] = Integer.parseInt(line[j]);
                }
            }
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void write(String path, int[][] matrix) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(path))) {
            for (int[] row : matrix) {
                StringBuilder line = new StringBuilder();
                for (int value : row) {
                    line.append(value).append(" ");
                }
                bw.write(line.toString().trim());
                bw.newLine();
            }
            bw.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) throws Exception {
        read("input.txt");
        //numThreads = Integer.parseInt(args[0]);
        numThreads = 0;
        if (numThreads != 0) {
            barrier = new CyclicBarrier(numThreads);    // create a barrier with the number of threads
        }

        if (numThreads == 0)
            sequentialConvolution();
        else
            parallelConvolution();

//        write("output.txt", matrix);
//        if (numThreads == 0) {
//            write("valid.txt", matrix);
//        } else {
//            compareFiles("output.txt", "valid.txt");
//        }
    }

    private static void compareFiles(String pathTest, String pathValid) throws Exception {
        try (BufferedReader readerTest = new BufferedReader(new FileReader(pathTest));
             BufferedReader readerValid = new BufferedReader(new FileReader(pathValid))) {

            String test;
            String valid;

            while ((test = readerTest.readLine()) != null && (valid = readerValid.readLine()) != null) {
                if (!valid.equals(test)) {
                    throw new Exception("Invalid output");
                }
            }

            if (readerTest.readLine() != null || readerValid.readLine() != null) {
                throw new Exception("Invalid output");
            }
        }
    }

    public static void sequentialConvolution() {
        long startTime = System.nanoTime();

        int[] previousLine = new int[M];
        int[] currentLine = new int[M];

        System.arraycopy(matrix[0], 0, previousLine, 0, M);
        System.arraycopy(matrix[0], 0, currentLine, 0, M);

        for (int i = 0; i < N; i++) {   // for each line
            int[] buffer = new int[M];  //store the computed values for the current row.
            for (int j = 0; j < M; j++) {
                int output; // the computed value for the current cell
                output = applyConvolution(previousLine, j, 0) + applyConvolution(currentLine, j, 1) + applyConvolution(matrix[min(N - 1, i + 1)], j, 2);

                buffer[j] = output;
            }

            System.arraycopy(buffer, 0, matrix[i], 0, M);
            System.arraycopy(currentLine, 0, previousLine, 0, currentLine.length);
            System.arraycopy(matrix[min(N - 1, i + 1)], 0, currentLine, 0, currentLine.length);
        }

        long endTime = System.nanoTime();
        System.out.println((double)(endTime - startTime) / 1E6);
    }

    public static void parallelConvolution() throws InterruptedException {
        Thread[] t = new MyThread[numThreads];

        int start, end = 0;
        int chunk = N / numThreads;
        int rest = N % numThreads;

        long startTime = System.nanoTime();

        for (int i = 0; i < t.length; i++) {
            start = end;
            end = start + chunk;
            if (rest > 0) { // if there are still lines to be distributed
                end++;
                rest--;
            }
            t[i] = new MyThread(start, end);
            t[i].start();
        }

        for (Thread thread : t) {
            thread.join();
        }

        long stopTime = System.nanoTime();

        System.out.println((double)(stopTime - startTime) / 1E6);
    }

    public static class MyThread extends Thread {
        int start, end;

        public MyThread(int start, int end) {
            this.start = start;
            this.end = end;
        }

        public void run() {
            int[] previousLine = new int[M];
            int[] currentLine = new int[M];

            System.arraycopy(matrix[Math.max(start - 1, 0)], 0, previousLine, 0, M);
            System.arraycopy(matrix[start], 0, currentLine, 0, M);

            int[] previousLineBuffer = new int[M];
            int[] nextLineBuffer = new int[M];

            for (int i = start; i < end; i++) {
                for (int j = 0; j < M; j++) {
                    int output;
                    output = applyConvolution(previousLine, j, 0) + applyConvolution(currentLine, j, 1) + applyConvolution(matrix[min(N - 1, i + 1)], j, 2);

                    if (i == start) {
                        previousLineBuffer[j] = output;
                    } else if (i == end - 1) {
                        nextLineBuffer[j] = output;
                    } else {
                        matrix[i][j] = output;
                    }
                }

                System.arraycopy(currentLine, 0, previousLine, 0, currentLine.length);
                System.arraycopy(matrix[min(N - 1, i + 1)], 0, currentLine, 0, currentLine.length);
            }

            try {
                barrier.await();
            } catch (InterruptedException | BrokenBarrierException ignored) {}

            System.arraycopy(previousLineBuffer, 0, matrix[start], 0, M);
            System.arraycopy(nextLineBuffer, 0, matrix[end - 1], 0, M);
        }
    }

    private static int applyConvolution(int[] values, int j, int kernelRow) {    //handle the borders
        return values[max(j - 1, 0)] * kernel[kernelRow][0] + values[j] * kernel[kernelRow][1] + values[min(M - 1, j + 1)] * kernel[kernelRow][2];
    }
}
