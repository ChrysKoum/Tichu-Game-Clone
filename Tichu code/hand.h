#ifndef HAND_H
#define HAND_H

#include <string>
#include "combination.h"

using namespace std;

/**
 * Class denoting a hand of a player.
 */
class Hand
{
private:
	Card** cards;
	int currentNumberOfCards;
    Combination** allCombinations;
    int allCombinationsSize;

public:
    /**
     * Initializes the hand that holds the cards.
     */
	Hand();

    /**
     * Deletes the hand by deleting its combinations and cards. Warning: this method
     * does not also delete each individual card! Cards are deleted by the deck.
     * However, this method deletes all combinations before deleting the combinations array.
     */
    ~Hand();

    /**
     * Clears the hand for a new round by clearing all combinations and setting the
     * value of the phoenix.
     */
    void clearHand();

    /**
     * Returns a combination of the hand given its index.
     *
     * @param index the index of the combination to be returned.
     * @return a combination of the hand given its index.
     */
    Combination* getCombination(int index);

    /**
     * Returns the number of combinations of the hand.
     *
     * @return the number of combinations of the hand.
     */
    int getNumberOfCombinations();

    /**
     * Adds a card to the hand.
     *
     * @param card the card to be added to the hand.
     */
	void addCard(Card* card);

    /**
     * Removes a card from the hand.
     *
     * @param card the card to be removed to the hand.
     */
	void removeCard(Card* card);

    /**
     * Removes a combination from the hand. This method also removes
     * all cards present in the combination.
     *
     * @param combination the combination to be removed to the hand.
     */
	void removeCombination(Combination* combination);

    /**
     * Returns the number of cards that are currently in the hand.
     *
     * @return the number of cards of the hand.
     */
	int getCardCount();

    /**
     * Returns a card of the hand given its index.
     *
     * @param index the index of the card to be returned.
     * @return a card of the hand given its index.
     */
	Card *getCard(int index);

    /**
     * Sets the value of the phoenix (if the hand has it) to a random
     * value between 2 and 14.
     *
     * @param value the value to set the phoenix to.
     */
    void setPhoenixValue(int value);

    /**
     * Returns a string representation of the hand, including all cards.
     *
     * @return the hand of the player as string.
     */
	string toString();

    /**
     * Returns the number of cards of the hand as a string.
     *
     * @return the number of cards of the hand as string.
     */
    string numberOfCardsToString();

    /**
     * Creates all the possible combinations of the hand given its cards. Combinations must
     * be put in the table allCombinations and the variable allCombinationsSize must be updated.
     */
    void createAllCombinations();

private:
    void addCombinationsToHand(Combination** combinations, int numCombinations);

    Combination** findLargerStraight(Combination** inputStraights, int inputSize, int& outputSize);

    Combination** findSingles(Card** cards, int numberOfCards, int& numSingles);
    Combination** findPairs(Card** cards, int numberOfCards, int& numPairs);
    Combination** findThreeOfAKinds(Card** cards, int numberOfCards, int& numThrees);
    Combination** findStairs(Card** cards, int numberOfCards, int& numStairs);
    Combination** findFullHouses(Card** cards, int numberOfCards, int& numFullHouses);
    Combination** findStraights(Card** cards, int numberOfCards, int& numStraights, bool keepAlsoFlushes);
    Combination** findFourOfAKinds(Card** cards, int numberOfCards, int& numFours);
    Combination** findStraightFlushes(Card** cards, int numberOfCards, int& numStraightFlushes);

    Combination** resizeArray(Combination** oldArray, int newSize);
};

#endif // HAND_H
