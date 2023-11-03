import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Arrays;
import java.util.Random;

public class Main {

    public static void generateMatrix(int n, int m) {
        int[][] matrix = new int[n][m];
        Random random = new Random();
        try (BufferedWriter writer = new BufferedWriter(new FileWriter("matrix_output.txt"))) {
            writer.write(n + "\n");
            writer.write(m + "\n");
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    matrix[i][j] = random.nextInt(100) + 1; // Generates random integers between 1 and 100
                    writer.write(matrix[i][j] + " ");
                }
                writer.write("\n");
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        // Example usage:
        int n = 10000; // Number of rows
        int m = 10000; // Number of columns

        generateMatrix(n, m);

    }
}
