#include <iostream>
#include <sstream>
#include "hand.h"
#include "card.h"
#include "combination.h"

Hand::Hand(){
    currentNumberOfCards = 0;
    allCombinationsSize = 0;
    allCombinations = new Combination*[allCombinationsSize];
    cards = new Card*[14];
}

Hand::~Hand(){
    for (int i = 0; i < allCombinationsSize; i++)
        delete allCombinations[i];
    allCombinationsSize = 0;
    delete[] allCombinations;
    delete[] cards;
}

void Hand::clearHand(){
    //for (int i = 0; i < allCombinationsSize; i++)
    //    delete allCombinations[i];
    allCombinationsSize = 0;
    allCombinations = new Combination*[allCombinationsSize];
}

int Hand::getNumberOfCombinations(){
    return allCombinationsSize;
}

Combination* Hand::getCombination(int index){
    return allCombinations[index];
}

void Hand::addCard(Card *card)
{
    int index = 0;
    while(index < currentNumberOfCards && (cards[index]->getValue() < card->getValue() ||
          (cards[index]->getValue() == card->getValue() && cards[index]->getSuit() > card->getSuit()))){
        index++;
    }
    // Move all cards to the right until index
    for (int j = currentNumberOfCards - 1; j >= index; j--)
        cards[j + 1] = cards[j];
    cards[index] = card;
//    cards[currentNumberOfCards] = card;
    currentNumberOfCards++;
}

void Hand::removeCard(Card* card){
    // Find the index of the card
    int index = -1;
    for (int i = 0; i < currentNumberOfCards; i++){
        if (cards[i]->equals(card)){
            index = i;
            break;
        }
    }
    // "Remove" the found card by moving all cards to the left until index
    for (; index < currentNumberOfCards - 1; index++)
        cards[index] = cards[index + 1];
    cards[currentNumberOfCards - 1] = NULL;
    currentNumberOfCards--;
}

void Hand::removeCombination(Combination* combination){
    // First remove all cards of combination
    for (int i = 0; i < combination->getNumberOfCards(); i++)
        removeCard(combination->getCard(i));
    // Remove the combination
    Combination** newCombinations = new Combination*[allCombinationsSize - 1];
    int j = 0;
    for (int i = 0; i < allCombinationsSize; i++){
        if (!(allCombinations[i]->equals(combination)))
            newCombinations[j++] = allCombinations[i];
    }
    delete[] allCombinations;
    allCombinations = newCombinations;
    allCombinationsSize--;
}

int Hand::getCardCount(){
    return currentNumberOfCards;
}

Card *Hand::getCard(int index){
    return cards[index];
}

string Hand::toString(){
    string str;
    for (int i = 0; i < currentNumberOfCards; i++)
        str += " " + getCard(i)->toString();
    return str;
}

string Hand::numberOfCardsToString(){
    stringstream ss;
    ss << currentNumberOfCards;
    return ss.str();
}

void Hand::addCombinationsToHand(Combination** combinations, int numCombinations){
    int newCombinationsSize = allCombinationsSize + numCombinations;
    Combination** newCombinations = new Combination*[newCombinationsSize];
    for (int i = 0; i < allCombinationsSize; i++)
        newCombinations[i] = allCombinations[i];
    for (int i = 0; i < numCombinations; i++)
        newCombinations[allCombinationsSize + i] = combinations[i];
    delete[] combinations;
    delete[] allCombinations;
    allCombinationsSize = newCombinationsSize;
    allCombinations = newCombinations;
}

void Hand::setPhoenixValue(int value){
    int phoenixIndex = -1;
    for (int i = 0; i < currentNumberOfCards; i++){
        if (cards[i]->hasSuit(PHOENIX))
            phoenixIndex = i;
    }
    if (phoenixIndex >= 0){
        Card* phoenix = cards[phoenixIndex];
        phoenix->setValue(value);
        removeCard(phoenix);
        addCard(phoenix);
    }
}

