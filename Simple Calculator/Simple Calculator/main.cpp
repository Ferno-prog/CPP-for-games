#include <iostream>

int main()
{
	float leftoperand;
	char operator1;
	float righttoperand;

	//get valid leftoperand
	std::cout << "Please enter a number: ";
	std::cin >> leftoperand;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Please enter a valid number: ";
		std::cin >> leftoperand;
	}

	//get valid operator
	std::cout << "Please enter an operator: ";
	std::cin >> operator1;
	while (operator1 != '+' && operator1 != '-' && operator1 != '*' && operator1 != '/')
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Please enter a valid operator: ";
		std::cin >> operator1;
	}

	//get valid righttoperand
	std::cout << "Please enter a number: ";
	std::cin >> righttoperand;
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cout << "Please enter a valid number: ";
		std::cin >> righttoperand;
	}

	if (operator1 == '+')
	{
		std::cout << leftoperand + righttoperand;
	}
	else if (operator1 == '-')
	{
		std::cout << leftoperand - righttoperand;
	}
	else if (operator1 == '*')
	{
		std::cout << leftoperand * righttoperand;
	}
	else if (operator1 == '/')
	{
		std::cout << leftoperand / righttoperand;
	}
	else
	{
		std::cout << "ERROR: An error has occurred.";
	}


	//prevents the terminal from automatically closing
	std::cout << "\nPress enter to continue..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin.get();

	return 0;
}