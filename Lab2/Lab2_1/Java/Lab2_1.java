import java.util.Scanner;

public class Lab2_1 {

    public static void main(String[] args) {

        //type tArr = double;

        final int MAX_LENGTH = 20;
        final int MIN_LENGTH = 1;
        final double MAX_NUM = 12345.0;
        final double MIN_NUM = -12345.0;

        double[] arr;

        int length, i, answer;
        double num, arithmMean, minDiff, absDiff, sumOfNums;
        boolean isIncorrect;

        //initialization
        length = 1;
        i = 0;
        answer = 1;
        num = 0;
        arithmMean = 0;
        minDiff = 0;
        absDiff = 0;
        sumOfNums = 0;
        isIncorrect = false;

        Scanner scan = new Scanner(System.in);

        do {

            isIncorrect = false;
            System.out.print("Enter the number of numbers in the list:\n");

            try {
                length = Integer.parseInt(scan.nextLine());

            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.print("Incorrect input, try again.\n");

            }
 
            if (!isIncorrect && (length < MIN_LENGTH || length > MAX_LENGTH)) {
                isIncorrect = true;
                System.out.printf("The number must fit the range [%d,%d]\n", MIN_LENGTH, MAX_LENGTH);

            }

        } while (isIncorrect);

        arr = new double[length];

        for (i = 0; i < length; i++) {

            System.out.printf("Element %d = ", i + 1);
            
            do {
                isIncorrect = false;

                try {
                    num = Integer.parseInt(scan.nextLine());

                } catch (NumberFormatException e) {
                    isIncorrect = true;
                    System.out.print("Incorrect input, try again.\n");

                }
 
                if (!isIncorrect && (num < MIN_NUM || num > MAX_NUM)) {
                    isIncorrect = true;
                    System.out.printf("The number must fit the range [%d,%d]\n", MIN_NUM, MAX_NUM);

                }

            } while (isIncorrect);

            arr[i] = num;
            sumOfNums = sumOfNums + num;
        } 

        scan.close();

        arithmMean = sumOfNums / length;
        minDiff = Math.abs(arithmMean - arr[0]);
        absDiff = arr[0];

        for (i = 0; i < length; i++){
            absDiff = Math.abs(arithmMean - arr[i]);

            if (minDiff > absDiff) {
                minDiff = absDiff;
                answer = i + 1;
            }
        }

        System.out.print(answer);
    }
}