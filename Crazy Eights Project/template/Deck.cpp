#include "Deck.h"
#include <iostream>
#include <algorithm>
#include <random>

Deck::Deck()
{
	this->deckVector = {};
	this->fillDeck();
	srand(time(0));
}



int Deck::getSize()
{
	return this->deckVector.size();
}

bool Deck::isEmpty()
{
	return this->deckVector.empty();
}

void Deck::shuffle()
{
	random_shuffle(begin(this->deckVector), end(this->deckVector));
}

void Deck::clear()
{
	this->deckVector.clear();
}

void Deck::fillDeck()
{
	//Iterates through all 13 cards for each suit separately.
	for (int i = 1; i < 14; i++) {
		Card nCard = Card(i, "Clubs");
		this->deckVector.push_back(nCard);
	}

	for (int i = 1; i < 14; i++) {
		Card nCard = Card(i, "Hearts");
		this->deckVector.push_back(nCard);
	}

	for (int i = 1; i < 14; i++) {
		Card nCard = Card(i, "Diamonds");
		this->deckVector.push_back(nCard);
	}

	for (int i = 1; i < 14; i++) {
		Card nCard = Card(i, "Spades");
		this->deckVector.push_back(nCard);
	}

}

void Deck::addCard(Card new_card)
{
	this->deckVector.push_back(new_card);
}

Card Deck::peekCard(int index)
{
	return this->deckVector[index];
}

Card Deck::peekTopCard()
{
	int topCardIndex = this->getSize() - 1;
	return this->peekCard(topCardIndex);
}

Card Deck::getCard(int index)
{
	//Temporary variable must be created to return object after deleting card from vector.
	Card tmpCard = this->deckVector[this->getSize() - 1];
	this->deckVector.erase(this->deckVector.begin() + index);
	return tmpCard;
}

void Deck::removeCard(int index)
{
	this->deckVector.erase(this->deckVector.begin() + index);
}

void Deck::printDeck()
{
	for (int i = 0; i < deckVector.size(); i++) {
		Card card = deckVector[i];
		std::cout << i + 1 << " - ";
		Deck::getCard(i);
		std::cout << std::endl;
	}
}

Card Deck::peekLastCard()
{
	int lastCardIndex = this->getSize() - this->getSize() + 1;
	return this->peekCard(lastCardIndex);
}

Card Deck::getLastCard()
{
	int topCardIndex = this->getSize() - this->getSize() + 1;
	return this->getCard(topCardIndex);
}

Card Deck::getDiscardPileCard(int index)
{
	Card tmpCard = this->discardPile[this->getSize() - 1];
	this->discardPile.erase(this->discardPile.begin() + index);
	return tmpCard;
}

Card Deck::getDiscardPileTopCard()
{
	int topCardIndex = this->getSize() - 1;
	return this->getDiscardPileCard(topCardIndex);
}

Card Deck::peekDiscardPileCard(int index)
{
	return this->discardPile[index];
}

Card Deck::peekDiscardPileTopCard()
{
	int topCardIndex = this->getDiscardPileSize() - 1;
	return this->peekDiscardPileCard(topCardIndex);
}

void Deck::addCardToDiscardPile(Card new_card)
{
	this->discardPile.push_back(new_card);
}

int Deck::getDiscardPileSize()
{
	return this->discardPile.size();
}


Card Deck::getTopCard()
{
	int topCardIndex = this->getSize() - 1;
	return this->getCard(topCardIndex);
}