import java.util.Scanner;

public class Lab2_2 {

    public static boolean discoverIsNumberPrime(int number) {

        int i;
        boolean isShouldStop, isNumberPrime;

        i = 2;
        isShouldStop = false;
        isNumberPrime = false;

        for (i = 2; i < number; i++) {

            if ((number % i == 0) && (!isShouldStop)) {
                isNumberPrime = false;
                isShouldStop = true;
            } else if (!isShouldStop)
                isNumberPrime = true;
        }

        if (number == 2)
            isNumberPrime = true;

        return isNumberPrime;
    }

    public static int readAndVerify(final int MIN_NUMBER, final int MAX_NUMBER, Scanner scanner) {

        final int LOWEST_MERS = 3;

        boolean isIncorrect;
        int num;

        num = 0;
        isIncorrect = true;

        do {

            System.out.print("Enter the number N: ");
            isIncorrect = false;

            try {
                num = Integer.parseInt(scanner.nextLine());
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

        return num;
    }

    public static int getPrimeNumber(int inputNum) {

        int number, counter, primeNumber;
        boolean isMustStop;

        number = 2;
        counter = 0;
        primeNumber = 2;
        isMustStop = false;

        if (inputNum == 2)
            primeNumber = 3;
        else {
            while (!isMustStop) {
                if (discoverIsNumberPrime(number))
                    counter++;

                if (counter == inputNum) {
                    isMustStop = true;
                    primeNumber = number;
                }

                number++;
            }
        }
        return primeNumber;
    }

    public static void getMersenneNumbers(int n) {

        final int MIN_ANSWER = 3;

        int i, j, answer, mersenneNumber;

        i = 1;
        j = 2;
        answer = MIN_ANSWER;
        mersenneNumber = 2;

        while (answer < n) {

            mersenneNumber = 2;

            for (j = 2; j < (getPrimeNumber(i) + 1); j++) 
                mersenneNumber = mersenneNumber * 2;
            

            mersenneNumber = mersenneNumber - 1;
            answer = mersenneNumber;

            if ((discoverIsNumberPrime(answer) == true) && (answer < n)) {
                if (i == 1)
                    System.out.println("The answers is: ");
                System.out.println(answer);
            }

            i++;
        }
    }

    public static void main(String[] args) {

        final int MIN_N = 4;
        final int MAX_N = 600000;

        int n;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Programm is finding all numbers lower then N that is prime Mersenne numbers.");
        
        n = readAndVerify(MIN_N, MAX_N, scanner);

        scanner.close();

        getMersenneNumbers(n);

    }
}
