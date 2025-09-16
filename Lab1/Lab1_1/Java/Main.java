import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        int checker;
        double a;
        double b;
        double arithmMean;
        double geomMean;
        boolean isIncorrect;
        boolean isCycleAllowed;

        checker = 0;
        a = 0.0;
        b = 0.0;
        arithmMean = 0.0;
        geomMean = 0.0;
        isIncorrect = true;
        isCycleAllowed = true;

        final int MIN = 0;
        final int MAX = 1000;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Программа считает среднее арифметическое и среднее геометрическое для чисел A и B, и показывает, что среднее арифметическое этих чисел не меньше их среднего геометрического.");

        while (isCycleAllowed) {

            while (isIncorrect) {

                isIncorrect = false;

                try {
                    System.out.print("Введите число A: ");
                    a = Double.parseDouble(scanner.nextLine());
                } catch (NumberFormatException e) {
                    isIncorrect = true;
                    System.out.println("Ошибка в записи числа А, повториет попытку.");
                }
 
                if (!isIncorrect && (a < MIN || a > MAX)) {
                    isIncorrect = true;
                    System.out.printf("Число A должно быть положительным и лежать в диапазоне [%d;%d], попробуйте ещё раз.\n", MIN, MAX);
                }
            }

            isIncorrect = true;

            while (isIncorrect) {

                isIncorrect = false;

                try {
                    System.out.print("Введите число B: ");
                    b = Double.parseDouble(scanner.nextLine());
                } catch (NumberFormatException e) {
                    isIncorrect = true;
                    System.out.println("Ошибка в записи числа B, повториет попытку.");
                }
 
                if (!isIncorrect && (b < MIN || b > MAX)) {
                    isIncorrect = true;
                    System.out.printf("Число B должно быть положительным и лежать в диапазоне [%d;%d], попробуйте ещё раз.\n", MIN, MAX);
                }
            }

            isIncorrect = true;

            arithmMean = (a + b) / 2;
            geomMean = Math.sqrt(a * b);

            if (arithmMean < geomMean) {
                System.out.println("Среднее арифметическое меньше чем среднее геометрическое заданных чисел.");
            } else {
                System.out.println("Cреднее арифметическое заданных чисел не меньше их среднего геометрического.");
            }

            System.out.println("Если хотите продолжить, введите число 1, если нет, то число 2.");
            checker = scanner.nextInt();

            if (checker == 1) {
                isCycleAllowed = true;
                System.out.println("Давайте заново.");
            } else {
                isCycleAllowed = false;
            }

        }
        scanner.close();
    }
}
