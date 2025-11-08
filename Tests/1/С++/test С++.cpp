
#include <iostream>
#include <fstream>

const int MIN_ORDER = 1;
const int MAX_ORDER = 10;
const int MIN_NUM = 1;
const int MAX_NUM = 100;

bool checkNumBounds(const int MIN_VALUE, const int MAX_VALUE, int num)
{
	    bool isIncorrect;
	    if (num < MIN_VALUE || num > MAX_VALUE)
	    {
	        std::cout << "Число вышло за допустимые пределы. Введите число от " << MIN_VALUE << " до " << MAX_VALUE << "." << std::endl;
	        isIncorrect = true;
	    }
	    else
	        isIncorrect = false;
	    return isIncorrect;
}

std::string readPathFile()
{
	    const int MIN_PATH_LENGTH = 5;
	    bool isIncorrect;
	    int pathLength;
    std::string path;
    do
    {
	        isIncorrect = false;
	        std::cout << std::endl << "Введите путь к файлу расширения.txt: ";
	        std::cin >> path;
	        pathLength = path.length();
        if ((pathLength < MIN_PATH_LENGTH) ||
	            (path[pathLength - 1] != 't') ||
	            (path[pathLength - 2] != 'x') ||
	            (path[pathLength - 3] != 't') ||
	            (path[pathLength - 4] != '.'))
	        {
            isIncorrect = true;
	            std::cout << "Некорректный ввод, укажите путь к файлу расширения.txt." << std::endl;
	        }
	    }
    while (isIncorrect);
	    return path;
}

std::string checkValidFilePath()
{
    bool isIncorrect;
	    std::string filePath;
	    std::ifstream fileName;
	    do
	    {
	        isIncorrect = false;
	        filePath = readPathFile();
	        fileName.open(filePath);
	        if (fileName.fail())
	        {
	            isIncorrect = true;
	            std::cout << "Файл не найден. Укажите путь к корректному файлу." << std::endl;
            std::cin.clear();
	        }
	        fileName.close();
	    }
    while (isIncorrect);
    return filePath;
}






void checkAppendToFile(bool& isIncorrect, std::ofstream& fileName)
{
    if (fileName.fail())
	    {
	        isIncorrect = true;
	        std::cout << "Файл доступен только для чтения или произошла ошибка доступа.Укажите путь к корректному файлу." << std::endl;
	        fileName.close();
	    }
}


int readIntFromFile(const int MIN_VALUE, const int MAX_VALUE,
	                    std::ifstream& fileName, bool& isIncorrect)
{
	    int num;
	    num = 0;
	    if (fileName.eof())
	        isIncorrect = true;
    else
	        if (!isIncorrect)
	        {
	            fileName >> num;
	            if (fileName.fail())
	            {
	                isIncorrect = true;
	                fileName.clear();
	            }
	            else
	                isIncorrect = checkNumBounds(MIN_VALUE, MAX_VALUE, num);
	        }
	    return num;
}

int readIntFromConsole(const int MIN_VALUE, const int MAX_VALUE)
{
	    bool isIncorrect;
	    int num;
    do
    {
	        isIncorrect = false;
	        std::cin >> num;
	        if (std::cin.fail())
	        {
	            isIncorrect = true;
	            std::cout << "Введите число от " << MIN_VALUE << " до "
	                      << MAX_VALUE << "!" << std::endl;
	            std::cin.clear();
	            while (std::cin.get() != '\n');
	        }
	        else
	            if (!isIncorrect && std::cin.get() != '\n')
	            {
	                std::cout << "Ошибка ввода! Введите только целое число без пробелов и других символов." << std::endl;
	                isIncorrect = true;
	                std::cin.clear();
	                while (std::cin.get() != '\n');
	            }


	            else
	                isIncorrect = checkNumBounds(MIN_VALUE, MAX_VALUE, num);
	    }
    while (isIncorrect);
	    return num;
}

int** loadMatrixFromConsole(int& order)
{
	    int** matrix;
    std::cout << std::endl << "Введите порядок матрицы: ";
	    order = readIntFromConsole(MIN_ORDER, MAX_ORDER);
	    std::cout << "Введите матрицу: " << std::endl;
	    matrix = new int* [order];
	    for (int i = 0; i < order; i++)
	        matrix[i] = new int[order];
	    for (int i = 0; i < order; i++)
	        for (int j = 0; j < order; j++)
	        {
	            std::cout << "Элемент матрицы[" << i + 1 << "]["
	                      << j + 1 << "]: ";
	            matrix[i][j] = readIntFromConsole(MIN_NUM, MAX_NUM);
	        }
	    return matrix;
}