void Hand::createAllCombinations(){
    int numSingles;
    Combination** singles = findSingles(cards, currentNumberOfCards, numSingles);
    addCombinationsToHand(singles, numSingles);

    int numPairs;
    Combination** pairs = findPairs(cards, currentNumberOfCards, numPairs);
    addCombinationsToHand(pairs, numPairs);

    int numThrees;
    Combination** threes = findThreeOfAKinds(cards, currentNumberOfCards, numThrees);
    addCombinationsToHand(threes, numThrees);

    int numStairs;
    Combination** stairs = findStairs(cards, currentNumberOfCards, numStairs);
    addCombinationsToHand(stairs, numStairs);

    int numFullHouses;
    Combination** fullHouses = findFullHouses(cards, currentNumberOfCards, numFullHouses);
    addCombinationsToHand(fullHouses, numFullHouses);

    int numStraights;
    Combination** straights = findStraights(cards, currentNumberOfCards, numStraights, false);
    addCombinationsToHand(straights, numStraights);

    int numFours;
    Combination** fours = findFourOfAKinds(cards, currentNumberOfCards, numFours);
    addCombinationsToHand(fours, numFours);

    int numStraightFlushes;
    Combination** straightFlushes = findStraightFlushes(cards, currentNumberOfCards, numStraightFlushes);
    addCombinationsToHand(straightFlushes, numStraightFlushes);
}

Combination** Hand::findLargerStraight(Combination** inputStraights, int inputSize, int& outputSize){
    outputSize = 0;
    for (int i = 0; i < inputSize - 1; i++)
    {
        int j = i + 1;
        while (j < inputSize && inputStraights[i]->getValue() + 1 == inputStraights[j]->getValue())
        {
            outputSize++;
            j++;
        }
    }
    Combination** outputStraights = new Combination*[outputSize];

    int finalCombinationsSize = 0;
    for (int i = 0; i < inputSize - 1; i++)
    {
        int j = i + 1;
        while (j < inputSize && inputStraights[i]->getValue() + 1 == inputStraights[j]->getValue())
        {
            // Get all cards without duplicates
            int numCards = 0;
            Card** combination = new Card*[inputStraights[i]->getNumberOfCards() + inputStraights[j]->getNumberOfCards()];
            for (int a = 0; a < inputStraights[i]->getNumberOfCards(); a++)
                combination[numCards++] = inputStraights[i]->getCard(a);
            for (int a = 0; a < inputStraights[j]->getNumberOfCards(); a++)
            {
                Card* toAdd = inputStraights[j]->getCard(a);
                bool alreadyExists = false; // First check if the card already exists
                for (int b = 0; b < numCards; b++)
                    alreadyExists = alreadyExists || (combination[b] == toAdd);
                if (!alreadyExists)
                    combination[numCards++] = inputStraights[j]->getCard(a);
            }
            // Delete extra space
            Card** newcombination = new Card*[numCards];
            for (int b = 0; b < numCards; b++)
                newcombination[b] = combination[b];
            delete[] combination;
            if (inputStraights[j]->hasType(STRAIGHT))
                outputStraights[finalCombinationsSize++] = new Straight(newcombination, numCards);
            else //if (inputStraights[j]->hasType(STAIRS))
                outputStraights[finalCombinationsSize++] = new Stairs(newcombination, numCards);
            j++;
        }
    }
    return outputStraights;
}

Combination** Hand::findSingles(Card** cards, int numberOfCards, int& numSingles){
    numSingles = numberOfCards;
    Combination** singles = new Combination*[numSingles];
    for (int i = 0; i < numberOfCards; i++)
        singles[i] = new Single(cards[i]);
    return singles;
}

