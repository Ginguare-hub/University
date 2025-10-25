import java.util.Scanner;

public class Lab2_3 {

    int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER, String str) {

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

    public static void main(String[] args) {

    }
}
