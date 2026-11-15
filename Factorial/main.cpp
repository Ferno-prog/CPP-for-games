#include <iostream>
#include <limits>

unsigned long long factorial(unsigned long n)
{
	if (n < 2)
	{
		return 1;
	}

	return n * factorial(n - 1);
}

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

unsigned long getNumber()
{
	long n;

	std::cout << "Enter a natural number (1 - 20): ";
	std::cin >> n;

	while (std::cin.fail() || n < 1 || n > 20)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Enter a natural number (1 - 20): ";
		std::cin >> n;
	}

	return static_cast<unsigned long>(n);
}

int main()
{
	unsigned long n = getNumber();
	std::cout << n << "! = " << factorial(n) << std::endl;
	return 0;
}