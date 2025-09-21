import java.util.Scanner;

public class Lab1_4 {

    public static void main(String[] args) {

        final double MAX_NUMBER = 1024.0;
        final double MIN_NUMBER = -1024.0;
        final int MAX_LENGTH = 10;
        final int MIN_LENGTH = 1;

        int length;
        int i;
        double n;
        boolean isIncorrect;

        length = 0;
        i = 0;
        n = 0.0;
        isIncorrect = false;

        double a[];
        double b[];

        Scanner scanner = new Scanner(System.in);

        System.out.print("Программа получает массив a, и преобразует его в массив b, где b(k)=2*a(k)+k.\n");

        do {

            isIncorrect = false;
            System.out.print("Введите число элементов массива a: ");

            try {
                length = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.println("Неправильный ввод, повторите попытку.");
            }
 
            if (!isIncorrect && (length < MIN_LENGTH || length > MAX_LENGTH)) {
                isIncorrect = true;
                System.out.printf("Число элементов массива должно лежать в диапазоне [%d;%d], попробуйте ещё раз.\n", MIN_LENGTH, MAX_LENGTH);
            }

        } while (isIncorrect);

        a = new double[length];
        b = new double[length];

        for (i = 0; i < length; i++) {
            do {

                isIncorrect = false;
                System.out.printf("Введите N%d элемент массива: ", i);

                try {
                    n = Double.parseDouble(scanner.nextLine());
                } catch (NumberFormatException e) {
                    isIncorrect = true;
                    System.out.println("Неправильный ввод, повторите попытку.");
                }
 
                if (!isIncorrect && (n < MIN_NUMBER || n > MAX_NUMBER)) {
                    isIncorrect = true;
                    System.out.printf("Степенью может являться только целое положительное число, которое принадлежит диапазону [%f;%f].\n", MIN_NUMBER, MAX_NUMBER);
                }

            } while (isIncorrect);

            a[i] = n;
        }

        scanner.close();

        for (i = 0; i < length; i++) {
            b[i] = 2 * a[i] + i + 1;
            System.out.printf("B[%d] = %f\n", i, b[i]);
        }
    }
}