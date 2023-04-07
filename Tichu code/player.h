#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "hand.h"
#include "table.h"

using namespace std;

/**
 * Enumeration used to represent the different statuses of the player.
 */
enum PlayerStatus {HASNTPLAYED, PASSED, PLAYED, WONTHETRICK};

/**
 * Class that implements a player of the game.
 */
class Player
{
protected:
	int index;
	string name;
	Card** bucket; // the bucket of the player that contains the cards that are picked up by the player
    int bucketSize;  // the current size of the bucket (initialized to 0 and incremented when cards are added)
	PlayerStatus status; // the status of the player, one of HASNTPLAYED, PASSED, PLAYED, HASNOCARDSLEFT, WONTHETRICK
    string team;
	Hand* hand; // the hand of the player
public:

    /**
     * Initializes a player setting the index, the name, and the status.
     * The size of the bucket is also initialized to zero.
     *
     * @param index the index of the player.
     */
	Player(int index);

    /**
     * Deletes the player by deleting its hand and bucket. Warning: this method
     * does not also delete each individual card! Cards are deleted by the deck.
     */
    virtual ~Player();

    /**
     * Returns the status of the player.
     *
     * @return the status of the player.
     */
    PlayerStatus getStatus();

    /**
     * Sets the status of the player.
     *
     * @param status the status to set the player to.
     */
    void setStatus(PlayerStatus status);

    /**
     * Checks whether the status of the player is the same as the one given.
     *
     * @param status the status to be checked against that of the player.
     * @return true if the status of the player is the same as the one given, or false otherwise.
     */
    bool hasStatus(PlayerStatus status);

    /**
     * Returns the name of the player.
     *
     * @return the name of the player.
     */
    string getName();

    /**
     * Returns the number of cards of the hand of the player.
     *
     * @return the number of cards of the hand of the player.
     */
    int getNumberOfCards();

    /**
     * Checks whether the player's hand has no cards left.
     *
     * @return true if the hand of the player has no cards left, or false otherwise.
     */
	bool hasNoCardsLeft();

    /**
     * Checks whether the player's hand has the Mah Jong card.
     *
     * @return true if the hand of the player has the Mah Jong card, or false otherwise.
     */
    bool hasMahJong();

    /**
     * Checks whether the player's hand has the Phoenix card.
     *
     * @return true if the hand of the player has the Phoenix card, or false otherwise.
     */
    bool hasPhoenix();

    /**
     * Adds a card to the hand of the player. This method only
     * calls the method addCard of the hand.
     *
     * @param card the card to be added to the hand of the player.
     */
    void addCardToHand(Card* card);

    /**
     * Removes a combination from the hand of the player. This method only
     * calls the method removeCombination of the hand.
     *
     * @param combination the combination to be removed from the hand of the player.
     */
	void removeCombinationFromHand(Combination* combination);

    /**
     * Adds the cards of the given combination to the bucket of the player and increases the bucketSize accordingly.
     *
     * @param combination the combination of which the cards are added to the bucket of the player.
     */
	void addCombinationToBucket(Combination* combination);

    /**
     * Adds the given cards to the bucket of the player and increases the bucketSize accordingly.
     *
     * @param cards the cards to be added to the bucket of the player.
     * @param numberOfCards the number of cards that are added to the bucket of the player.
     */
	void addCardsToBucket(Card** cards, int numberOfCards);

    /**
     * Initializes (clears) the hand of the player and creates the combinations. This method only
     * calls the method clearHand and then the method createAllCombinations of the hand.
     */
    void createHandCombinations();

    /**
     * Computes and returns the number of combinations that are playable on top of the given combination.
     *
     * @param combination the top (last played) combination of the table to check how many combinations
                          can be played by the player.
     * @return the number of combinations that the player can play on top of the given combination.
     */
    int findNumberOfPlayableCombinations(Combination* combination);

    /**
     * Computes and returns the combinations that are playable on top of the given combination.
     *
     * @param combination the top (last played) combination of the table to check how many combinations
                          can be played by the player.
     * @return the combinations that the player can play on top of the given combination.
     */
    Combination** findPlayableCombinations(Combination* combination, int &numPlayableCombinations);

    /**
     * Helper method for calling the method setPhoenixValue. Full parameter documentation available at setPhoenixValue.
     */
    void setTheValueOfThePhoenix(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer);

    /**
     * Helper method for calling the method decideAndPlay. Full parameter documentation available at decideAndPlay.
     */
    Combination* playCombinationOrPass(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer);

    /**
     * Sets the value of the phoenix.
     *
     * This method has to be implemented from all derived classes of Player.
     *
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @return an integer from 1 to 14, determining the value of the Phoenix for this trick.
     */
    virtual int setPhoenixValue(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable) = 0;

    /**
     * Decides which of the playableCombinations is going to be played. The player can also decide to pass by returning -1.
     *
     * Warning: this method MUST return a combination if the lastCombinationOnTable given to it as a parameter is NULL.
     * In other words, if there is no combination on the table, then the player MUST play.
     *
     * This method has to be implemented from all derived classes of Player.
     *
     * @param playableCombinations the combinations that the player can play on top of the given combination as a dynamic array.
     * @param numPlayableCombinations the number of combinations that the player can play on top of the given combination.
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @return an integer as an index to the array playableCombinations, determining which combination will be played,
     *         or -1 if the player does not wish to play. The returned index MUST be from 0 to numPlayableCombinations-1.
     */
    virtual int decideAndPlay(Combination** playableCombinations, int numPlayableCombinations, Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable) = 0;

