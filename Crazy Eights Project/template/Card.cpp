#include "Card.h"

Card::Card(int initRank, string newSuit)
{
	this->rank = initRank;
	this->suit = newSuit;
}

int Card::getRank()
{
	return this->rank;
}

string Card::getSuit()
{
	return this->suit;
}

void Card::setRank(int newRank)
{
	this->rank = newRank;
}

void Card::setSuit(string newSuit)
{
	this->suit = newSuit;
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
