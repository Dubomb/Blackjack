#pragma once

#include <string>
#include <vector>

class Hand
{
public:
	Hand();
	
	std::string add_card(const std::array<int, 52>& deck, int& card);
	void clear_hand();

	int get_total() const;

	std::string get_card_string(int card) const;
	std::string get_hand_string() const;

private:
	std::vector<int> hand;
	int hand_total;
	int ace_count;
};