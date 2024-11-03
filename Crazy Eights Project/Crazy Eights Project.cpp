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
#pragma comment(lib, "winmm.lib")

using namespace std;

//Player 1
void generatePlayer1Hand(Deck& gameDeck, Player& player1);
void printPlayer1Hand( Player& player1);
void playerChoice(Deck& gameDeck, Player& player1, Player& player2Hand, int player_number);
void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int playerchoice, bool is_move_valid, int player_number);


//Player 2
void generatePlayer2Hand(Deck& gameDeck, Player& player2);
void printPlayer2Hand(Player& player2);
//void playerChoice(Deck& gameDeck, Player& player1);
//void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int playerchoice, bool is_move_valid);

//discard pile
void generateDiscardPile(Deck& gameDeck);

//creating new obstances of classes
Deck gameDeck = Deck();
Deck discardPile = Deck();
Player player1Hand = Player();
Player player2Hand = Player();


int main()
{   
    gameDeck.shuffle();
    generatePlayer1Hand(gameDeck, player1Hand);
    generatePlayer2Hand(gameDeck, player2Hand);
    
    generateDiscardPile(gameDeck);

    cout << discardPile.getSize() << endl;
    Card top_card = discardPile.peekDiscardPileTopCard(); //gets the top card from deck
  
    cout << "\nTop card is " << top_card.toString() << endl; //prints the words to the cards

    int player_number = 0;
    int discard_pile_pointer = 0;
    while (player1Hand.getHandSize() > 0 or player2Hand.getHandSize() > 0) {
        printPlayer1Hand(player1Hand); //prints players hand
        player_number = 1;
        playerChoice(gameDeck, player1Hand, player2Hand, player_number);//runs the function so player 1 can decide what to do
        printPlayer2Hand(player2Hand); //prints players hand
        player_number = 2;
        playerChoice(gameDeck, player1Hand, player2Hand, player_number );
    }
}

void generateDiscardPile(Deck& gameDeck) {
    discardPile.clear();
    Card first_card = gameDeck.getTopCard();
    discardPile.addCardToDiscardPile(first_card);
}

void generatePlayer1Hand(Deck & gameDeck, Player& player1Hand) {
    for (int i = 0; i < 5; i++) {
        Card new_card = gameDeck.getTopCard();
        player1Hand.addCard(new_card);
    }    
}

void generatePlayer2Hand(Deck& gameDeck, Player& player2Hand) {
    for (int i = 0; i < 5; i++) {
        Card new_card = gameDeck.getTopCard();
        player2Hand.addCard(new_card);
    }
}

void printPlayer1Hand(Player& player1Hand) {
    cout << "\nPlayer 1's Hand" << endl;
    for (int i = 0; i < player1Hand.getHandSize(); i++) {
        std::cout << i + 1 << " - ";
        Card card_peeked = player1Hand.peekCard(i);
        std::cout << card_peeked.toString() << std::endl;
    }
    cout << player1Hand.getHandSize() + 1 << " - Pick up card " << endl;
}

void printPlayer2Hand(Player& player2Hand) {
    cout << "\nPlayer 2's Hand" << endl;
    for (int i = 0; i < player2Hand.getHandSize(); i++) {
        std::cout << i + 1 << " - ";
        Card card_peeked = player2Hand.peekCard(i);
        std::cout << card_peeked.toString() << std::endl;
    }
    cout << player2Hand.getHandSize() + 1 << " - Pick up card " << endl;
}
 
