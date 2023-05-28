#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void PrintRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << setw(4) << a[rowNo][colNo];
    if (colNo < colCount - 1)
        PrintRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void PrintRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    PrintRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        PrintRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void InputRow(int** a, const int rowNo, const int colCount, int colNo)
{
    cout << "a[" << rowNo << "][" << colNo << "] = ";
    cin >> a[rowNo][colNo];
    if (colNo < colCount - 1)
        InputRow(a, rowNo, colCount, colNo + 1);
    else
        cout << endl;
}

void InputRows(int** a, const int rowCount, const int colCount, int rowNo)
{
    InputRow(a, rowNo, colCount, 0);
    if (rowNo < rowCount - 1)
        InputRows(a, rowCount, colCount, rowNo + 1);
    else
        cout << endl;
}

void CreateRow(int** a, const int rowNo, const int colCount,
               const int Low, const int High, int colNo)
{
    a[rowNo][colNo] = Low + rand() % (High - Low + 1);
    if (colNo < colCount - 1)
        CreateRow(a, rowNo, colCount, Low, High, colNo + 1);
}

void CreateRows(int** a, const int rowCount, const int colCount,
                const int Low, const int High, int rowNo)
{
    CreateRow(a, rowNo, colCount, Low, High, 0);
    if (rowNo < rowCount - 1)
        CreateRows(a, rowCount, colCount, Low, High, rowNo + 1);
}

int SumRowsWithNegativeElements(int** a, const int rowCount, const int colCount, int rowNo)
{
    int sum = 0;
    bool hasNegativeElement = false;

    for (int j = 0; j < colCount; j++)
    {
        if (a[rowNo][j] < 0)
        {
            hasNegativeElement = true;
            break;
        }
    }

    if (hasNegativeElement)
    {
        for (int j = 0; j < colCount; j++)
        {
            sum += a[rowNo][j];
        }
    }

    if (rowNo < rowCount - 1)
        return sum + SumRowsWithNegativeElements(a, rowCount, colCount, rowNo + 1);
    else
        return sum;
}

bool IsMaxInRowN(int** a, const int rowNo, const int max, const int colCount,
                 int colNo)
{
    if (a[rowNo][colNo] > max)
        return false;
    if (colNo < colCount - 1)
        return IsMaxInRowN(a, rowNo, max, colCount, colNo + 1);
    else
        return true;
}

bool IsMinInColK(int** a, const int colNo, const int min, const int rowCount,
                 int rowNo)
{
    if (a[rowNo][colNo] < min)
        return false;
    if (rowNo < rowCount - 1)
        return IsMinInColK(a, colNo, min, rowCount, rowNo + 1);
    else
        return true;
}

void FindSaddlePoints(int** a, const int rowCount, const int colCount, int& No, int rowNo)
{
    for (int j = 0; j < colCount; j++)
    {
        int currentElement = a[rowNo][j];
        bool isMaxInRow = IsMaxInRowN(a, rowNo, currentElement, colCount, 0);
        bool isMinInCol = IsMinInColK(a, j, currentElement, rowCount, 0);

        if (isMaxInRow && isMinInCol)
        {
            cout << setw(4) << ++No << setw(6) << rowNo << setw(6) << j << endl;
        }
    }

    if (rowNo < rowCount - 1)
        FindSaddlePoints(a, rowCount, colCount, No, rowNo + 1);
}

int main()
{
    srand((unsigned)time(NULL));
    int Low = -7;
    int High = 7;
    int rowCount, colCount;

    cout << "rowCount = ";
    cin >> rowCount;

    cout << "colCount = ";
    cin >> colCount;

    int** a = new int*[rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    InputRows(a, rowCount, colCount, 0);

    PrintRows(a, rowCount, colCount, 0);

    int sum = SumRowsWithNegativeElements(a, rowCount, colCount, 0);
    cout << "Sum of rows with at least one negative element: " << sum << endl;

    cout << endl;
    cout << "Saddle points: max in row & min in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
    int No = 0;
    FindSaddlePoints(a, rowCount, colCount, No, 0);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

