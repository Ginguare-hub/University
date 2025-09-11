import java.util.Scanner;

public class Main {

    public static void main(String[] args) {

        int checker = 0;
        double a = 1.0;
        double b = 1.0;
        double arithmMean = 1.0;
        double geomMean = 1.0;
        boolean isIncorrect = true;
        boolean isCycleAllowed = true;

        final int MIN = 0;
        final int MAX = 1000;

        Scanner scanner = new Scanner(System.in);

        System.out.println("Программа считает среднее арифметическое и среднее геометрическое для чисел a и b, и показывает, что среднее арифметическое этих чисел не меньше их среднего геометрического.");

        while (isCycleAllowed) {

            while (isIncorrect) {

                isIncorrect = false;

                try {
                    System.out.print("Введите число a:  ");
                    a = Double.parseDouble(scanner.nextLine());
                } catch (NumberFormatException e) {
                    isIncorrect = true;
                    System.out.println("Ошибка в записи числа a, повториет попытку.");
                }
 
                if (!isIncorrect && (a < MIN || a > MAX)) {
                    isIncorrect = true;
                    System.out.println("Число a должно быть положительным и лежать в диапазоне (" + MIN + ";" + MAX + "), попробуйте ещё раз.");
                }
            }

            isIncorrect = true;

            while (isIncorrect) {

                isIncorrect = false;

                try {
                    System.out.print("Введите число b:  ");
                    b = Double.parseDouble(scanner.nextLine());
                } catch (NumberFormatException e) {
                    isIncorrect = true;
                    System.out.println("Ошибка в записи числа b, повториет попытку.");
                }
 
                if (!isIncorrect && (b < MIN || b > MAX)) {
                    isIncorrect = true;
                    System.out.println("Число b должно быть положительным и лежать в диапазоне (" + MIN + ";" + MAX + "), попробуйте ещё раз.");
                }
            }

            isIncorrect = true;

            arithmMean = (a + b) / 2;
            geomMean = Math.sqrt(a * b);

            if (arithmMean < geomMean) {
                System.out.println("Среднее арифметическое меньше чем среднее геометрическое заданных чисел.");
            } else {
                System.out.println("Среднее арифметическое не меньше чем среднее геометрическое заданных чисел.");
            }
            //System.out.print(arithmMean);
            System.out.println("Если хотите продолжить, введите число 1, если нет, то число 2");
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