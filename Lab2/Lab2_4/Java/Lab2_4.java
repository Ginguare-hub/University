import java.util.Scanner;
import java.io.*;

public class Lab2_4 {

    public static void writePurpose() {
        System.out.print("Convert a number from base (2, 8, 10) to base-16 numeral system.\n");
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

    public static boolean isFileNotEmpty(String filePath) {
        boolean isNotEmpty;
        File testFile;

        isNotEmpty = false;
        testFile = new File(filePath);

        if (testFile.exists() && testFile.length() > 0)
            isNotEmpty = true;

        return isNotEmpty;
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
        else if (!isFileOutput && !isFileNotEmpty(filePath))
            System.out.print("Error, file is empty.\n");
        else {
            checkInput = true;
            System.out.print("Assigning is completed successfully.\n");
        }
        return checkInput;
    }

    public static boolean checkIsNumberValid(long number, final long BASE) {
        boolean isValid;
        long tempNumber;

        isValid = true;
        tempNumber = number;

        while ((tempNumber != 0) && isValid) {
            if ((tempNumber % 10 > BASE) || (tempNumber % 10 == BASE))
                isValid = false;
            tempNumber = tempNumber / 10;
        }

        if (number < 0)
            isValid = false;

        return isValid;
    }

    public static long readAndVerify(final long MIN_NUMBER, final long MAX_NUMBER, String str, Scanner scanner) {
        boolean isIncorrect;
        long number;

        number = 0;
        isIncorrect = true;

        do {
            System.out.print(str);
            isIncorrect = false;

            try {
                number = Long.parseLong(scanner.nextLine());
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

    public static int readAndVerifyBase(String str, Scanner scanner) {
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
            if (!isIncorrect && (number != 2) && (number != 8) && (number != 10)) {
                isIncorrect = true;
                System.out.println("The number must be equals to 2, 8 or 10.");
            }

        } while (isIncorrect);
        return number;
    }

    public static long readAndVerifyForConversion(final long MIN_NUMBER, final long BASE, String str, Scanner scanner) {
        final long MAX_BINARY = 1111111111111111111L;
        final long MAX_OCTAL = 777777;
        final long MAX_DECIMAL = 524286;

        boolean isIncorrect;
        long number;
        long localMaxNumber;

        number = 0;
        localMaxNumber = 0;
        isIncorrect = true;

        if (BASE == 2)
            localMaxNumber = MAX_BINARY;
        else if (BASE == 8)
            localMaxNumber = MAX_OCTAL;
        else
            localMaxNumber = MAX_DECIMAL;

        do {
            isIncorrect = false;

            number = readAndVerify(0, localMaxNumber, str, scanner);

            if (!checkIsNumberValid(number, BASE)) {
                System.out.printf("Every digit must not be equal or higher than %d.\n", BASE);
                isIncorrect = true;
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

        number = (int) readAndVerify(0, 1, "> ", scanner);

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

    public static long getNumberOfDigits(long number) {
        long answer;
        answer = 0;
        if (number == 0)
            answer = 1;
        else
            while (number != 0) {
                number = number / 10;
                answer = answer + 1;
            }

        return answer;
    }

    public static long powerOfTwo(int power) {
        long i;
        long answer;

        i = 0;
        answer = 1;

        for (i = 1; i <= power; i++)
            answer = answer * 2;

        return answer;
    }

    public static char tetradeToHexadecimal(int tetrade) {
        char[] cArray;
        long answer;
        int i;

        answer = 0;
        i = 0;

        cArray = new char[] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

        while (tetrade != 0) {
            answer = answer + (tetrade % 10) * powerOfTwo(i);
            tetrade = tetrade / 10;
            i++;
        }

        return cArray[(int) answer];
    }

    public static char[] binaryToHexadecimal(long bNumber) {
        final int H_NUMBER = 10000;
        final int BASE_B = 2;

        int counter;
        long tetrade;
        long aLength;
        char[] answerArray;

        counter = 0;
        tetrade = 0;
        aLength = 0;
        answerArray = null;

        aLength = 0;

        if (checkIsNumberValid(bNumber, BASE_B)) {

            aLength = getNumberOfDigits(bNumber) / 4;

            if ((getNumberOfDigits(bNumber) % 4) > 0)
                aLength = aLength + 1;

            counter = 0;

            answerArray = new char[(int) aLength];

            if (bNumber != 0)
                while (bNumber != 0) {
                    tetrade = bNumber % H_NUMBER;
                    bNumber = bNumber / H_NUMBER;
                    answerArray[counter] = tetradeToHexadecimal((int) tetrade);

                    counter = counter + 1;
                }
            else if (bNumber == 0)
                answerArray[(int) counter] = tetradeToHexadecimal(0);
        } else
            answerArray = null;

        return answerArray;
    }

    public static long octalToBinary(long oNumber) {
        final int BASE_O = 8;
        final int O_NUMBER = 1000;

        long digit;
        long n;
        long answer;
        long[] transformArray;

        digit = 0;
        answer = 0;
        n = 1;

        transformArray = new long[] { 0, 1, 10, 11, 100, 101, 110, 111 };

        if (checkIsNumberValid(oNumber, BASE_O)) {

            while (oNumber != 0) {
                digit = oNumber % 10;
                oNumber = oNumber / 10;
                answer = answer + n * transformArray[(int) digit];
                n = n * O_NUMBER;
            }

        }

        return answer;
    }

    public static long decimalToBinary(long dNumber) {
        final int BASE_B = 2;
        final int ARRAY_LENGTH = 64;

        long[] reverseAnswerArray;
        int i;
        int highArray;
        long answer;

        i = 0;
        answer = 0;

        reverseAnswerArray = new long[ARRAY_LENGTH];

        while (dNumber > 0) {
            reverseAnswerArray[i] = dNumber % BASE_B;
            dNumber = dNumber / BASE_B;
            i++;
        }

        highArray = ARRAY_LENGTH - 1;

        for (i = highArray; i >= 0; i--)
            answer = answer * 10 + reverseAnswerArray[i];

        return answer;
    }

    public static void reverseArray(char[] arrayA) {
        int i;
        int halfHigh;
        char temp;

        i = 0;
        halfHigh = arrayA.length / 2;

        for (i = 0; i < halfHigh; i++) {
            temp = arrayA[i];
            arrayA[i] = arrayA[arrayA.length - 1 - i];
            arrayA[arrayA.length - 1 - i] = temp;
        }
    }

    public static void writeOutArray(char[] arrayA) {
        int i;

        i = 0;

        System.out.print("The answer is: ");

        for (i = 0; i < arrayA.length; i++)
            System.out.print(arrayA[i]);

        System.out.print("\n");
    }

    public static char[] octalToHexadecimal(long number) {
        long bNumber;
        char[] answerArray;

        bNumber = 0;
        answerArray = null;

        bNumber = octalToBinary(number);
        answerArray = binaryToHexadecimal(bNumber);

        return answerArray;
    }

    public static char[] decimalToHexadecimal(long number) {
        long bNumber;
        char[] answerArray;

        bNumber = 0;
        answerArray = null;

        bNumber = decimalToBinary(number);
        answerArray = binaryToHexadecimal(bNumber);

        return answerArray;
    }

    public static char[] convertNumber(long number, long base) {
        char[] answerArray;

        answerArray = null;

        if (base == 2)
            answerArray = binaryToHexadecimal(number);
        else if (base == 8)
            answerArray = octalToHexadecimal(number);
        else
            answerArray = decimalToHexadecimal(number);

        return answerArray;
    }

    public static int[] readBaseAndNumberFromFile(String filePath, BufferedReader fileReader) {
        final int ARRAY_LENGTH = 2;
        int[] shortArray;
        String line;
        String[] elements;

        shortArray = null;
        line = "";

        shortArray = new int[ARRAY_LENGTH];

        try {
            line = fileReader.readLine();
            elements = line.split(" ");

            shortArray[0] = Integer.parseInt(elements[0]);
            shortArray[1] = Integer.parseInt(elements[1]);
        } catch (NumberFormatException e) {
            System.out.print("Incorrect numeric data: matrix element.\n");
            shortArray = null;
        } catch (IOException e) {
            System.out.print("Error, IOException.\n");
            shortArray = null;
        }

        if (shortArray != null && ((shortArray[0] != 2) && (shortArray[0] != 8) && (shortArray[0] != 10))) {
            System.out.println("The base must be equals to 2, 8 or 10.");
            shortArray = null;
        }

        if ((shortArray != null) && (!checkIsNumberValid(shortArray[1], (int) shortArray[0]))) {
            System.out.println("Error, incorrect matrix data.");
            shortArray = null;
        }

        return shortArray;
    }

    public static char[] readingStage(Scanner consoleScanner) {
        boolean isFromFile;
        boolean isOutput;
        boolean isAllDone;
        long base;
        long numberBefConv;
        int[] dataArray;
        char[] answerArray;
        String filePath;

        isOutput = false;
        isAllDone = true;
        base = 0;
        numberBefConv = 0;
        dataArray = null;
        answerArray = null;
        filePath = "";

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isFromFile) {

            do {
                isAllDone = true;
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    dataArray = readBaseAndNumberFromFile(filePath, bufReader);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (dataArray != null) {
                    base = dataArray[0];
                    numberBefConv = dataArray[1];
                    answerArray = convertNumber(numberBefConv, base);
                }

                if (dataArray == null) {
                    System.out.println("Something went wrong, try again.");
                    isAllDone = false;
                }

            } while (!isAllDone);

        } else {

            base = readAndVerifyBase("Write the base of number: ", consoleScanner);
            numberBefConv = readAndVerifyForConversion(0, base, "Write number that will be converted: ", consoleScanner);
            answerArray = convertNumber(numberBefConv, base);
        }

        return answerArray;
    }

    public static boolean writeNumberIntoFile(String filePath, char[] answerArray) {   
        int i;
        boolean isIncorrect;

        i = 0;
        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {

            fileWriter.write("The answer is: ");
            reverseArray(answerArray);

            for (i = 0; i < answerArray.length; i++)
                fileWriter.write(answerArray[i]);

            System.out.print("Number written to file successfully.\n");
            fileWriter.close();

        } catch (IOException e) {
            System.out.print("The unexpected error is found.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static void writingStage(char[] answerArray, Scanner consoleScanner) {
        boolean isToFile;
        boolean isOutput;
        boolean isAllUndone; 
        String filePath;

        isToFile = false;
        isOutput = true;
        isAllUndone = false;
        filePath = "";

        isToFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (answerArray == null) 
            System.out.println("Error, something went wrong when reading numeric data.");
        else
            if (isToFile) {
                do {
                    filePath = assignMyFile(isOutput, consoleScanner);
                    isAllUndone = writeNumberIntoFile(filePath, answerArray);
                } while (isAllUndone);
            } else {
                reverseArray(answerArray);
                writeOutArray(answerArray);
            }
    }

    public static void main(String[] args) {
        char[] myArray;
        Scanner consoleScanner = new Scanner(System.in);

        myArray = null;

        writePurpose();
        myArray = readingStage(consoleScanner);
        writingStage(myArray, consoleScanner);

        consoleScanner.close();
    }
}