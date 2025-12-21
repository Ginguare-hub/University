import java.util.Scanner;
import java.io.*;

public class myFiles {

    public static void writePurpose() {
        System.out.print("REWRITE_REWRITE_REWRITE");
    }

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

    public static boolean isFileText(String filePath) {
        final int MIN_PATH_LENGTH = 4;

        boolean isText;
        int pathLength;
        
        isText = true;
        pathLength = filePath.length();

        if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.charAt(pathLength - 1) != 't')
                || (filePath.charAt(pathLength - 2) != 'x') || (filePath.charAt(pathLength - 3) != 't')
                || (filePath.charAt(pathLength - 4) != '.'))
            isText = false;

        return isText;
    }

    public static boolean checkMyFile(String filePath, boolean isFileOutput) {
        boolean checkInput;
        File testFile;

        checkInput = false;
        testFile = new File(filePath);

        if (!testFile.exists())
            System.out.print("Error, file with path <" + filePath + "> is not exists.\n");
        else if (!isFileText(filePath))
            System.out.print("Error, filename is not .txt\n");
        else if (!isFileOutput && !testFile.canRead())
            System.out.print("Error, no access to read the file.\n");
        else if (isFileOutput && !testFile.canWrite())
            System.out.print("Error, no access to write into the file.\n");
        else {
            checkInput = true;
            System.out.print("Assigning is completed successfully.\n");
        }
        return checkInput;
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

    public static int[][] createMatrix(int size) {
        int[][] matrix;
        matrix = new int[size][size];
        return matrix;
    }

    public static int[][] readMatrixFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;

        int[][] matrix;
        int matrixSize;
        int i;
        int j;

        matrix = null;
        matrixSize = 0;
        i = 0;
        j = 0;

        matrixSize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write matrix length: ", scanner);
        matrix = createMatrix(matrixSize);

        for (i = 0; i < matrixSize; i++)
            for (j = 0; j < matrixSize; j++) {
                System.out.printf("Write element [%d,%d] of matrix: ", i, j);
                matrix[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "", scanner);
            }

        return matrix;
    }

    public static String askTheFilePath(Scanner scanner) {
        String filePath;
        System.out.print("Write the existing file path: ");
        filePath = scanner.nextLine();
        return filePath;
    }

    public static String assignMyFile(boolean isFileOutput, Scanner scanner) {
        String filePath;
        boolean isIncorrect;

        filePath = "";
        isIncorrect = false;

        do {
            filePath = askTheFilePath(scanner);
            isIncorrect = !checkMyFile(filePath, isFileOutput);
        } while (isIncorrect);

        return filePath;
    }

    public static void writeMatrixIntoConsole(int[][] matrix) {
        int matrixLength;

        matrixLength = matrix.length;

        System.out.print("The result matrix is: \n");
        for (int i = 0; i < matrixLength; i++) {
            for (int j = 0; j < matrixLength; j++)
                System.out.print(matrix[i][j] + " ");
            System.out.print("\n");
        }
    }

    public static int[][] readMatrixFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath, BufferedReader fileReader) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;

        int[][] matrix;
        int matrixSize;
        int i;
        int j;
        String[] elements;
        String line;
        String kad;

        matrix = null;
        matrixSize = 0;
        i = 0;
        j = 0;
        line = "";

        try {
            kad = fileReader.readLine();
            matrixSize = Integer.parseInt(kad);
        } catch (NumberFormatException e) {
            System.out.print("Error, NumberFormatException.\n");
        } catch (IOException e) {
            System.out.print("Error, IOException.\n");
        }

        if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH) {
            System.out.printf("Incorrect matrix length, the number must fit the range [%d,%d].\n", MIN_LENGTH,
                    MAX_LENGTH);
            matrix = null;
        } else {
            matrix = createMatrix(matrixSize);

            for (i = 0; i < matrixSize; i++) {
                try {
                    line = fileReader.readLine();
                    elements = line.split(" ");
                    for (j = 0; j < matrixSize; j++) {
                        matrix[i][j] = Integer.parseInt(elements[j]);
                    }
                } catch (IOException e) {
                    System.out.print("Error, something went wrong with matrix read from file.");
                }
            }
        }
        return matrix;
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

    public static boolean writeMatrixIntoFile(String filePath, int[][] matrix) {

        int matrixLength;
        boolean isIncorrect;

        matrixLength = matrix.length;
        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {

            fileWriter.write("The result matrix is: \n");
            for (int i = 0; i < matrixLength; i++) {
                for (int j = 0; j < matrixLength; j++) {
                    fileWriter.write(matrix[i][j] + " ");
                }
                fileWriter.write("\n");
            }
            System.out.print("Matrix written to file successfully.\n");
            fileWriter.close();
        } catch (IOException e) {
            System.out.print("Error with file write.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static int[][] readingStage(Scanner consoleScanner) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int[][] matrix;
        boolean isFromFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        matrix = null;
        isFromFile = false;
        isOutput = false;
        isAllUndone = true;
        matrix = null;
        filePath = "";

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);
        isOutput = false;

        if (isFromFile) {
            isAllUndone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (matrix == null)
                    System.out.print("Error with reading matrix data, bad file read or file is not open for reading.\n");
                else
                    isAllUndone = false;

            } while (isAllUndone);
        } else
            matrix = readMatrixFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);

        return matrix;
    }

    public static void writingStage(int[][] matrix, Scanner consoleScanner) {
        boolean isToFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        isToFile = false;
        isOutput = false;
        filePath = "";

        isToFile = workWithConsoleOrFile(true, consoleScanner);
        isOutput = true;

        if (isToFile) {
            do {
                filePath = assignMyFile(isOutput, consoleScanner);
                isAllUndone = writeMatrixIntoFile(filePath, matrix);
            } while (isAllUndone);
        } else
            writeMatrixIntoConsole(matrix);
    }

    public static void main(String[] args) {
        int[][] matrix;
        Scanner consoleScanner = new Scanner(System.in);

        matrix = null;

        writePurpose();
        matrix = readingStage(consoleScanner);
        writingStage(matrix, consoleScanner);

        consoleScanner.close();
    }
}