Combination** Hand::findPairs(Card** cards, int numberOfCards, int& numPairs){
    numPairs = 0;
    Combination** pairs = new Combination*[1000];
    for (int i = 0; i < numberOfCards - 1; i++)
    {
        int j = i + 1;
        while (j < numberOfCards && cards[i]->getValue() == cards[j]->getValue())
        {
            if (cards[i]->canBeInCombination() && cards[j]->canBeInCombination())
                pairs[numPairs++] = new Pair(cards[i], cards[j]);
            j++;
        }
    }
    return resizeArray(pairs, numPairs);
}

Combination** Hand::findThreeOfAKinds(Card** cards, int numberOfCards, int& numThrees){
    numThrees = 0;
    Combination** threes = new Combination*[1000];
    for (int i = 0; i < numberOfCards - 2; i++)
    {
        int j = i + 1;
        while (j < numberOfCards - 1 && cards[i]->getValue() == cards[j]->getValue())
        {
            int k = j + 1;
            while (k < numberOfCards && cards[i]->getValue() == cards[k]->getValue())
            {
                if (cards[i]->canBeInCombination() && cards[j]->canBeInCombination() && cards[k]->canBeInCombination())
                    threes[numThrees++] = new ThreeOfAKind(cards[i], cards[j], cards[k]);
                k++;
            }
            j++;
        }
    }
    return resizeArray(threes, numThrees);
}

Combination** Hand::findStairs(Card** cards, int numberOfCards, int& numStairs){
    numStairs = 0;
    Combination** stairs = new Combination*[1000];

    // Get pairs and convert them to one-stairs
    int oneStairsSize;
    Combination** pairs = findPairs(cards, numberOfCards, oneStairsSize);
    Combination** oneStairs = new Combination*[oneStairsSize];
    for (int i = 0; i < oneStairsSize; i++){
        Card** sCards =  new Card*[2]; sCards[0] = pairs[i]->getCard(0); sCards[1] = pairs[i]->getCard(1);
        oneStairs[i] = new Stairs(sCards, 2);
        delete pairs[i];
    }
    delete[] pairs;

    int stairLength = 2;
    int inputSize = oneStairsSize;
    Combination** inputStairs = oneStairs;
    while (stairLength < (numberOfCards / 2) + 1)
    {
        // Find all stairs of size stairLength
        int outputSize;
        Combination** outputStairs = findLargerStraight(inputStairs, inputSize, outputSize);

        // Keep all stairs with stairLength larger than or equal to 2
        if (stairLength >= 2)
        {
            for (int i = 0; i < outputSize; i++)
                stairs[numStairs++] = outputStairs[i];
        }
        else{
            for (int i = 0; i < inputSize; i++)
                delete inputStairs[i];
        }

        delete[] inputStairs;
        inputSize = outputSize;
        inputStairs = outputStairs;
        stairLength++;
    }
    delete[] inputStairs;

    return resizeArray(stairs, numStairs);
}

Combination** Hand::findFullHouses(Card** cards, int numberOfCards, int& numFullHouses){
    numFullHouses = 0;
    Combination** fullHouses = new Combination*[1000];

    // Get pairs
    int pairsSize;
    Combination** pairs = findPairs(cards, numberOfCards, pairsSize);

    // Get threes of a kind
    int threesSize = 0;
    Combination** threes = findThreeOfAKinds(cards, numberOfCards, threesSize);

    for (int i = 0; i < threesSize; i++)
    {
        for (int j = 0; j < pairsSize; j++)
        {
            // Check if the two combinations contain any same card
            if (!(threes[i]->containsCard(pairs[j]->getCard(0)) || threes[i]->containsCard(pairs[j]->getCard(1))))
                fullHouses[numFullHouses++] = new FullHouse((ThreeOfAKind*)threes[i], (Pair*)pairs[j]);
        }
    }
    for (int i = 0; i < threesSize; i++)
        delete threes[i];
    delete[] threes;
    for (int j = 0; j < pairsSize; j++)
        delete pairs[j];
    delete[] pairs;
    return resizeArray(fullHouses, numFullHouses);
}

