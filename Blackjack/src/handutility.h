// 
// file: handutility.h
// 
// Header file for the Hand class
// Provides several functions for managing cards and getting card information
// 
// @author Philip Napoli
// 

#pragma once

#include <string>
#include <vector>

/// Class representing a player's hand
/// Provides functionality for managing a player's hand
class Hand
{
public:
	/// Constructor for initializing the player's hand
	/// Sets member variable values and reserves some memory for cards
	Hand();
	
	/// Adds a card to the player's hand and increases the sum of the cards
	/// This function accounts for aces in the deck
	/// 
	/// @param card The card to add to the player's hand
	/// @return The string representation of the card
	std::string add_card(int card);

	/// Clears all cards from the players hand
	/// Also resets member variables to their appropriate starting values
	void clear_hand();

	/// Provides the total value of all of the cards in the hand
	/// 
	/// @return The sum of the cards in the player's hand
	int get_total() const;

	/// Provides the string representation of a player's card
	/// For instance, the card number representing an ace will become "A"
	/// Numbers that are already valid will simply be returned in string form
	/// 
	/// @param card The card number to get the string of
	/// @return The string representation of the card
	std::string get_card_string(int card) const;

	/// Gathers the string representation of each card in the player's hand
	/// The string will contain the strings of every card, space separated
	/// 
	/// @return A string representing the entire hand of the player
	std::string get_hand_string() const;

private:
	std::vector<int> hand;	///< The card values for the player's hand
	int hand_total;			///< The sum of cards in the hand
	int ace_count;			///< The number of aces in the hand
};