import java.util.Scanner;

class Lab1_3 {

    public static void main(String[] args) {

        double x0, x1, derivative, lowerLimit, upperLimit, funcFromXEqualX, epsilon;
        int count = 0;

        x0 = 0.0;
        x1 = 0.0;
        derivative = 0.0;
        lowerLimit = 0.0;
        upperLimit = 1.0;

        Scanner scanner = new Scanner(System.in);

        System.out.print("Программа находит корень уравнения ln(7,622x) – 8,59х + 5 = 0 с точностью эпсилон методом простой итерации.\n");
        System.out.print("Введите число эпсилон, рекомендуемое значение от 0.1\n");
        epsilon = Double.parseDouble(scanner.nextLine());

        x1 = (lowerLimit + upperLimit) / 2;
        x0 = x1;

        funcFromXEqualX = ((Math.log(7.622*x0) + 5) / 8.59);
        derivative = 1 / (8.59 * x0);

        if (Math.abs(derivative)  < 1) {
            do {
                count = count + 1;
                x0 = x1;
                funcFromXEqualX = (Math.log(7.622 * x0) + 5) / 8.59;
                x1 = funcFromXEqualX;
            } while (((Math.abs(x1 - x0)) > epsilon) && (count < 100));

        System.out.printf("X = %d  %d", x1, count); 
         
        } else {
        System.out.print("Корней методом простой итерации на данном промежутке найти не удалось\n"); 
        } 

        scanner.close();
    }   
}