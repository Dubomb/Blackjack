#include "deckutility.h"

#include <iostream>

Deck::Deck()
	: current_card(0)
{
	generator = std::default_random_engine(device());
}

void Deck::shuffle()
{
	current_deck = std::array<int, 52>(Deck::default_deck);
	std::shuffle(current_deck.begin(), current_deck.end(), generator);

	current_card = 0;
}

int Deck::draw_card()
{
	int card = current_deck[current_card];

	current_card++;

	std::cout << current_card << "\n";

	if (current_card >= 52)
	{
		shuffle();
	}

	return card;
}

int Deck::get_cards_drawn() const
{
	return current_card;
}

const std::array<int, 52> Deck::default_deck = 
		{ 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
		6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10,
		11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13 };