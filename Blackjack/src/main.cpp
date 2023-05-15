#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
#include <random>
#include <ctime>

const  int STARTING_MONEY = 100;
const int BLACKJACK = 21;
const int BLACKJACK_MULTIPLIER = 3;
const int WIN_MULTIPLIER = 2;
const int DEALER_LIMIT = 17;

const std::array<int, 52> deck = { 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5,
									6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 
									11, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 13 };

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

std::string get_card_string(int card)
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

void print_hand(const std::vector<int>& hand)
{
	for (int card : hand)
	{
		std::cout << get_card_string(card) << " ";
	}

	std::cout << "\n";
}

int main()
{
	std::cout << "Welcome to blackjack!\n";

	bool running = true;

	int money = STARTING_MONEY;

	std::random_device device;
	std::default_random_engine generator(device());

	while (running && money > 0)
	{
		std::string command;

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

			std::vector<int> player_hand;
			player_hand.reserve(4);

			std::vector<int> dealer_hand;
			dealer_hand.reserve(4);

			std::vector<int> current_deck(deck.begin(), deck.end());
			std::shuffle(current_deck.begin(), current_deck.end(), generator);

			std::cout << "Drawing cards!\n\n";

			int current_card = 0;

			int player_sum = 0;
			int dealer_sum = 0;

			int player_ace_count = 0;
			int dealer_ace_count = 0;

			for (; current_card < 2; current_card++)
			{
				player_hand.emplace_back(current_deck[current_card]);

				if (current_deck[current_card] == 1)
				{
					player_sum += 11;
					player_ace_count++;
				}
				else
				{
					player_sum += std::clamp(current_deck[current_card], 1, 10);
				}
			}

			dealer_hand.emplace_back(current_deck[current_card]);

			if (current_deck[current_card] == 1)
			{
				dealer_sum += 11;
				dealer_ace_count++;
			}
			else
			{
				dealer_sum += std::clamp(current_deck[current_card], 1, 10);
			}

			current_card++;

			std::cout << "Your hand is: ";
			print_hand(player_hand);

			std::cout << "The dealer's hand is: ";
			print_hand(dealer_hand);

			while (player_sum < BLACKJACK)
			{
				std::cout << "\nType \"hit\" to take another card or \"stand\" to end your turn.\n";
				std::cout << "Your total is: " << player_sum << "\n";

				std::getline(std::cin, command);

				if (!command.compare("hit"))
				{
					player_hand.emplace_back(current_deck[current_card]);

					if (current_deck[current_card] == 1)
					{
						player_sum += 11;
						player_ace_count++;
					}
					else
					{
						player_sum += std::clamp(current_deck[current_card], 1, 10);
					}

					if (player_sum > BLACKJACK && player_ace_count > 0)
					{
						player_sum -= 10;
						player_ace_count--;
					}

					std::cout << "\nYou drew a " << get_card_string(current_deck[current_card]) << "!\n";
					std::cout << "Your hand is ";
					print_hand(player_hand);

					current_card++;
				}
				else if (!command.compare("stand"))
				{
					break;
				}
				else
				{
					std::cout << "Unknown input. Please enter a valid command.\n";
				}
			}

			if (player_sum == BLACKJACK)
			{
				std::cout << "\nYou have blackjack!\n";

				money += bet * BLACKJACK_MULTIPLIER;
				continue;
			}
			else if (player_sum > BLACKJACK)
			{
				std::cout << "\nYou bust!\n";
				continue;
			}

			while (dealer_sum < DEALER_LIMIT)
			{
				dealer_hand.emplace_back(current_deck[current_card]);

				if (current_deck[current_card] == 1)
				{
					dealer_sum += 11;
					dealer_ace_count++;
				}
				else
				{
					dealer_sum += std::clamp(current_deck[current_card], 1, 10);
				}

				if (dealer_sum > BLACKJACK && dealer_ace_count > 0)
				{
					dealer_sum -= 10;
					dealer_ace_count--;
				}

				std::cout << "\nDealer drew a " << get_card_string(current_deck[current_card]) << "!\n";
				std::cout << "Dealer hand is ";
				print_hand(dealer_hand);
				std::cout << "Dealer total is " << dealer_sum << "\n";

				current_card++;
			}

			if (dealer_sum > BLACKJACK)
			{
				std::cout << "\nDealer bust!\n";
				money += bet * WIN_MULTIPLIER;
			}
			else if (dealer_sum > player_sum)
			{
				std::cout << "\nDealer wins!\n";
			}
			else if (dealer_sum < player_sum)
			{
				std::cout << "\nYou win!\n";

				money += bet * WIN_MULTIPLIER;
			}
			else
			{
				std::cout << "\nTied with the dealer! No winner.\n";
				money += bet;
			}
		}
		else
		{
			std::cout << "Unknown input. Please enter a valid command.\n";
		}
	}

	std::cout << "\nThanks for playing!\n";

	return 0;
}