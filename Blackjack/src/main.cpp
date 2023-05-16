#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>

#include "handutility.h"
#include "deckutility.h"

const int STARTING_MONEY = 100;
const int BLACKJACK = 21;
const int BLACKJACK_MULTIPLIER = 3;
const int WIN_MULTIPLIER = 2;
const int DEALER_LIMIT = 17;

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

	Deck current_deck;

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

			current_deck.shuffle();

			std::cout << "Drawing cards!\n\n";

			while (current_deck.get_cards_drawn() < 2)
			{
				player_hand.add_card(current_deck.draw_card());
			}

			dealer_hand.add_card(current_deck.draw_card());

			std::cout << "Your hand is: " << player_hand.get_hand_string();

			std::cout << "Your total is: " << player_hand.get_total() << "\n\n";

			std::cout << "The dealer's hand is: " << dealer_hand.get_hand_string() << "\n";

			while (player_hand.get_total() < BLACKJACK)
			{
				std::cout << "\nType \"hit\" to take another card or \"stand\" to end your turn.\n";

				std::getline(std::cin, command);

				if (!command.compare("hit"))
				{
					std::string card_string = player_hand.add_card(current_deck.draw_card());

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
				std::string card_string = dealer_hand.add_card(current_deck.draw_card());

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