import java.util.Scanner;
import java.io.*;

public class Lab3_5_J {

    public static void writePurpose() {
        System.out.print("The program replaces separators with \"+\" and calculates the sum of numbers in the string.\n");
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

    public static String[] createStringArray(int size) {
        String[] array1;
        array1 = new String[size];
        return array1;
    }

    public static String[] splitString(String str) {
        int startPos;
        int pos;
        int count;
        String[] answerArray;

        count = 0;
        pos = 0;
        startPos = 0;
        answerArray = null;

        while (pos < str.length()) {
            while (pos < str.length() && str.charAt(pos) == ' ')
                pos++;

            if (pos < str.length()) {
                count++;
                while (pos < str.length() && str.charAt(pos) != ' ')
                    pos++;
            }
        }

        if (count == 0)
            answerArray = null;
        else {
            answerArray = createStringArray(count);
            count = 0;
            pos = 0;

            while (pos < str.length()) {
                while (pos < str.length() && str.charAt(pos) == ' ')
                    pos++;

                if (pos < str.length()) {
                    startPos = pos;
                    while (pos < str.length() && str.charAt(pos) != ' ')
                        pos++;

                    answerArray[count] = str.substring(startPos, pos);
                    count++;
                }
            }
        }

        return answerArray;
    }

    public static String[] readArrayFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath, BufferedReader fileReader, StringBuilder givenString) {

        String[] array1;
        boolean isErrorNotFound;
        String separatorString;
        String line;

        array1 = null;
        isErrorNotFound = true;
        separatorString = "";
        line = "";

        try {
            line = fileReader.readLine();
        } catch (NumberFormatException e) {
            array1 = null;
        } catch (IOException e) {
            array1 = null;
        }

        if (array1 == null) {
            try {
                separatorString = fileReader.readLine();
            } catch (IOException e) {
                System.out.print("Incorrect numeric data: array element.\n");
                array1 = null;
                isErrorNotFound = false;
            }

            if (separatorString != null)
                array1 = splitString(separatorString);

            if (isErrorNotFound) {
                try {
                    line = fileReader.readLine();
                    if (line != null)
                        givenString.append(line);
                } catch (IOException e) {
                    System.out.print("Incorrect data: string.\n");
                    givenString.setLength(0);
                    isErrorNotFound = false;
                }
            }
        }

        return array1;
    }

