// Crazy Eights Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "template\Card.h"
#include "template\Deck.h"
#include "template\Player.h"
#include <Windows.h>
#include <mmsyscom.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <cwchar>
#include <cctype>
#pragma comment(lib, "winmm.lib")

using namespace std;

//Player 1
void generatePlayer1Hand(Deck& gameDeck, Player& player1);
void printPlayer1Hand( Player& player1);
void playerDecision(Deck& gameDeck, Player& player1, Player& player2Hand, int playerNumber);
void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int playerChoice, bool isMoveValid, int playerNumber);
void player1RemoveCard(Player& player1Hand, int playerChoice, Card chosenCard, bool isMoveValid);

//Player 2
void generatePlayer2Hand(Deck& gameDeck, Player& player2);
void printPlayer2Hand(Player& player2);
void player2RemoveCard(Player& player2Hand, int playerChoice, Card chosenCard, bool isMoveValid);

//discard pile
void generateDiscardPile(Deck& gameDeck);

//creating new obstances of classes
Deck gameDeck = Deck();
Deck discardPile = Deck();
Player player1Hand = Player();
Player player2Hand = Player();



int main()
{   
    

    PlaySound(TEXT("KSI Thick of it.wav"), NULL, SND_FILENAME | SND_ASYNC);//playes music file
   
;   gameDeck.shuffle(); //shuffles the deck
    generatePlayer1Hand(gameDeck, player1Hand); //prints players 1 hand
    generatePlayer2Hand(gameDeck, player2Hand);//prints players 2 hand
    
    generateDiscardPile(gameDeck); //adds the first card to the discard pile

    Card topCard = discardPile.peekDiscardPileTopCard(); //gets the top card from deck
    cout << "Top card is " << topCard.toString() << endl; //prints the words to the cards

    int playerNumber = 0;
    int discardPile_pointer = 0;
    bool gameRunning = true;
    while (player1Hand.getHandSize() > 0 or player2Hand.getHandSize() > 0 and gameRunning == true) {
        if (gameRunning == true) {
            printPlayer1Hand(player1Hand); //prints players hand
            playerNumber = 1;
            playerDecision(gameDeck, player1Hand, player2Hand, playerNumber);//runs the function so player 1 can decide what to do
            if (player1Hand.getHandSize() == 0) {
                cout << "Player 1 wins" << endl;
                gameRunning = false;
            } 
        }
        if (gameRunning == true) {
            printPlayer2Hand(player2Hand); //prints players hand
            playerNumber = 2;
            playerDecision(gameDeck, player1Hand, player2Hand, playerNumber);
            if (player2Hand.getHandSize() == 0) {
                cout << "Player 2 wins" << endl;
                gameRunning = false;
            }
        }
        
    }
   
    
}

void generateDiscardPile(Deck& gameDeck) {
    discardPile.clear();
    Card firstCard = gameDeck.getTopCard();
    discardPile.addCardToDiscardPile(firstCard);
}

void generatePlayer1Hand(Deck & gameDeck, Player& player1Hand) {
    for (int i = 0; i < 5; i++) {
        Card newCard = gameDeck.getTopCard();
        player1Hand.addCard(newCard);
    }    
}

void generatePlayer2Hand(Deck& gameDeck, Player& player2Hand) {
    for (int i = 0; i < 5; i++) { 
        Card newCard = gameDeck.getTopCard();
        player2Hand.addCard(newCard);
    }
}

void printPlayer1Hand(Player& player1Hand) {
    cout << "\nPlayer 1's Hand" << endl;
    for (int i = 0; i < player1Hand.getHandSize(); i++) {
        std::cout << i + 1 << " - ";
        Card cardPeeked = player1Hand.peekCard(i);
        std::cout << cardPeeked.toString() << std::endl;
    }
    cout << player1Hand.getHandSize() + 1 << " - Pick up card " << endl;
}

