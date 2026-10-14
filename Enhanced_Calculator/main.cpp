#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>

//https://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/

bool isNumber(const std::string& token)
{
	return std::isdigit(token[0]) || (token.size() > 1 && (token[0] == '-' || token[0] == '+') && std::isdigit(token[1]));
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

	std::cout << "Please enter a sum (every number, operator and bracket has to be space seperated and the sum has to end with =): ";

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
			operatorStack.pop_back();
		}
		else if (isOperator(token) && (operatorStack.empty() || operatorStack.back() == "("))
		{
			operatorStack.push_back(token);
		}
		else if (isOperator(token) && !operatorStack.empty() &&
			(getPrecedence(token) > getPrecedence(operatorStack.back()) ||
			(getPrecedence(token) == getPrecedence(operatorStack.back()) && isRightAssociative(token))))
		{
			operatorStack.push_back(token);
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
			float leftOperant;
			float rightOperant;

			rightOperant = stack.back();
			stack.pop_back();
			leftOperant = stack.back();
			stack.pop_back();

			if (RPN[i] == "+")
			{
				stack.push_back(leftOperant + rightOperant);
			}
			else if (RPN[i] == "-")
			{
				stack.push_back(leftOperant - rightOperant);
			}
			else if (RPN[i] == "*")
			{
				stack.push_back(leftOperant * rightOperant);
			}
			else if (RPN[i] == "/")
			{
				if (rightOperant == 0.0f)
				{
					std::cout << "ERROR: Cant divide by 0." << std::endl;;
					return std::numeric_limits<float>::quiet_NaN();
				}
				stack.push_back(leftOperant / rightOperant);
			}
			else if (RPN[i] == "^")
			{
				stack.push_back(std::pow(leftOperant, rightOperant));
			}
			else if (RPN[i] == "%")
			{
				if (rightOperant == 0.0f)
				{
					std::cout << "ERROR: Cant modulo by 0." << std::endl;
					return std::numeric_limits<float>::quiet_NaN();
				}
				stack.push_back(std::fmod(leftOperant, rightOperant));
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
	while (true)
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