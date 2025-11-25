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

    public static boolean isFileText(String filePath) {
        final int MIN_PATH_LENGTH = 4;

        //String fileExt;
        boolean isText;
        int pathLength = filePath.length();

        isText = true;

        if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.charAt(pathLength - 1) != 't') || (filePath.charAt(pathLength - 2) != 'x') || (filePath.charAt(pathLength - 3) != 't') || (filePath.charAt(pathLength - 4) != '.'))
            isText = false;

        return isText;
    }

    public static boolean checkMyFile(/*File testFile, */boolean isFileOutput) {
        boolean checkInput;
        String filePath;
        checkInput = false;
        filePath = testFile.getAbsolutePath();

        if (testFile.exists()) {
            System.out.print("Error, file with path <" + filePath + "> is not exists.\n");
        } else if (!isFileText(filePath))
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

    // public static int[][] writeInMatrix(int arrLength, Scanner scanner) {
    // final int MIN_NUMBER = -100000;
    // final int MAX_NUMBER = 100000;

    // int i;
    // int j;
    // int[][] arrayA;

    // i = 0;
    // j = 0;

    // arrayA = new int[arrLength][arrLength];

    // for (i = 0; i < arrLength; i++) {
    // for (j = 0; j < arrLength; j++) {
    // System.out.printf("Write element [%d][%d] of matrix: ", i, j);
    // arrayA[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "Write element: ",
    // scanner);
    // }
    // }
    // return arrayA;
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

    public static String askTheFilePath(Scanner scanner) {
        String filePath;

        System.out.print("Write the existing file path: ");
        filePath = scanner.nextLine();

        return filePath;
    }

    public static String assignMyFile(boolean isFileOutput, Scanner scanner) {
        String filePath;
        boolean isIncorrect;

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

    public static int[][] readMatrixFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath,
            BufferedReader fileReader) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;

        int[][] matrix;
        int matrixSize;
        int i;
        int j;
        String[] elements;
        String line;

        matrixSize = 0;
        i = 0;
        j = 0;

        // inputFile = new File(filePath);
        try {
            matrixSize = Integer.parseInt(fileReader.readLine());
        } catch (NumberFormatException e) {
            System.out.print("Error, NumberFormatException.");
        } catch (IOException e) {
            System.out.print("Error, IOException.");
        }
        // System.out.print(matrixSize);

        // if (inputFile.eof())
        // {
        // cout << "FILE IS EMPTY" << endl;
        // matrix = 0;
        // }
        // else
        // {

        if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH) {
            System.out.printf("Incorrect matrix length, the number must fit the range [%d,%d].\n", MIN_LENGTH,
                    MAX_LENGTH);
            matrix = null;
        } else {
            matrix = createMatrix(matrixSize);

            // for (i = 0; i < matrixSize; i++)
            // for (j = 0; j < matrixSize; j++) {
            // matrix[i][j] = Integer.parseInt(fileScanner.nextLine());
            // }

            for (i = 0; i < matrixSize; i++) {
                try {
                    // elements = null;
                    line = fileReader.readLine();
                    elements = line.split(" ");
                    for (j = 0; j < matrixSize; j++) {
                        matrix[i][j] = Integer.parseInt(elements[j]);
                    }
                } catch (IOException e) {
                    System.out.print("Error, something went wrong with matrix read from file.");
                }
            }

            // if (inputFile.fail())
            // {
            // //cout << "Error with reading matrix data, bad file read." << endl;
            // //delete[] matrix;
            // deleteMatrix(matrix, matrixSize);
            // matrix = 0;
            // }
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

    public static void main(String[] args) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int[][] matrix;
        boolean isFromFile;
        boolean isToFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;
        BufferedReader bufReader;
        //Scanner fileScanner;
        Scanner consoleScanner = new Scanner(System.in);
        // BufferedReader bufReader = new BufferedReader(new FileReader(filePath));

        isFromFile = false;
        isToFile = false;
        isOutput = false;
        isAllUndone = true;

        //fileScanner = null;
        bufReader = null;

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);
        isOutput = false;

        // try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath)))
        // {
        // Scanner fileScanner = new Scanner(bufReader);
        // //num = Integer.parseInt(fileScanner.nextLine());
        // //fileScanner.close();
        // } catch (NumberFormatException e) {
        // System.out.println("˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜.");
        // }

        // try {
        // bufReader = new BufferedReader(new FileReader(filePath));
        // fileScanner = new Scanner(bufReader);
        // } catch (FileNotFoundException e) {
        // System.out.print("Error, file not found.");
        // }

        if (isFromFile) {
            isAllUndone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try {
                    bufReader = new BufferedReader(new FileReader(filePath));
                    //fileScanner = new Scanner(bufReader);
                } catch (FileNotFoundException e) {
                    System.out.print("Error, file not found.");
                }

                matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader);

                if (matrix == null)
                    System.out.print("Error with reading matrix data, bad file read.\n");
                else
                    isAllUndone = false;

            } while (isAllUndone);
        } else
            matrix = readMatrixFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);

        writeMatrixIntoConsole(matrix);

        // filePath = assignMyFile(isOutput, scanner);
        // try {
        // bufReader = new BufferedReader(new FileReader(filePath));
        // fileScanner = new Scanner(bufReader);
        // a = readMatrixFromConsole(MIN_NUMBER, MAX_NUMBER, fileScanner);
        // writeOutMatrix(a);
        // fileScanner.close();
        // } catch (FileNotFoundException e) {
        // System.out.print("Error, file not found.");
        // }

        //fileScanner.close();
        consoleScanner.close();
    }
}
