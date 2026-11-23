#include <iostream>
#include <limits>
#include <cmath>
#include <utility>

float max(const float* array, int n)
{
	float largest = std::numeric_limits<float>::lowest();

	for (int i = 0; i < n; i++)
	{
		if (array[i] > largest)
		{
			largest = array[i];
		}
	}

	return largest;
}

float min(const float* array, int n)
{
	float smallest = std::numeric_limits<float>::max();

	for (int i = 0; i < n; i++)
	{
		if (array[i] < smallest)
		{
			smallest = array[i];
		}
	}

	return smallest;
}

float sum(const float* array, int n)
{
	float total = 0;

	for (int i = 0; i < n; i++)
	{
		total += array[i];
	}

	return total;
}

float mean(const float* array, int n)
{
	return sum(array, n) / n;
}

float var(const float* array, int n)
{
	float average = mean(array, n);
	float result = 0;

	for (int i = 0; i < n; i++)
	{
		float difference = (array[i] - average);
		result += difference * difference;
	}

	return result / n;
}

float stdDev(const float* array, int n)
{
	
	return std::sqrt(var(array, n));
}

void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readSizeOfArray()
{
	int n;

	std::cout << "Please enter the number of elements of the array: ";
	std::cin >> n;

	while (std::cin.fail() || std::cin.peek() != '\n' || n < 1)
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the number of elements of the array: ";
		std::cin >> n;
	}

	return n;
}

float readValue(int i)
{
	float v;

	std::cout << "Please enter the value of [ " << i << " ]: ";
	std::cin >> v;

	while (std::cin.fail() || std::cin.peek() != '\n')
	{
		clearInput();

		std::cerr << "ERROR: Invalid input." << std::endl;
		std::cout << "Please enter the value of [ " << i << " ]: ";
		std::cin >> v;
	}

	return v;
}

template <typename T>
void bubbleSort(T* arr, int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		bool swapped = false;

		for (int j = 0; j < n - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				T tmp = std::move(arr[j]);
				arr[j] = std::move(arr[j + 1]);
				arr[j + 1] = std::move(tmp);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

int main()
{
	int n = readSizeOfArray();
	float* array = new float[n];

	for (int i = 0; i < n; i++)
	{
		array[i] = readValue(i);
	}

	std::cout << "Max: " << max(array, n) << std::endl;
	std::cout << "Min: " << min(array, n) << std::endl;
	std::cout << "Sum: " << sum(array, n) << std::endl;
	std::cout << "Mean: " << mean(array, n) << std::endl;
	std::cout << "Variance: " << var(array, n) << std::endl;
	std::cout << "Standard deviation: " << stdDev(array, n) << std::endl;

	bubbleSort(array, n);

	std::cout << "Your array sorted is: [ ";
	for (int i = 0; i < n; i++)
	{
		if (i > 0) std::cout << ", ";
		std::cout << array[i];
	}
	std::cout << " ]." << '\n';

	delete[] array;
	return 0;
}