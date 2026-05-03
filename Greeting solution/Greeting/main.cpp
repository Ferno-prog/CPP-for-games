#include <iostream>
#include <string>
#include <limits>

int main()
{

	std::string name;
	int age;

	std::cout << "Please enter your name: ";
	std::cin >> name;

	std::cout << "Please enter your age: ";
	std::cin >> age;

	while (age < 0 || std::cin.fail())
	{
		std::cout << "ERROR: Invalid answer." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		std::cout << "Please enter your age: ";
		std::cin >> age;
	}

	std::cout << "Hello, " << name << ". You are " << age << " years old." << std::endl;

	std::cout << "Press enter to continue..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}