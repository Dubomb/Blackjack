// 
// file: deckutility.cpp
// 
// Implementation of the Deck class
// Provides functions to simulate drawing cards from a deck
// 
// @author Philip Napoli
// 

#include "deckutility.h"

/// Initializes the random number generator
/// Also sets the current deck to the start deck and current card to the start
Deck::Deck()
	: current_card(0)
{
	generator = std::default_random_engine(device());
	current_deck = std::array<int, 52>(Deck::start_deck);
}

/// Randomizes the order of the cards in the deck
/// Resets the current card to reveal back to the start
void Deck::shuffle()
{
	std::shuffle(current_deck.begin(), current_deck.end(), generator);

	current_card = 0;
}

/// Draws a card from the deck and returns the numerical value
/// If the last card in the deck has been drawn, the deck is reshuffled
int Deck::draw_card()
{
	int card = current_deck[current_card];

	current_card++;

	if (current_card >= 52)
	{
		shuffle();
	}

	return card;
}

/// Returns the number of cards that have been drawn from the current deck
int Deck::get_cards_drawn() const
{
	return current_card;
}

// 1: Ace
// 2-10: Respective values
// 11: Jack
// 12: Queen
// 13: King
const std::array<int, 52> Deck::start_deck = 
		{ 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
		6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10,
		11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13 };