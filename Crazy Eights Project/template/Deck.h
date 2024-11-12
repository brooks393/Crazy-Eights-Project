#pragma once
#include <vector>
#include <string>
#include "Card.h"

using namespace std;

/**
 * @brief Deck class represents a collection of cards in a vector format. 
 * Intended to represent a deck, however can be used for stock piles, discard piles, and other uses.
 */
class Deck
{
private:
	vector<Card> deck_vector; //Deck Vector
	vector<Card> discard_pile; //Discard Pile Vector
public:
	
	Deck(); //Constructor to make a new deck. Pre-fills the deck with ordered cards by default.
	int getSize();//Gets the size of the deck + returns number of cards in deck
	bool isEmpty();//Returns true/false depending on whether there are any cards in the deck.return boolean flag of if the deck is empty.
	void shuffle();//Shuffles the deck into a pseudo-random order. 
	void clear();//Removes all cards from the deck.
	void fillDeck();//Fills the deck with all 52 cards. Does not shuffle the deck.
	void addCard(Card new_card); //Adds a new card to the deck. Card is placed at the back of the deck vector. param new_card New card object to be added to the deck.
	Card peekTopCard();//Returns the card at the top of deck. Will return the last card in the vector and will not be removed from the deck.
	Card peekCard(int index); //Returns the card at the given index. Card will not be removed from the deck. Param index The index of the desired card.return Card object of the card at the given index.
	Card getTopCard();//Removes and returns the card at the top of the deck. Will return the last card in the vector and will be removed from the deck.
	Card getCard(int index); //Removes and returns the card at the given index. Card will be removed from the deck
	void removeCard(int index);//Removes the card at the given index from the deck. Does not return the removed card.
	void printDeck();
	Card peekLastCard();
	Card getLastCard();
	//discard pile
	Card getDiscardPileCard(int index);
	Card getDiscardPileTopCard();
	Card peekDiscardPileCard(int index);
	Card peekDiscardPileTopCard();
	void addCardToDiscardPile(Card new_card);
	int getDiscardPileSize();
};

