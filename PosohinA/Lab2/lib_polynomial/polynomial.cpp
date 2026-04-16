#include"../lib_polynomial/polynomial.h"
#include <iomanip>

int entering_degree(const char a) {
	int deg;
	while (true) {
		while (true) {
			std::cout << "degree l" << a << " = ";
			std::cin >> deg;

			if (std::cin.fail()) {
				std::cout << "Error: Invalid input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		if (0 <= deg && deg <= 9)
			break;
		else
			std::cout << "Erorr\n";
	}
	return deg;
}

bool chek_deg(int A, int B) {
	while (A != 0) {
		if (A % 10 < B % 10)
			return false;
		A /= 10;
		B /= 10;
	}
	return true;
}


Polynomial::Polynomial() : view() {}

Polynomial::Polynomial(const List A) : view(A) {}

Polynomial::~Polynomial() { view.clear(); }

void Polynomial::record() {
	std::cout <<"enter the monomials step by step. General view of the monome K * x^l1 * y^l2 * z^l3\nl1,l2,l3 - (0 - 9), k - the real coefficient" << "To stop typing, write K = 0" << std::endl;
	int i = 1;
	int sum_deg;
	double rat;
	int l1, l2, l3, degree;

	while (true) {

		while (true) {
			std::cout << "Enter " << i << " monom" << std::endl;
			std::cout << "Ratio K = \n";
			std::cin >> rat;

			if (std::cin.fail()) {
				std::cout << "Error: Invalid input!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
				break;
		}
		i++;
		if (rat == 0)
			break;

		l1 = entering_degree('1');
		l2 = entering_degree('2');
		l3 = entering_degree('3');
		sum_deg = l1 + l2 + l3;
		degree = 100 * l1 + 10 * l2 + l3;

		std::pair<double, int> monome = { rat, degree };

		if (view.is_empty()) {
			view.push_back(monome);
			std::cout << "Monom recorded\n";
			continue;
		}
		bool flage = false;

		auto it = view.begin();

		if (sum_numb(monome.second) > sum_numb((*it).second)) {
			view.push_front(monome);
			flage = true;
		}

		if (!flage) {
			for (auto it = view.begin(); it != view.end(); ++it) {
				Node* curr = it.get_current();

				if (monome.second == curr->_val.second) {
					curr->_val.first += monome.first;
					flage = true;
					break;
				}

				if (curr->_next == nullptr) {
					view.push_back(monome);
					flage = true;
					break;
				}
				
				else {
					Node* nextcur = curr->_next;

					if (sum_numb(monome.second) > sum_numb( nextcur->_val.second) && sum_numb(monome.second) < sum_numb(curr->_val.second)) {
						view.insert(curr, monome);
						flage = true;
						break;
					}
				}
			}
		}
	} 
	std::cout << "your polynomial: " << (*this) << std::endl;
}


Polynomial Polynomial::operator + (const Polynomial& A) const {
	Polynomial new_Polynomial;
	auto it1 = view.begin();
	auto it2 = A.view.begin();

	while (it1 != view.end() && it2 != view.end()){
		if ((*it1).second == (*it2).second) {
			double sum = (*it1).first + (*it2).first;
			if (sum != 0.0) {
				std::pair<double, int> monome = { sum, (*it1).second };
				new_Polynomial.view.push_back(monome);
			}
			++it1;
			++it2;
		}

		else if ((*it1).second > (*it2).second) {
			new_Polynomial.view.push_back(*it1);
			it1++;
		}

		else if ((*it1).second < (*it2).second) {
			new_Polynomial.view.push_back(*it2);
			it2++;
		}
	}

	for(it1; it1 != view.end(); it1++)
		new_Polynomial.view.push_back((*it1));

	for (it2; it2 != view.end(); it2++)
		new_Polynomial.view.push_back((*it2));

	return new_Polynomial;
}

Polynomial Polynomial::operator - (const Polynomial& A) const {
	Polynomial new_Polynomial;
	new_Polynomial = (*this) + (A * (-1.0));
	return new_Polynomial;
}

Polynomial& Polynomial::operator = (const Polynomial& A) {
	view = A.view;
	return (*this);
}

Polynomial Polynomial::operator * (double A) const {
	Polynomial new_Polynomial;
	new_Polynomial.view.push_back(std::pair<double, int>(A, 0));
	return (*this) * new_Polynomial;
}

Polynomial Polynomial::operator * (const Polynomial& A) const {
	Polynomial new_Polynomial;
	int deg;
	auto it1 = view.begin();

	for (it1; it1 != view.end(); it1++) {
		for (auto it2 = A.view.begin(); it2 != view.end(); it2++) {
			deg = (*it1).second + (*it2).second;

			if (chek_deg(deg, (*it1).second) || chek_deg(deg, (*it2).second)) {
				std::pair<double, int> new_pair = { ((*it1).first * (*it2).first), deg };
		
				bool found = true;
				for (auto resIt = new_Polynomial.view.begin(); resIt != new_Polynomial.view.end(); ++resIt) {
					Node* curr = resIt.get_current();
					if ((*resIt).second == new_pair.second) {
						(*resIt).first += new_pair.first;
						found = false;
						break;
					}
					
					else if (curr->_next == nullptr) {
						new_Polynomial.view.push_back(new_pair);
						found = false;
						break;
					}

					else {
						Node* nextcur = curr->_next;

						if (sum_numb(new_pair.second) > sum_numb(nextcur->_val.second) && sum_numb(new_pair.second) < sum_numb(curr->_val.second)) {
							new_Polynomial.view.insert(curr, new_pair);
							found = false;
							break;
						}
					}
				}

				if (found)
					new_Polynomial.view.push_back(new_pair);
			}

			else
				throw std::logic_error("overflou");
		}
	}
	return new_Polynomial;
}

const Polynomial operator * (double val, const Polynomial& A) {
	return A * val;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
	for (auto it = p.view.begin(); it != p.view.end(); ++it) {
		if ((*it).first == 0.0) 
			continue;

		if ((*it).first > 0) 
			os << " + ";

		else 
			os << " - ";
		
		if (std::abs((*it).first) != 1.0 || (*it).second == 0)
			os << std::abs((*it).first);
		
		if ((*it).second > 0) {
			int l1 = (*it).second / 100;
			int l2 = ((*it).second / 10) % 10;
			int l3 = (*it).second % 10;

			if (l1 > 0) 
				os << "x^" << l1;

			if (l2 > 0)
				os << " * y^" << l2;

			if (l3 > 0)
				os << " * z^" << l3;
		}
	}
	return os;
}

bool Polynomial::operator == (const Polynomial& A) const {
	bool flage = true;
	auto it1 = view.begin();
	auto it2 = A.view.begin();

	while (it1 != view.end() && it2 != A.view.end()) {
		if ((*it1) != (*it2)) {
			flage = false;
			break;
		}
		it1++;
		it2++;
	}
	if (it1 != nullptr)
		flage = false;

	else if (it2 != nullptr)
		flage = false;

	return flage;
}
