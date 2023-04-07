#include "combination.h"

Combination::Combination(){

}

Combination::Combination(Card** cards, CombinationType type, int numberOfCards){
    this->cards = cards;
    this->type = type;
    this->numberOfCards = numberOfCards;
}

Combination::~Combination(){
    delete[] cards;
}

bool Combination::containsCard(Card* card){
    for (int i = 0; i < getNumberOfCards(); i++){
        if (cards[i]->equals(card))
            return true;
    }
    return false;
}

CombinationType Combination::getType(){
    return this->type;
}

bool Combination::hasType(CombinationType type){
    return this->type == type;
}

float Combination::getValue(){
    return value;
}

int Combination::getNumberOfCards(){
    return numberOfCards;
}

Card* Combination::getCard(int index){
    return cards[index];
}

bool Combination::equals(Combination* otherCombination){
    if (hasType(otherCombination->getType())){
        for (int i = 0; i < numberOfCards; i++){
            if (!(otherCombination->containsCard(cards[i])))
                return false;
        }
        return true;
    }
    return false;
}

bool Combination::canBePlayed(Combination *last){
    Combination *current = this;
    // Last combination on table is not a bomb
    if (!(last->hasType(FOUROFAKIND) || last->hasType(STRAIGHTFLUSH))){
        // Any combination of the same type and same number of cards and value greater than the value of the last combination can be played
        if (current->hasType(last->getType()) && current->getNumberOfCards() == last->getNumberOfCards() &&
                current->getValue() > last->getValue())
            return true;
        // Any bomb combination can be played
        if (current->hasType(FOUROFAKIND) || current->hasType(STRAIGHTFLUSH))
            return true;
    }
    // Last combination on table is a four of a kind bomb
    else if (last->hasType(FOUROFAKIND)){
        // Any four of a kind bomb with value greater than the value of the last combination can be played
        if (current->hasType(FOUROFAKIND) && current->getValue() > last->getValue())
            return true;
        // Any straight flush bomb can be played
        if (current->hasType(STRAIGHTFLUSH))
            return true;
    }
    // Last combination on table is a straight flush bomb
    else if (last->hasType(STRAIGHTFLUSH)){
        // Any straight flush bomb with more cards can be played
        if (current->hasType(STRAIGHTFLUSH) && current->getNumberOfCards() > last->getNumberOfCards())
            return true;
        // Any straight flush bomb with equal number of cards and value greater than the value of the last combination can be played
        if (current->hasType(STRAIGHTFLUSH) && current->getNumberOfCards() == last->getNumberOfCards() &&
                (current->getValue() > last->getValue()))
            return true;
    }
    // If none of the above returns true then the current combination cannot be played
    return false;
}

string Combination::toString(){
    string combinationTypeArray[] = {"SINGLE", "PAIR", "THREEOFAKIND", "STAIRS", "FULLHOUSE",
                                     "STRAIGHT", "FOUROFAKIND", "STRAIGHTFLUSH"};
    string str = combinationTypeArray[type];
    str += "[";
    for (int i = 0; i < getNumberOfCards(); i++){
        str += " " + cards[i]->toString();
    }
    str += " ]";
    return str;
}

Single::Single(Card* card) : Combination(){
    cards = new Card*[1];
    cards[0] = card;
    type = SINGLE;
    numberOfCards = 1;
    value = card->hasSuit(PHOENIX) ? card->getValue() + 0.5 : card->getValue();
}

void Single::setValue(float value){
    if (cards[0]->hasSuit(PHOENIX)){
        cards[0]->setValue(value);
        this->value = value + 0.5;
    }
}

Pair::Pair(Card* card1, Card* card2) : Combination(){
    cards = new Card*[2];
    cards[0] = card1;
    cards[1] = card2;
    type = PAIR;
    numberOfCards = 2;
    value = card1->getValue();
}

ThreeOfAKind::ThreeOfAKind(Card* card1, Card* card2, Card* card3) : Combination(){
    cards = new Card*[3];
    cards[0] = card1;
    cards[1] = card2;
    cards[2] = card3;
    type = THREEOFAKIND;
    numberOfCards = 3;
    value = card1->getValue();
}

Stairs::Stairs(Card** cards, int numberOfCards) : Combination(cards, STAIRS, numberOfCards){
    value = cards[numberOfCards - 1]->getValue();
}

Straight::Straight(Card** cards, int numberOfCards) : Combination(cards, STRAIGHT, numberOfCards){
    value = cards[numberOfCards - 1]->getValue();
}

bool Straight::cardsHaveTheSameSuit(){
    // Check if all cards of the combination have the same suit
    int suit = cards[0]->getSuit();
    int numCardsWithSameSuit = 1;
    for (int i = 1; i < numberOfCards; i++){
        if (cards[i]->getSuit() == suit)
            numCardsWithSameSuit++;
        else
            break;
    }
    return numCardsWithSameSuit == numberOfCards;
}

FullHouse::FullHouse(ThreeOfAKind* combination1, Pair* combination2) : Combination(){
    numberOfCards = combination1->getNumberOfCards() + combination2->getNumberOfCards();
    cards = new Card*[numberOfCards];
    for (int i = 0; i < combination1->getNumberOfCards(); i++)
        cards[i] = combination1->getCard(i);
    for (int i = 0; i < combination2->getNumberOfCards(); i++)
        cards[i + combination1->getNumberOfCards()] = combination2->getCard(i);
    type = FULLHOUSE;
    value = 100 * combination1->getCard(0)->getValue() + combination2->getCard(0)->getValue();
}

FourOfAKind::FourOfAKind(Card* card1, Card* card2, Card* card3, Card* card4) : Combination(){
    cards = new Card*[4];
    cards[0] = card1;
    cards[1] = card2;
    cards[2] = card3;
    cards[3] = card4;
    type = FOUROFAKIND;
    numberOfCards = 4;
    value = cards[0]->getValue();
}

StraightFlush::StraightFlush(Straight* combination) : Combination(){
    numberOfCards = combination->getNumberOfCards();
    cards = new Card*[numberOfCards];
    for (int i = 0; i < numberOfCards; i++)
        cards[i] = combination->getCard(i);
    type = STRAIGHTFLUSH;
    value = cards[numberOfCards - 1]->getValue();
}
