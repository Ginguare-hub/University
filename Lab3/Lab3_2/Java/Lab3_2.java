import java.util.Scanner;
import java.util.HashSet;
import java.io.*;

public class Lab3_2 {

    public static void writePurpose() {
        System.out.print("The program generates two sets, the first of which contains all prime numbers from the given set, and the second of which contains all composite numbers.\n");
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
        File testFile;
        boolean checkInput;

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

    public static HashSet<Integer> readSetFromFile(final int MIN_NUMBER, final int MAX_NUMBER, String filePath, BufferedReader fileReader) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 10000;

        HashSet<Integer> mySet;
        int i;
        int mySetLength;
        int setElement;
        boolean isFine;

        mySet = new HashSet<Integer>();
        i = 0;
        mySetLength = 0;
        setElement = 0;
        isFine = true;

        try {
            mySetLength = Integer.parseInt(fileReader.readLine());
        } catch (NumberFormatException e) {
            System.out.print("Error, NumberFormatException.\n");
            isFine = false;
        } catch (IOException e) {
            System.out.print("Error, IOException.\n");
            isFine = false;
        }

        if (isFine) {
            if ((mySetLength < MIN_LENGTH) || (mySetLength > MAX_LENGTH)) {
                System.out.printf("Incorrect set length, the number must fit the range [%d,%d].\n", MIN_LENGTH, MAX_LENGTH);
                mySet.clear();
                isFine = false;
            }
        }

        if (isFine) {
            for (i = 0; i < mySetLength; i++) {
                try {
                    setElement = Integer.parseInt(fileReader.readLine());
                } catch (NumberFormatException e) {
                    mySet.clear();
                    isFine = false;
                    System.out.print("Incorrect numeric data: set element.\n");
                } catch (IOException e) {
                    mySet.clear();
                    isFine = false;
                    System.out.print("Error, IOException.\n");
                }

                if (isFine)
                    mySet.add(setElement);
            }
        }

        if (mySet.isEmpty())
            System.out.print("Error, incorrect set data.\n");

        return mySet;
    }

    public static HashSet<Integer> readSetFromConsole(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 1000;

        HashSet<Integer> set1;
        int i;
        int setLength;
        int setElement;

        set1 = new HashSet<Integer>();
        i = 0;
        setLength = 0;
        setElement = 0;

        setLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write set length: ", scanner);

        for (i = 0; i < setLength; i++) {
            System.out.print("Write element of set: ");
            setElement = readAndVerify(MIN_NUMBER, MAX_NUMBER, "", scanner);
            set1.add(setElement);
        }

        return set1;
    }

