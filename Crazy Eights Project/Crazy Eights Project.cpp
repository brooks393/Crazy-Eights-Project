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
void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int player_choice, bool is_move_valid, int player_number);
void player1RemoveCard(Player& player1Hand, int player_choice, Card chosen_card, bool is_move_valid);

//Player 2
void generatePlayer2Hand(Deck& gameDeck, Player& player2);
void printPlayer2Hand(Player& player2);
void player2RemoveCard(Player& player2Hand, int player_choice, Card chosen_card, bool is_move_valid);

//discard pile
void generateDiscardPile(Deck& gameDeck);

//creating new obstances of classes
Deck gameDeck = Deck();
Deck discardPile = Deck();
Player player1Hand = Player();
Player player2Hand = Player();


int main()
{   
    PlaySound(TEXT("KSI Thick of it.wav"), NULL, SND_FILENAME | SND_ASYNC);
;   gameDeck.shuffle();
    generatePlayer1Hand(gameDeck, player1Hand);
    generatePlayer2Hand(gameDeck, player2Hand);
    
    generateDiscardPile(gameDeck);

    Card top_card = discardPile.peekDiscardPileTopCard(); //gets the top card from deck
  
    cout << "Top card is " << top_card.toString() << endl; //prints the words to the cards

    int player_number = 0;
    int discard_pile_pointer = 0;
    while (player1Hand.getHandSize() > 0 or player2Hand.getHandSize() > 0) {
        printPlayer1Hand(player1Hand); //prints players hand
        player_number = 1;
        playerChoice(gameDeck, player1Hand, player2Hand, player_number);//runs the function so player 1 can decide what to do
        printPlayer2Hand(player2Hand); //prints players hand
        player_number = 2;
        playerChoice(gameDeck, player1Hand, player2Hand, player_number);
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
    int player_choice = 0;
    bool is_move_valid = false;
    //cout << "Player 1 Enter choice to make" << endl;
    cin >> player_choice;
    checkCard(gameDeck, player1Hand, player2Hand, player_choice, is_move_valid, player_number);
}
  
void player1RemoveCard(Player& player1Hand, int player_choice, Card chosen_card, bool is_move_valid) {
    player1Hand.removeCard(player_choice - 1); //removes the card the player wants to lay
    discardPile.addCardToDiscardPile(chosen_card); //adds the card to the discard pile
    Card picked_card = discardPile.peekDiscardPileTopCard(); //looks at the discard pile top card
    cout << "Top card is " << picked_card.toString() << endl; //outputs the top card
    is_move_valid = true;
}

void player2RemoveCard( Player& player2Hand, int player_choice, Card chosen_card, bool is_move_valid) {
    player2Hand.removeCard(player_choice - 1); //removes the card the player wants to lay
    discardPile.addCardToDiscardPile(chosen_card); //adds the card to the discard pile
    Card picked_card = discardPile.peekDiscardPileTopCard(); //looks at the discard pile top card
    cout << "Top card is " << picked_card.toString() << endl; //outputs the top card
    is_move_valid = true;
}

//checks card suit, rank and wild + picking up cards 
void checkCard(Deck& gameDeck, Player& player1Hand, Player& player2Hand, int player_choice, bool is_move_valid, int player_number)
{
    //Player 1
    if (player_number == 1) { //if is player 1
        //if number is bigger than player hand size
        while (player_choice > player1Hand.getHandSize() + 1) {// while players input is greater than the players hand size + 1
            system("cls");
            cout << "Player 1 Please enter a valid number" << endl; //enter another valid input
            Card picked_card = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << picked_card.toString() << endl;//outputs the discard piles top card
            printPlayer1Hand(player1Hand);
            cin >> player_choice; //gets players input again
        }
        //if is pick up card
        int deck_pointer = 0; //used to increment the index for the main deck
        while (player_choice == player1Hand.getHandSize() + 1) { //while players input is the pick up option, aka players hand size + 1
            system("cls");
            Card new_card = gameDeck.getTopCard();  //gets the decks top card 
            player1Hand.addCard(new_card); //adds the new card into the players hand
            Card picked_card = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << picked_card.toString() << endl;//outputs the discard piles top card
            printPlayer1Hand(player1Hand); //prints the players hand and passes the new player hand into it
            deck_pointer = deck_pointer + 1; //increments the deck pointer by 1
            cout << "deck has " << gameDeck.getSize() << " cards left" << endl; //prints the size of the deck to check that cards are being removed
            cin >> player_choice; //gets players input again
        }
        Card chosen_card = player1Hand.peekCard(player_choice - 1); //gets the players card from the number the player entered
        Card top_card = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
        //if is Wild Card 
        if (chosen_card.getRank() == 8) {
            system("cls");
            player1RemoveCard(player1Hand, player_choice, chosen_card, is_move_valid); //remove the card funtion
            int suit_picker = 0;
            cout << "\nPlease pick a suit" << endl;
            vector<string> suits = { "Diamonds", "Hearts", "Clubs", "Spades" }; //vector with the suit options
            for (int i = 0; i < suits.size(); i++) { //loop to print out the vector
                std::cout << i + 1 << " - "; //prints "1 - ", "2 - " etc
                cout << suits[i] << endl; //finished it with the vector element "1 - Diamonds", "2 - Hearts" etc
            }
            cin >> suit_picker; //gets players input
            cout << "The suit is now " << suits[suit_picker - 1] << endl; //output the suit the player wants
        }
        //if is Same Suit 
        else if (chosen_card.getSuit() == top_card.getSuit()) { //check if the chosen card is the same suit
            system("cls");
            player1RemoveCard(player1Hand, player_choice, chosen_card, is_move_valid);
        }
        //if is Same Rank
        else if (chosen_card.getRank() == top_card.getRank()) {
            system("cls");
            player1RemoveCard(player1Hand, player_choice, chosen_card, is_move_valid);
        }
        //if is not a valid move
        else if (is_move_valid == false) {
            system("cls");
            cout << "Not a valid move, try again" << endl;
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            is_move_valid = true;
            printPlayer1Hand(player1Hand);
            playerChoice(gameDeck, player1Hand, player2Hand, player_number);
            
        }
    }
        //Player 2
    else if (player_number == 2) {

        //if number is bigger than player hand size
        while (player_choice > player1Hand.getHandSize() + 1) {// while players input is greater than the players hand size + 1
            cout << "Player 2 Please enter a valid number" << endl; //enter another valid input
            cin >> player_choice; //gets players input again
        }

        //if is pick up card
        int deck_pointer = 0; //used to increment the index for the main deck
        while (player_choice == player2Hand.getHandSize() + 1) { //while players input is the pick up option, aka players hand size + 1
            Card new_card = gameDeck.getTopCard();  //gets the decks top card 
            player2Hand.addCard(new_card); //adds the new card into the players hand
            Card picked_card = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card
            cout << "Top card is " << picked_card.toString() << endl;//outputs the discard piles top card
            printPlayer2Hand(player2Hand); //prints the players hand and passes the new player hand into it
            deck_pointer = deck_pointer + 1; //increments the deck pointer by 1
            cout << "deck has " << gameDeck.getSize() << " cards left" << endl; //prints the size of the deck to check that cards are being removed
            cin >> player_choice; //gets players input again
        }

        Card chosen_card = player2Hand.peekCard(player_choice - 1); //gets the players card from the number the player entered
        Card top_card = discardPile.peekDiscardPileTopCard(); //looks at the discard piles top card

        //if is Wild Card 
        if (chosen_card.getRank() == 8) {
            player2RemoveCard(player2Hand, player_choice, chosen_card, is_move_valid);
            int suit_picker = 0;
            cout << "\nPlease pick a suit" << endl;
            vector<string> suits = { "Diamonds", "Hearts", "Clubs", "Spades" }; //vector with the suit options
            for (int i = 0; i < suits.size(); i++) { //loop to print out the vector
                std::cout << i + 1 << " - "; //prints "1 - ", "2 - " etc
                cout << suits[i] << endl; //finished it with the vector element "1 - Diamonds", "2 - Hearts" etc
            }
            cin >> suit_picker; //gets players input
            cout << "The suit is now " << suits[suit_picker - 1] << endl; //output the suit the player wants
        }

        //if is Same Suit 
        else if (chosen_card.getSuit() == top_card.getSuit()) {
            player2RemoveCard(player2Hand, player_choice, chosen_card, is_move_valid);
        }

        //if is Same Rank
        else if (chosen_card.getRank() == top_card.getRank()) {
            player2RemoveCard(player2Hand, player_choice, chosen_card, is_move_valid);
        }

        //if is not a valid move
        else if (is_move_valid == false) {
            cout << "Not a valid move, try again" << endl;
            Card picked_card = discardPile.peekDiscardPileTopCard();
            cout << "Top card is " << picked_card.toString() << endl;
            is_move_valid = true;
            printPlayer2Hand(player2Hand);
            playerChoice(gameDeck, player2Hand, player2Hand, player_number);
        }
    }
}

