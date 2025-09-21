import java.util.Scanner;

public class Lab1_2 {

    public static void main(String[] args) {

        final int MAX_N = 30;
        final int MIN_N = 1;

        int n, i, sumOfNumbers, number;
        boolean isIncorrect;

        n = 0;
        i = 0;
        sumOfNumbers = 0;
        number = 1;
        isIncorrect = true;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Программа считает сумму заданную в условии задачи №2 варианта №20");

        do {

            isIncorrect = false;

            try {
                System.out.print("Введите верхнюю границу суммирования: ");
                n = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.println("Неправильный ввод, повторите попытку.");
            }
 
            if (!isIncorrect && (n < MIN_N || n > MAX_N)) {
                isIncorrect = true;
                System.out.printf("Степенью может являться только целое положительное число, которое принадлежит диапазону [%d;%d].\n", MIN_N, MAX_N);
            }

        } while (isIncorrect);

        scanner.close();

        for (i = 0; i < n; i++) {
            number = number * -2;
            sumOfNumbers = sumOfNumbers + number;
        }

        System.out.printf("Сумма равна %d", sumOfNumbers);
    }
}