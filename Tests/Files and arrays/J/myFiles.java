import java.util.Scanner;
import java.io.*;

public class myFiles {

    public static int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER, String str, Scanner scanner) {

        boolean isIncorrect;
        int number;

        number = 0;
        isIncorrect = true;

        do {

            System.out.print(str);
            isIncorrect = false;

            try {
                number = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.println("Incorrect input, try again.");
            }

            if (!isIncorrect && (number < MIN_NUMBER || number > MAX_NUMBER)) {
                isIncorrect = true;
                System.out.printf("The number must fit the range [%d,%d].\n", MIN_NUMBER, MAX_NUMBER);
            }

        } while (isIncorrect);

        return number;
    }

    public static boolean workWithConsoleOrFile(boolean isOutput, Scanner scanner) {
        int number;
        boolean isFromFile;

        number = 0;
        isFromFile = false;

        if (isOutput)
            System.out.print("If data is output to the console write 0, if from file write 1.\n");
        else
            System.out.print("If data is entered from the console write 0, if from file write 1.\n");

        number = readAndVerify(0, 1, "> ", scanner);

        if (number == 1)
            isFromFile = true;
        else
            isFromFile = false;

        if (isFromFile)
            if (isOutput)
                System.out.print("The data is output to a file.\n");
            else
                System.out.print("The data is entered from a file.\n");
        else if (isOutput)
            System.out.print("The data is output to the console.\n");
        else
            System.out.print("The data is entered from the console.\n");

        return isFromFile;
    }

    // public static int[][] writeInMatrix(int arrLength, Scanner scanner) {
    //     final int MIN_NUMBER = -100000;
    //     final int MAX_NUMBER = 100000;

    //     int i;
    //     int j;
    //     int[][] arrayA;

    //     i = 0;
    //     j = 0;

    //     arrayA = new int[arrLength][arrLength];

    //     for (i = 0; i < arrLength; i++) {
    //         for (j = 0; j < arrLength; j++) {
    //             System.out.printf("Write element [%d][%d] of matrix: ", i, j);
    //             arrayA[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "Write element: ", scanner);
    //         }
    //     }
    //     return arrayA;
    // }

    public static int[][] createMatrix(int size) {
        int[][] matrix;

        matrix = new int[size][size];

        // for (int i = 0; i < size; i++)
        // matrix[i] = new int[size];

        return matrix;
    }

    public static int[][] readMatrixFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;

        int[][] matrix;
        int matrixSize;
        int i;
        int j;

        i = 0;
        j = 0;
        matrixSize = 0;

        matrixSize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write matrix length: ", scanner);

        matrix = createMatrix(matrixSize);

        for (i = 0; i < matrixSize; i++)
            for (j = 0; j < matrixSize; j++) {
                System.out.printf("Write element [%d,%d] of matrix: ", i, j);
                matrix[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "", scanner);
            }

        return matrix;
    }

    public static void writeMatrixIntoConsole(int[][] matrix, int size) {
        System.out.print("The result matrix is: \n");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++)
                System.out.print(matrix[i][j] + " ");
            System.out.print("\n");
        }
    }

    public static void writeOutMatrix(int[][] arrayA) {
        int i;
        int j;
        int n;

        i = 0;
        j = 0;
        n = arrayA.length;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                System.out.print(arrayA[i][j] + " ");
            }
            System.out.print("\n");
        }
    }

    public static void main(String[] args) {

        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER =  100000;

        int[][] a;
        boolean isFromFile;
        boolean isOutput;
        Scanner scanner = new Scanner(System.in);

        isFromFile = false;
        isOutput = false;

        isFromFile = workWithConsoleOrFile(isOutput, scanner);

        a = readMatrixFromConsole(MIN_NUMBER, MAX_NUMBER, scanner);
        writeOutMatrix(a);

        scanner.close();
    }
}
