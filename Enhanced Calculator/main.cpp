#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

enum class TokenType {
	Number,
	Operator,
	leftParenthesis,
	rightParenthesis
};

enum class Associativity {
	Left,
	Right
};

struct Token {
	TokenType type;
	std::string text;
};

struct OperatorInfo {
	int precedence;
	Associativity associativity;
};

static const std::unordered_map<char, OperatorInfo> operators = {
	{'+', {1, Associativity::Left}},
	{'-', {1, Associativity::Left}},
	{'*', {2, Associativity::Left}},
	{'/', {2, Associativity::Left}},
	{'%', {2, Associativity::Left}},
	{'^', {3, Associativity::Right}}
};

int main()
{
	std::string input;
	std::vector<Token> tokens;

	std::getline(std::cin >> std::ws, input);

	for (size_t i = 0; i < input.size(); ++i)
	{
		if (std::isspace(input[i]))
		{
			continue;
		}
		else if (std::isdigit(input[i]))
		{
			std::string number;

			while (i < input.size() && (std::isdigit(input[i]) || std::isspace(input[i])))
			{
				if (std::isspace(input[i]))
				{
					i++;
					continue;
				}
				number += input[i];
				i++;
			}

			tokens.push_back({ TokenType::Number, number });
			i--;
		}
		else if (operators.contains(input[i]))
		{
			tokens.push_back({ TokenType::Operator, std::string(1, input[i])});
		}
	}

	for (size_t i = 0; i < tokens.size(); ++i)
	{
		std::cout << tokens[i].text << std::endl;
	}

	return 0;
}