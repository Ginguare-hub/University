import java.util.ArrayList;
import java.util.Scanner;

public class Lab1_4 {

    public static void main(String[] args) {

        final double MAX_NUMBER = 1024.0;
        final double MIN_NUMBER = -1024.0;
        final int MAX_LENGHT = 10;
        final int MIN_LENGHT = 1;

        int lenght;
        int i;
        double n;
        boolean isIncorrect;

        lenght = 0;
        i = 0;
        n = 0.0;
        isIncorrect = false;

        ArrayList<Double> a;
        ArrayList<Double> b;

        Scanner scanner = new Scanner(System.in);

        do {

            isIncorrect = false;

            try {
                System.out.print("Введите число элементов массива a: ");
                lenght = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                isIncorrect = true;
                System.out.println("Неправильный ввод, повторите попытку.");
            }
 
            if (!isIncorrect && (lenght < MIN_LENGHT || lenght > MAX_LENGHT)) {
                isIncorrect = true;
                System.out.printf("Число элементов массива должно лежать в диапазоне [%d;%d], попробуйте ещё раз.\n", MIN_LENGHT, MAX_LENGHT);
            }

        } while (isIncorrect);

        a = new ArrayList<>(lenght);
        b = new ArrayList<>(lenght);

        for (i = 0; i < lenght; i++) {
            do {

                isIncorrect = false;

                try {
                    System.out.printf("Введите N%d элемент массива: ", i);
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

            a.add(i, n);
        }

        scanner.close();

        for (i = 0; i < lenght; i++) {
            b.add(i, 2 * a.get(i) + i + 1);
            System.out.printf("B[%d] = %f\n", i, b.get(i));
        }
    }
}