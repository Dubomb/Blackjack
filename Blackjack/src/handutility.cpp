#include "handutility.h"

#include <algorithm>
#include <array>
#include <iostream>

const int BLACKJACK = 21;

Hand::Hand()
	: hand_total(0), ace_count(0)
{
	hand.reserve(4);
}

std::string Hand::add_card(const std::array<int, 52>& deck, int& card)
{
	int card_number = hand.emplace_back(deck[card]);

	if (deck[card] == 1)
	{
		hand_total += 11;
		ace_count++;
	}
	else
	{
		hand_total += std::clamp(deck[card], 1, 10);
	}

	card++;

	if (hand_total > BLACKJACK && ace_count > 0)
	{
		hand_total -= 10;
		ace_count--;
	}

	return get_card_string(card_number);
}

void Hand::clear_hand()
{
	hand.clear();
	hand_total = 0;
	ace_count = 0;
}

int Hand::get_total() const
{
	return hand_total;
}

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

std::string Hand::get_hand_string() const
{
	std::string s = "";

	for (int card : hand)
	{
		s += get_card_string(card) + " ";
	}

	return s;
}