void printPlayer2Hand(Player& player2Hand) {
    cout << "\nPlayer 2's Hand" << endl;
    for (int i = 0; i < player2Hand.getHandSize(); i++) {
        std::cout << i + 1 << " - ";
        Card cardPeeked = player2Hand.peekCard(i);
        std::cout << cardPeeked.toString() << std::endl;
    }
    cout << player2Hand.getHandSize() + 1 << " - Pick up card " << endl;
}
 
void playerDecision(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int playerNumber) {
    int playerChoice = 0;
    bool isMoveValid = false;
    //cout << "Player 1 Enter choice to make" << endl;
    cin >> playerChoice;
    checkCard(gameDeck, player1Hand, player2Hand, playerChoice, isMoveValid, playerNumber);
}
  
void player1RemoveCard(Player& player1Hand, int playerChoice, Card chosenCard, bool isMoveValid) {
    player1Hand.removeCard(playerChoice - 1); //removes the card the player wants to lay
    discardPile.addCardToDiscardPile(chosenCard); //adds the card to the discard pile
    Card pickedCard = discardPile.peekDiscardPileTopCard(); //looks at the discard pile top card
    cout << "Top card is " << pickedCard.toString() << endl; //outputs the top card
    isMoveValid = true;
}

void player2RemoveCard( Player& player2Hand, int playerChoice, Card chosen_card, bool isMoveValid) {
    player2Hand.removeCard(playerChoice - 1); //removes the card the player wants to lay
    discardPile.addCardToDiscardPile(chosen_card); //adds the card to the discard pile
    Card picked_card = discardPile.peekDiscardPileTopCard(); //looks at the discard pile top card
    cout << "Top card is " << picked_card.toString() << endl; //outputs the top card
    isMoveValid = true;
}

