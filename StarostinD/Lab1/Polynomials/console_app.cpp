#include <Windows.h>
#include <iostream>
#include <vector>
#include <limits>
#include "Polynomial.h"

using namespace std;

enum Options { Enter = 1, Show, Add, Sub, Mult_c, Mult_p, Delete, Exit };

void print_menu() {
	system("cls");
	cout << "Choose what you want to do:\n";
	cout << "1. Enter a polynomial\n";
	cout << "2. Show all polynomials\n";
	cout << "3. Add two polynomials\n";
	cout << "4. Subtract two polynomials\n";
	cout << "5. Multiply a polynomial by a scalar\n";
	cout << "6. Multiply two polynomials\n";
	cout << "7. Delete polynomial from list\n";
	cout << "8. Exit\n";
}

void insert_polynomial(vector<Polynomial>& storage) {
	try {
		system("cls");
		string input;
		cout << "Enter a polynomial. Format: Space-separated monomials: CXYZ,\n";
		cout << "where C is the coefficient and X, Y, Z are degrees.\n";
		cout << "\nOptional '+' or '-' may precede each monomial. Example: 1111 - 231 + -12453 - 123\n";
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		getline(cin, input);
		storage.push_back(Polynomial(input));
	}
	catch (std::exception e) {
		cerr << "Error! " << e.what();
		system("pause");
		return;
	}

}

void show_all(vector<Polynomial>& storage) {
	system("cls");
	if (storage.size() == 0) {
		cout << "List is empty\n";
		return;
	}
	for (int i = 0; i < storage.size(); ++i) {
		cout << i + 1 << ". " << storage[i].get(1) << '\n';
	}
}

void add(vector<Polynomial>& storage) {
	system("cls");
	if (storage.size() < 2) {
		cout << "Not enough polynomials. Add " << 2 - storage.size() << " more.\n";
		return;
	}
	int choice;
	cout << "You want to see all polynomials? 1. Yes 2. No\n";
	cin >> choice;
	system("cls");
	if (choice == 1) {
		show_all(storage);
	}
	size_t first, second;
	cout << "Enter the number of the first polynomial: ";
	cin >> first;
	--first;
	if (first >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[first].get(1) << '\n';
	cout << "Enter the number of the second polynomial: ";
	cin >> second;
	--second;
	if (second >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[second].get(1) << '\n';
	cout << "The result of the addition is: ";
	Polynomial res(storage[first] + storage[second]);
	cout << res.get(1) << '\n';
	cout << "You want to save it? 1.Yes 2. No\n";
	cin >> choice;
	if (choice == 1) {
		storage.push_back(res);
		cout << "Result index is " << storage.size() << "\n";
	}
}

void subtract(vector<Polynomial>& storage) {
	system("cls");
	if (storage.size() < 2) {
		cout << "Not enough polynomials. Add " << 2 - storage.size() << " more.\n";
		return;
	}
	int choice;
	cout << "You want to see all polynomials? 1. Yes 2. No\n";
	cin >> choice;
	system("cls");
	if (choice == 1) {
		show_all(storage);
	}
	size_t first, second;
	cout << "Enter the number of the first polynomial: ";
	cin >> first;
	--first;
	if (first >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[first].get(1) << '\n';
	cout << "Enter the number of the second polynomial: ";
	cin >> second;
	--second;
	if (second >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[second].get(1) << '\n';
	cout << "The result of the subtraction is: ";
	Polynomial res(storage[first] - storage[second]);
	cout << res.get(1) << '\n';
	cout << "You want to save it? 1.Yes 2. No\n";
	cin >> choice;
	if (choice == 1) {
		storage.push_back(res);
		cout << "Result index is " << storage.size() << "\n";
	}
}

void multiply_p(vector<Polynomial>& storage) {
	system("cls");
	if (storage.size() < 2) {
		cout << "Not enough polynomials. Add " << 2 - storage.size() << " more.\n";
		return;
	}
	int choice;
	cout << "You want to see all polynomials? 1. Yes 2. No\n";
	cin >> choice;
	system("cls");
	if (choice == 1) {
		show_all(storage);
	}
	size_t first, second;
	cout << "Enter the number of the first polynomial: ";
	cin >> first;
	--first;
	if (first >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[first].get(1) << '\n';
	cout << "Enter the number of the second polynomial: ";
	cin >> second;
	--second;
	if (second >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[second].get(1) << '\n';
	try {
		Polynomial res(storage[first] * storage[second]);
		cout << "The result of the multiplication is: ";
		cout << res.get(1) << '\n';
		cout << "You want to save it? 1.Yes 2. No\n";
		cin >> choice;
		if (choice == 1) {
			storage.push_back(res);
			cout << "Result index is " << storage.size() << "\n";
		}
	}
	catch(std::exception e) {
		cerr << "Error! " << e.what();
		return;
	}
}

void multiply_c(vector<Polynomial>& storage) {
	system("cls");
	if (storage.size() < 1) {
		cout << "Not enough polynomials. Add 1 more.\n";
		return;
	}
	int choice;
	cout << "You want to see all polynomials? 1. Yes 2. No\n";
	cin >> choice;
	system("cls");
	if (choice == 1) {
		show_all(storage);
	}
	size_t poly;
	double num;
	cout << "Enter the number of the polynomial: ";
	cin >> poly;
	--poly;
	if (poly >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << storage[poly].get(1) << '\n';
	cout << "Enter the number: ";
	cin >> num;
	Polynomial res(storage[poly] * num);
	cout << "The result of the multiplication is: ";
	cout << res.get(1) << '\n';
	cout << "You want to save it? 1.Yes 2. No\n";
	cin >> choice;
	if (choice == 1) {
		storage.push_back(res);
		cout << "Result index is " << storage.size() << "\n";
	}
}

void erase(vector<Polynomial>& storage) {
	system("cls");
	if (storage.size() == 0) {
		cout << "No polynomials in list.\n";
		return;
	}
	int choice;
	cout << "You want to see all polynomials? 1. Yes 2. No\n";
	cin >> choice;
	system("cls");
	if (choice == 1) {
		show_all(storage);
	}
	size_t poly;
	cout << "Enter the number of the polynomial: ";
	cin >> poly;
	--poly;
	if (poly >= storage.size()) {
		cout << "Invalid index!\n";
		return;
	}
	cout << "Are you sure you want to delete " << storage[poly].get(1) << "? 1. Yes 2. No\n";
	choice;
	cin >> choice;
	if (choice == 1) {
		storage.erase(storage.begin() + poly);
		cout << "Success\n";
	}

}

bool process_input(Options opt, vector<Polynomial>& storage) {
	switch (opt) {
	case Enter:
		insert_polynomial(storage);
		break;
	case Show:
		show_all(storage);
		system("pause");
		break;
	case Add:
		add(storage);
		system("pause");
		break;
	case Sub:
		subtract(storage);
		system("pause");
		break;
	case Mult_c:
		multiply_c(storage);
		system("pause");
		break;
	case Mult_p:
		multiply_p(storage);
		system("pause");
		break;
	case Delete:
		erase(storage);
		system("pause");
		break;
	case Exit:
		return 1;
		break;
	default:
		cout << "Wrong input, try again.\n";
		system("pause");
		break;
	}
	return 0;
}

int main() {
	vector<Polynomial> storage;
	Options choice;
	bool exit = 0;
	while (!exit) {
		print_menu();
		int t;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		}
		std::cin >> t;
		choice = (Options)t;
		exit = process_input(choice, storage);
	}
}