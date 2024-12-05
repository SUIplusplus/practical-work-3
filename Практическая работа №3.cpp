#include <iostream>
#include <Windows.h>
using namespace std;

void InputCheck(int& number)
{
    while (cin.fail())
    {
        cin.clear();
        cin.sync();
        cin.ignore(1000, '\n');
        cout << "Введите ЧИСЛО" << endl;
        cin >> number;
    }
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
    CONSOLE_SCREEN_BUFFER_INFO cbsi;
    if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
    {
        return cbsi.dwCursorPosition;
    }
    else
    {
        COORD invalid = { 0, 0 };
        return invalid;
    }
}

void FillMatrixA(int* matrix, int N, const int& delay, HANDLE hStdout, COORD destCoord) {
    COORD current = GetConsoleCursorPosition(hStdout);
    int Q = current.Y;
    int num;
    for (int j = 0; j < N; ++j)
    {
        destCoord.X = j * 3 + 1;
        if (j % 2 == 0)
        {
            for (int i = 0; i < N; ++i)
            {
                num = rand() % (N * N + 1);
                *(matrix + i * N + j) = num;
                destCoord.Y = i + Q;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << num << '\r';
                cout.flush();
                Sleep(delay);
            }
        }
        else
        {
            for (int i = N - 1; i >= 0; --i)
            {
                num = rand() % (N * N + 1);
                *(matrix + i * N + j) = num;
                destCoord.Y = i + Q;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << num << '\r';
                cout.flush();
                Sleep(delay);
            }
        }
    }
    destCoord.X = 0;
    destCoord.Y = Q + N;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void FillMatrixB(int* matrix, int N, const int& delay, HANDLE hStdout, COORD destCoord) {
    COORD current = GetConsoleCursorPosition(hStdout);
    int Q = current.Y;
    int num, k = 1;
    int top = 0, bottom = N - 1, left = 0, right = N - 1;

    while (k <= N * N)
    {
        destCoord.Y = top + Q;
        for (int j = left; j <= right; ++j)
        {
            num = rand() % (N * N + 1);
            *(matrix + top * N + j) = num;
            destCoord.X = j * 3 + 1;;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << num << '\r';
            cout.flush();
            Sleep(delay);
            k++;
        }
        top++;

        destCoord.X = right * 3 + 1;
        for (int i = top; i <= bottom; ++i)
        {
            num = rand() % (N * N + 1);
            *(matrix + i * N + right) = num;
            destCoord.Y = i + Q;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << num << '\r';
            cout.flush();
            Sleep(delay);
            k++;
        }
        right--;

        destCoord.Y = bottom + Q;
        if (top <= bottom)
        {
            for (int j = right; j >= left; --j)
            {
                num = rand() % (N * N + 1);
                *(matrix + bottom * N + j) = num;
                destCoord.X = j * 3 + 1;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << num << '\r';
                cout.flush();
                Sleep(delay);
                k++;
            }
            bottom--;
        }

        destCoord.X = left * 3 + 1;
        if (left <= right)
        {
            for (int i = bottom; i >= top; --i)
            {
                num = rand() % (N * N + 1);
                *(matrix + i * N + left) = num;
                destCoord.Y = i + Q;
                SetConsoleCursorPosition(hStdout, destCoord);
                cout << num << '\r';
                cout.flush();
                Sleep(delay);
                k++;
            }
            left++;
        }
    }
    destCoord.X = 0;
    destCoord.Y = N + Q;
    SetConsoleCursorPosition(hStdout, destCoord);
}

void ReplaceBlocksA(int* matrix, int* newMatrix, int N)
{
    for (int i = 0; i < N * N; ++i)
    {
        if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N * N / 2) = *(matrix + i);
        }
        else if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 > N * N / 2)
        {
            *(newMatrix + i - N * N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 > N * N / 2)
        {
            *(newMatrix + i - N / 2) = *(matrix + i);
        }
    }
}

void ReplaceBlocksB(int* matrix, int* newMatrix, int N)
{
    for (int i = 0; i < N * N; ++i)
    {
        if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N / 2 + N * N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N * N / 2 - N / 2) = *(matrix + i);
        }
        else if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 > N * N / 2)
        {
            *(newMatrix + i + N / 2 - N * N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 > N * N / 2)
        {
            *(newMatrix + i - N / 2 - N * N / 2) = *(matrix + i);
        }
    }
}

void ReplaceBlocksC(int* matrix, int* newMatrix, int N)
{
    for (int i = 0; i < N * N; ++i)
    {
        if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N * N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N * N / 2) = *(matrix + i);
        }
        else if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 > N * N / 2)
        {
            *(newMatrix + i - N * N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 > N * N / 2)
        {
            *(newMatrix + i - N * N / 2) = *(matrix + i);
        }
    }
}

