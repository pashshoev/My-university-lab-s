#include <iostream>
#include <ctime>
using namespace std;

int*count_of_neg_nums(int **arr , int n , int m)
{
    //Возвращает массив где i-тое число - это количество отрицательных элементов в i-той строке матрицы
    int *res= new int[n];
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] < 0)
                count++;
        }
        res[i] = count;
        count = 0;
    }
    return res;
}


int** sdvig(int** matrix, int n, int m, int* shift)
{
    // Выделение памяти для результата
    int** res = new int* [n];
    for (int s = 0; s < n; s++)
    {
        res[s] = new int[m];
    }


    int l, k = 0;
    for (int i = 0; i < n; i++)
    {
        l = m - shift[i]; // shift[i] - насколько надо сдвинуть, [ l ]-тый элемент который окажется вначале нового массива после сдвига 

        while (l < m) // Сначала записываем те элементы которые после сдвига должны оказаться вначале нового массива
        {
            res[i][k] = matrix[i][l];
            l++; k++;
        }

        l = 0;
        while (l < m - shift[i])// Дописываем остальные элементы в конец нового массива
        {
            res[i][k] = matrix[i][l];
            l++; k++;
        }
        k = 0; l = 0;
    }
    return res;
}
int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(0));

    int n = 0, m = 0;
    cout << "Введите количество строк матрицы\n";
    cin >> n;
    if (cin.fail() || n < 1)
    {
        
        cout << "\n\nОшибка!\nВведeно недопустимое значение\n\n";
        system("color 4");
        return 0;
    }
    else
    {
        cout << "Введите количество столбцов\n";
        cin >> m;
        if (cin.fail() || m < 1)
        {
            cout << "\n\nОшибка!\nВведeно недопустимое значение\n\n";
            system("color 4");
            return 0;
        }
    }
    //Выделение памяти для исходного массива
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[m];
    }
    // Заполняем случайными числами     
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix[i][j] = rand() % (n*m) - (n*m)/2;
        }
    }
    ///////
    cout << "Исходная матрицы:\n\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout<< matrix[i][j] <<" ";
        }
        cout << endl;
    }

    int* arr = count_of_neg_nums(matrix, n, m); // i-тое число этого массива это количество отрицательных элементов в  i-той строке исходной матрицы

    int** res = sdvig(matrix, n, m, arr);

    cout << "\n\nОбработанная матрица:\n\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << res[i][j] << " ";
        }
        cout << "------------Сдвинуто вправо на " << arr[i] << " индекса ( циклический)\n";
    }

    // Освобождение памяти
    delete[] arr;
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
        delete[] res[i];
    }
    delete[] matrix;
    delete[] res;
}
