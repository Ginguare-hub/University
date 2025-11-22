import java.util.Scanner;
import java.io.*;

public class MatrixProcessor {
    // Константы
    private static final int ERROR_NUMBER = 37707;
    private static final int MIN_LENGTH = 1;
    private static final int MAX_LENGTH = 20;
    private static final int MIN_NUMBER = -10000;
    private static final int MAX_NUMBER = 10000;
    
    // Проверки ----------------------------------------------------------------------
    
    public static int readAndVerify(Scanner scanner, int minNumber, int maxNumber, String message) {
        int number = 0;
        boolean isCorrect = false;
        
        do {
            System.out.print(message);
            
            if (scanner.hasNextInt()) {
                number = scanner.nextInt();
                scanner.nextLine();
                
                if (number < minNumber || number > maxNumber) {
                    System.out.println("The number must fit the range [" + minNumber + "," + maxNumber + "].");
                    isCorrect = false;
                } else {
                    isCorrect = true;
                }
            } else {
                System.out.println("Incorrect input, try again.");
                scanner.nextLine();
                isCorrect = false;
            }
        } while (!isCorrect);
        
        return number;
    }
    
    public static boolean isFileText(String filePath) {
        if (filePath.length() <= 4) {
            return false;
        }
        
        return filePath.endsWith(".txt");
    }
    
    public static boolean isFileNotEmpty(String filePath) {
        try {
            FileInputStream file = new FileInputStream(filePath);
            int fileSize = file.available();
            file.close();
            return fileSize > 0;
        } catch (IOException e) {
            return false;
        }
    }
    
    public static boolean canRead(String filePath) {
        try {
            FileInputStream file = new FileInputStream(filePath);
            file.close();
            return true;
        } catch (IOException e) {
            return false;
        }
    }
    
    public static boolean canWrite(String filePath) {
        try {
            FileOutputStream file = new FileOutputStream(filePath, true);
            file.close();
            return true;
        } catch (IOException e) {
            return false;
        }
    }
    
    public static boolean fileExists(String filePath) {
        try {
            FileInputStream file = new FileInputStream(filePath);
            file.close();
            return true;
        } catch (IOException e) {
            return false;
        }
    }
    
    public static boolean checkMyFile(String filePath, boolean isFileOutput) {
        if (!fileExists(filePath)) {
            System.out.println("Error, file with path <" + filePath + "> is not exists.");
            return false;
        }
        
        if (!isFileText(filePath)) {
            System.out.println("Error, filename is not .txt");
            return false;
        }
        
        if (!isFileOutput && !canRead(filePath)) {
            System.out.println("Error, no access to read the file.");
            return false;
        }
        
        if (isFileOutput && !canWrite(filePath)) {
            System.out.println("Error, no access to write into the file.");
            return false;
        }
        
        if (!isFileOutput && !isFileNotEmpty(filePath)) {
            System.out.println("Error, file is empty.");
            return false;
        }
        
        System.out.println("Assigning is completed successfully.");
        return true;
    }
    
    // Основные функции ------------------------------------------------------------
    
    public static boolean workWithConsoleOrFile(Scanner scanner, boolean isOutput) {
        int number = 0;
        
        if (isOutput) {
            System.out.println("If data is output to the console write 0, if from file write 1.");
        } else {
            System.out.println("If data is entered from the console write 0, if from file write 1.");
        }
        
        number = readAndVerify(scanner, 0, 1, "> ");
        boolean isFromFile = (number == 1);
        
        if (isFromFile) {
            if (isOutput) {
                System.out.println("The data is output to a file.");
            } else {
                System.out.println("The data is entered from a file.");
            }
        } else {
            if (isOutput) {
                System.out.println("The data is output to the console.");
            } else {
                System.out.println("The data is entered from the console.");
            }
        }
        
        return isFromFile;
    }
    