Combination** Hand::findStraights(Card** cards, int numberOfCards, int& numStraights, bool keepAlsoFlushes){
    numStraights = 0;
    Combination** straights = new Combination*[1000];

    // Get singles and convert them to one-straights
    int oneCardStraightsSize = 0;
    for (int i = 0; i < numberOfCards; i++)
    {
        if (cards[i]->canBeInCombination()) oneCardStraightsSize++;
    }
    int singlesSize;
    Combination** singles = findSingles(cards, numberOfCards, singlesSize);
    Combination** oneCardStraights = new Combination*[oneCardStraightsSize];
    oneCardStraightsSize = 0;
    for (int i = 0; i < singlesSize; i++)
    {
        if (singles[i]->getCard(0)->canBeInCombination()){
            Card** sCards =  new Card*[1]; sCards[0] = singles[i]->getCard(0);
            oneCardStraights[oneCardStraightsSize++] = new Straight(sCards, 1);
        }
        delete singles[i];
    }
    delete[] singles;

    int straightLength = 2;
    int inputSize = oneCardStraightsSize;
    Combination** inputStraights = oneCardStraights;
    while (straightLength < numberOfCards + 1)
    {
        // Find all straights of size straightLength
        int outputSize = 0;
        Combination** outputStraights = findLargerStraight(inputStraights, inputSize, outputSize);

        // Keep all straights with straightLength larger than or equal to 5
        if (straightLength >= 5)
        {
            for (int i = 0; i < outputSize; i++)
            {
                if (keepAlsoFlushes || (!((Straight*)outputStraights[i])->cardsHaveTheSameSuit()))
                    straights[numStraights++] = outputStraights[i];
            }
        }
        else{
            for(int i = 0; i < inputSize; i++)
                delete inputStraights[i];
        }

        delete[] inputStraights;
        inputSize = outputSize;
        inputStraights = outputStraights;
        straightLength++;
    }
    delete[] inputStraights;

    return resizeArray(straights, numStraights);
}

Combination** Hand::findFourOfAKinds(Card** cards, int numberOfCards, int& numFours){
    numFours = 0;
    Combination** fours = new Combination*[1000];
    for (int i = 0; i < numberOfCards - 3; i++)
    {
        int j = i + 1;
        while (j < numberOfCards - 2 && cards[i]->getValue() == cards[j]->getValue())
        {
            int k = j + 1;
            while (k < numberOfCards - 1 && cards[i]->getValue() == cards[k]->getValue())
            {
                int l = k + 1;
                while (l < numberOfCards && cards[i]->getValue() == cards[l]->getValue())
                {
                    if (cards[i]->canBeInBomb() && cards[j]->canBeInBomb() && cards[k]->canBeInBomb() && cards[l]->canBeInBomb())
                        fours[numFours++] = new FourOfAKind(cards[i], cards[j], cards[k], cards[l]);
                    l++;
                }
                k++;
            }
            j++;
        }
    }
    return resizeArray(fours, numFours);
}

Combination** Hand::findStraightFlushes(Card** cards, int numberOfCards, int& numStraightFlushes){
    numStraightFlushes = 0;
    Combination** straightFlushes = new Combination*[1000];

    int straightsSize = 0;
    Combination** straights = findStraights(cards, numberOfCards, straightsSize, true);

    for (int i = 0; i < straightsSize; i++)
    {
        if (((Straight*)straights[i])->cardsHaveTheSameSuit())
            straightFlushes[numStraightFlushes++] = new StraightFlush((Straight*)straights[i]);
    }
    return resizeArray(straightFlushes, numStraightFlushes);
}

Combination** Hand::resizeArray(Combination** oldArray, int newSize){
    Combination** newArray = new Combination*[newSize];
    for (int i = 0; i < newSize; i++)
        newArray[i] = oldArray[i];
    delete[] oldArray;
    return newArray;
}
