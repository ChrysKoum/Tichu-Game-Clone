#include <sstream>
#include "card.h"

Card::Card(){

}

Card::Card(int value, CardSuit suit){
    this->value = value;
    this->suit = suit;
}

Card::~Card(){

}

CardSuit Card::getSuit(){
	return suit;
}

bool Card::hasSuit(CardSuit suit){
	return this->suit == suit;
}

int Card::getValue(){
	return value;
}

void Card::setValue(int value){
    if (suit == PHOENIX)
        this->value = value;
}

string Card::toString(){
    string suitStringArray[] = {"JADE", "SWORD", "PAGODA", "STAR", "MAHJONG", "DRAGON", "PHOENIX", "DOG"};
    string suitString = suitStringArray[suit];
	string valueString;
    switch (value){
        case 11: valueString = "J"; break;
        case 12: valueString = "Q"; break;
        case 13: valueString = "K"; break;
        case 14: valueString = "A"; break;
        default: stringstream ss; ss << value; valueString = ss.str();
    }
    return valueString + ":" + suitString;
}

bool Card::equals(Card* otherCard){
    return value == otherCard->value && suit == otherCard->suit;
}
