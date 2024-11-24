#include <iostream>
#include <fstream>

using namespace std;

void readData(double& a, double& b, double& h, int& n, char& f, char nameOfFile[]);
bool fillFromFile(double& a, double& b, double& h, int& n);
void checkValidInput();
void checkValidParams(double a, double b, double h, int n);
double calculate(double x, int n);
void file(char f, double x, int n, const char nameOfFile[]);

int main()
{
    setlocale(LC_ALL, "ukr");
    double a, b, h;
    int n;
    char f;
    char nameOfFile[50];

    try {
        readData(a, b, h, n, f, nameOfFile);
        checkValidParams(a, b, h, n);
        cout << endl;
        for (double x = a; x <= b; x += h) {
            if (f == '+') {
                file(f, x, n, nameOfFile);
            }
            cout << "Коли x = " << x << " та n = " << n << ", y = " << calculate(x, n) << endl;
        }
    }
    catch (const char* e) {
        cout << e << endl;
        return 1;
    }
    catch (...) {
        cout << "\033[1;31mНевiдома помилка.\033[0m" << endl;
        return 2;
    }

    return 0;
}

void checkValidInput() {
    if (cin.fail()) {
        throw "\033[1;31mВведенi данi некоректнi.\033[0m";
    }
}
bool fillFromFile(double& a, double& b, double& h, int& n) {
    char choice;
    cout << "Отримати значення з файлу? Введiть \"+\", якщо так: ";
    cin >> choice;
    if (choice == '+') {
        ifstream inFile("inputData.txt");
        inFile >> a >> b >> h >> n;
        inFile.close();
        return true;
    }
    return false;
}

void readData(double& a, double& b, double& h, int& n, char& f, char nameOfFile[]) {
    if (!fillFromFile(a, b, h, n)) {
        cout << "Введiть значення початку iнтервалу: ";
        cin >> a;
        checkValidInput();
        cout << "Введiть значення кiнця iнтервалу: ";
        cin >> b;
        checkValidInput();
        cout << "Введiть значення кроку: ";
        cin >> h;
        checkValidInput();
        cout << "Введiть значення n (n >= 4): ";
        cin >> n;
        checkValidInput();
    }
    cout << "Чи хочете Ви записати результати у файл? Введiть \"+\", якщо так: ";
    cin >> f;
    checkValidInput();
    if (f == '+') {
        cout << "Введiть назву файлу: ";
        cin.ignore();
        cin.getline(nameOfFile, 50);
        checkValidInput();
    }
}

void checkValidParams(double a, double b, double h, int n) {
    if (a > b) {
        throw "\033[1;31mПомилка. Значення початку повинно бути менше за значення кiнця.\033[0m";
    }
    if (h <= 0) {
        throw "\033[1;31mПомилка. Значення кроку повинно бути бiльше за 0.\033[0m";
    }
    if (n < 4) {
        throw "\033[1;31mПомилка. Значення n повинно бути бiльше за 4.\033[0m";
    }
}

double calculate(double x, int n) {
    double y;
    if (x < 0) {
        y = 1;
        for (int j = 2; j <= n - 2; j++) {
            y *= j + 1;
        }
    }
    else {
        y = 0;
        for (int i = 0; i <= n - 1; i++) {
            double p = 1;
            for (int j = 0; j <= n - 1; j++) {
                p *= x + i + j * j;
            }
            y += p;
        }
    }
    return y;
}

void file(char f, double x, int n, const char nameOfFile[]) {
    if (f == '+') {
        ofstream fout;
        fout.open(nameOfFile, ofstream::app);

        if (!fout.is_open()) {
            cout << "\033[1;31mПомилка вiдкриття файлу.\033[0m" << endl;
        }
        fout << "Коли x = " << x << " та n = " << n << ", y = " << calculate(x, n) << endl;
        fout.close();
    }
}
