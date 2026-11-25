#include <iostream>
#include <cstdint>
#include <limits>
#include <bitset>
#include <string>

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInRange(const int min, const int max, const std::string& what)
{
	int input;

	std::cout << "Please enter " << what << " in the range (" << min << " - " << max << "): ";
	std::cin >> input;

	while (std::cin.fail() || std::cin.peek() != '\n' || input < min || input > max)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter " << what << " in the range (" << min << " - " << max << "): ";
		std::cin >> input;
	}

	return input;
}

int countSetBits(const uint8_t value)
{
	int count = 0;

	for (int i = 0; i < 8; i++)
	{
		if (value & (1 << i))
		{
			count++;
		}
	}

	return count;
}

bool isBitSet(const uint8_t value, const int n)
{
	return (value & (1 << n)) != 0;
}

uint8_t setBit(const uint8_t value, const int n) { return static_cast<std::uint8_t>(value | (1 << n)); }
uint8_t clearBit(const uint8_t value, const int n) { return static_cast<std::uint8_t>(value & ~(1 << n)); }
uint8_t invertBit(const uint8_t value, const int n) { return static_cast<std::uint8_t>(value ^ (1 << n)); }

void printBinaryAndDecimal(const std::string& text, const uint8_t value)
{
	std::cout << text << ": Binary: " << std::bitset<8>(value) << " Decimal: " << static_cast<int>(value) << '\n';
}

bool askToContinue()
{
	char answer;

	std::cout << "Go again? (y/n): ";
	std::cin >> answer;
	clearInput();

	while (answer != 'y' && answer != 'n')
	{
		std::cerr << "ERROR: Please enter y or n." << std::endl;
		std::cout << "Go again? (y/n): ";
		std::cin >> answer;
		clearInput();
	}

	return answer == 'y';
}

int main()
{
	do
	{
		uint8_t number = static_cast<uint8_t>(getIntInRange(0, 255, "an integer"));
		int n = getIntInRange(0, 7, "a bit position");

		std::cout << static_cast<int>(number) << " in binary: " << std::bitset<8>(number) << '\n';
		std::cout << "Amount of bits that are set: " << countSetBits(number) << '\n';
		std::cout << "Bit " << n << " is set: " << (isBitSet(number, n) ? "true" : "false") << '\n';

		printBinaryAndDecimal("The new value with the nth bit set", setBit(number, n));
		printBinaryAndDecimal("The new value with the nth bit cleared", clearBit(number, n));
		printBinaryAndDecimal("The new value with the nth bit inverted", invertBit(number, n));
		printBinaryAndDecimal("The value shifted left", static_cast<uint8_t>(number << n));
		printBinaryAndDecimal("The value shifted right", static_cast<uint8_t>(number >> n));

	} while (askToContinue());

	return 0;
}