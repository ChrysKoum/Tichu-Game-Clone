#ifndef DECK_H
#define DECK_H

#include "card.h"

/**
 * Class that implements a deck of cards. It shuffles the cards and
 * deals them to the players.
 */
class Deck
{
private:
    Card** cards;
    int deckSize; // the number of cards in the deck
    int cardsUsed; // holds the number of cards already dealt from the top of the card deck

public:
    /**
     * Initializes a tichu deck with 56 cards.
     */
	Deck();

    /**
     * Destroys this deck of cards by deleting also all the cards.
     */
	~Deck();

    /**
     * Shuffles the cards of the deck.
     */
	void shuffleCards();

    /**
     * Removes the next card from the deck and returns it. If there are no more cards
     * in the deck, calling this function results in an error.
     *
     * @return a card removed from the deck.
     */
	Card *deal();

    /**
     * Returns the number of cards not dealt yet from the deck.
     *
     * @return the number of cards left in the deck.
     */
	int cardsLeft();
};

#endif // DECK_H
