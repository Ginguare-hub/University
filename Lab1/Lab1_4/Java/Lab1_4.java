package University.Lab1.Lab1_4.Java;

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
        boolean isAllCorrect;

        lenght = 0;
        i = 0;
        n = 0.0;
        isAllCorrect = true;

        Scanner scanner = new Scanner(System.in);

        do {

            isAllCorrect = true;

            try {
                System.out.print("Введите число элементов массива a: ");
                lenght = Integer.parseInt(scanner.nextLine());
            } catch (NumberFormatException e) {
                isAllCorrect = false;
                System.out.println("Неправильный ввод, повторите попытку.");
            }
 
            if (isAllCorrect && (lenght < MIN_LENGHT || lenght > MAX_LENGHT)) {
                isAllCorrect = false;
                System.out.printf("Число элементов массива должно лежать в диапазоне [%d;%d], попробуйте ещё раз.\n", MIN_LENGHT, MAX_LENGHT);
            }

        } while (!isAllCorrect);

        ArrayList<Double> a = new ArrayList<>(lenght);
        ArrayList<Double> b = new ArrayList<>(lenght);

        for (i = 0; i < lenght; i++) {
            do {

                isAllCorrect = true;

                try {
                    System.out.printf("Введите N%d элемент массива: ", i);
                    n = Double.parseDouble(scanner.nextLine());
                } catch (NumberFormatException e) {
                    isAllCorrect = false;
                    System.out.println("Неправильный ввод, повторите попытку.");
                }
 
                if (isAllCorrect && (n < MIN_NUMBER || n > MAX_NUMBER)) {
                    isAllCorrect = false;
                    System.out.printf("Степенью может являться только целое положительное число, которое принадлежит диапазону [%f;%f].\n", MIN_NUMBER, MAX_NUMBER);
                }

            } while (!isAllCorrect);

            a.add(i, n);

        }

        for (i = 0; i < lenght; i++) {
            b.add(i, 2 * a.get(i) + i + 1);
            System.out.printf("B[%d] = %f\n", i, b.get(i));
        }

        scanner.close();


    }

}