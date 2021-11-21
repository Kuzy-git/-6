#include <iostream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <windows.h>

float criteria[20][20];//коэфициент критерия
char name_of_criteria[20][20];//название критерия
int n;//кол-во критериев
int shift;//сдвиг 
char error[20];//переменная для обнаружения ошибки ввода
int choice;//счетчик ошибок ввода
float balance;//остаток или избыток от суммы весовых коэфициентов 
float maximum = 0;//максимальный весовой коэфициент
int index = 0;//индекс максимального весового коэфициента

using namespace std;

int most(float criteria[20][20], int n, float maximum, int index)//функция находит максимальный весовой коэфициент
{
    maximum = criteria[n + 1][0];
    for (int g = 1; g < n; g++)
    {
        if (maximum < criteria[n + 1][g])
        {
            maximum = criteria[n + 1][g];
            index = g;
        }
    }
    return 0;
}

int coefficients(float criteria[20][20], int n)//функция находит весовые коэфициенты
{

    for (int k = 0; k < n; k++)//цикл находит весовые коэфициенты
    {
        criteria[n + 1][k] = criteria[n][k] / criteria[n][n];
        criteria[n + 1][k] = round(criteria[n + 1][k] * 100) / 100; //округление до сотых
    }
    for (int s = 0; s < n; s++)//цикл находит сумму весовых коэфициентов
        criteria[n + 1][n] = criteria[n + 1][n] + criteria[n + 1][s];
    balance = criteria[n + 1][n] - 1;

    if ((balance > 0) || (balance < 0))//лог.оператор определяет, есть ли избыток или недостаток
    {
        most(criteria, n, maximum, index);
        criteria[n + 1][index] = criteria[n + 1][index] - balance;
    }
    return 0;
}

int sums(float criteria[20][20], int n)//функция находит сумму строки, и сумму сумм строк
{
    for (int j = 0; j < n; j++)// цикл находит сумму строки
    {
        for (int i = 0; i < n; i++)
            criteria[n][j] = criteria[n][j] + criteria[i][j];
    }
    for (int k = 0; k < n; k++)//цикл находит сумму сумм строк
        criteria[n][n] = criteria[n][n] + criteria[n][k];
    return 0;

}

int input(float criteria[20][20], int n, int shift)//функция ввода таблицы
{
    cout << "\nВведите оценку сравнения. От 1-го до 9-ти.\n";
    for (int j = 0; j < n - 1; j++)//цикл введения с клавиатуры 
    {
        for (int i = 1 + shift; i < n; i++)
        {
            cout << "\nВведите коэфициент отношнения ";
            for (int c = 0; c < 4; c++)//цикл выводит назване критерия
                cout << name_of_criteria[j][c];
            cout << " к ";
            for (int d = 0; d < 5; d++)//цикл выводит назване критерия
                cout << name_of_criteria[i][d];
            cout << ": ";
            for (;;)//цикл проверяет есть ли ошибка при вводе коэфициента
            {
                choice = 0;//переменная считает ошибки
                cin.getline(error, 20);
                for (int l = 0; l < 20; l++)
                {
                    switch (error[l])
                    {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case '.':
                    case '\0':
                        break;

                    default:
                        choice++;
                        break;
                    }
                }
                if (choice == 0)//если ошибок нет
                {
                    criteria[i][j] = atof(error);//char в float
                    choice = 0;
                    if (criteria[i][j] > 0 && criteria[i][j] <= 9)//коэфициент входит в возможный диапазон?
                        break;
                    else
                    {
                        cout << "   Коэфициент должен находиться в диапазоне от 1-го до 9-ти! " << endl;
                        cout << "Введите коэфициент: ";
                    }
                }
                if (choice != 0)//если ошибки есть
                {
                    cout << "   Вы можете ввести коэфициенты от 1-го до 9-ти! Помните, что дробные коэфициенты вводятся через запятую!";
                    cout << endl << "Введите коэфициент: ";
                    choice = 0;
                    continue;
                }
            }
            criteria[i][j] = round(criteria[i][j] * 100) / 100;//округляет число до 2-ух знаков после запятой
            criteria[j][i] = 1 / criteria[i][j];//заполнение второй половины таблицы
            criteria[j][i] = round(criteria[j][i] * 100) / 100;
        }
        shift++;//переменная сдвигающая элементы, каждую итерацию
    }
    for (int g = 0; g < n; g++)//цикл заполняет диогональ таблицы единицами
        criteria[g][g] = 1;
    return 0;
}

int output(float criteria[20][20], int n)//функция вывода таблицы
{
    cout << endl << "    ";
    for (int f = 0; f < n; f++)//вывод названия критерия
    {
        cout << "|";
        for (int d = 0; d < 5; d++)
        {
            if (name_of_criteria[f][d] != '\0')
                cout << name_of_criteria[f][d];
            else
                cout << " ";
        }
        cout << "|";
    }
    cout << "|Сумма||Коэф.|" << endl;
    for (int s = 0; s <= n; s++)
    {
        for (int i = 0; i < 4; i++)//вывод названия критерия
        {
            if (name_of_criteria[s][i] != '\0')
                cout << name_of_criteria[s][i];
            else
                cout << " ";
        }
        for (int k = 0; k <= n + 1; k++)//вывод коэфициентов критерия
        {
            cout << "|";
            cout.width(5);
            cout << criteria[k][s];
            cout << "|";
        }
        cout << endl;
    }
    return 0;
}

int title(char name_of_criteria[20][20], int n)
{
    cout << endl << "Введите названия критериев, которые вы хотите сравнить." << endl;
    cout << "Название критерия состоит из 4-ех символов." << endl;
    cout << "В случае, если вы введете больше 4-ех символов, программа будет игнорировать последующие символы." << endl;
    for (int i = 0; i < n; i++)
    {
        cout << endl << "Название критерия №" << i + 1 << ": ";
        cin.getline(name_of_criteria[i], 20);
    }
    return 0;
}

int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    for (;;)
    {
        choice = 0;
        cout << "Введите кол-во критериев: ";
        cin.getline(error, 20);
        for (int i = 0; i < 20; i++)
        {
            switch (error[i])
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '\0':
                break;

            default:
                choice++;
                break;
            }
        }
        if (choice == 0)
        {
            n = atoi(error);//char в int
        }
        else
            cout << "Вы ввели недопустимый символ!";

        if (n > 20)//если ввели больше 20-ти критериев
            cout << endl << "   Максимальное кол-во критериев = 20!" << endl;
        else if ((n < 2) && (n >= 0) && (choice == 0))//если ввели 1 или 2 критерия
            cout << endl << "   Что бы сравнить критерии, их должно быть, как минимум 2!" << endl;
        else if (choice != 0)
            continue;
        else
            break;
    }
    title(name_of_criteria, n);
    input(criteria, n, shift);
    sums(criteria, n);
    coefficients(criteria, n);
    output(criteria, n);
    return 0;
}