void playerChoice(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int player_number) {
    int playerchoice = 0;
    bool is_move_valid = false;
    //cout << "Player 1 Enter choice to make" << endl;
    cin >> playerchoice;
    checkCard(gameDeck, player1Hand, player2Hand, playerchoice, is_move_valid, player_number);
}


    
void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int playerchoice, bool is_move_valid, int player_number)
{
    //Player 1
    if (player_number == 1) {

        //if number is bigger than player hand size
        while (playerchoice > player1Hand.getHandSize() + 1) {// while players input is greater than the players hand size + 1
            cout << "Player 1 Please enter a valid number" << endl; //enter another valid input
            cin >> playerchoice;
        }

        //if is pick up card
        int deck_pointer = 0; //used to increment the index for the main deck
        while (playerchoice == player1Hand.getHandSize() + 1) { //while players input is the pick up option, aka players hand size + 1
            Card new_card = gameDeck.getTopCard();  //gets the decks top card 
            player1Hand.addCard(new_card); //adds the new card into the players hand
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            printPlayer1Hand(player1Hand); //prints the players hand and passes the new player hand into it
            deck_pointer = deck_pointer + 1; //increments the deck pointer by 1
            cout << "deck has " << gameDeck.getSize() << " cards left" << endl; //prints the size of the deck to check that cards are being removed
            cin >> playerchoice;
        }

        Card chosen_card = player1Hand.peekCard(playerchoice - 1);
        Card top_card = discardPile.peekDiscardPileTopCard();

        //if is Wild Card 
        if (chosen_card.getRank() == 8) {
            player1Hand.removeCard(playerchoice - 1);
            discardPile.addCardToDiscardPile(chosen_card);
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            int suit_picker = 0;
            cout << "\nPlease pick a suit" << endl;
            vector<string> suits = { "Diamonds", "Hearts", "Clubs", "Spades" };
            for (int i = 0; i < suits.size(); i++) {
                std::cout << i + 1 << " - ";
                cout << suits[i] << endl;
            }
            cin >> suit_picker;
            cout << "The suit is now " << suits[suit_picker - 1] << endl;
            is_move_valid = true;
        }

        //if is Same Suit 
        else if (chosen_card.getSuit() == top_card.getSuit()) {
            player1Hand.removeCard(playerchoice - 1);
            discardPile.addCardToDiscardPile(chosen_card);
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            is_move_valid = true;
        }

        //if is Same Rank
        else if (chosen_card.getRank() == top_card.getRank()) {
            player1Hand.removeCard(playerchoice - 1);
            discardPile.addCardToDiscardPile(chosen_card);
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
          is_move_valid = true;
        }

        //if is not a valid move
        else if (is_move_valid == false) {
            cout << "Not a valid move, try again" << endl;
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            is_move_valid = true;
            printPlayer1Hand(player1Hand);
            playerChoice(gameDeck, player1Hand, player2Hand, player_number);
        }

        //Player 2
        else if (player_number == 2) {

            //if number is bigger than player hand size
            while (playerchoice > player2Hand.getHandSize() + 1) {// while players input is greater than the players hand size + 1
                cout << "Player 2 Please enter a valid number" << endl; //enter another valid input
                cin >> playerchoice;
            }

            //if is pick up card
            int deck_pointer = 0; //used to increment the index for the main deck
            while (playerchoice == player2Hand.getHandSize() + 1) { //while players input is the pick up option, aka players hand size + 1
                Card new_card = gameDeck.getTopCard();  //gets the decks top card 
                player2Hand.addCard(new_card); //adds the new card into the players hand
                Card picked_card = discardPile.peekDiscardPileTopCard();
                cout << "Top card is " << picked_card.toString() << endl;
                is_move_valid = true;
                printPlayer2Hand(player2Hand); //prints the players hand and passes the new player hand into it
                deck_pointer = deck_pointer + 1; //increments the deck pointer by 1
                cout << "deck has " << gameDeck.getSize() << " cards left" << endl; //prints the size of the deck to check that cards are being removed
                cin >> playerchoice;
            }

            Card chosen_card = player2Hand.peekCard(playerchoice - 1);
            Card top_card = discardPile.peekDiscardPileTopCard();

            // if is a wild card
            if (chosen_card.getRank() == 8) {
                player2Hand.removeCard(playerchoice - 1);
                discardPile.addCardToDiscardPile(chosen_card);
                Card picked_card = discardPile.peekDiscardPileTopCard();
                cout << "Top card is " << picked_card.toString() << endl;
                int suit_picker = 0;
                cout << "\nPlease pick a suit" << endl;
                vector<string> suits = { "Diamonds", "Hearts", "Clubs", "Spades" };
                for (int i = 0; i < suits.size(); i++) {
                    std::cout << i + 1 << " - ";
                    cout << suits[i] << endl;
                }
                cin >> suit_picker;
                cout << "The suit is now " << suits[suit_picker - 1] << endl;
                is_move_valid = true;
            }

            //if is same suit
            else if (chosen_card.getSuit() == top_card.getSuit()) {
                player2Hand.removeCard(playerchoice - 1);
                discardPile.addCardToDiscardPile(chosen_card);
                Card picked_card = discardPile.peekDiscardPileTopCard(); //removing card
                cout << "Top card is " << picked_card.toString() << endl;
                is_move_valid = true;
            }

            //if is same rank
            else if (chosen_card.getRank() == top_card.getRank()) {
                player2Hand.removeCard(playerchoice - 1);
                discardPile.addCardToDiscardPile(chosen_card);
                Card picked_card = discardPile.peekDiscardPileTopCard();
                cout << "Top card is " << picked_card.toString() << endl;
                is_move_valid = true;
            }

            //if is not a valid move
            if (is_move_valid == false) {
                cout << "Not a valid move, try again" << endl;
                Card picked_card = discardPile.peekDiscardPileTopCard();
                cout << "Top card is " << picked_card.toString() << endl;
                is_move_valid = true;
                printPlayer2Hand(player2Hand);
                playerChoice(gameDeck, player1Hand, player2Hand, player_number);
            }
        }
    }
}
