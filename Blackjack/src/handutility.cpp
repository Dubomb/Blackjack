//
// file: handutility.cpp
//
// Implementation of the Hand class
// Creates functionality for dealing with player hands
//
// @author Philip Napoli
//

#include "handutility.h"

const int BLACKJACK = 21; ///< Card sum of a blackjack

/// Initializes the player's hand and member variables
Hand::Hand()
	: hand_total(0), ace_count(0)
{
	hand.reserve(4);
}

/// Adds a card to the player hand and calculates resulting sum
std::string Hand::add_card(int card)
{
	int card_number = hand.emplace_back(card);

	if (card == 1)
	{
		hand_total += 11;
		ace_count++;
	}
	else
	{
		hand_total += std::clamp(card, 1, 10);
	}

	// Checks if an ace value of 11 must be converted to a 1
	if (hand_total > BLACKJACK && ace_count > 0)
	{
		hand_total -= 10;
		ace_count--;
	}

	return get_card_string(card_number);
}

/// Clears the hand vector and resets total and ace count
void Hand::clear_hand()
{
	hand.clear();
	hand_total = 0;
	ace_count = 0;
}

/// Returns the sum of the player's hand
int Hand::get_total() const
{
	return hand_total;
}

/// Returns the string of a card in the player's hand
std::string Hand::get_card_string(int card) const
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

/// Converts the player's entire hand to a string
std::string Hand::get_hand_string() const
{
	std::string s = "";

	for (int card : hand)
	{
		s += get_card_string(card) + " ";
	}

	return s;
}