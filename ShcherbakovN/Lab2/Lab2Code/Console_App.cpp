#include "MainTable.h"
#include "Polynom.h"

void print_menu() // Функция для вывода меню в консоль.
{
	std::cout << "+------------------------+MENU+------------------------+\n";
	std::cout << "1 - Creating/Replacing the first polynomial\n" << "2 - Creating/Replacing the second polynomial\n";
	std::cout << "3 - Add polynomials\n" << "4 - Subtract polynomials\n" << "5 - Multiply a polynomial by a constant\n";
	std::cout << "6 - Multiply polynomials\n" << "7 - Insert data into a table\n" << "8 - Querying data from a table by key\n";
	std::cout << "9 - Delete data from the table by key\n" << "10 - Outputting the program menu to the console\n"; 
	std::cout << "0 - Saving logs AND Shutting down the program\n";
	std::cout << "+------------------------------------------------------+\n";
}

std::string input_key() // Функция для ввода ключа для данной записи пользователем.
{
	std::string user_key = ""; // Буфер ввода пользователем.
	std::cout << "Enter the key for this record:\n";

	std::getline(std::cin, user_key); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_key.
	return user_key;
}

void saveResultOfOperationWithPolynomials(Polynomial& polynom, MainTable<std::string, Polynomial>& table) // Функция сохранения результатов операций с полиномами в таблицу.
{
	std::cout << "0 - put the result of adding polynomials in a table (insert), 1 - do nothing.\nEnter:\n";
	std::string user_input_save = ""; // Буфер ввода пользователем.

	bool flag_save = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
	int temp_save = -1; // Результат выбора пользователем.
	while (flag_save)
	{
		std::getline(std::cin, user_input_save); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input_save.
		try
		{
			temp_save = std::stoi(user_input_save); // std::stoi() преобразует строку user_input_save в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

			if (temp_save == 0)
			{
				std::string key = input_key();

				table.insertALL(key, polynom);
				std::cout << "The insertion is completed.\n";
				flag_save = false;
			}
			else if (temp_save == 1)
			{
				flag_save = false;
			}
			else
			{
				std::cout << "INVALID INPUT.\n0 - put the result of adding polynomials in a table (insert), 1 - do nothing.\nEnter:\n";
				continue;
			}
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT.\n0 - put the result of adding polynomials in a table (insert), 1 - do nothing.\nEnter:\n";
			continue;
		}
	}
}

Polynomial input_polynom() // Функция для ввода полинома пользователем с консоли (из лабораторной работы #1).
{
	std::cout << "The coefficients of monomials are real numbers.\nThe degree of a monomial is a three-digit number, where the hundreds digit is the degree of variable X, the tens digit is the degree of variable Y, and the units digit is the degree of variable Z.\n";

	bool flag_input = true; // Флаг для ввода пользователем всех нужных ему мономов.

	std::vector<std::pair<double, size_t>> source; // Вектор для хранения данных первого полинома, который будет передан в конструктор класса Polynomial для создания первого полинома.

	std::string user_input = ""; // Буфер ввода пользователем.

	while (flag_input)
	{
		// Вводим коэффициент монома:
		std::cout << "Enter the coefficient of the monomial:\n";

		double temp_coeff = 0.0; // Коэффициент монома.
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		try
		{
			temp_coeff = std::stod(user_input); // std::stod() преобразует строку user_input в число с плавающей запятой (double). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа double, будет выброшено исключение std::out_of_range.

			if (std::fabs(temp_coeff) < EPSILON) // Проверка на равенство коэффциеинта 0.
			{
				std::cout << "INVALID INPUT. The coefficient of the monomial must be different from 0.\n";
				continue;
			}
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Please enter a real number as the coefficient of the monomial.\n";
			continue;
		}


		// Вводим степень монома:
		std::cout << "Enter the degree of the monomial:\n";

		size_t temp_deg = -1; // Степень монома.
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		try
		{
			temp_deg = std::stoull(user_input); // std::stoull() преобразует строку user_input в беззнаковое целое число (unsigned long long). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа unsigned long long, будет выброшено исключение std::out_of_range.

			if (temp_deg > 999 || temp_deg < 0) // Проверка на выход значения степени монома за установленные пределы.
			{
				std::cout << "INVALID INPUT. Please enter an integer between 0 and 999 as the degree of the monomial.\n";
				continue;
			}
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Please enter an integer between 0 and 999 as the degree of the monomial.\n";
			continue;
		}

		source.push_back({ temp_coeff, temp_deg }); // Добавляем моном в вектор source для последующей записи в полином.

		// Даём пользователю выбор: продолжить ввод полинома(1) или завершить(0).
		std::cout << "1 - Continue entering the polynomial, 0 - Finish entering the polynomial.\nEnter:\n";
		bool flag_temp = true; // Флаг для выбора пользователем нужного варианта ответа.
		while (flag_temp)
		{
			int temp = -1; // Результат выбора пользователем.
			std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
			try
			{
				temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

				if (temp == 0)
				{
					flag_input = false;
					flag_temp = false;
				}
				else if (temp == 1)
				{
					flag_temp = false;
				}
				else
				{
					std::cout << "INVALID INPUT.\n1 - Continue entering the polynomial, 0 - Finish entering the polynomial.\nEnter:\n";
					continue;
				}
			}
			catch (std::exception)
			{
				std::cout << "INVALID INPUT.\n1 - Continue entering the polynomial, 0 - Finish entering the polynomial.\nEnter:\n";
				continue;
			}
		}
	}

	Polynomial temp_p1(source); // Создаём полином с данными, которые ввёл пользователь (source).
	return temp_p1; // Возврат из функции полученного полинома.
}

