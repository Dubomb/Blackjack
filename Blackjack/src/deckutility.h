#pragma once

#include <array>
#include <random>

class Deck
{
public:
	Deck();

	void shuffle();

	int draw_card();

	int get_cards_drawn() const;

private:
	static const std::array<int, 52> default_deck;

	std::array<int, 52> current_deck;
	int current_card;

	std::random_device device;
	std::default_random_engine generator;
};