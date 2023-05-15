#include <iostream>
#include <string>

constexpr int STARTING_MONEY = 100;

int main()
{
	std::cout << "Welcome to blackjack!\n";

	bool running = true;

	int money = STARTING_MONEY;

	while (running)
	{
		std::string command;

		std::cout << "Type \"quit\" to stop or \"play\" to play.\n";

		std::getline(std::cin, command);

		if (!command.compare("quit"))
		{
			running = false;
		}
		else if (!command.compare("play"))
		{
			std::cout << "How much would you like to bet? You have $" << money << "\n";

			int bet = 0;

			while (true)
			{
				std::getline(std::cin, command);

				try
				{
					bet = std::stoi(command);
				}
				catch (...)
				{
					std::cout << "Bad input!\n";
				}

				if (bet > 0 && bet <= money)
				{
					break;
				}

				std::cout << "Please enter a valid bet!\n";
			}

			money -= bet;

			std::cout << "Remaining money: $" << money << "\n";
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}
	}

	return 0;
}