int input_value_int() // Ввод значения integer с консоли.
{
	std::cout << "Enter the integer value for this record:\n";
	std::string user_input = ""; // Буфер ввода пользователем.
	while (true)
	{
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		try
		{
			int result = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. если число слишком велико для типа int, будет выброшено исключение std::out_of_range.
			return result; // Возвращаем результат ввода пользователем.
		}
		catch (std::exception)
		{
			std::cout << "Invalid input. Integer is expected\nEnter:\n";
			continue;
		}
	}
}

double input_value_double() // Ввод значения double с консоли.
{
	std::cout << "Enter the double value for this record:\n";
	std::string user_input = ""; // Буфер ввода пользователем.
	while (true)
	{
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		try
		{
			double result = std::stod(user_input); // std::stod() преобразует строку user_input в число с плавающей запятой (double). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа double, будет выброшено исключение std::out_of_range.
			return result; // Возвращаем результат ввода пользователем.
		}
		catch (std::exception)
		{
			std::cout << "Invalid input. Double is expected\nEnter:\n";
			continue;
		}
	}
}

std::string input_value_string() // Ввод значения std::string с консоли.
{
	std::cout << "Enter the string value for this record:\n";
	std::string result = ""; // Буфер ввода пользователем.
	std::getline(std::cin, result); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
	return result; // Возвращаем результат ввода пользователем.
}

bool input_value_bool() // Ввод значения bool с консоли.
{
	std::cout << "Enter the bool value for this record:\n";
	while (true)
	{
		int result = -1;
		std::string user_input = ""; // Буфер ввода пользователем.
		bool flag_stoi = true; // Флаш ввода 0/1 с консоли.
		while (flag_stoi)
		{
			std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
			try
			{
				result = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. если число слишком велико для типа int, будет выброшено исключение std::out_of_range.
				flag_stoi = false;
			}
			catch (std::exception)
			{
				std::cout << "Invalid input. Bool(0/1) is expected\nEnter:\n";
				continue;
			}
		}

		if (result == 0)
		{
			return false;
		}
		else if (result == 1)
		{
			return true;
		}
		else
		{
			std::cout << "Invalid input. 0/1 is expected\nEnter:\n";
		}
	}
}

char input_value_char() // Ввод значения char с консоли.
{
	std::cout << "Enter the char value for this record:\n";
	std::string user_input = ""; // Буфер ввода пользователем.
	while (true)
	{
		std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
		if (user_input.length() == 1)
		{
			return user_input[0]; // Возвращаем первый символ строки ввода.
		}
		else
		{
			std::cout << "Invalid input. Char is expected\nEnter:\n";
		}
	}
}

