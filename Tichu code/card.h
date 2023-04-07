#ifndef CARD_H
#define CARD_H

#include <string>

using namespace std;

/**
 * Enumeration used to represent the different suits of cards.
 */
enum CardSuit {JADE, SWORD, PAGODA, STAR, MAHJONG, DRAGON, PHOENIX, DOG};

/**
 * Class denoting a card.
 */
class Card
{
protected:
    CardSuit suit; // the suit of the card, one of JADE, SWORD, PAGODA, STAR,
                   // or one of the special cards MAHJONG, DRAGON, PHOENIX, DOG
    int value;

    /**
     * Initializes the card without setting any parameter values. This method should
     * only called by the constructor of any classes extending the Combination class.
     */
    Card();

    /**
     * Initializes the card with its value and its suit.
     *
     * @param value the value of the card.
     * @param suit the suit of the card.
     */
    Card(int value, CardSuit suit);

public:
    /**
     * Deletes the card.
     */
    virtual ~Card();

    /**
     * Returns the suit of the card.
     *
     * @return the suit of the card.
     */
    CardSuit getSuit();

    /**
     * Checks whether the suit of the card is the same as the one given.
     *
     * @param suit the suit to be checked against that of the card.
     * @return true if the suit of the card is the same as the one given, or false otherwise.
     */
    bool hasSuit(CardSuit suit);

    /**
     * Returns the value of the card.
     *
     * @return the value of the card.
     */
    int getValue();

    /**
     * Sets the value of the Phoenix. This function should be called once
     * before every turn of the player that has the Phoenix in hand. If this
     * function is called on any other card, then nothing happens.
     *
     * @param value the value to set the Phoenix to.
     */
    void setValue(int value);

    /**
     * Checks if this card is equal to the card given.
     *
     * @param otherCard the card to compare with this card.
     * @return true if this card is equal to the other card, or false otherwise.
     */
    bool equals(Card* otherCard);

    /**
     * Returns the points of the card.
     * This method has to be implemented from all derived classes of Card.
     *
     * @return the points of the card.
     */
    virtual int getPoints() = 0;

    /**
     * Checks whether the card can participate in a combination.
     * This method has to be implemented from all derived classes of Card.
     *
     * @return true if the card can be in a combination, or false otherwise.
     */
    virtual bool canBeInCombination() = 0;

    /**
     * Checks whether the card can participate in a bomb combination.
     * This method has to be implemented from all derived classes of Card.
     *
     * @return true if the card can be in a bomb combination, or false otherwise.
     */
    virtual bool canBeInBomb() = 0;

    /**
     * Returns a string representation of the card.
     *
     * @return the card as string.
     */
    string toString();
};

/**
 * Class denoting a simple card.
 */
class SimpleCard : public Card{
public:
    /**
     * Initializes the simple card with its value and its suit.
     *
     * @param value the value of the card.
     * @param suit the suit of the card.
     */
    SimpleCard(int value, CardSuit suit);

    /**
     * Returns the points of the card. Fives (5) have 5 points, tens (10) have ten points
     * and kings (K) have 10 points. All other cards have 0 points.
     *
     * @return the points of the card.
     */
    int getPoints();

    /**
     * Checks whether this simple card can participate in a combination.
     *
     * @return true if the card can be in a combination, or false otherwise.
     */
    bool canBeInCombination();

    /**
     * Checks whether this simple card can participate in a bomb combination.
     *
     * @return true if the card can be in a bomb combination, or false otherwise.
     */
    bool canBeInBomb();
};

/**
 * Class denoting a special card.
 */
class SpecialCard : public Card{
public:
    /**
     * Initializes the special card with its suit. This method also has to initialize the value
     * of the special card. The Mah Jong should have value 1, the Dragon should have value 15,
     * the Phoenix should have value -1, and the Dog should have value -1.
     *
     * @param value the value of the card.
     * @param suit the suit of the card.
     */
    SpecialCard(CardSuit suit);

    /**
     * Returns the points of the card. The Dragon has 25 points, the Phoenix has -25 points
     * and all other cards have 0 points.
     *
     * @return the points of the card.
     */
    int getPoints();

    /**
     * Checks whether this special card can participate in a combination.
     *
     * @return true if the card can be in a combination, or false otherwise.
     */
    bool canBeInCombination();

    /**
     * Checks whether this special card can participate in a bomb combination.
     *
     * @return true if the card can be in a bomb combination, or false otherwise.
     */
    bool canBeInBomb();
};

#endif // CARD_H