void ReplaceBlocksD(int* matrix, int* newMatrix, int N)
{
    for (int i = 0; i < N * N; ++i)
    {
        if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 <= N * N / 2)
        {
            *(newMatrix + i + N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 <= N * N / 2)
        {
            *(newMatrix + i - N / 2) = *(matrix + i);
        }
        else if ((i + 1) % N <= N / 2 && (i + 1) % N != 0 && i + 1 > N * N / 2)
        {
            *(newMatrix + i + N / 2) = *(matrix + i);
        }
        else if (((i + 1) % N > N / 2 || (i + 1) % N == 0) && i + 1 > N * N / 2)
        {
            *(newMatrix + i - N / 2) = *(matrix + i);
        }
    }
}

void InsertSort(int* matrix, int N)
{
    int key, j;

    for (int i = 1; i != N; ++i)
    {
        key = *(matrix + i);
        j = i - 1;

        while (j >= 0 && key < *(matrix + j))
        {
            *(matrix + j + 1) = *(matrix + j);
            j -= 1;
        }
        *(matrix + j + 1) = key;
    }
}

void Multiply(int* matrix, int N, int X)
{
    for (int i = 0; i < N * N; ++i)
        *(matrix + i) *= X;
}

void Divide(int* matrix, int N, int X)
{
    for (int i = 0; i < N * N; ++i)
        *(matrix + i) /= X;
}

void Add(int* matrix, int N, int X)
{
    for (int i = 0; i < N * N; ++i)
        *(matrix + i) += X;
}

void Subtract(int* matrix, int N, int X)
{
    for (int i = 0; i < N * N; ++i)
        *(matrix + i) -= X;
}

int main() {
    setlocale(0, "");
    srand(time(0));
    HANDLE hStdout;
    COORD destCoord;
    destCoord.X = 0;
    destCoord.Y = 0;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int N, delay = 10;

    cout << "Введите порядок матрицы (6, 8 или 10): ";
    cin >> N;
    InputCheck(N);

    int newMatrix6[6][6];
    int matrix6[6][6];

    int newMatrix8[8][8];
    int matrix8[8][8];

    int newMatrix10[10][10];
    int matrix10[10][10];

    int* matrix;
    int* newMatrix;

    switch (N)
    {
    case 6:
        matrix = *matrix6;
        newMatrix = *newMatrix6;
        break;
    case 8:
        matrix = *matrix8;
        newMatrix = *newMatrix8;
        break;
    case 10:
        matrix = *matrix10;
        newMatrix = *newMatrix10;
        break;
    default:
        cout << "Порядок матрицы должен быть 6, 8 или 10." << endl;
        return 1;
    }

    int choice;
    cout << "Введите номер схемы заполнения матрицы: ";
    cin >> choice;
    InputCheck(choice);

    switch (choice)
    {
    case 1:
        FillMatrixA(matrix, N, delay, hStdout, destCoord);
        break;
    case 2:
        FillMatrixB(matrix, N, delay, hStdout, destCoord);
        break;
    default:
        cout << "Нет такого варианта" << endl;
    }

    cout << "Введите номер схемы перестановки блоков матрицы: ";
    cin >> choice;
    InputCheck(choice);

    switch (choice)
    {
    case 1:
        ReplaceBlocksA(matrix, newMatrix, N);
        break;
    case 2:
        ReplaceBlocksB(matrix, newMatrix, N);
        break;
    case 3:
        ReplaceBlocksC(matrix, newMatrix, N);
        break;
    case 4:
        ReplaceBlocksD(matrix, newMatrix, N);
        break;
    default:
        cout << "Нет такого варианта" << endl;
    }

    int i = 0;
    for (int* ptr = newMatrix; ptr < newMatrix + N * N; ++ptr)
    {
        cout << *ptr << " ";
        if ((i + 1) % N == 0)
            cout << "\n";
        i++;
    }

    InsertSort(newMatrix, N * N);
    cout << "Отсортированная матрица: " << endl;
    i = 0;
    for (int* ptr = newMatrix; ptr < newMatrix + N * N; ++ptr)
    {
        cout << *ptr << " ";
        if ((i + 1) % N == 0)
            cout << "\n";
        i++;
    }

    int X;
    cout << "Введите число: ";
    cin >> X;
    InputCheck(X);
    cout << "1 - сложение\n2 - вычитание\n3 - умножение\n4 - деление" << endl;
    cout << "Введите номер операции: ";
    cin >> choice;
    InputCheck(choice);

    switch (choice)
    {
    case 1:
        Add(newMatrix, N, X);
        break;
    case 2:
        Subtract(newMatrix, N, X);
        break;
    case 3:
        Multiply(newMatrix, N, X);
        break;
    case 4:
        Divide(newMatrix, N, X);
        break;
    default:
        cout << "Нет такого варианта." << endl;
    }

    i = 0;
    for (int* ptr = newMatrix; ptr < newMatrix + N * N; ++ptr)
    {
        cout << *ptr << " ";
        if ((ptr - newMatrix + 1) % N == 0)
            cout << "\n";
        i++;
    }

    return 0;
}