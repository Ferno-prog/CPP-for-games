#include <iostream>
#include <string>
#include <limits>

int main()
{

	std::string name;
	int age = 0;

	std::cout << "Please enter your name: ";
	std::cin >> name;

	std::cout << "Please enter your age: ";
	std::cin >> age;

	while (std::cin.fail() || age < 0)
	{
		std::cout << "ERROR: Invalid answer." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Please enter your age: ";
		std::cin >> age;
	}

	if (age < 25)
	{
		std::cout << "Hello, " << name << ". You are only " << age << " years old." << std::endl;
	}
	else if (age < 50)
	{
		std::cout << "Hello, " << name << ". You are already " << age << " years old." << std::endl;
	}
	else
	{
		std::cout << "Hello, " << name << ". You are very wise for " << age << " years old." << std::endl;
	}

	return 0;
}