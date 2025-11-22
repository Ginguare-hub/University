import java.util.Scanner;

public class Lab2_5 {

    public static int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER, String str, Scanner scanner) {
        boolean isIncorrect;
        int number;

        isIncorrect = true;
        number = 0;

        do {
            System.out.print(str + "\n");
            System.out.print("> ");
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

    public static int[] createArray(Scanner scanner) {
        final int MIN_LENGTH = 1;
        final int MAX_LENGTH = 30;
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int[] myArray;
        int i;
        int arrLength;
        int number;
        boolean isIncorrect;

        i = 0;
        number = 0;
        isIncorrect = false;
        arrLength = readAndVerify(MIN_LENGTH, MAX_LENGTH, "Write length of array: ", scanner);

        myArray = new int[arrLength];

        for (i = 0; i < arrLength; i++) {
            do {
                System.out.printf("Element of array[%d] = ", i);
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

            myArray[i] = number;
        }

        return myArray;
    }

    public static void writeArray(int[] myArray, int arrLength) {
        int i;
        i = 0;
        for (i = 0; i < arrLength; i++)
            System.out.println(myArray[i]);
    }

    public static int[] changeArray(int[] myArray, int arrLength) {
        final int LIMIT = 2;

        int i;
        int j;
        int k;

        i = 0;
        j = 0;
        k = 0;

        for (i = 0; i < LIMIT; i++)
            if (i == 0) {
                for (j = 0; j < arrLength; j++)
                    for (k = 0; k < arrLength; k++)
                        if ((myArray[k] == 0) && !(myArray[j] == 0) && (j < k)) {
                            myArray[k] = myArray[k] + myArray[j];
                            myArray[j] = myArray[k] - myArray[j];
                            myArray[k] = myArray[k] - myArray[j];
                        }
            } else
                for (j = 0; j < arrLength; j++)
                    for (k = 0; k < arrLength; k++)
                        if ((myArray[k] < 0) && !(myArray[j] == 0) && !(myArray[j] < 0) && (j < k)) {
                            myArray[k] = myArray[k] + myArray[j];
                            myArray[j] = myArray[k] - myArray[j];
                            myArray[k] = myArray[k] - myArray[j];
                        }
        return myArray;
    }

    public static void main(String[] args) {
        int arrLength;
        int[] arrayA;
        Scanner scanner = new Scanner(System.in);

        arrLength = 0;
        arrayA = createArray(scanner);
        arrLength = arrayA.length;
        arrayA = changeArray(arrayA, arrLength);
        writeArray(arrayA, arrLength);

        scanner.close();
    }
}
