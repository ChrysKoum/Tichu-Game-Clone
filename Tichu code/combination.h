#ifndef COMBINATION_H
#define COMBINATION_H

#include <string>
#include "card.h"

using namespace std;

/**
 * Enumeration used to represent the different types of combinations.
 */
enum CombinationType {SINGLE, PAIR, THREEOFAKIND, STAIRS, FULLHOUSE, STRAIGHT, FOUROFAKIND, STRAIGHTFLUSH};

/**
 * Class denoting a combination. Combinations can be single cards, pairs, threes of a king, etc.
 */
class Combination{
protected:
    Card** cards;
    CombinationType type;
    int numberOfCards;
    float value;

protected:
    /**
     * Initializes the combination without setting any parameter values. This method should
     * only called by the constructor of any classes extending the Combination class.
     */
    Combination();

    /**
     * Initializes the combination with its cards and its type. This method should
     * only called by the constructor of any classes extending the Combination class.
     *
     * @param cards the cards of the combination.
     * @param type the type of the combination (one of the CombinationType).
     * @param numberOfCards the number of cards of the combination.
     */
    Combination(Card** cards, CombinationType type, int numberOfCards);

public:
    /**
     * Deletes the combination by only deleting the cards array. Warning: this method
     * does not also delete each individual card! Cards are deleted by the deck.
     */
    ~Combination();

    /**
     * Returns a card of the combination given its index.
     *
     * @param index the index of the card to be returned.
     * @return a card of the combination given its index.
     */
    Card* getCard(int index);

    /**
     * Checks whether the combination contains the card that is given as a parameter.
     *
     * @param card the card to check if it is contained in the combination.
     * @return true if the combination contains the card given, or false otherwise.
     */
    bool containsCard(Card* card);

    /**
     * Returns the type of the combination.
     *
     * @return the type of the combination.
     */
    CombinationType getType();

    /**
     * Checks whether type of the combination is the same as the one given.
     *
     * @param type the type to be checked against that of the combination.
     * @return true if type of the combination is the same as the one given, or false otherwise.
     */
    bool hasType(CombinationType type);

    /**
     * Returns the value of the combination.
     *
     * @return the value of the combination.
     */
    float getValue();

    /**
     * Returns the number of cards of the combination.
     *
     * @return the number of cards of the combination.
     */
    int getNumberOfCards();

    /**
     * Checks if this combination is equal to the combination given. This happens if the
     * the two combinations have the same type as well as the same cards.
     *
     * @param otherCombination the combination to compare with this combination.
     * @return true if this combination is equal to the other combination, or false otherwise.
     */
    bool equals(Combination* otherCombination);

    /**
     * Checks if the current combination can be played after the last combination.
     *
     * @param last the last combination to check if the current combination is playable.
     * @return true if the current combination can be played after the last one, or false otherwise.
     */
    bool canBePlayed(Combination *last);

    /**
     * Returns a string representation of the combination.
     *
     * @return the combination as string.
     */
    string toString();
};

/**
 * Class denoting a single combination. Example: SINGLE[ 8:JADE ]
 */
class Single : public Combination{
public:
    /**
     * Initializes the single combination with one card. This method should set all
     * variables of the combination.
     *
     * @param card the card of the combination.
     */
    Single(Card* card);

    /**
     * Sets the value of the combination if it is a Phoenix.
     *
     * @param value the value to set the combination to.
     */
    void setValue(float value);
};

/**
 * Class denoting a pair combination. Example: PAIR[ 8:JADE 8:STAR ]
 */
class Pair : public Combination{
public:
    /**
     * Initializes the pair combination with two cards. This method should set all
     * variables of the combination.
     *
     * @param card1 the first card of the combination.
     * @param card2 the second card of the combination.
     */
    Pair(Card* card1, Card* card2);
};

/**
 * Class denoting a three of a kind combination. Example: THREEOFAKIND[ 5:PAGODA 5:JADE 5:STAR ]
 */
class ThreeOfAKind : public Combination{
public:
    /**
     * Initializes the three of a kind combination with three cards. This method should set all
     * variables of the combination.
     *
     * @param card1 the first card of the combination.
     * @param card2 the second card of the combination.
     * @param card3 the third card of the combination.
     */
    ThreeOfAKind(Card* card1, Card* card2, Card* card3);
};

/**
 * Class denoting a stairs combination. Example: STAIRS[ 2:PAGODA 2:JADE 3:PAGODA 3:STAR 4:PAGODA 4:SWORD ]
 */
class Stairs : public Combination{
public:
    /**
     * Initializes the stairs combination with a dynamic array of cards. This method should set all
     * variables of the combination.
     *
     * @param cards the cards of the combination.
     * @param numberOfCards the number of cards of the combination.
     */
    Stairs(Card** cards, int numberOfCards);
};

/**
 * Class denoting a full house combination. Example: FULLHOUSE[ 5:PAGODA 5:JADE 5:STAR 2:PAGODA 2:JADE ]
 */
class FullHouse : public Combination{
public:
    /**
     * Initializes the full house combination with a three of kind and a pair combination. This method
     * should set all variables of the combination. Note that this method should not delete the
     * combinations given as input.
     *
     * @param combination1 the three of a kind combination.
     * @param combination2 the pair combination.
     */
    FullHouse(ThreeOfAKind* combination1, Pair* combination2);
};

/**
 * Class denoting a straight combination. Example: STRAIGHT[ 2:PAGODA 3:JADE 4:STAR 5:STAR 6:SWORD ]
 */
class Straight : public Combination{
public:
    /**
     * Initializes the straight combination with a dynamic array of cards. This method should set all
     * variables of the combination.
     *
     * @param cards the cards of the combination.
     * @param numberOfCards the number of cards of the combination.
     */
    Straight(Card** cards, int numberOfCards);

    /**
     * Checks whether all cards of this straight have the same suit.
     *
     * @return true if all cards of this straight have the same suit, or false otherwise.
     */
    bool cardsHaveTheSameSuit();
};

/**
 * Class denoting a four of a kind combination. Example: FOUROFAKIND[ 8:PAGODA 8:SWORD 8:JADE 8:STAR ]
 */
class FourOfAKind : public Combination{
public:
    /**
     * Initializes the four of a kind combination with four cards. This method should set all
     * variables of the combination.
     *
     * @param card1 the first card of the combination.
     * @param card2 the second card of the combination.
     * @param card3 the third card of the combination.
     * @param card4 the fourth card of the combination.
     */
    FourOfAKind(Card* card1, Card* card2, Card* card3, Card* card4);
};

/**
 * Class denoting a straight flush combination. Example: STRAIGHTFLUSH[ 4:JADE 5:JADE 6:JADE 7:JADE 8:JADE ]
 */
class StraightFlush : public Combination{
public:
    /**
     * Initializes the straight flush combination with a straight combination. This method should
     * set all variables of the combination. Note that this method should not check whether the cards
     * of the given combination all have the same suit (this is already checked). Also this method
     * should not delete the combinations given as input.
     *
     * @param combination the straight combination.
     */
    StraightFlush(Straight* combination);
};

#endif // COMBINATION_H
