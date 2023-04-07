#include "card.h"

// TODO: Implement here the methods of SimpleCard and SpecialCard
// Copy your implementation from the fourth deliverable

SimpleCard :: SimpleCard(int value, CardSuit suit):Card(value,suit){}

int SimpleCard :: getPoints(){
    if(value == 5){
        return 5;
    }
    if(value == 10 || value == 13){
        return 10;
    }
    return 0;
}

bool SimpleCard :: canBeInCombination()
{
    return 1;
}

bool SimpleCard :: canBeInBomb()
{
    return 1;
}
    SpecialCard::SpecialCard(CardSuit suit):Card(){
        this->suit = suit;
        if(suit == MAHJONG)
            value = 1;
        else if(suit == DRAGON)
            value = 15;
        else value = -1;
    }

    int SpecialCard::getPoints(){
        if(suit == PHOENIX)
            return -25;
        if(suit == DRAGON)
            return 25;
        return 0;
    }

    bool SpecialCard::canBeInCombination(){
        if(suit == DOG || suit == DRAGON)
            return 0;
        return 1;
    }

    bool SpecialCard::canBeInBomb(){
        return 0;
    }