int** loadMatrixFromFile(const int order, std::ifstream& fileName,
                         bool& isIncorrect)
{
	    int** matrix;
	    matrix = new int* [order];
    for (int i = 0; i < order; i++)
	        matrix[i] = new int[order];
	    for (int i = 0; i < order; i++)
	        for (int j = 0; j < order; j++)
	            matrix[i][j] = readIntFromFile(MIN_NUM, MAX_NUM, fileName,
	                                           isIncorrect);
	    if (isIncorrect)
	        std::cout << "В файле обнаружены некорректные значения." << std::endl << "Все элементы матрицы должны быть целыми числами от " << MIN_NUM << " до " << MAX_NUM << ".Укажите путь к корректному файлу." << std::endl;
	    else
	        if (!fileName.eof())
	        {
	            isIncorrect = true;
	            std::cout << "Обнаружены лишние значения в файле. Укажите путь к корректному файлу." << std::endl;
	        }
	        else
	            std::cout << "Данные успешно прочитаны." << std::endl;
    return matrix;
}

int* findDuplicateElements(int**& matrix, const int order, int& tempK)
{
    int* duplicates;
	    int duplicatesLength;
	    bool keepChecking;
	    tempK = 0;
	    duplicatesLength = (order * order) / 2;
	    duplicates = new int[duplicatesLength];
	    for (int k = 0; k < duplicatesLength; k++)
	        duplicates[k] = 0;
	    for (int i = 0; i < order; i++)
	        for (int j = 0; j < order; j++)
	            if (matrix[i][j])
	            {
	                keepChecking = true;
	                for (int i1 = 0; i1 < order; i1++)
	                    for (int j1 = 0; j1 < order; j1++)
	                        if ((matrix[i][j] == matrix[i1][j1]) && 
                            ((i != i1) || (j != j1)))
	                        {
	                            if (keepChecking)
	                            {
                                duplicates[tempK] = matrix[i][j];
	                                tempK++;
	                                keepChecking = false;
	                            }
	                            matrix[i1][j1] = 0;
	                        }
	            }
    return duplicates;
}

int choosingFileOrConsole()
{
	    int inputOutputMode;
	    std::cout << std::endl << "Выберите режим ввода данных: " << std::endl << "1) Введите 1 для использования консоли." << std::endl << "2) Введите 2 для использования текстового файла." << std::endl << std::endl << "Номер выбранного варианта: ";
	    inputOutputMode = readIntFromConsole(1, 2);
	    return inputOutputMode;
}

int** obtainValues(int& order, int**& matrix)
{
	    int inputMode;
	    bool isIncorrect;
	    std::string filePath;
	    std::ifstream fileName;
	    inputMode = choosingFileOrConsole();
	    if (inputMode == 1)
	        matrix = loadMatrixFromConsole(order);
    else
	        do
	        {
	            isIncorrect = false;
	            filePath = checkValidFilePath();
	            fileName.open(filePath);
	            order = readIntFromFile(MIN_ORDER, MAX_ORDER, fileName, isIncorrect);
	            if (!isIncorrect)
	                matrix = loadMatrixFromFile(order, fileName, isIncorrect);
	            else
	                std::cout << "Порядок матрицы должен быть целым числом от " << MIN_ORDER << " до " << MAX_ORDER << ".Укажите путь к корректному файлу." << std::endl;

	                fileName.close();
	        }
        while (isIncorrect);
	    return matrix;
}

void writeTask()
{
	    std::cout << "Дана матрица  А, состоящая из nхn-натуральных чисел." << std::endl << "Выбрать элементы, встречающиеся более  одного раза." << std::endl << std::endl;
}

void writeToFile(const int* answer, const int order)
{
    std::ofstream fileName;
	    std::string filePath;
	    bool isIncorrect;
	    do
	    {
	        isIncorrect = false;
	        filePath = checkValidFilePath();
	        fileName.open(filePath);
	        checkAppendToFile(isIncorrect, fileName);
	    } 
	    while (isIncorrect);
	    if (order == 0)
	        fileName << "В матрице отсутствуют элементы, встречающиеся более одного раза.";
    else
    {
	        fileName << "Элементы матрицы, встречающиеся более одного раза: ";
	        for (int i = 0; i < order; i++)
	            fileName << answer[i] << " ";
    }
    fileName.close();
	    std::cout << "Ответ выведен в текстовый файл.";
}

void writeAnswer(const int* answer, const int order)
{
	    int outputMode;
    outputMode = choosingFileOrConsole();
	    if (outputMode == 1)
        if (order == 0)
	            std::cout << "В матрице отсутствуют элементы, встречающиеся более одного раза.";
        else
	        {
	            std::cout << std::endl << "Элементы матрицы, встречающиеся более одного раза: ";
	            for (int i = 0; i < order; i++)
	                std::cout << answer[i] << "  ";
	        }
    else
	        writeToFile(answer, order);
}

void deleteMatrix(int**& matrix, const int order)
{
    for (int i = 0; i < order; i++)
	        delete[] matrix[i];
	    delete[] matrix;
}

int main()
{
    setlocale(LC_ALL, "Russian");

	    int** matrix;
	    int* answer;
	    int order, tempK;
	    writeTask();
	    matrix = obtainValues(order, matrix);
	    answer = findDuplicateElements(matrix, order, tempK);
	    writeAnswer(answer, tempK);
	    deleteMatrix(matrix, order);
	    delete[] answer;
    return 0;
}