template <typename TKey, typename TValue>
void insertToTable(MainTable<TKey, TValue>& table_, TValue (*input_func)()) // Шаблонная функция для универсальной вставки записи в таблицу (таблицы). TValue(*input_func)() - объявление указателя на функцию, для вызова функций, возвращающих разные TValue: так сможем передавать функцию в качестве аргумента.
{
	std::string key = input_key(); // Получаем ключ записи.

	TValue value = input_func(); // Получаем значение записи.

	table_.insertALL(key, value); // Вставка записи в таблицу.

	std::cout << "The insertion is completed." << std::endl;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& polynom_) // Перегруженный оператор вывода полиномов.
{
	polynom_.print_polynom(); // Вывод полинома в консоль std::cout.
	return out;
}

template <typename TKey, typename TValue>
void findInTable(MainTable<TKey, TValue>& table_, const bool& outputFactor_) // Шаблонная функция для универсального поиска записи в таблице (таблицах) по ключу.
{
	if (table_.is_emptyALL()) // Проверка на пустоту таблицы.
	{
		std::cout << "The table is empty." << std::endl;
		return;
	}

	std::string key = input_key(); // Получаем ключ записи.

	TValue* value = table_.findALL(key).value; // Получаем результат поиска записи по ключу: указатель на значение записи или nullptr (если не найдена запись).
	if (value != nullptr)
	{
		std::cout << "The search is completed: " << *value << std::endl;
		if (outputFactor_) // Проверка на то, хочет ли пользователь извлечь (получить и удалить) значение записи.
		{
			table_.removeALL(key);
			std::cout << "The remove is completed." << std::endl;
		}
	}
	else
	{
		std::cout << "The record was not found." << std::endl;
	}
}

template <typename TKey, typename TValue>
void removeFromTable(MainTable<TKey, TValue>& table_) // Шаблонная функция для универсального удаления записи по ключу из таблицы (таблиц).
{
	if (table_.is_emptyALL()) // Проверка на пустоту таблицы.
	{
		std::cout << "The table is empty." << std::endl;
		return;
	}

	std::string key = input_key(); // Получаем ключ записи.

	table_.removeALL(key); // Удаление записи по ключу.
	std::cout << "The removal is completed.\n";
}

enum ValueType // Перечисление. Набор именованных целоичисленных констант.
{
	INTEGER, // 0
	DOUBLE, // 1
	STRING, // 2
	POLYNOMIAL, // 3
	BOOL, // 4
	CHAR // 5
};

