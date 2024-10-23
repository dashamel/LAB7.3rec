#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int size, const int Low, const int High);
void Input(int** a, const int size, int i = 0, int j = 0);
void Print(int** a, const int size, int i = 0, int j = 0);
int CountLocalMinimal(int** a, const int size, int i = 0, int j = 0, int localMinimalCount = 0);
bool IsLocalMinimum(int** a, const int size, int i, int j);
int SumMainDiagonal(int** a, const int size, int i = 0, int j = 1, int sum = 0);

int main() {
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 15;

    int size;
    cout << "Enter the size : ";
    cin >> size;

    int** a = new int* [size];
    for (int i = 0; i < size; i++)
        a[i] = new int[size];

    Input(a, size);
    Print(a, size);

    int localMinimalCount = CountLocalMinimal(a, size);
    cout << "The number of local minimal : " << localMinimalCount << endl;

    int sumDiagonal = SumMainDiagonal(a, size);
    cout << "Sum above the main diagonal : " << sumDiagonal << endl;

    for (int i = 0; i < size; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}

// Рекурсивне введення елементів
void Input(int** a, const int size, int i, int j) {
    if (i == size) return;

    cout << "a[" << i << "][" << j << "] = ";
    cin >> a[i][j];

    if (j < size - 1)
        Input(a, size, i, j + 1);  // Рекурсія для наступного елемента в рядку
    else
        Input(a, size, i + 1, 0);  // Перехід на наступний рядок
}

// Рекурсивний вивід елементів
void Print(int** a, const int size, int i, int j) {
    if (i == size) return;

    cout << setw(4) << a[i][j];

    if (j < size - 1)
        Print(a, size, i, j + 1);  // Рекурсія для наступного елемента в рядку
    else {
        cout << endl;
        Print(a, size, i + 1, 0);  // Перехід на наступний рядок
    }
}

// Рекурсивний підрахунок локальних мінімумів
int CountLocalMinimal(int** a, const int size, int i, int j, int localMinimalCount) {
    if (i == size) return localMinimalCount;

    if (IsLocalMinimum(a, size, i, j))
        localMinimalCount++;

    if (j < size - 1)
        return CountLocalMinimal(a, size, i, j + 1, localMinimalCount);  // Наступний елемент у рядку
    else
        return CountLocalMinimal(a, size, i + 1, 0, localMinimalCount);  // Наступний рядок
}

// Перевірка на локальний мінімум
bool IsLocalMinimum(int** a, const int size, int i, int j) {
    int currentElement = a[i][j];

    for (int x = i - 1; x <= i + 1; x++) {
        for (int y = j - 1; y <= j + 1; y++) {
            if (x >= 0 && x < size && y >= 0 && y < size) {
                if (a[x][y] < currentElement) {
                    return false;
                }
            }
        }
    }
    return true;
}

// Рекурсивний підрахунок суми над головною діагоналлю
int SumMainDiagonal(int** a, const int size, int i, int j, int sum) {
    if (i == size) return sum;

    if (j < size) {
        sum += abs(a[i][j]);
        return SumMainDiagonal(a, size, i, j + 1, sum);  // Продовження для наступного елемента праворуч
    }
    else {
        return SumMainDiagonal(a, size, i + 1, i + 2, sum);  // Перехід до наступного рядка
    }
}
