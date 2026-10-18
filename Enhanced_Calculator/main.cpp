#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <cctype>

//https://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/

bool isNumber(const std::string& token)
{
	return std::isdigit(static_cast<unsigned char>(token[0])) || (token.size() > 1 && (token[0] == '-' || token[0] == '+') && std::isdigit(static_cast<unsigned char>(token[1])));
}

bool isOperator(const std::string& token)
{
	return token == "+" || token == "-" || token == "*" || token == "/" || token == "%" || token == "^";
}

int getPrecedence(const std::string& token)
{
	if (token == "^")
	{
		return 3;
	}
	else if (token == "/" || token == "*" || token == "%")
	{
		return 2;
	}
	else if (token == "+" || token == "-")
	{
		return 1;
	}

	return -1;
}

bool isRightAssociative(const std::string& token)
{
	return token == "^";
}

std::vector<std::string> getInput()
{
	std::string input;
	std::vector<std::string> tokens;

	std::cout << "Please enter a sum (every number, operator and bracket has to be space separated and the sum has to end with =): ";

	while (std::cin >> input)
	{
		if (input == "=")
		{
			break;
		}
		tokens.push_back(input);
	}
	return tokens;
}

std::vector<std::string> toRPN(std::vector<std::string>& tokens)
{
	std::vector<std::string> output;
	std::vector<std::string> operatorStack;
	for (int i = 0; i < tokens.size(); ++i)
	{
		std::string token = tokens[i];

		if (isNumber(token))
		{
			output.push_back(token);
		}
		else if (token == "(")
		{
			operatorStack.push_back(token);
		}
		else if (token == ")")
		{
			while (!operatorStack.empty() && operatorStack.back() != "(")
			{
				output.push_back(operatorStack.back());
				operatorStack.pop_back();
			}

			if (operatorStack.empty())
			{
				std::cout << "ERROR: No matching parenthesis found." << std::endl;
				return std::vector<std::string>();
			}
			operatorStack.pop_back();
		}
		else if (isOperator(token))
		{
			while (!operatorStack.empty() && 
				(getPrecedence(token) < getPrecedence(operatorStack.back()) ||
				(getPrecedence(token) == getPrecedence(operatorStack.back()) && !isRightAssociative(token))))
			{
				output.push_back(operatorStack.back());
				operatorStack.pop_back();
			}
			operatorStack.push_back(token);
		}
		else
		{
			std::cout << "ERROR: No match was found for this token." << std::endl;
			return std::vector<std::string>();
		}

	}
	while (!operatorStack.empty())
	{
		output.push_back(operatorStack.back());
		operatorStack.pop_back();
	}
	return output;
}

float solveRPN(const std::vector<std::string>& RPN)
{
	std::vector<float> stack;

	for (int i = 0; i < RPN.size(); ++i)
	{
		if (isNumber(RPN[i]))
		{
			stack.push_back(std::stof(RPN[i]));
		}
		else if (isOperator(RPN[i]))
		{
			float leftOperand;
			float rightOperand;

			if (stack.size() < 2)
			{
				std::cout << "ERROR: Missing operand." << std::endl;
				return std::numeric_limits<float>::quiet_NaN();
			}

			rightOperand = stack.back();
			stack.pop_back();
			leftOperand = stack.back();
			stack.pop_back();

			if (RPN[i] == "+")
			{
				stack.push_back(leftOperand + rightOperand);
			}
			else if (RPN[i] == "-")
			{
				stack.push_back(leftOperand - rightOperand);
			}
			else if (RPN[i] == "*")
			{
				stack.push_back(leftOperand * rightOperand);
			}
			else if (RPN[i] == "/")
			{
				if (rightOperand == 0.0f)
				{
					std::cout << "ERROR: Can't divide by 0." << std::endl;;
					return std::numeric_limits<float>::quiet_NaN();
				}
				stack.push_back(leftOperand / rightOperand);
			}
			else if (RPN[i] == "^")
			{
				stack.push_back(std::pow(leftOperand, rightOperand));
			}
			else if (RPN[i] == "%")
			{
				if (rightOperand == 0.0f)
				{
					std::cout << "ERROR: Can't modulo by 0." << std::endl;
					return std::numeric_limits<float>::quiet_NaN();
				}
				stack.push_back(std::fmod(leftOperand, rightOperand));
			}
			else
			{
				std::cout << "ERROR: Something went massively wrong." << std::endl;
				return std::numeric_limits<float>::quiet_NaN();
			}
		}
		else
		{
			std::cout << "ERROR: Invalid input." << std::endl;
			return std::numeric_limits<float>::quiet_NaN();
		}

	}
	if (stack.size() != 1)
	{
		std::cout << "ERROR: Invalid expression." << std::endl;
		return std::numeric_limits<float>::quiet_NaN();
	}
	return stack.back();
}

void printVector(const std::vector<std::string>& tokens)
{
	for (int i = 0; i < tokens.size(); ++i)
	{
		std::cout << tokens[i] << std::endl;
	}
}

int main()
{
	while (std::cin)
	{
		std::vector<std::string> tokens = getInput();
		float result = solveRPN(toRPN(tokens));
		if (!std::isnan(result))
		{
			std::cout << result << std::endl;
		}
	}
	return 0;
}