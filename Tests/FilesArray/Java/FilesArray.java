import java.util.Scanner;
import java.io.*;

public class FilesArray {

    public static void writePurpose() {
        System.out.print("REWRITE_REWRITE_REWRITE \n");
    }

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

        if ((filePath.length() < MIN_PATH_LENGTH) 
                || (filePath.charAt(pathLength - 1) != 't')
                || (filePath.charAt(pathLength - 2) != 'x') 
                || (filePath.charAt(pathLength - 3) != 't')
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
        boolean isFromFile;
        int number;

        isFromFile = false;
        number = 0;

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

    public static int[] createArray(int size) {
        int[] array1;
        array1 = new int[size];
        return array1;
    }

    public static int[] readArrayFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath, BufferedReader fileReader) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 100;

        int[] array1;
        int arraySize;
        int i;
        String[] elementsArray;
        String element;
        String line;

        array1 = null;
        elementsArray = null;
        arraySize = 0;
        i = 0;
        line = "";

        try {
            element = fileReader.readLine();
            arraySize = Integer.parseInt(element);
        } catch (NumberFormatException e) {
            System.out.print("Error, NumberFormatException.\n");
        } catch (IOException e) {
            System.out.print("Error, IOException.\n");
        }

        if (arraySize < MIN_LENGTH || arraySize > MAX_LENGTH) {
            System.out.printf("Incorrect array length, the number must fit the range [%d,%d].\n", MIN_LENGTH, MAX_LENGTH);
            array1 = null;
        } else {
            array1 = createArray(arraySize);

            try {
                line = fileReader.readLine();
                elementsArray = line.split(" ");
            } catch (IOException e) {
                System.out.print("Error, something went wrong with read from file.");
            }

            for (i = 0; i < arraySize; i++) {
                array1[i] = Integer.parseInt(elementsArray[i]);
            }
        }
        return array1;
    }

    public static int[] readArrayFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 100;

        int[] array1;
        int arraySize;
        int i;

        array1 = null;
        arraySize = 0;
        i = 0;

        arraySize = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write array length: ", scanner);
        array1 = createArray(arraySize);

        for (i = 0; i < arraySize; i++) {
            System.out.printf("Write element [%d] of array: ", i);
            array1[i] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "", scanner);
        }

        return array1;
    }

    public static boolean writeArrayIntoFile(String filePath, int[] array1) {

        int arraySize;
        boolean isIncorrect;

        arraySize = array1.length;
        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {

            fileWriter.write("The result array is: \n");

            for (int i = 0; i < arraySize; i++) {     
                fileWriter.write(array1[i] + " ");      
            }

            fileWriter.write("\n");
            System.out.print("Array written to file successfully.\n");
            fileWriter.close();
        } catch (IOException e) {
            System.out.print("Error with file write.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static void writeArrayIntoConsole(int[] array1) {
        int arraySize;
        arraySize = array1.length;
        System.out.print("The result array is: \n");

        for (int i = 0; i < arraySize; i++) {
            System.out.print(array1[i] + " ");
        }

        System.out.print("\n");
    }

    public static int[] readingStage(Scanner consoleScanner) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int[] array1;
        boolean isFromFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        array1 = null;
        isFromFile = false;
        isAllUndone = true;
        filePath = "";
        
        isOutput = false;
        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isFromFile) {
            isAllUndone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    array1 = readArrayFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (array1 == null)
                    System.out.print("Error with reading data, bad file read or file is not open for reading.\n");
                else
                    isAllUndone = false;

            } while (isAllUndone);
        } else
            array1 = readArrayFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);

        return array1;
    }

    public static void writingStage(int[] array1, Scanner consoleScanner) {
        boolean isToFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        isToFile = false;
        filePath = "";

        isOutput = true;
        isToFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isToFile) {
            do {
                filePath = assignMyFile(isOutput, consoleScanner);
                isAllUndone = writeArrayIntoFile(filePath, array1);
            } while (isAllUndone);
        } else
            writeArrayIntoConsole(array1);
    }

    public static void main(String[] args) {
        int[] matrix;
        Scanner consoleScanner = new Scanner(System.in);

        matrix = null;

        writePurpose();
        matrix = readingStage(consoleScanner);
        writingStage(matrix, consoleScanner);

        consoleScanner.close();
    }
}
