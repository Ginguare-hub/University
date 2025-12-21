import java.util.Scanner;
import java.io.*;

public class java_files_singleData {

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

    public static int readIntegerFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {
        final int MIN_LENGTH = 0;
        final int MAX_LENGTH = 1000000;

        int answer;
        answer = 0;
        answer = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write number: ", scanner);

        return answer;
    }

    public static int readIntegerFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath, BufferedReader fileReader) {
        final int MIN_LENGTH = 0;
        final int MAX_LENGTH = 1000000;

        int intAnswer;
        String strAnswer;

        intAnswer = 0;
        strAnswer = "";

        try {
            strAnswer = fileReader.readLine();
            intAnswer = Integer.parseInt(strAnswer);
        } catch (NumberFormatException e) {
            System.out.print("Error, NumberFormatException.\n");
        } catch (IOException e) {
            System.out.print("Error, IOException.\n");
        }

        if (intAnswer < MIN_LENGTH || intAnswer > MAX_LENGTH) {
            System.out.printf("Incorrect number, the number must fit the range [%d,%d].\n", MIN_LENGTH, MAX_LENGTH);
            intAnswer = 0;
        }

        return intAnswer;
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

    public static void writeIntegerIntoConsole(int number) {
        System.out.printf("The result is: " + number);
    }

    public static boolean writeMatrixIntoFile(String filePath, int number) {
        boolean isIncorrect;
        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write("The result is: \n" + number);
            System.out.print("Number written to file successfully.\n");
            fileWriter.close();
        } catch (IOException e) {
            System.out.print("Error with file write.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static int readingStage(Scanner consoleScanner) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int number;
        boolean isFromFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        number = 0;
        isFromFile = false;
        isOutput = false;
        isAllUndone = true;
        filePath = "";

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);
        isOutput = false;

        if (isFromFile) {
            isAllUndone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    number = readIntegerFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (number == 0)
                    System.out.print("There is might be error with reading number, bad file read or file is not open for reading.\n");
                else
                    isAllUndone = false;

            } while (isAllUndone);
        } else
            number = readIntegerFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);

        return number;
    }

    public static void writingStage(int number, Scanner consoleScanner) {
        boolean isToFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        isToFile = false;
        isAllUndone = false;
        isOutput = false;
        filePath = "";

        isToFile = workWithConsoleOrFile(true, consoleScanner);
        isOutput = true;

        if (isToFile) {
            do {
                filePath = assignMyFile(isOutput, consoleScanner);
                isAllUndone = writeMatrixIntoFile(filePath, number);
            } while (isAllUndone);
        } else
            writeIntegerIntoConsole(number);
    }

    public static void main(String[] args) {
        int number;
        Scanner consoleScanner = new Scanner(System.in);

        number = 0;

        writePurpose();
        number = readingStage(consoleScanner);
        writingStage(number, consoleScanner);

        consoleScanner.close();
    }
}
