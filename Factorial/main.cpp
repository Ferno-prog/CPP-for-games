#include <iostream>
#include <limits>
#include <cstdint>

std::uint64_t factorial(std::uint32_t n)
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

std::uint32_t getNumber()
{
	int n = 0;
	constexpr int MAX_INPUT = 20;

	std::cout << "Enter a natural number (0 - " << MAX_INPUT << "): ";
	std::cin >> n;

	while (std::cin.fail() || std::cin.peek() != '\n' || n < 0 || n > MAX_INPUT)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Enter a natural number (0 - " << MAX_INPUT << "): ";
		std::cin >> n;
	}

	return static_cast<std::uint32_t>(n);
}

int main()
{
	std::uint32_t n = getNumber();
	std::cout << n << "! = " << factorial(n) << std::endl;
	return 0;
}