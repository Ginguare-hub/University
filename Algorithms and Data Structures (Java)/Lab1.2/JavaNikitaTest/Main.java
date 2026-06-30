import java.util.*;

public class Main {
    public static void main(String[] args) {
        List<Integer> guys = guys();
        int step = countingRhyme(guys);
        countingRhyme2(step);
    }

    public static List<Integer> guys() {
        int num;
        boolean isCorrect;
        Scanner scanner = new Scanner(System.in);
        List<Integer> guyGroup = new ArrayList<>();

        do {
            isCorrect = true;
            System.out.print("Введите число ребят: ");
            num = scanner.nextInt();

            if (num > 1000 || num < 1) {
                System.out.println("Введите число меньше 1000 но больше 0");
                isCorrect = false;
            }
        } while (!isCorrect);

        for (int i = 0; i < num; i++) {
            guyGroup.add(i + 1);
        }
        return guyGroup;
    }

    public static int countingRhyme(List<Integer> guys) {
        int step;
        int index = 0;
        Scanner scanner = new Scanner(System.in);
        List<Integer> circle = new ArrayList<>(guys);
        List<Integer> lose = new ArrayList<>();

        System.out.print("Введите шаг: ");
        step = scanner.nextInt();

        while (circle.size() > 1) {
            index = (index + step - 1) % circle.size();
            lose.add(circle.get(index));
            circle.remove(index);
        }

        System.out.println("Выбывшие: " + lose);
        System.out.println("Оставшийся: " + circle.get(0));
        return step;
    }

    public static void countingRhyme2(int step) {
        for (int n = 1; n <= 30; n++) {
            List<Integer> circle = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                circle.add(i);
            }

            List<Integer> lose = new ArrayList<>();
            int index = 0;

            while (circle.size() > 1) {
                index = (index + step - 1) % circle.size();
                lose.add(circle.get(index));
                circle.remove(index);
            }

            System.out.println("Для " + n + " человек:");
            System.out.println("Выбывшие: " + lose);
            System.out.println("Оставшийся: " + circle.get(0));
            System.out.println();
        }
    }
}
