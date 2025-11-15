import java.util.Scanner;

public class Lab2_2 {

    public static boolean discoverIsNumberPrime(int number) {

        int i;
        boolean isShouldNotStop;
        boolean isNumberPrime;

        i = 2;
        isShouldNotStop = true;
        isNumberPrime = false;

        for (i = 2; i < number; i++) {

            if ((number % i == 0) && (isShouldNotStop)) {
                isNumberPrime = false;
                isShouldNotStop = false;
            } else if (isShouldNotStop)
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

        isIncorrect = true;
        num = 0;

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

        int number;
        int counter;
        int primeNumber;
        boolean isMustNotStop;

        number = 2;
        counter = 0;
        primeNumber = 2;
        isMustNotStop = true;

        if (inputNum == 2)
            primeNumber = 3;
        else {
            while (isMustNotStop) {

                if (discoverIsNumberPrime(number))
                    counter++;

                if (counter == inputNum) {
                    isMustNotStop = false;
                    primeNumber = number;
                }

                number++;
            }
        }
        return primeNumber;
    }

    public static void getMersenneNumbers(int n) {

        final int MIN_ANSWER = 3;

        int i;
        int j;
        int answer;
        int mersenneNumber;
        int mersenneNumberP1;

        i = 1;
        j = 2;
        answer = MIN_ANSWER;
        mersenneNumber = 2;
        mersenneNumberP1 = 0;

        while (answer < n) {

            mersenneNumber = 2;
            mersenneNumberP1 = getPrimeNumber(i) + 1;

            for (j = 2; j < mersenneNumberP1; j++) 
                mersenneNumber = mersenneNumber * 2;
            
            mersenneNumber = mersenneNumber - 1;
            answer = mersenneNumber;

            if ((discoverIsNumberPrime(answer)) && (answer < n)) {
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