    public static int[][] readMatrixFromFile(int minNumber, int maxNumber, String filePath) {
        try {
            Scanner fileScanner = new Scanner(new FileInputStream(filePath));
            
            if (!fileScanner.hasNextInt()) {
                System.out.println("Error reading matrix length.");
                fileScanner.close();
                return null;
            }
            
            int matrixSize = fileScanner.nextInt();
            
            if (matrixSize < MIN_LENGTH || matrixSize > MAX_LENGTH) {
                System.out.println("Incorrect matrix length, the number must fit the range [" 
                         + MIN_LENGTH + "," + MAX_LENGTH + "].");
                fileScanner.close();
                return null;
            }
            
            int[][] matrix = new int[matrixSize][matrixSize];
            
            for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                    if (!fileScanner.hasNextInt()) {
                        System.out.println("Incorrect numeric data: matrix element.");
                        fileScanner.close();
                        return null;
                    }
                    matrix[i][j] = fileScanner.nextInt();
                    
                    if (matrix[i][j] < minNumber || matrix[i][j] > maxNumber) {
                        System.out.println("Matrix element out of range.");
                        fileScanner.close();
                        return null;
                    }
                }
            }
            
            fileScanner.close();
            return matrix;
            
        } catch (IOException e) {
            System.out.println("Error opening file: " + e.getMessage());
            return null;
        }
    }
    
    public static int[][] readMatrixFromConsole(Scanner scanner) {
        int matrixSize = readAndVerify(scanner, MIN_LENGTH, MAX_LENGTH, "Write matrix length: ");
        int[][] matrix = new int[matrixSize][matrixSize];
        
        for (int i = 0; i < matrixSize; i++) {
            for (int j = 0; j < matrixSize; j++) {
                String prompt = "Write element [" + i + "," + j + "] of matrix: ";
                matrix[i][j] = readAndVerify(scanner, MIN_NUMBER, MAX_NUMBER, prompt);
            }
        }
        
        return matrix;
    }
    
    public static String askTheFilePath(Scanner scanner) {
        System.out.print("Write the existing file path: ");
        return scanner.nextLine();
    }
    
    public static String assignMyFile(Scanner scanner, boolean isFileOutput) {
        String filePath;
        boolean isCorrect = false;
        
        do {
            filePath = askTheFilePath(scanner);
            isCorrect = checkMyFile(filePath, isFileOutput);
        } while (!isCorrect);
        
        return filePath;
    }
    
    public static void writeMatrixIntoConsole(int[][] matrix) {
        System.out.println("The result matrix is: ");
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[i].length; j++) {
                System.out.print(matrix[i][j] + " ");
            }
            System.out.println();
        }
    }
    
    public static void writeMatrixIntoFile(String filePath, int[][] matrix) {
        try {
            PrintWriter writer = new PrintWriter(new FileOutputStream(filePath));
            writer.println("The result matrix is: ");
            
            for (int i = 0; i < matrix.length; i++) {
                for (int j = 0; j < matrix[i].length; j++) {
                    writer.print(matrix[i][j] + " ");
                }
                writer.println();
            }
            
            writer.close();
            System.out.println("Matrix written to file successfully.");
        } catch (IOException e) {
            System.out.println("Error creating file: " + e.getMessage());
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        boolean isFromFile = false;
        boolean isToFile = false;
        int[][] matrix = null;
        
        // Ввод данных
        isFromFile = workWithConsoleOrFile(scanner, false);
        
        if (isFromFile) {
            boolean isAllDone = false;
            
            do {
                String filePath = assignMyFile(scanner, false);
                matrix = readMatrixFromFile(MIN_NUMBER, MAX_NUMBER, filePath);
                
                if (matrix != null) {
                    isAllDone = true;
                } else {
                    System.out.println("Error reading matrix from file. Please try again.");
                }
            } while (!isAllDone);
            
        } else {
            matrix = readMatrixFromConsole(scanner);
        }
        
        // Вывод данных
        isToFile = workWithConsoleOrFile(scanner, true);
        
        if (isToFile) {
            String filePath = assignMyFile(scanner, true);
            writeMatrixIntoFile(filePath, matrix);
        } else {
            writeMatrixIntoConsole(matrix);
        }
        
        System.out.println("Press ENTER to close the program.");
        scanner.nextLine();
        scanner.close();
    }
}