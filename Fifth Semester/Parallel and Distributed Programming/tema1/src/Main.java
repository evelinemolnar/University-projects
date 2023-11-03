import java.io.*;
import java.util.Scanner;

public class Main {

    private static int numRows, numCols, kernelRows, kernelCols, numThreads, offset;
    private static int[][] inputMatrix, convolutionKernel, outputMatrix;

    public static void readInput(String path) {
        try {
            File file = new File(path);
            Scanner scanner = new Scanner(file);

            numRows = Integer.parseInt(scanner.nextLine());
            numCols = Integer.parseInt(scanner.nextLine());

            inputMatrix = new int[numRows][numCols];

            for (int i = 0; i < numRows; i++) {
                String data = scanner.nextLine();
                String[] line = data.split(" ");
                for (int j = 0; j < numCols; j++) {
                    inputMatrix[i][j] = Integer.parseInt(line[j]);
                }
            }

            kernelRows = Integer.parseInt(scanner.nextLine());
            kernelCols = Integer.parseInt(scanner.nextLine());

            convolutionKernel = new int[kernelRows][kernelCols];

            for (int i = 0; i < kernelRows; i++) {
                String data = scanner.nextLine();
                String[] line = data.split(" ");
                for (int j = 0; j < kernelCols; j++) {
                    convolutionKernel[i][j] = Integer.parseInt(line[j]);
                }
            }

            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("An error occurred while reading input.");
            e.printStackTrace();
        }
    }

    public static void writeOutput(String path, int[][] matrix) {
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(path));
            for (int[] row : matrix) {
                for (int value : row) {
                    writer.write(value + " ");
                }
                writer.newLine();
            }
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static int singlePixelConvolution(int x, int y) {
        int output = 0;
        for (int i = 0; i < kernelRows; i++) {
            for (int j = 0; j < kernelCols; j++) {
                int ii = x - offset + i;
                int jj = y - offset + j;

                if (ii < 0) ii = 0;
                else if (ii >= numRows) ii = numRows - 1;
                if (jj < 0) jj = 0;
                else if (jj >= numCols) jj = numCols - 1;

                output += inputMatrix[ii][jj] * convolutionKernel[i][j];
            }
        }
        return output;
    }

    public static void sequentialConvolution() {
        long startTime = System.nanoTime();

        //parcurgerea fiecarui "pixel" si aplicarea convolutiei
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                outputMatrix[i][j] = singlePixelConvolution(i, j);
            }
        }

        long endTime = System.nanoTime();
        System.out.println((double)(endTime - startTime) / 1E6);
    }

    public static void parallelConvolution() throws InterruptedException {
        //crearea unui vector de threaduri
        Thread[] t = new MyThread[numThreads];

        int start, end = 0;
        int mx = Math.max(numRows, numCols);
        int chunk = mx / numThreads;
        int rest = mx % numThreads;

        long startTime = System.nanoTime();

        for (int i = 0; i < t.length; i++) {
            start = end;
            end = start + chunk;
            if (rest > 0) {
                end++;
                rest--;
            }
            t[i] = new MyThread(numCols, start, end, outputMatrix);
            t[i].start();
        }

        for (Thread thread : t) {
            thread.join();
        }

        long stopTime = System.nanoTime();

        System.out.println((double)(stopTime - startTime) / 1E6);
    }

    public static void compareFiles(String filePath1, String filePath2) throws Exception {
        File objTest = new File(filePath1);
        Scanner readerTest = new Scanner(objTest);

        File objValid = new File(filePath2);
        Scanner readerValid = new Scanner(objValid);

        while (readerTest.hasNextLine() && readerValid.hasNextLine()) {
            String test = readerTest.nextLine();
            String valid = readerValid.nextLine();

            if (!valid.equals(test)) {
                throw new Exception("Invalid output");
            }
        }

        if (readerTest.hasNextLine() || readerValid.hasNextLine()) {
            throw new Exception("Invalid output");
        }
    }

    public static void main(String[] args) throws Exception {
        readInput("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1\\src\\input.txt");
        //alocare matrice output
        outputMatrix = new int[numRows][numCols];

        //numThreads = Integer.parseInt(args[0]); //powershell
        numThreads = 2;
        offset = (kernelRows - 1) / 2;  //pentru a putea face convolutia si pe margini(ajustrarea matricei)

        if (numThreads == 0) {
            sequentialConvolution();
        } else {
            parallelConvolution();
        }

        if (numThreads == 0) {
            writeOutput("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1\\src\\output2.txt", outputMatrix);
        } else {
            writeOutput("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1\\src\\output.txt", outputMatrix);
            compareFiles("C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1\\src\\output.txt", "C:\\Users\\eveli\\OneDrive\\Desktop\\anul3\\PPD\\tema1\\src\\output2.txt");
        }

    }

    public static class MyThread extends Thread {
        int numCols, start, end;
        int[][] outputMatrix;

        public MyThread(int numCols, int start, int end, int[][] outputMatrix) {
            this.numCols = numCols;
            this.start = start;
            this.end = end;
            this.outputMatrix = outputMatrix;
        }

        public void run() {
            if (numRows > numCols) {
                for (int i = start; i < end; i++) {
                    for (int j = 0; j < numCols; j++) {
                        this.outputMatrix[i][j] = singlePixelConvolution(i, j);
                    }
                }
            } else {
                for (int i = 0; i < numRows; i++) {
                    for (int j = start; j < end; j++) {
                        this.outputMatrix[i][j] = singlePixelConvolution(i, j);
                    }
                }
            }
        }
    }
}