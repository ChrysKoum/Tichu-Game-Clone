#include <algorithm>
#include "deck.h"
#include "shuffler.h"

using namespace std;

Deck::Deck(){
    deckSize = 56;
    cards = new Card*[deckSize];

    cardsUsed = 0;
    for (int suit = 0; suit <= 3; suit++){
        for (int value = 2; value <= 14; value++)
            cards[cardsUsed++] = new SimpleCard(value, (CardSuit)suit);
    }
    cards[cardsUsed++] = new SpecialCard(MAHJONG);
    cards[cardsUsed++] = new SpecialCard(DRAGON);
    cards[cardsUsed++] = new SpecialCard(PHOENIX);
    cards[cardsUsed++] = new SpecialCard(DOG);
    cardsUsed = 0;
}

Deck::~Deck(){
    for (int i = 0; i < deckSize; i++)
        delete cards[i];
    delete[] cards;
}

void Deck::shuffleCards(){
    shuffle(cards, cardsLeft());
    cut(cards, cardsLeft());
    cardsUsed = 0;
}

int Deck::cardsLeft(){
    return deckSize - cardsUsed;
}

Card *Deck::deal(){
    Card* c = cards[cardsUsed];
    cardsUsed++;
    return c;
}