//checks card suit, rank and wild + picking up cards 
void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int playerChoice, bool isMoveValid, int playerNumber)
{
    string line;
    size_t pos;

    //Player 1
    if (playerNumber == 1) { //if is player 1
        //if number is bigger than player hand size
        while (playerChoice > player1Hand.getHandSize() + 1) {// while players input is greater than the players hand size + 1
            system("cls");
            cout << "Player 1 Please enter a valid number" << endl; //enter another valid input
            Card pickedCard = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << pickedCard.toString() << endl;//outputs the discard piles top card
            printPlayer1Hand(player1Hand);
            cin >> playerChoice; //gets players input again
        }
        //if is pick up card
        int deckPointer = 0; //used to increment the index for the main deck
        while (playerChoice == player1Hand.getHandSize() + 1) { //while players input is the pick up option, aka players hand size + 1
            system("cls");
            Card newCard = gameDeck.getTopCard();  //gets the decks top card 
            player1Hand.addCard(newCard); //adds the new card into the players hand
            Card pickedCard = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << pickedCard.toString() << endl;//outputs the discard piles top card
            printPlayer1Hand(player1Hand); //prints the players hand and passes the new player hand into it
            deckPointer = deckPointer + 1; //increments the deck pointer by 1
            cout << "deck has " << gameDeck.getSize() << " cards left" << endl; //prints the size of the deck to check that cards are being removed
            cin >> playerChoice; //gets players input again
        }

        
        if (playerChoice == NULL or !std::getline(std::cin, line))
        {
            throw std::runtime_error("unexpected input error!\n");
        }
        
        Card chosenCard = player1Hand.peekCard(playerChoice - 1); //gets the players card from the number the player entered
        Card topCard = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
        //if is Wild Card 
        if (chosenCard.getRank() == 8) {
            system("cls");
            player1RemoveCard(player1Hand, playerChoice, chosenCard, isMoveValid); //remove the card funtion
            int suitPicker = 0;
            cout << "\nPlease pick a suit" << endl;
            vector<string> suits = { "Diamonds", "Hearts", "Clubs", "Spades" }; //vector with the suit options
            for (int i = 0; i < suits.size(); i++) { //loop to print out the vector
                std::cout << i + 1 << " - "; //prints "1 - ", "2 - " etc
                cout << suits[i] << endl; //finished it with the vector element "1 - Diamonds", "2 - Hearts" etc
            }
            cin >> suitPicker; //gets players input
            cout << "The suit is now " << suits[suitPicker - 1] << endl; //output the suit the player wants
            topCard.setSuit(suits[suitPicker - 1]); //sets the suit the player wants
            discardPile.addCardToDiscardPile(topCard);
        }
        //if is Same Suit 
        else if (chosenCard.getSuit() == topCard.getSuit()) { //check if the chosen card is the same suit
            system("cls");
            player1RemoveCard(player1Hand, playerChoice, chosenCard, isMoveValid);
        }
        //if is Same Rank
        else if (chosenCard.getRank() == topCard.getRank()) {
            system("cls");
            player1RemoveCard(player1Hand, playerChoice, chosenCard, isMoveValid);
        }
        //if is not a valid move
        else if (isMoveValid == false) {
            system("cls");
            cout << "Not a valid move, try again" << endl;
            Card pickedCard = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << pickedCard.toString() << endl;
            isMoveValid = true;
            printPlayer1Hand(player1Hand);
            playerDecision(gameDeck, player1Hand, player2Hand, playerNumber);
            
        }
        
        
    }
        //Player 2
    else if (playerNumber == 2) {

        //if number is bigger than player hand size
        while (playerChoice > player2Hand.getHandSize() + 1) {// while players input is greater than the players hand size + 1
            system("cls");
            cout << "Player 2 Please enter a valid number" << endl; //enter another valid input
            Card pickedCard = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << pickedCard.toString() << endl;//outputs the discard piles top card
            printPlayer2Hand(player2Hand);
            cin >> playerChoice; //gets players input again
        }

        //if is pick up card
        int deckPointer = 0; //used to increment the index for the main deck
        while (playerChoice == player2Hand.getHandSize() + 1) { //while players input is the pick up option, aka players hand size + 1
            system("cls");
            Card newCard = gameDeck.getTopCard();  //gets the decks top card 
            player2Hand.addCard(newCard); //adds the new card into the players hand
            Card pickedCard = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << pickedCard.toString() << endl;//outputs the discard piles top card
            printPlayer2Hand(player2Hand); //prints the players hand and passes the new player hand into it
            deckPointer = deckPointer + 1; //increments the deck pointer by 1
            cout << "deck has " << gameDeck.getSize() << " cards left" << endl; //prints the size of the deck to check that cards are being removed
            cin >> playerChoice; //gets players input again
        }

        Card chosenCard = player2Hand.peekCard(playerChoice - 1); //gets the players card from the number the player entered
        Card topCard = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card

        //if is Wild Card 
        if (chosenCard.getRank() == 8) {
            system("cls");
            player2RemoveCard(player2Hand, playerChoice, chosenCard, isMoveValid);
            int suitPicker = 0;
            cout << "\nPlease pick a suit" << endl;
            vector<string> suits = { "Diamonds", "Hearts", "Clubs", "Spades" }; //vector with the suit options
            for (int i = 0; i < suits.size(); i++) { //loop to print out the vector
                std::cout << i + 1 << " - "; //prints "1 - ", "2 - " etc
                cout << suits[i] << endl; //finished it with the vector element "1 - Diamonds", "2 - Hearts" etc
            }
            cin >> suitPicker; //gets players input
            cout << "The suit is now " << suits[suitPicker - 1] << endl; //output the suit the player wants
            topCard.setSuit(suits[suitPicker - 1]); //sets the suit the player wants
            discardPile.addCardToDiscardPile(topCard);
        }

        //if is Same Suit 
        else if (chosenCard.getSuit() == topCard.getSuit()) {
            system("cls");
            player2RemoveCard(player2Hand, playerChoice, chosenCard, isMoveValid);
        }

        //if is Same Rank
        else if (chosenCard.getRank() == topCard.getRank()) {
            system("cls");
            player2RemoveCard(player2Hand, playerChoice, chosenCard, isMoveValid);
        }

        //if is not a valid move
        else if (isMoveValid == false) {
            system("cls");
            cout << "Not a valid move, try again" << endl;
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            isMoveValid = true;
            printPlayer2Hand(player2Hand);
            playerDecision(gameDeck, player2Hand, player2Hand, playerNumber);
        }
    }
}

