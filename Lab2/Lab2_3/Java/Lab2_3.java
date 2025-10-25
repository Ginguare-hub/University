import java.util.Scanner;

public class Lab2_3 {

    public static int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER, String str) {

        boolean isIncorrect;
        int num;

        num = 0;
        isIncorrect = true;

        Scanner scnr = new Scanner(System.in);

        do {

            System.out.print(str);
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
            }

        } while (isIncorrect);

        scnr.close();

        return num;
    }

    public static int[][] writeInMatrix(int n) {
        final int MIN_NUMBER = -100000;
        final int MAX_NUMBER = 100000;

        int i;
        int j;
        //int k;
        int[][] arrayA;

        i = 0;
        j = 0;
        //k = 0;

        arrayA = new int[n][n];
        // for (k = 0; k < n; k++)
        //     arrayA[k] = new int[n];

        // cout << sizeof(arrayA);

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                System.out.printf("Write element [%d][%d] of matrix: ", i, j);
                arrayA[i][j] = readAndVerify(MIN_NUMBER, MAX_NUMBER, "Write element: ");
            }
        }

        return arrayA;
    }

    public static void writeOutMatrix(int[][] arrayA) {
        int i;
        int j;
        int n;

        i = 0;
        j = 0;
        n = arrayA.length;

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                System.out.print(arrayA[i][j] + " ");
            }
            System.out.print("\n");
        }
    }

    public static int[][] sortConditional(int[][] arrayA) { // Попробовать не возвращать знавение а просто ссылкой менять массив

        int i;
        int j;
        int k;
        int limiter;
        int boubleSortLimiter;
        int arrLength;

        i = 0;
        j = 0;
        k = 1;
        limiter = arrayA.length - 1;
        boubleSortLimiter = arrayA.length * (arrayA.length / 2);
        arrLength = arrayA.length;

        for (k = 1; k < (boubleSortLimiter + 1); k++) {

            limiter = arrLength - 1;

            for (i = 0; i < arrLength; i++) {

                if (i % 2 == 1) {
                    if (i == 2 * (arrLength / 2))
                        limiter = (arrLength - 1) - 1;

                    for (j = 0; j < limiter + 1; j++) {

                        if ((j + 1 < arrLength - 1) || (j + 1 == arrLength - 1)) {
                            if (arrayA[i][j] < arrayA[i][j + 1]) {
                                arrayA[i][j] = arrayA[i][j] + arrayA[i][j + 1];
                                arrayA[i][j + 1] = arrayA[i][j] - arrayA[i][j + 1];
                                arrayA[i][j] = arrayA[i][j] - arrayA[i][j + 1];
                            }
                        } else if ((i + 2 < arrLength - 1) || (i + 2 == arrLength - 1)) {
                            if (arrayA[i][j] < arrayA[i + 2][0]) {
                                arrayA[i][j] = arrayA[i][j] + arrayA[i + 2][0];
                                arrayA[i + 2][0] = arrayA[i][j] - arrayA[i + 2][0];
                                arrayA[i][j] = arrayA[i][j] - arrayA[i + 2][0];
                            }
                        }
                    }
                }
            }
        }

        return arrayA;
    }

    public static void main(String[] args) {

        final int MIN_ORDER = 1;
        final int MAX_ORDER = 10;

        int n;
        int[][] a;

        n = readAndVerify(MIN_ORDER, MAX_ORDER, "Write the order of the matrix: ");

        a = writeInMatrix(n);

        a = sortConditional(a);

        writeOutMatrix(a);

    }
}
