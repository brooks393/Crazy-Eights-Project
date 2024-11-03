#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Card.h"

using namespace std;


/**
 * @brief Player class represents a single player, either human or bot. Player has a name, a hand, and a score. 
 * Class does not get input from terminal directly.
 */
class Player
{
private:

	string name; //Name of the player playing.
	vector<Card> hand;//Player's hand.
	int score;//Players score

public:

	Player();//Constructor to create a Player. Sets player name to "Unamed Player", hand starts empty, and score starts at 0.
	string getName();//Gets the player's name.
	void setName(string new_name);//Sets the player's name.
	int getHandSize(); //Gets the number of cards in the player's hand. Returns size
	vector<Card> getHand();//Gets the entire hand of the player.return The vector containing Card objects.
	void clearHand();//Clears the player's hand. Removes all cards from the player's hand permanently.
	bool isEmpty();
	/**
	 * Returns the card at the given index. Important to note is the card will not be removed from the player's hand.
	 * \return Card object of the card at the given index.
	 */
	Card peekCard(int index);
	/**
	 * Removes and returns the card at the given index. Important to note is the card will be removed from the player's hand..
	 * \return Card object of the card at the given index.
	 */
	Card getCard(int index);
	/**
	 * Adds a new card to the player's hand. Card is placed at the back of the hand vector.
	 * \param new_card New card object to be added to the player's hand.
	 */
	void addCard(Card new_card);
	/**
	 * Removes the card at the given index from the player's hand.
	 * \param index The index of the card to be removed.
	 */
	void removeCard(int index);

	/**
	 * Calculates and returns the sum of all ranks from cards in the player's hand. Important to note is face cards are interpreted as 11, 12, and 13.
	 * \return Sum of all cards in player's hand.
	 */
	int sumHand();
	/**
	 * Iterates over all card objects in the player's hand and outputs each card's toString to terminal on separate lines.
	 */
	void outputHand();

	/**
	 * Alter the player's score by given integer.
	 * \param toAdd Score to add to player's score. Score will be reduced if toAdd is negative.
	 */
	void changeScoreBy(int toAdd);
	/**
	 * Set a new score, overwriting the previous score.
	 * \param newScore New player score, given as an integer.
	 */
	void setScore(int newScore);
	/**
	 * Gets the player's score.
	 * \return Player's score, given as an integer.
	 */
	int getScore();
};