    public static String askTheFilePath(Scanner scanner) {
        String filePath;
        
        filePath = "";
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

    public static boolean writeSetIntoFile(String filePath, HashSet<Integer> setOfPrime, HashSet<Integer> setOfNonPrime) {
        boolean isIncorrect;

        isIncorrect = false;

        try (FileWriter fileWriter = new FileWriter(filePath)) {
            if (setOfPrime.isEmpty())
                fileWriter.write("There is no prime numbers in given set.\n");
            else {
                fileWriter.write("The result elements of set with prime numbers is: \n");
                for (int element: setOfPrime)
                    fileWriter.write(element + " ");
            }

            fileWriter.write("\n");

            if (setOfNonPrime.isEmpty())
                fileWriter.write("There is no non-prime numbers in given set.\n");
            else {
                fileWriter.write("The result elements of set with non-prime numbers is: \n");
                for (int element: setOfNonPrime)
                    fileWriter.write(element + " ");
            }

            fileWriter.close();
        } catch (IOException e) {
            System.out.print("The unexpected error is found.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static void writeSetIntoConsole(HashSet<Integer> setOfPrime, HashSet<Integer> setOfNonPrime) {

        if (setOfPrime.isEmpty())
            System.out.print("There is no prime numbers in given set.\n");
        else {
            System.out.print("The result elements of set with prime numbers is: \n");
            for (int element: setOfPrime)
                System.out.print(element + " ");
        }

        System.out.print("\n");

        if (setOfNonPrime.isEmpty())
            System.out.print("There is no non-prime numbers in given set.\n");
        else {
            System.out.print("The result elements of set with non-prime numbers is: \n");
            for (int element: setOfNonPrime)
                System.out.print(element + " ");
        }

        System.out.print("\n");
    }

    public static boolean discoverIsNumberPrime(int number) {
        int i;
        int numberP1;
        boolean isShouldNotStop;
        boolean isPrime;

        i = 2;
        numberP1 = 0;
        isShouldNotStop = true;
        isPrime = false;

        if (number < 2)
            isPrime = false;
        else {
            numberP1 = number - 1;

            for (i = 2; i <= numberP1; i++) {
                if ((number % i == 0) && (isShouldNotStop)) {
                    isPrime = false;
                    isShouldNotStop = false;
                } else 
                    if (isShouldNotStop)
                        isPrime = true;
            }

            if (number == 2)
                isPrime = true;
        }

        return isPrime;
    }

    public static void divideSet(HashSet<Integer> givenSet, HashSet<Integer> setOfPrime, HashSet<Integer> setOfNonPrime) {
        int setElement;

        setElement = 0;

        for (int element: givenSet) {
            setElement = element;
            
            if (discoverIsNumberPrime(setElement))
                setOfPrime.add(setElement);
            else
                setOfNonPrime.add(setElement);
        }
    }

    public static HashSet<Integer> readingStage(Scanner consoleScanner) {
        final int MIN_NUMBER = 0;
        final int MAX_NUMBER = 100000;

        HashSet<Integer> set1;
        String filePath;
        boolean isAllDone;
        boolean isFromFile;
        boolean isOutput;

        set1 = new HashSet<Integer>();
        isAllDone = true;
        isOutput = false;
        isFromFile = false;
        filePath = "";

        isFromFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isFromFile) {
            isAllDone = true;
            do {
                filePath = assignMyFile(isOutput, consoleScanner);

                try (BufferedReader bufReader = new BufferedReader(new FileReader(filePath))) {
                    set1 = readSetFromFile(MIN_NUMBER, MAX_NUMBER, filePath, bufReader);
                    bufReader.close();
                } catch (IOException e) {
                    System.out.print("Error, something went wrong.\n");
                }

                if (set1.isEmpty())
                    isAllDone = false;
                else
                    isAllDone = true;

            } while (!isAllDone);
        } else
            set1 = readSetFromConsole(MIN_NUMBER, MAX_NUMBER, consoleScanner);

        return set1;
    }

    public static void writingStage(HashSet<Integer> setOfPrime, HashSet<Integer> setOfNonPrime, Scanner consoleScanner) {
        String filePath;
        boolean isToFile;
        boolean isAllUndone;
        boolean isOutput;

        isToFile = false;
        isAllUndone = false;
        isOutput = true;
        filePath = "";

        isToFile = workWithConsoleOrFile(isOutput, consoleScanner);

        if (isToFile) {
            do {
                filePath = assignMyFile(isOutput, consoleScanner);
                isAllUndone = writeSetIntoFile(filePath, setOfPrime, setOfNonPrime);
            } while (isAllUndone);
        } else
            writeSetIntoConsole(setOfPrime, setOfNonPrime);
    }

    public static void main(String[] args) {
        HashSet<Integer> givenSet;
        HashSet<Integer> setOfPrime;
        HashSet<Integer> setOfNonPrime;
        Scanner consoleScanner = new Scanner(System.in);

        givenSet = new HashSet<Integer>();
        setOfNonPrime = new HashSet<Integer>();
        setOfPrime = new HashSet<Integer>();

        writePurpose();
        givenSet = readingStage(consoleScanner);
        divideSet(givenSet, setOfPrime, setOfNonPrime);
        writingStage(setOfPrime, setOfNonPrime, consoleScanner);

        consoleScanner.close();
    }
}