import java.util.Scanner;
import java.io.*;

public class Main {
    public static int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER, String str, Scanner scanner) {
        boolean isIncorrect;
        int number;

        isIncorrect = true;
        number = 0;

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

        if ((filePath.length() < MIN_PATH_LENGTH) || (filePath.charAt(pathLength - 1) != 't') || (filePath.charAt(pathLength - 2) != 'x') || (filePath.charAt(pathLength - 3) != 't') || (filePath.charAt(pathLength - 4) != '.'))
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

    public static int[] createArr(int size) {
        int[] arr;
        arr = new int[size];
        return arr;
    }

    public static int[] readArrFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;

        int[] arr;
        int arrSize;
        int i;

        i = 0;

        arrSize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write array length: ", scanner);
        arr = createArr(arrSize);

        for (i = 0; i < arrSize; i++){
            System.out.printf("Write element [%d] of array: ", i);
            arr[i] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "", scanner);
        }

        return arr;
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

    public static void writeArrIntoConsole(int[] answer) {
        System.out.print("The result array is: \n");
        for (int i = 0; i < answer.length; i++) {
            System.out.print(answer[i] + " ");
        }
        System.out.println();
    }

    public static int[][] readTwoArraysFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath, BufferedReader fileReader) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;

        int[][] arrays = new int[2][];
        int size1, size2;
        String line;
        String[] elements;

        try {
            line = fileReader.readLine();
            if (line == null) {
                System.out.print("Error: File is empty.\n");
                return null;
            }
            size1 = Integer.parseInt(line.trim());

            line = fileReader.readLine();
            if (line == null) {
                System.out.print("Error: Missing elements for first array.\n");
                return null;
            }
            elements = line.trim().split("\\s+");

            if (size1 < MIN_LENGTH || size1 > MAX_LENGTH) {
                System.out.printf("Incorrect first array length, the number must fit the range [%d,%d].\n", MIN_LENGTH, MAX_LENGTH);
                return null;
            }
            if (elements.length < size1) {
                System.out.print("Error: Not enough elements for first array in file.\n");
                return null;
            }

            arrays[0] = createArr(size1);
            for (int i = 0; i < size1; i++) {
                arrays[0][i] = Integer.parseInt(elements[i]);
                if (arrays[0][i] < MIN_NUMBER || arrays[0][i] > MAX_NUMBER) {
                    System.out.printf("Element %d in first array is out of range [%d,%d].\n", arrays[0][i], MIN_NUMBER, MAX_NUMBER);
                    return null;
                }
            }

            line = fileReader.readLine();
            if (line == null) {
                System.out.print("Error: Missing size for second array.\n");
                return null;
            }
            size2 = Integer.parseInt(line.trim());

            line = fileReader.readLine();
            if (line == null) {
                System.out.print("Error: Missing elements for second array.\n");
                return null;
            }
            elements = line.trim().split("\\s+");

            if (size2 < MIN_LENGTH || size2 > MAX_LENGTH) {
                System.out.printf("Incorrect second array length, the number must fit the range [%d,%d].\n", MIN_LENGTH, MAX_LENGTH);
                return null;
            }
            if (elements.length < size2) {
                System.out.print("Error: Not enough elements for second array in file.\n");
                return null;
            }
            arrays[1] = createArr(size2);
            for (int i = 0; i < size2; i++) {
                arrays[1][i] = Integer.parseInt(elements[i]);
                if (arrays[1][i] < MIN_NUMBER || arrays[1][i] > MAX_NUMBER) {
                    System.out.printf("Element %d in second array is out of range [%d,%d].\n", arrays[1][i], MIN_NUMBER, MAX_NUMBER);
                    return null;
                }
            }

        } catch (NumberFormatException e) {
            System.out.print("Error: Invalid number format in file.\n");
            return null;
        } catch (IOException e) {
            System.out.print("Error: IOException while reading file.\n");
            return null;
        }

        return arrays;
    }

    public static boolean writeArrayIntoFile(String filePath, int[] answer) {
        boolean isIncorrect;
        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write("The result array is: \n");
            for (int i = 0; i < answer.length; i++) {
                fileWriter.write(answer[i] + " ");
            }
            fileWriter.write("\n");
            System.out.print("Array written to file successfully.\n");
        } catch (IOException e) {
            System.out.print("Error with file write.\n");
            isIncorrect = true;
        }
        return isIncorrect;
    }

    public static int[][] readingBothStages(Scanner consoleScanner) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int[][] bothArrays = new int[2][];
        boolean isFromFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        isFromFile = false;
        isOutput = false;
        isAllUndone = true;
        filePath = "";

        System.out.println("Choose input method for both arrays:");
        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);
        isOutput = false;

        if (isFromFile) {
            isAllUndone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    bothArrays = readTwoArraysFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader);
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (bothArrays == null || bothArrays[0] == null || bothArrays[1] == null)
                    System.out.print("Error with reading arrays data, bad file read or file is not open for reading.\n");
                else
                    isAllUndone = false;

            } while (isAllUndone);
        } else {
            System.out.println("Enter first sorted array (ascending order):");
            bothArrays[0] = readArrFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);
            System.out.println("Enter second sorted array (ascending order):");
            bothArrays[1] = readArrFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);
        }

        return bothArrays;
    }

    public static int[] mergeArr(int[] a, int[] b) {
        int n = a.length;
        int m = b.length;
        int[] c = new int[n + m];
        int i = 0, j = 0, k = 0;

        while (i < n && j < m) {
            if (a[i] < b[j]) {
                c[k++] = a[i++];
            } else {
                c[k++] = b[j++];
            }
        }
        while (i < n) {
            c[k++] = a[i++];
        }
        while (j < m) {
            c[k++] = b[j++];
        }
        return c;
    }

    public static void writingStage(int[] answer, Scanner consoleScanner) {
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
                isAllUndone = writeArrayIntoFile(filePath, answer);
            } while (isAllUndone);
        } else
            writeArrIntoConsole(answer);
    }

    public static void main(String[] args) {
        int[][] bothArrays;
        int[] answer;
        Scanner consoleScanner = new Scanner(System.in);

        bothArrays = readingBothStages(consoleScanner);

        answer = mergeArr(bothArrays[0], bothArrays[1]);

        writingStage(answer, consoleScanner);

        consoleScanner.close();
    }
}
