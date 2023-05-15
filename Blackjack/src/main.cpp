#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>

constexpr int STARTING_MONEY = 100;

const std::array<int, 52> deck = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
									6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 
									11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13 };

int get_bet(int money)
{
	std::string command;

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
			continue;
		}

		if (bet > 0 && bet <= money)
		{
			break;
		}

		std::cout << "Please enter a valid bet!\n";
	}

	return bet;
}

std::string get_card_string(int card)
{
	switch (card)
	{
	case 1:
		return "A";
	case 11:
		return "J";
	case 12:
		return "Q";
	case 13:
		return "K";
	default:
		return std::to_string(card);
	}
}

void print_hand(const std::vector<int>& hand)
{
	std::cout << "Current hand is: ";

	for (int card : hand)
	{
		std::cout << get_card_string(card) << " ";
	}

	std::cout << "\n";
}

int main()
{
	std::cout << "Welcome to blackjack!\n";

	bool running = true;

	int money = STARTING_MONEY;

	std::random_device device;
	std::default_random_engine generator(device());

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

			int bet = get_bet(money);

			money -= bet;

			std::cout << "Remaining money: $" << money << "\n";

			std::cout << "Let's begin!\n";

			std::vector<int> hand;
			hand.reserve(4);

			std::vector<int> current_deck(deck.begin(), deck.end());
			std::shuffle(current_deck.begin(), current_deck.end(), generator);

			std::cout << "Drawing cards!\n";

			print_hand(current_deck);
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}
	}

	return 0;
}