int main()
{
	bool flag = true; // Флаг работы программы.

	Polynomial p1, p2, res_p; // p1, p2 - полиномы для ввода пользователем; res_p - результирующий полином.

	// Объявляем таблицы с допустимыми к использованию типами данных:
	MainTable<std::string, int> tableInt;
	MainTable<std::string, double> tableDouble;
	MainTable<std::string, std::string> tableString;
	MainTable<std::string, Polynomial> tablePolynomial;
	MainTable<std::string, bool> tableBool;
	MainTable<std::string, char> tableChar;

	ValueType typeValue; // Выбранный тип данных пользователем.

	std::cout << "+---------------------+TYPE_VALUE+---------------------+\n";
	std::cout << "0 - integer\n" << "1 - double\n" << "2 - std::string\n" << "3 - Polynomial\n" << "4 - bool\n" << "5 - char\n";
	std::cout << "+--------------------+ENTER_CHOICE+--------------------+\n";
	std::string user_input_type = ""; // Буфер ввода пользователем.

	bool flag_type = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
	int temp_type = -1; // Результат выбора пользователем.
	while (flag_type)
	{
		std::getline(std::cin, user_input_type); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input_type.
		try
		{
			temp_type = std::stoi(user_input_type); // std::stoi() преобразует строку user_input_type в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

			switch (temp_type)
			{
			case 0:
			{
				typeValue = INTEGER;
				flag_type = false;
				break;
			}
			case 1:
			{
				typeValue = DOUBLE;
				flag_type = false;
				break;
			}
			case 2:
			{
				typeValue = STRING;
				flag_type = false;
				break;
			}
			case 3:
			{
				typeValue = POLYNOMIAL;
				flag_type = false;
				break;
			}
			case 4:
			{
				typeValue = BOOL;
				flag_type = false;
				break;
			}
			case 5:
			{
				typeValue = CHAR;
				flag_type = false;
				break;
			}
			default:
			{
				std::cout << "INVALID INPUT. Select the data type to work with the table.\n";
				std::cout << "+--------------------+ENTER_CHOICE+--------------------+\n";
				break;
			}
			}
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Select the data type to work with the table.\n";
			std::cout << "+--------------------+ENTER_CHOICE+--------------------+\n";
			continue;
		}
	}

	print_menu(); // Выводим меню для пользователя.

	while (flag)
	{
		std::cout << "+--------------------+ENTER_CHOICE+--------------------+\n";

		std::string choice = ""; // Буфер для выбора команды пользователем.
		int num_choice = 0; // Число для главного switch-case.
		std::getline(std::cin, choice);  // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной choice.

		// Отлавливаем исключение, если пользователь вводит не число.
		try
		{
			num_choice = std::stoi(choice); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.
		}
		catch (std::exception)
		{
			std::cout << "INVALID INPUT. Please enter a number from 0 to 10\n";
			continue; // Переход к началу цикла, чтобы пользователь мог ввести правильное значение команды.
		}

		switch (num_choice)
		{
			case 1:
				p1 = input_polynom(); // Применяем перегруженный оператор присваивания полиномов.
				p1.print_polynom();
				break;
			case 2:
				p2 = input_polynom(); // Применяем перегруженный оператор присваивания полиномов.
				p2.print_polynom();
				break;
			case 3:
			{
				if (!p1.is_empty() && !p2.is_empty()) // Если полиномы не пусты, то выполняем команду.
				{
					res_p = p1 + p2; // Используем перегруженные операторы сложения и присваивания.
					res_p.print_polynom();

					if (typeValue == POLYNOMIAL)
					{
						saveResultOfOperationWithPolynomials(res_p, tablePolynomial); // Сохранение результата операции с полиномами.
					}
				}
				else
				{
					if (p1.is_empty())
					{
						std::cout << "The first polynomial is empty.\n";
					}
					if (p2.is_empty())
					{
						std::cout << "The second polynomial is empty.\n";
					}
				}

				break;
			}
			case 4:
			{
				if (!p1.is_empty() && !p2.is_empty()) // Если полиномы не пусты, то выполняем команду.
				{
					std::cout << "0 - subtract the second from the first polynomial (p1 - p2), 1 - subtract the first from the second polynomial (p2 - p1).\nEnter:\n";
					std::string user_input = ""; // Буфер ввода пользователем.

					bool flag_temp = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
					int temp = -1; // Результат выбора пользователем.
					while (flag_temp)
					{
						std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
						try
						{
							temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

							if (temp == 0 || temp == 1)
							{
								if (temp == 0)
								{
									res_p = p1 - p2; // Используем перегруженные операторы вычитания и присваивания.
									res_p.print_polynom();
								}
								else
								{
									res_p = p2 - p1; // Используем перегруженные операторы вычитания и присваивания.
									res_p.print_polynom();
								}

								if (typeValue == POLYNOMIAL)
								{
									saveResultOfOperationWithPolynomials(res_p, tablePolynomial); // Сохранение результата операции с полиномами.
								}
								flag_temp = false;
							}
							else
							{
								std::cout << "INVALID INPUT.\n0 - subtract the second from the first polynomial (p1 - p2), 1 - subtract the first from the second polynomial (p2 - p1).\nEnter:\n";
								continue;
							}
						}
						catch (std::exception)
						{
							std::cout << "INVALID INPUT.\n0 - subtract the second from the first polynomial (p1 - p2), 1 - subtract the first from the second polynomial (p2 - p1).\nEnter:\n";
							continue;
						}
					}
				}
				else
				{
					if (p1.is_empty())
					{
						std::cout << "The first polynomial is empty.\n";
					}
					if (p2.is_empty())
					{
						std::cout << "The second polynomial is empty.\n";
					}
				}

				break;
			}
			case 5:
			{
				std::cout << "0 - multiply the first(p1) polynomial by a constant, 1 - multiply the second(p2) polynomial by a constant.\nEnter:\n";
				std::string user_input = ""; // Буфер ввода пользователем.

				bool flag_temp = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
				int temp = -1; // Результат выбора пользователем.
				double temp_const = -1; // Значение константы, введенное пользователем.
				while (flag_temp)
				{
					std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
					try
					{
						temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

						if (temp == 0 && !p1.is_empty() || temp == 1 && !p2.is_empty())
						{
							// Ввод константы пользователем.
							std::cout << "Enter a constant (real number):\n";

							bool flag_const = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
							while (flag_const)
							{
								std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
								try
								{
									temp_const = std::stod(user_input); // std::stod() преобразует строку user_input в число с плавающей запятой (double). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа double, будет выброшено исключение std::out_of_range.
									flag_const = false;
								}
								catch (std::exception)
								{
									std::cout << "INVALID INPUT.\nEnter a constant (real number):";
									continue;
								}
							}

							// Выбор полинома пользователем.
							if (temp == 0)
							{
								res_p = p1 * temp_const;
								res_p.print_polynom();
							}
							else if (temp == 1)
							{
								res_p = p2 * temp_const;
								res_p.print_polynom();
							}

							if (typeValue == POLYNOMIAL)
							{
								saveResultOfOperationWithPolynomials(res_p, tablePolynomial); // Сохранение результата операции с полиномами.
							}
							flag_temp = false;
						}
						else if (temp == 0 && p1.is_empty())
						{
							std::cout << "The first polynomial is empty.\n";
							flag_temp = false;
						}
						else if (temp == 1 && p2.is_empty())
						{
							std::cout << "The second polynomial is empty.\n";
							flag_temp = false;
						}
						else
						{
							std::cout << "INVALID INPUT.\n0 - multiply the first(p1) polynomial by a constant, 1 - multiply the second(p2) polynomial by a constant.\nEnter:\n";
							continue;
						}
					}
					catch (std::exception)
					{
						std::cout << "INVALID INPUT.\n0 - multiply the first(p1) polynomial by a constant, 1 - multiply the second(p2) polynomial by a constant.\nEnter:\n";
						continue;
					}
				}

				break;
			}
			case 6:
			{
				if (!p1.is_empty() && !p2.is_empty()) // Если полиномы не пусты, то выполняем команду.
				{
					try
					{
						res_p = p1 * p2; // Используем перегруженные операторы умножения и присваивания.
						res_p.print_polynom();

						if (typeValue == POLYNOMIAL)
						{
							saveResultOfOperationWithPolynomials(res_p, tablePolynomial); // Сохранение результата операции с полиномами.
						}
					}
					catch (std::range_error)
					{
						std::cout << "The degrees of the obtained variables are greater than 9. The maximum degree of a polynomial is 999.\n";
					}
				}
				else
				{
					if (p1.is_empty())
					{
						std::cout << "The first polynomial is empty.\n";
					}
					if (p2.is_empty())
					{
						std::cout << "The second polynomial is empty.\n";
					}
				}

				break;
			}
			case 7:
			{
				switch (typeValue)
				{
					case INTEGER:
					{
						insertToTable(tableInt, input_value_int); // Вызываем универсальную функцию вставки.
						break;
					}
					case DOUBLE:
					{
						insertToTable(tableDouble, input_value_double); // Вызываем универсальную функцию вставки.
						break;
					}
					case STRING:
					{
						insertToTable(tableString, input_value_string); // Вызываем универсальную функцию вставки.
						break;
					}
					case POLYNOMIAL:
					{
						insertToTable(tablePolynomial, input_polynom); // Вызываем универсальную функцию вставки.
						break;
					}
					case BOOL:
					{
						insertToTable(tableBool, input_value_bool); // Вызываем универсальную функцию вставки.
						break;
					}
					case CHAR:
					{
						insertToTable(tableChar, input_value_char); // Вызываем универсальную функцию вставки.
						break;
					}
				}

				break;
			}
			case 8:
			{
				std::cout << "0 - output the record data by key from the table, 1 - extract record data by key from the table.\nEnter:\n";
				std::string user_input = ""; // Буфер ввода пользователем.

				bool outputFactor = false; // Фактор вывода данных записи: false - только выводить; true - вывести и удалить запись (извлечь).

				bool flag_temp = true; // Флаг для выполнения команды до тех пор, пока не будет введено верное значение выбора.
				int temp = -1; // Результат выбора пользователем.
				while (flag_temp)
				{
					std::getline(std::cin, user_input); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_input.
					try
					{
						temp = std::stoi(user_input); // std::stoi() преобразует строку user_input в целое число (int). Если строка не может быть преобразована в число, будет выброшено исключение std::invalid_argument. Если число слишком велико для типа int, будет выброшено исключение std::out_of_range.

						if (temp == 0)
						{
							outputFactor = false;
							flag_temp = false;
						}
						else if (temp == 1)
						{
							outputFactor = true;
							flag_temp = false;
						}
						else
						{
							std::cout << "INVALID INPUT.\n0 - output the record data by key from the table, 1 - extract record data by key from the table.\nEnter:\n";
							continue;
						}
					}
					catch (std::exception)
					{
						std::cout << "INVALID INPUT.\n0 - output the record data by key from the table, 1 - extract record data by key from the table.\nEnter:\n";
						continue;
					}
				}

				switch (typeValue)
				{
					case INTEGER:
					{
						findInTable(tableInt, outputFactor); // Вызываем универсальную функцию поиска записи по ключу.
						break;
					}
					case DOUBLE:
					{
						findInTable(tableDouble, outputFactor); // Вызываем универсальную функцию поиска записи по ключу.
						break;
					}
					case STRING:
					{
						findInTable(tableString, outputFactor); // Вызываем универсальную функцию поиска записи по ключу.
						break;
					}
					case POLYNOMIAL:
					{
						findInTable(tablePolynomial, outputFactor); // Вызываем универсальную функцию поиска записи по ключу.
						break;
					}
					case BOOL:
					{
						findInTable(tableBool, outputFactor); // Вызываем универсальную функцию поиска записи по ключу.
						break;
					}
					case CHAR:
					{
						findInTable(tableChar, outputFactor); // Вызываем универсальную функцию поиска записи по ключу.
						break;
					}
				}

				break;
			}
			case 9:
			{
				switch (typeValue)
				{
					case INTEGER:
					{
						removeFromTable(tableInt);
						break;
					}
					case DOUBLE:
					{
						removeFromTable(tableDouble);
						break;
					}
					case STRING:
					{
						removeFromTable(tableString);
						break;
					}
					case POLYNOMIAL:
					{
						removeFromTable(tablePolynomial);
						break;
					}
					case BOOL:
					{
						removeFromTable(tableBool);
						break;
					}
					case CHAR:
					{
						removeFromTable(tableChar);
						break;
					}
				}

				break;
			}
			case 10:
			{
				print_menu();
				break;
			}
			case 0:
			{
				std::string file_name = ""; // Буфер ввода пользователем.
				std::cout << "Enter the file name:\n";

				std::getline(std::cin, file_name); // std::getline() считает строку из стандартного потока ввода (std::cin) до первого символа новой строки ('\n') и сохраняет её в переменной user_key.

				switch (typeValue)
				{
					case INTEGER:
					{
						tableInt.saveLogs(file_name);
						break;
					}
					case DOUBLE:
					{
						tableDouble.saveLogs(file_name);
						break;
					}
					case STRING:
					{
						tableString.saveLogs(file_name);
						break;
					}
					case POLYNOMIAL:
					{
						tablePolynomial.saveLogs(file_name);
						break;
					}
					case BOOL:
					{
						tableBool.saveLogs(file_name);
						break;
					}
					case CHAR:
					{
						tableChar.saveLogs(file_name);
						break;
					}
				}

				std::cout << "Logs are saved.\n";
				std::cout << "Shutdown program.\n";
				flag = false;
				break;
			}
			default:
			{
				std::cout << "INVALID INPUT. Please enter a number from 0 to 10\n";
				break;
			}
		}
	}
	return 0;
}