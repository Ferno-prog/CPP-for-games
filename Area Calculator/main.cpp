#include <iostream>
#include <limits>
#include <cmath>

const float PI = 3.141592653f;

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char getShape()
{
	char shape;

	std::cout << "Please enter a shape (circle(C), square(S), rectangle(R), triangle(T)): ";
	std::cin >> shape;
	clearInput();

	while (shape != 'C' && shape != 'S' && shape != 'R' && shape != 'T')
	{
		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter a shape (circle(C), square(S), rectangle(R), triangle(T)): ";
		std::cin >> shape;
		clearInput();
	}

	return shape;
}

void outputCircleData()
{
	double r;

	std::cout << "Please enter the radius: ";
	std::cin >> r;

	while (std::cin.fail() || r <= 0)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the radius: ";
		std::cin >> r;
	}

	std::cout << "The circumference of the circle is " << 2 * PI * r << '\n';
	std::cout << "The area of the circle is " << PI * r * r << '\n';
}

void outputSquareData()
{
	double s;

	std::cout << "Please enter the length: ";
	std::cin >> s;

	while (std::cin.fail() || s <= 0)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the length: ";
		std::cin >> s;
	}

	std::cout << "The perimeter of the square is " << 4 * s << '\n';
	std::cout << "The area of the square is " << s * s << '\n';
}

void outputRectangleData()
{
	double w;
	double h;

	std::cout << "Please enter the width: ";
	std::cin >> w;

	while (std::cin.fail() || w <= 0)
	{
		clearInput();
		
		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the width: ";
		std::cin >> w;
	}

	std::cout << "Please enter the height: ";
	std::cin >> h;

	while (std::cin.fail() || h <= 0)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the height: ";
		std::cin >> h;
	}

	std::cout << "The perimeter of the rectangle is " << 2 * w + 2 * h << '\n';
	std::cout << "The area of the rectangle is " << w * h << '\n';
}

void outputTriangleData()
{
	double b;
	double h;

	std::cout << "Please enter the base: ";
	std::cin >> b;

	while (std::cin.fail() || b <= 0)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the base: ";
		std::cin >> b;
	}

	std::cout << "Please enter the height: ";
	std::cin >> h;

	while (std::cin.fail() || h <= 0)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the height: ";
		std::cin >> h;
	}

	std::cout << "The perimeter of the right triangle is " << b + h + std::sqrt(b * b + h * h) << '\n';
	std::cout << "The area of the triangle is " << b * h / 2 << '\n';
}

void outputShapeData(const char shape)
{
	switch (shape)
	{
	case '1':
	case 'c':
	case 'C':
		outputCircleData();
		break;
	case '2':
	case 's':
	case 'S':
		outputSquareData();
		break;
	case '3':
	case 'r':
	case 'R':
		outputRectangleData();
		break;
	case '4':
	case 't':
	case 'T':
		outputTriangleData();
		break;
	default:
		break;
	}
}

int main()
{
	outputShapeData(getShape());
	return 0;
}