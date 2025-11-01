import java.util.Scanner;

public class Test {

    public static int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER) {

        final int LOWEST_MERS = 3;

        boolean isIncorrect;
        int num;

        num = 0;
        isIncorrect = true;

        Scanner scnr = new Scanner(System.in);

        do {

            System.out.print("Enter the number N: ");
            isIncorrect = false;

            try {
                num = Integer.parseInt(scnr.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.println("Incorrect input, try again.");
            }

            if (!isIncorrect && (num < MIN_NUMBER || num > MAX_NUMBER)) {
                isIncorrect = true;
                System.out.printf("The number must fit the range [%d,%d].\n", MIN_NUMBER, MAX_NUMBER);
                if (num < (LOWEST_MERS + 1))
                    System.out.println("There are no prime Mersenne numbers, lower then 3.");
            }

        } while (isIncorrect);

        scnr.close();

        return num;
    }



    public static int[][] writeInMatrix(int n) {
        int[][] arrayA;
        int i;
        int j;

        i = 0;
        j = 0;

        arrayA = new int[n][n];

        Scanner scanner = new Scanner(System.in);

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) { 
                arrayA[i][j] = Integer.parseInt(scanner.nextLine());
            }
        }


        scanner.close();
        return arrayA;
    }

    public static void main(String[] args) {

        int[][] myArray;

        myArray = writeInMatrix(readAndVerify(0, 10));
        
    }
}
