import java.util.Scanner;
import java.io.*;

public class Lab2_6 {

    public static void writePurpose() {
        System.out.print("A two-dimensional matrix A of order n is given. The progtam arranges the elements of the rows with even numbers of the matrix in descending order.\n");
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

    public static boolean checkMyFile(String filePath) {
        boolean checkInput;
        File testFile;

        checkInput = false;
        testFile = new File(filePath);

        if (!testFile.exists())
            System.out.print("Error, file with path <" + filePath + "> is not exists.\n");
        else if (!isFileText(filePath))
            System.out.print("Error, filename is not .txt\n");
        else if (!testFile.canWrite())
            System.out.print("Error, no access to write into the file.\n");
        else {
            checkInput = true;
            System.out.print("Assigning is completed successfully.\n");
        }
        return checkInput;
    }

    public static boolean workWithConsoleOrFile(Scanner scanner) {
        int number;
        boolean isFromFile;

        number = 0;
        isFromFile = false;

        System.out.print("If data is output to the console write 0, if from file write 1.\n");
        number = readAndVerify(0, 1, "> ", scanner);

        if (number == 1)
            isFromFile = true;
        else
            isFromFile = false;

        if (isFromFile)
            System.out.print("The data is output to a file.\n");
        else 
            System.out.print("The data is output to the console.\n");


        return isFromFile;
    }

    public static String askTheFilePath(Scanner scanner) {
        String filePath;
        System.out.print("Write the existing file path: ");
        filePath = scanner.nextLine();
        return filePath;
    }

    public static String assignMyFile(Scanner scanner) {
        String filePath;
        boolean isIncorrect;

        filePath = "";
        isIncorrect = false;

        do {
            filePath = askTheFilePath(scanner);
            isIncorrect = !checkMyFile(filePath);
        } while (isIncorrect);

        return filePath;
    }

    public static int sumOfProperDivisors(int number) {
        int i;
        int sumOfDivisors;
        int numberDivTwo;

        i = 0;
        sumOfDivisors = 0;
        numberDivTwo = number / 2 + 1;

        for (i = 1; i < numberDivTwo; i++)
            if (number % i == 0)
                sumOfDivisors = sumOfDivisors + i;

        return sumOfDivisors;
    }

    public static void findAnbicableNumbersConsole() {
        final int MY_LIMIT = 100001;

        int sumOfDivisors;
        int i;
        int j;

        sumOfDivisors = 0;
        i = 0;
        j = 1;

        for (i = 1; i < MY_LIMIT; i++) {
            sumOfDivisors = sumOfProperDivisors(i);
            if ((i < sumOfDivisors) && (i == sumOfProperDivisors(sumOfDivisors))) {
                System.out.printf("%d.  %d And %d\n", j, i, sumOfDivisors);
                j++;
            }
        }
    }

    public static boolean findAnbicableNumbersFile(String filePath) {
        final int MY_LIMIT = 100001;
        
        int sumOfDivisors;
        int i;
        int j;
        boolean isIncorrect;
        
        sumOfDivisors = 0;
        i = 0;
        j = 1;
        isIncorrect = false;
        
        // for (i = 1; i < MY_LIMIT; i++) {
        //     sumOfDivisors = sumOfProperDivisors(i);
        //     if ((i < sumOfDivisors) && (i == sumOfProperDivisors(sumOfDivisors))) {
        //         System.out.printf("%d.  %d And %d\n", j, i, sumOfDivisors);
        //         j++;
        //     }
        // }
        
        //----------------
    
        try (FileWriter fileWriter = new FileWriter(filePath)) {
    
            fileWriter.write("Ambicable numbers lower than 100000: \n");

            for (i = 1; i < MY_LIMIT; i++) {
                sumOfDivisors = sumOfProperDivisors(i);
                if ((i < sumOfDivisors) && (i == sumOfProperDivisors(sumOfDivisors))) {
                    fileWriter.write(j + ".  " + i + " And " + sumOfDivisors + "\n");
                    j++;
                }
            }
            fileWriter.close();

        } catch (IOException e) {
            System.out.print("Error with file write.\n");
            isIncorrect = true;
        }

        return isIncorrect;
    }

    public static void writingStage(Scanner consoleScanner) {
        boolean isToFile;
        boolean isAllUndone;
        String filePath;

        isToFile = false;
        isAllUndone = false;
        filePath = "";

        isToFile = workWithConsoleOrFile(consoleScanner);

        if (isToFile) {
            do {
                filePath = assignMyFile(consoleScanner);
                System.out.print("Do not open the file before messege about algorithm is done is not arrived.\n");
                isAllUndone = findAnbicableNumbersFile(filePath);
                System.out.print("Program is completed. File can be opened.\n");
            } while (isAllUndone);
        } 
        else {
            findAnbicableNumbersConsole();
            System.out.print("Program is completed.\n");
        }
    }

    public static void main(String[] args) {
        Scanner consoleScanner = new Scanner(System.in);

        writePurpose();
        writingStage(consoleScanner);

        consoleScanner.close();
    }

}
