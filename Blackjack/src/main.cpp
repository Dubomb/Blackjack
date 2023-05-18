#include <iostream>

#include "handutility.h"
#include "deckutility.h"

const int STARTING_MONEY = 100;
const int BLACKJACK = 21;
const int BLACKJACK_MULTIPLIER = 3;
const int WIN_MULTIPLIER = 2;
const int LOSE_MULTIPLIER = 0;
const int TIE_MULTIPLIER = 1;
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

void initial_draw(Deck& deck, Hand& player_hand, Hand& dealer_hand)
{
	player_hand.clear_hand();
	dealer_hand.clear_hand();

	std::cout << "Drawing cards!\n\n";

	player_hand.add_card(deck.draw_card());
	player_hand.add_card(deck.draw_card());

	dealer_hand.add_card(deck.draw_card());

	std::cout << "Your hand is: " << player_hand.get_hand_string() << "\n";
	std::cout << "Your total is: " << player_hand.get_total() << "\n\n";

	std::cout << "The dealer's hand is: " << dealer_hand.get_hand_string() << "\n\n";
}

int player_phase(Deck & deck, Hand& player_hand)
{
	int current_round = 1;
	std::string command;

	while (player_hand.get_total() < BLACKJACK)
	{
		std::cout << "=====> PLAYER ROUND " << current_round << " <=====\n\n";

		std::cout << "Type \"hit\" to take another card or \"stand\" to end your turn.\n";

		std::getline(std::cin, command);

		if (!command.compare("hit"))
		{
			std::string card_string = player_hand.add_card(deck.draw_card());

			std::cout << "\nYou drew a " << card_string << "!\t\t";
			std::cout << "Your hand is " << player_hand.get_hand_string() << "\n";

			std::cout << "Your total is: " << player_hand.get_total() << "\n\n";
		}
		else if (!command.compare("stand"))
		{
			std::cout << "\n";
			break;
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}

		current_round++;
	}
}

int dealer_phase(Deck& deck, Hand& dealer_hand)
{
	int current_round = 1;

	while (dealer_hand.get_total() < DEALER_LIMIT)
	{
		std::cout << "=====> DEALER ROUND " << current_round << " <=====\n";

		std::string card_string = dealer_hand.add_card(deck.draw_card());

		std::cout << "\nDealer drew a " << card_string << "!\t\t";
		std::cout << "Dealer hand is " << dealer_hand.get_hand_string() << "\n";

		std::cout << "Dealer total is " << dealer_hand.get_total() << "\n\n";

		current_round++;
	}
}

int play(Deck& deck)
{
	Hand player_hand;
	Hand dealer_hand;

	initial_draw(deck, player_hand, dealer_hand);

	player_phase(deck, player_hand);
	int final_player_total = player_hand.get_total();

	if (final_player_total == BLACKJACK)
	{
		std::cout << "You have blackjack!\n";
		return BLACKJACK_MULTIPLIER;
	}
	else if (final_player_total > BLACKJACK)
	{
		std::cout << "You bust!\n";
		return LOSE_MULTIPLIER;
	}

	dealer_phase(deck, dealer_hand);
	int final_dealer_total = dealer_hand.get_total();

	if (dealer_hand.get_total() > BLACKJACK)
	{
		std::cout << "Dealer bust! You win!\n";
		return WIN_MULTIPLIER;
	}
	else if (final_dealer_total > final_player_total)
	{
		std::cout << "Dealer wins!\n";
		return LOSE_MULTIPLIER;
	}
	else if (final_dealer_total < final_player_total)
	{
		std::cout << "You win!\n";
		return WIN_MULTIPLIER;
	}
	else
	{
		std::cout << "Tied with the dealer! No winner.\n";
		return TIE_MULTIPLIER;
	}
}

void start_game()
{
	bool running = true;
	int money = STARTING_MONEY;

	Deck current_deck;
	current_deck.shuffle();

	std::string command;

	while (running && money > 0)
	{
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

			int win_multiplier = play(current_deck);
			money += bet * win_multiplier;
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}
	}
}

int main()
{
	std::cout << "Welcome to blackjack!\n";

	start_game();

	std::cout << "\nThanks for playing!\n";

	return 0;
}