import java.util.Scanner;

class Lab1_3 {

    public static void main(String[] args) {

        final double A = 7.622;
        final double B = 8.59;
        final double C = 5.0;
        final double UPPER_LIMIT = 0.5;
        final double LOWER_LIMIT = 1.0;
        final int MAX_ITERATIONS = 20;

        double x0, x1, derivative, equivEquation, epsilon, diff;
        int count = 0;
        boolean isIncorrect = false;

        x0 = 0.0;
        x1 = 0.0;
        derivative = 0.0;
        equivEquation = 0.0;
        epsilon = 1;
        diff = 0.0;

        Scanner scanner = new Scanner(System.in);

        System.out.printf("Программа находит корень уравнения ln(%fx) - %fх + %f = 0 с точностью эпсилон методом простой итерации.\n", A, B, C);

        do {
            System.out.print("Введите положительное число эпсилон, рекомендуемое значение менее 0.1\n");

            try {
                epsilon = Double.parseDouble(scanner.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.println("Неправильный ввод, повторите попытку снова.");
            }
 
            if (!isIncorrect && (epsilon < 0 || epsilon == 0)) {
                isIncorrect = true;
                System.out.printf("Эпсилон - положительное сколь угодно малое вещественное число, эпсилон должен быть больше 0\n");
            }

        } while (isIncorrect);

        scanner.close();

        x1 = (LOWER_LIMIT + UPPER_LIMIT) / 2;
        x0 = x1;

        equivEquation = ((Math.log(A*x0) + C) / B);
        derivative = 1 / (B * x0);

        if (Math.abs(derivative)  < 1) {
            do {
                count = count + 1;
                x0 = x1;
                equivEquation = (Math.log(A * x0) + C) / B;
                x1 = equivEquation;
                diff = Math.abs(x1 - x0);
            } while ((diff > epsilon) && (count < MAX_ITERATIONS));

            System.out.printf("X = %.15f", x1); 

        } else {
            System.out.print("Корней методом простой итерации на данном промежутке найти не удалось\n"); 
        } 
    }   
}