import java.util.Scanner;

public class Lab2_6 {

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

    public static void findAnbicableNumbers() {
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

    public static void main(String[] args) {
        findAnbicableNumbers();
    }

}
