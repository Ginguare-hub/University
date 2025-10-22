import java.util.Scanner;

public class Lab2_1 {

    public static void main(String[] args) {

        final int MAX_LENGTH = 20;
        final int MIN_LENGTH = 1;
        final double MAX_NUM =  12345.0;
        final double MIN_NUM = -12345.0;

        int length, i;
        double num, arithmMean, minDiff, currDiff, sumOfNums;
        boolean isIncorrect;
        
        double[] arr;

        length = 1;
        i = 0;
        num = 0;
        arithmMean = 0;
        minDiff = 0;
        currDiff = 0;
        sumOfNums = 0;
        isIncorrect = false;

        Scanner scan = new Scanner(System.in);

        System.out.print("Programm finds the element(s) in the list, that most fits with the arithmetic mean of the series.\n");

        do {

            isIncorrect = false;
            System.out.print("Enter the number of numbers in the list: ");

            try {
                length = Integer.parseInt(scan.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.print("Incorrect input, try again.\n");
            }
 
            if (!isIncorrect && (length < MIN_LENGTH || length > MAX_LENGTH)) {
                isIncorrect = true;
                System.out.printf("The number must fit the range [%d,%d].\n", MIN_LENGTH, MAX_LENGTH);
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
                    System.out.printf("The number must fit the range [%d,%d].\n", MIN_NUM, MAX_NUM);
                }

            } while (isIncorrect);

            arr[i] = num;
            sumOfNums = sumOfNums + num;
        } 

        scan.close();

        arithmMean = sumOfNums / length;
        minDiff = Math.abs(arithmMean - arr[0]);

        for (i = 0; i < length; i++) {
            currDiff = Math.abs(arithmMean - arr[i]);
            if (minDiff > currDiff) {
                minDiff = currDiff;
            }
        }

        System.out.print("The element(s) ");

        for (i = 0; i < length; i++) {
            currDiff = Math.abs(arithmMean - arr[i]);
            if (minDiff == currDiff) {
                System.out.printf("%d ", i + 1);
            }
        }

        System.out.print("in the list is the number(s), that most fits with the arithmetic mean of the series.\n");
    }
}