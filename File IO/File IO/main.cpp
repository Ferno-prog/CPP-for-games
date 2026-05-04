#include <fstream>
#include <iostream>

struct highscore
{
	char name[4];
	uint32_t score;
};

int main()
{
	//Write ascii file.
	{
		std::ofstream highscores("highscores.txt");
		if (!highscores)
		{
			std::cerr << "ERROR: Could not open file for writing." << std::endl;
			return 1;
		}

		highscores << "Kaw " << 2007 << std::endl;
		highscores << "Fer " << 2012 << std::endl;
		highscores << "Ted " << 102 << std::endl;

		if (highscores.bad())
		{
			std::cerr << "ERROR: An error accured while writing to the file.";
			return 1;
		}

		highscores.close();
		// File will close when it goes out of scope.
	}

	{
		std::ofstream highscores("highscores.txt", std::ios::app);
		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;
			return 1;
		}

		highscores << "Jer " << 1967 << std::endl;

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to write to file." << std::endl;
			return 1;
		}

		highscores.close();
	}
	{
		std::ifstream highscores("highscores.txt");
		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;
			return 1;
		}

		char name[4];
		int score;
		while (highscores >> name >> score)
		{
			std::cout << name << " " << score << std::endl;
		}

		if (highscores.bad())
		{
			std::cerr << "ERROR: Reading the file" << std::endl;
			return 1;
		}

		highscores.close();
		// File will be closed when it goes out of scope.
	}

	{
		std::ofstream highscores("highscores.bin", std::ios::binary);
		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;
			return 1;
		}

		highscore scores[] = {
		{"Kaw", 2007},
		{"Fer", 2012},
		{"Ted", 102 },
		{"Jer", 1967}
		};
		auto numScores = std::size(scores);

		highscores.write(reinterpret_cast<const char*>(&numScores), sizeof(numScores));
		highscores.write(reinterpret_cast<const char*>(scores), numScores * sizeof(highscore));

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to write to file." << std::endl;
			return 1;
		}
		highscores.close();
		// File will be closed when it goes out of scope.
	}

	std::cout << std::endl;

	{
		std::ifstream highscores("highscores.bin", std::ios::binary);
		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;
			return 1;
		}

		size_t numEntries;
		highscores.read(reinterpret_cast<char*>(&numEntries), sizeof(numEntries));

		highscore* scores = new highscore[numEntries];

		highscores.read(reinterpret_cast<char*>(scores), numEntries * sizeof(highscore));

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to read from file." << std::endl;
			return 1;
		}

		for (int i = 0; i < numEntries; ++i)
		{
			std::cout << scores[i].name << " " << scores[i].score << std::endl;
		}

		delete[] scores;
		highscores.close(); // Return any system resources.

	}

	return 0;
}