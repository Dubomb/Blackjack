// 
// file: main.cpp
// 
// Main program code for the blackjack game
// Handles the main gameplay loop, user input, and console output
//
// @author Philip Napoli
// 

#include <iostream>

#include "handutility.h"
#include "deckutility.h"

const int STARTING_MONEY = 100; ///< Money that the player starts with
const int BLACKJACK = 21; ///< The value representing a blackjack
const int BLACKJACK_MULTIPLIER = 3; ///< The multiplier for bet after blackjack
const int WIN_MULTIPLIER = 2; ///< The multiplier for bet after winning
const int LOSE_MULTIPLIER = 0; ///< The multipler for bet after losing
const int TIE_MULTIPLIER = 1; ///< The multiplier for bet after tying
const int DEALER_LIMIT = 17; ///< The value that the dealer draws until

/// Gets user input until a valid bet is received
/// A valid bet is less than or equal to money and greater than zero
/// 
/// @param money The money that the player has
/// @return the bet input by the player
int get_bet(int money)
{
	std::string command;

	int bet = 0;

	while (true)
	{
		std::getline(std::cin, command);

		// Attempts to convert the input to an integer
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

/// Performs the initial draws for the player and dealer
/// The player draws two cards and the dealer draws one card
/// Additionally, handles output for this phase of the game
/// 
/// @param deck The deck to draw from
/// @param player_hand The player's hand to put cards into
/// @param dealer_hand The dealer's hand to put cards into
void initial_draw(Deck& deck, Hand& player_hand, Hand& dealer_hand)
{
	player_hand.clear_hand();
	dealer_hand.clear_hand();

	std::cout << "Drawing cards!\n\n";

	player_hand.add_card(deck.draw_card());
	player_hand.add_card(deck.draw_card());
	std::cout << "Your hand is: " << player_hand.get_hand_string() << "\n";
	std::cout << "Your total is: " << player_hand.get_total() << "\n\n";

	dealer_hand.add_card(deck.draw_card());
	std::cout << "The dealer's hand is: " << dealer_hand.get_hand_string() << "\n\n";
}

/// Performs the player's phase of the game
/// Receives input from the player and adds cards to the player's hand
/// Ends once blackjack is met/exceeded, or until the player chooses to stand
/// 
/// @param deck The deck to draw cards from
/// @param player_hand The player's hand to put cards into
void player_phase(Deck & deck, Hand& player_hand)
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

/// Performs the dealers's phase of the game
/// Ends once the dealer threshold is exceeded
/// 
/// @param deck The deck to draw cards from
/// @param player_hand The dealers's hand to put cards into
void dealer_phase(Deck& deck, Hand& dealer_hand)
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

/// Handles the main gameplay of blackjack
/// Invokes helper functions for card draws and compares final hand totals
/// 
/// @param deck The deck to draw cards from
/// @return The amount to multiply the player's bet by based on the outcome
int play(Deck& deck)
{
	Hand player_hand;
	Hand dealer_hand;

	initial_draw(deck, player_hand, dealer_hand);

	player_phase(deck, player_hand);
	int final_player_total = player_hand.get_total();

	// Comparison if the player has blackjack or has exceeded the limit
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

	// Comparison between the dealer's hand and player's hand
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

/// Begins the main gameplay loop for blackjack
/// Handles the player's bet and money
/// Also calculates the player's winnings after each round
/// Ends the loop if the player wishes to stop or runs out of money
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

			// Multiplies the bet by the multipler and adds it to the total
			int win_multiplier = play(current_deck);
			money += bet * win_multiplier;
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}
	}
}

/// The main function that begins the main game loop
int main()
{
	std::cout << "Welcome to blackjack!\n";

	start_game();

	std::cout << "\nThanks for playing!\n";

	return 0;
}