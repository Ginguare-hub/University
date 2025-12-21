import java.util.Scanner;
import java.io.*;

public class Lab3_1 {

    public static void writePurpose() {
        System.out.print("Extract substring representing an integer from a string containing letters, digits, dots, \"+\" and \"-\".\n");
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

    public static String readStringFromConsole(Scanner scanner) {
        String answer;
        answer = "";
        answer = scanner.nextLine();
        return answer;
    }

    public static String readStringFromFile(String filePath, BufferedReader fileReader) {
        String strAnswer;

        strAnswer = "";

        try {
            strAnswer = fileReader.readLine();
        } catch (NumberFormatException e) {
            System.out.print("Error, NumberFormatException.\n");
        } catch (IOException e) {
            System.out.print("Error, IOException.\n");
        }

        return strAnswer;
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

    public static void writeStringIntoConsole(String str) {
        System.out.printf("The result is: " + str);
    }

    public static boolean writeStringIntoFile(String filePath, String str) {
        boolean isIncorrect;
        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write("Extracted integer: " + str);
            System.out.print("Answer written to file successfully.\n");
            fileWriter.close();
        } catch (IOException e) {
            System.out.print("Error with file write.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static boolean isDigit(char myChar) {
        boolean answer;
    
        answer = false;
    
        if ((myChar >= '0') && (myChar <= '9'))
            answer = true;
    
        return answer;
    }

    public static String extractInteger(String inputStr) {
        int i, j;
        String answer;
        boolean isNotFound;
    
        i = 0;
        j = 0;
        answer = "";
        isNotFound = true;
    
        while ((i < inputStr.length()) && isNotFound) {
            if (((inputStr.charAt(i) == '+') || (inputStr.charAt(i) == '-')) && (i + 1 < inputStr.length()) && isDigit(inputStr.charAt(i + 1))) {
            
                answer = answer + inputStr.charAt(i);
                j = i + 1;
            
                while ((j < inputStr.length()) && isNotFound) {
                    if (isDigit(inputStr.charAt(j)))
                        answer = answer + inputStr.charAt(j);
                
                    if (j == inputStr.length() - 1)
                        isNotFound = false;
                
                    if (isNotFound && (j + 1 < inputStr.length()) && isDigit(inputStr.charAt(j + 1))) {
                        if (j + 1 == inputStr.length() - 1) {
                            answer = answer + inputStr.charAt(j + 1);
                            isNotFound = false;
                        }
                    } else
                        isNotFound = false;
                    j++;
                }
            }
            i++;
        }
        return answer;
    }

    public static String readingStage(Scanner consoleScanner) {
        boolean isFromFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;
        String answer;

        isFromFile = false;
        isOutput = false;
        isAllUndone = true;
        filePath = "";
        answer = "";

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);
        isOutput = false;

        if (isFromFile) {
            isAllUndone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    answer = readStringFromFile(filePath, bufReader);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (answer == "")
                    System.out.print("There is might be error with reading, bad file read or file is not open for reading.\n");
                else
                    isAllUndone = false;

            } while (isAllUndone);
        } else
            answer = readStringFromConsole(consoleScanner);

        return answer;
    }

    public static void writingStage(String answer, Scanner consoleScanner) {
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
                isAllUndone = writeStringIntoFile(filePath, answer);
            } while (isAllUndone);
        } else
            writeStringIntoConsole(answer);
    }

    public static void main(String[] args) {
        String str;
        Scanner consoleScanner = new Scanner(System.in);

        str = "";

        writePurpose();
        str = readingStage(consoleScanner);
        str = extractInteger(str);
        writingStage(str, consoleScanner);

        consoleScanner.close();
    }
}
