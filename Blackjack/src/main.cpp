#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>

#include "handutility.h"

const int STARTING_MONEY = 100;
const int BLACKJACK = 21;
const int BLACKJACK_MULTIPLIER = 3;
const int WIN_MULTIPLIER = 2;
const int DEALER_LIMIT = 17;

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

int main()
{
	std::cout << "Welcome to blackjack!\n";

	bool running = true;

	int money = STARTING_MONEY;

	std::random_device device;
	std::default_random_engine generator(device());

	while (running && money > 0)
	{
		std::string command;

		Hand player_hand;
		Hand dealer_hand;

		std::cout << "\nType \"quit\" to stop or \"play\" to play.\n";

		std::getline(std::cin, command);

		if (!command.compare("quit"))
		{
			running = false;
		}
		else if (!command.compare("play"))
		{
			std::cout << "\nHow much would you like to bet? You have $" << money << "\n";

			int bet = get_bet(money);

			money -= bet;

			std::cout << "\nRemaining money: $" << money << "\n\n";

			std::array<int, 52> current_deck(deck);
			std::shuffle(current_deck.begin(), current_deck.end(), generator);

			std::cout << "Drawing cards!\n\n";

			int current_card = 0;

			while (current_card < 2)
			{
				player_hand.add_card(current_deck, current_card);
			}

			dealer_hand.add_card(current_deck, current_card);

			std::cout << "Your hand is: " << player_hand.get_hand_string();

			std::cout << "Your total is: " << player_hand.get_total() << "\n\n";

			std::cout << "The dealer's hand is: " << dealer_hand.get_hand_string() << "\n";

			while (player_hand.get_total() < BLACKJACK)
			{
				std::cout << "\nType \"hit\" to take another card or \"stand\" to end your turn.\n";

				std::getline(std::cin, command);

				if (!command.compare("hit"))
				{
					std::string card_string = player_hand.add_card(current_deck, current_card);

					std::cout << "\nYou drew a " << card_string << "!\n";
					std::cout << "Your hand is " << player_hand.get_hand_string() << "\n";

					std::cout << "Your total is: " << player_hand.get_total() << "\n";
				}
				else if (!command.compare("stand"))
				{
					break;
				}
				else
				{
					std::cout << "Unknown input. Please enter a valid command.\n";
				}
			}

			int final_player_total = player_hand.get_total();

			if (final_player_total == BLACKJACK)
			{
				std::cout << "\nYou have blackjack!\n";

				money += bet * BLACKJACK_MULTIPLIER;
				continue;
			}
			else if (final_player_total > BLACKJACK)
			{
				std::cout << "\nYou bust!\n";
				continue;
			}

			while (dealer_hand.get_total() < DEALER_LIMIT)
			{
				std::string card_string = dealer_hand.add_card(current_deck, current_card);

				std::cout << "\nDealer drew a " << card_string << "!\n";
				std::cout << "Dealer hand is " << dealer_hand.get_hand_string() << "\n";

				std::cout << "Dealer total is " << dealer_hand.get_total() << "\n";
			}

			int final_dealer_total = dealer_hand.get_total();

			if (dealer_hand.get_total() > BLACKJACK)
			{
				std::cout << "\nDealer bust!\n";
				money += bet * WIN_MULTIPLIER;
			}
			else if (final_dealer_total > final_player_total)
			{
				std::cout << "\nDealer wins!\n";
			}
			else if (final_dealer_total < final_player_total)
			{
				std::cout << "\nYou win!\n";

				money += bet * WIN_MULTIPLIER;
			}
			else
			{
				std::cout << "\nTied with the dealer! No winner.\n";
				money += bet;
			}
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}
	}

	std::cout << "\nThanks for playing!\n";

	return 0;
}