    /**
     * Takes all cards from the hand and the bucket of the player given and adds them to the bucket of
     * the player.
     *
     * @param otherPlayer the player from which all the cards (hand and bucket) are taken.
     */
    void getHandAndBucketFromPlayer(Player* otherPlayer);

    /**
     * Returns a string representation of the player, including the player's name
     * and the cards of the player's hand.
     *
     * @return the player as string.
     */
	string toString();

    /**
     * Computes and returns the number of points of the cards in the player's bucket.
     *
     * @return the total number of points for all cards in the player's bucket.
     */
	int countBucketPoints();
};

/**
 * Class that implements a computer player that plays randomly.
 */
class ComputerPlayer : public Player
{
public:
    /**
     * Initializes a computer player setting the index and all variables of the player.
     *
     * @param index the index of the player.
     */
	ComputerPlayer(int index);

    /**
     * Sets the value of the phoenix to a random value between 1 and 14.
     *
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @return an integer from 1 to 14, determining the value of the Phoenix for this trick.
     */
    int setPhoenixValue(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable);

    /**
     * Decides which of the playableCombinations is going to be played. The player can also decide to pass by returning -1.
     * This computer player initially decides to play with 75% probability or pass with 25% probability. After that (and
     * if the player decides to play), then the combination that is played is randomly selected from the list of all
     * playable combinations.
     *
     * Warning: this method MUST return a combination if the lastCombinationOnTable given to it as a parameter is NULL.
     * In other words, if there is no combination on the table, then the player MUST play.
     *
     * @param playableCombinations the combinations that the player can play on top of the given combination as a dynamic array.
     * @param numPlayableCombinations the number of combinations that the player can play on top of the given combination.
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @return an integer as an index to the array playableCombinations, determining which combination will be played,
     *         or -1 if the player does not wish to play. The returned index MUST be from 0 to numPlayableCombinations-1.
     */
    int decideAndPlay(Combination** playableCombinations, int numPlayableCombinations, Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable);
};

/**
 * Class that implements a human player that plays according to the input given by the console.
 */
class HumanPlayer : public Player
{
public:
    /**
     * Initializes a human player setting the index and all variables of the player.
     *
     * @param index the index of the player.
     */
	HumanPlayer(int index);

    /**
     * Sets the value of the phoenix to a value between 1 and 14 given by the user.
     *
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @param combination the top (last played) combination of the table.
     * @return an integer from 1 to 14, determining the value of the Phoenix for this trick.
     */
    int setPhoenixValue(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable);

    /**
     * Decides which of the playableCombinations is going to be played. The player can also decide to pass by returning -1.
     * This player prints all combinations and requests input in the console in order to decide what to play or (if allowed)
     * whether to pass.
     *
     * Warning: this method MUST return a combination if the lastCombinationOnTable given to it as a parameter is NULL.
     * In other words, if there is no combination on the table, then the player MUST play.
     *
     * @param playableCombinations the combinations that the player can play on top of the given combination as a dynamic array.
     * @param numPlayableCombinations the number of combinations that the player can play on top of the given combination.
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @return an integer as an index to the array playableCombinations, determining which combination will be played,
     *         or -1 if the player does not wish to play. The returned index MUST be from 0 to numPlayableCombinations-1.
     */
    int decideAndPlay(Combination** playableCombinations, int numPlayableCombinations, Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable);
};

/**
 * Class that implements a smart player that plays according to the state of the game.
 */
class SmartPlayer : public Player
{
public:
    /**
     * Initializes a smart player setting the index and all variables of the player.
     *
     * @param index the index of the player.
     */
	SmartPlayer(int index);

    /**
     * Sets the value of the phoenix according to a smart strategy.
     *
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @param combination the top (last played) combination of the table.
     * @return an integer from 1 to 14, determining the value of the Phoenix for this trick.
     */
    int setPhoenixValue(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable);

    /**
     * Decides which of the playableCombinations is going to be played or decides to pass by returning -1,
     * according to a smart strategy.
     *
     * Warning: this method MUST return a combination if the lastCombinationOnTable given to it as a parameter is NULL.
     * In other words, if there is no combination on the table, then the player MUST play.
     *
     * @param playableCombinations the combinations that the player can play on top of the given combination as a dynamic array.
     * @param numPlayableCombinations the number of combinations that the player can play on top of the given combination.
     * @param table the table of the game, which can be used to check all combinations that are played.
     * @param playerStatuses the statuses of all players as an array of type PlayerStatus.
     * @param numberOfCardsPerPlayer the number of cards of each player as an array of integers.
     * @param lastCombinationOnTable the top (last played) combination of the table.
     * @return an integer as an index to the array playableCombinations, determining which combination will be played,
     *         or -1 if the player does not wish to play. The returned index MUST be from 0 to numPlayableCombinations-1.
     */
    int decideAndPlay(Combination** playableCombinations, int numPlayableCombinations, Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable);
};

#endif // PLAYER_H
