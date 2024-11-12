#include "Card.h"

Card::Card(int init_rank, string init_suit)
{
	this->rank = init_rank;
	this->suit = init_suit;
}

int Card::getRank()
{
	return this->rank;
}

string Card::getSuit()
{
	return this->suit;
}

void Card::setRank(int new_rank)
{
	this->rank = new_rank;
}

void Card::setSuit(string new_suit)
{
	this->suit = new_suit;
}

string Card::toString()
{
	if (this->rank == 11) {
		return "Jack of " + this->getSuit();
	}
	if (this->rank == 12) {
		return "Queen of " + this->getSuit();
	}
	if (this->rank == 13) {
		return "King of " + this->getSuit();
	}
	return to_string(this->rank) + " of " + this->getSuit();
}