    public static String[] readArrayFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner, StringBuilder givenString) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 100;

        String[] array1;
        int i;
        int arrayLength;
        String arrayElement;

        array1 = null;
        i = 0;
        arrayLength = 0;
        arrayElement = "";

        System.out.print("The length of the separators should decrease with increasing order.\n");
        arrayLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write amount of separators: ", scanner);
        array1 = createStringArray(arrayLength);

        for (i = 0; i < arrayLength; i++) {
            System.out.printf("Write separator with index [%d] : ", i);
            arrayElement = scanner.nextLine();
            array1[i] = arrayElement;
        }

        System.out.print("Write the string of numbers between separators.\n");
        givenString.append(scanner.nextLine());

        return array1;
    }

    public static boolean writeStringIntoFile(String filePath, String answerString) {
        boolean isIncorrect;

        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            fileWriter.write(answerString + "\n");
            System.out.print("Answer written to file successfully.\n");
            fileWriter.close();
        } catch (IOException e) {
            System.out.print("The unexpected error is found.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static void writeStringIntoConsole(String answerString) {
        System.out.print(answerString + "\n");
    }

    public static boolean checkIsStringValid(String givenString) {
        int i;
        boolean isValid;

        i = 1;
        isValid = true;

        if (givenString.isEmpty())
            isValid = false;

        if (isValid) {
            if (!((((givenString.charAt(0) > '0') || (givenString.charAt(0) == '0')) && ((givenString.charAt(0) < '9') || (givenString.charAt(0) == '9')))
                    && (((givenString.charAt(givenString.length() - 1) > '0') || (givenString.charAt(givenString.length() - 1) == '0'))
                            && ((givenString.charAt(givenString.length() - 1) < '9') || (givenString.charAt(givenString.length() - 1) == '9')))))
                isValid = false;
        }

        if (isValid) {
            for (i = 0; i < givenString.length(); i++) {
                if ((i + 1 < givenString.length()) && ((givenString.charAt(i) == '+') && (givenString.charAt(i + 1) == '+')))
                    isValid = false;

                if (!Character.isDigit(givenString.charAt(i)) && givenString.charAt(i) != ',' && givenString.charAt(i) != '+')
                    isValid = false;
            }
        }

        return isValid;
    }

    public static String findSumFromString(String givenString) {
        double sumOfNumbers;
        double number;
        int i;
        int partLength;
        int partIndex;
        String stringPart;
        String answerString;
        boolean isFine;
        boolean isThereNumbers;
        boolean isNumberFull;

        sumOfNumbers = 0.0;
        number = 0.0;
        i = 0;
        partLength = 0;
        partIndex = 0;
        stringPart = "";
        isFine = true;
        isThereNumbers = false;
        isNumberFull = false;
        answerString = "";

        isFine = checkIsStringValid(givenString);

        if (isFine) {
            for (i = 0; i < givenString.length(); i++) {
                if ((givenString.charAt(i) == '+') || (i == givenString.length() - 1)) {
                    partLength = i - partIndex;

                    if (i == givenString.length() - 1)
                        partLength = i - partIndex + 1;

                    stringPart = givenString.substring(partIndex, partIndex + partLength);
                    partIndex = i + 1;
                    isNumberFull = true;
                }

                if (isNumberFull) {
                    stringPart = stringPart.replace(',', '.');

                    try {
                        number = Double.parseDouble(stringPart);
                        isThereNumbers = true;
                    } catch (NumberFormatException e) {
                        System.out.print("Error with StrToFloat transformation.\n");
                        isFine = false;
                    }
                }

                isNumberFull = false;

                sumOfNumbers = sumOfNumbers + number;
                number = 0;
                stringPart = "";
            }
        }

        if (!isFine)
            answerString = "The string contains invalid characters or their position is incorrect.";
        else
            answerString = givenString + "=" + String.format("%.1f", sumOfNumbers);

        if (!isThereNumbers)
            answerString = "There are no correct numbers in the line.";

        return answerString;
    }

    public static String findAnswerString(String[] arrayOfSeparators, String givenString) {
        String separator;
        String substring;
        String answerString;
        int i;
        int j;
        int specialLength;
        int lengthOfSeparator;

        separator = "";
        substring = "";
        answerString = "";
        i = 0;
        j = 0;
        specialLength = 0;
        lengthOfSeparator = 0;

        for (i = 0; i < arrayOfSeparators.length; i++) {
            separator = arrayOfSeparators[i];
            lengthOfSeparator = separator.length();
            specialLength = givenString.length() - lengthOfSeparator + 1;
            j = 0;

            while (j < specialLength) {
                substring = givenString.substring(j, j + lengthOfSeparator);

                if (substring.equals(separator)) {
                    givenString = givenString.substring(0, j) + "+"
                            + givenString.substring(j + lengthOfSeparator);
                    specialLength = givenString.length() - lengthOfSeparator + 1;
                }

                j++;
            }
        }

        answerString = findSumFromString(givenString);

        return answerString;
    }

    public static String[] readingStage(Scanner consoleScanner, StringBuilder givenString) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        String[] array1;
        boolean isFromFile;
        boolean isAllDone;
        boolean isOutput;
        String filePath;

        array1 = null;
        isFromFile = false;
        isOutput = false;
        isAllDone = true;
        filePath = "";

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isFromFile) {
            isAllDone = true;
            do {
                isAllDone = true;
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    array1 = readArrayFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader, givenString);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (array1 == null)
                    isAllDone = false;

            } while (!isAllDone);
        } else {
            array1 = readArrayFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner, givenString);
        }

        return array1;
    }

    public static void writingStage(String answerString, Scanner consoleScanner) {
        boolean isToFile;
        boolean isAllUndone;
        boolean isOutput;
        String filePath;

        isToFile = false;
        isOutput = true;
        filePath = "";

        isToFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isToFile) {
            do {
                filePath = assignMyFile(isOutput, consoleScanner);
                isAllUndone = writeStringIntoFile(filePath, answerString);
            } while (isAllUndone);
        } else
            writeStringIntoConsole(answerString);
    }

    public static void main(String[] args) {
        String[] arrayOfSeparators;
        StringBuilder givenString;
        String answerString;
        Scanner consoleScanner = new Scanner(System.in);

        arrayOfSeparators = null;
        givenString = new StringBuilder("");
        answerString = "";

        writePurpose();
        arrayOfSeparators = readingStage(consoleScanner, givenString);
        answerString = findAnswerString(arrayOfSeparators, givenString.toString());
        writingStage(answerString, consoleScanner);

        consoleScanner.close();
    }
}