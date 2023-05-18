// 
// file: deckutility.h
// 
// Header file for the Deck class
// Provides functions to simulate drawing cards from a deck
// 
// @author Philip Napoli
// 

#pragma once

#include <random>

/// Class representing a deck of 52 cards
/// Provides functions for drawing and shuffling the deck
class Deck
{
public:
	/// Constructor for initializing the deck of cards for usage
	Deck();

	/// Randomizes the order of the cards in the deck
	/// Resets the position in the deck to begin drawing from the top
	void shuffle();

	/// Removes a card from the deck and provides the removed card
	/// Reshuffles the deck if the last card has been drawn
	/// 
	/// @return A numerical representation of the card that was removed
	int draw_card();

	/// Provides the number of cards that have been drawn from the deck
	/// 
	/// @return The number of cards drawn
	int get_cards_drawn() const;

private:
	static const std::array<int, 52> start_deck; ///< Unshuffled deck of cards

	std::array<int, 52> current_deck; ///< Current deck in use
	int current_card; ///< Current card in the deck to reveal

	std::random_device device; ///< Uniform random number device
	std::default_random_engine generator; ///< RNG for shuffling
};