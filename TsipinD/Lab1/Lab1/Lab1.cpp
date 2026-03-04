// Lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <cstdlib>
#include "polynomial.h"


void printMenu() {
    std::cout << "\n========= ACTIONS MENU =========\n";
    std::cout << "1. Enter Polynom 1 (P1)\n";
    std::cout << "2. Enter Polynom 2 (P2)\n";
    std::cout << "3. Show the current polynomials\n";
    std::cout << "4. Add (P1 + P2)\n";
    std::cout << "5. Div (P1 - P2)\n";
    std::cout << "6. Mul (P1 * P2)\n";
    std::cout << "7. Mul P1 by a number\n";
    std::cout << "0. Exit\n";
    std::cout << "==================================\n";
    std::cout << "Choose action: ";
}

int main()
{
    Polynom p1, p2, res;
    int choice = -1;

    while (true) {
        printMenu();

        if (!(std::cin >> choice)) {
            std::cout << "Input error. Enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) break;

        try {
            switch (choice) {
            case 1:
                std::cout << "Enter P1:\n";
                p1 = Polynom(); // обнуляем старый
                p1.read();
                system("cls");
                break;

            case 2:
                std::cout << "Enter P2:\n";
                p2 = Polynom(); 
                p2.read();
                system("cls");
                break;

            case 3:
                system("cls");
                std::cout << "P1: "; p1.print(); std::cout << "\n";
                std::cout << "P2: "; p2.print(); std::cout << "\n";
                break;

            case 4:
                res = p1 + p2;
                system("cls");
                std::cout << "Result (+): "; res.print(); std::cout << "\n";
                break;

            case 5:
                res = p1 - p2;
                system("cls");
                std::cout << "Result (-): "; res.print(); std::cout << "\n";
                break;

            case 6:
                res = p1 * p2;
                system("cls");
                std::cout << "Result (*): "; res.print(); std::cout << "\n";
                break;

            case 7:
                double factor;
                system("cls");
                std::cout << "Enter the number for mul P1: ";
                std::cin >> factor;
                res = p1 * factor;
                std::cout << "Result: "; res.print(); std::cout << "\n";
                break;

            default:
                std::cout << "Uncorrect number.\n";
                break;
            }
        }
        catch (const std::exception& e) {
            std::cerr << "An error has occurred: " << e.what() << std::endl;
        }
    }

    std::cout << "The program is completed.\n";
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
