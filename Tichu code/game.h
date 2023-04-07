#ifndef GAME_H
#define GAME_H

#include "table.h"
#include "deck.h"
#include "player.h"

/**
 * Class denoting the game.
 */
class Game
{
private:
    Table* table;
    Deck* deck;
    Player** players;
    int rankingIndex;
    int* ranking;

public:
    /**
     * Initializes a game setting the table, the deck, and the players.
     * The ranking is also initialized.
     *
     * @param table the table of the game.
     * @param deck the deck of the game.
     * @param players the players of the game.
     */
    Game(Table* table, Deck* deck, Player** players);

    /**
     * Deletes the game by deleting the ranking. Warning: this method does not also delete
     * the table, the deck, and the players! These are deleted by the main function.
     */
    ~Game();

    /**
     * Starts a round of the game by dealing the cards of the deck to the players and finding
     * out which player should start playing first (i.e. the one having the Mah Jong card)
     *
     * @return the index of the player that plays first (i.e. the one having the Mah Jong card).
     */
    int startRound();

    /**
     * Prints the state of the game, including all players and their cards.
     */
    void printState();

    /**
     * Checks whether the partner of the player of which the index is given has no cards left.
     *
     * @param playerIndex the index that indicates which player has last played and is an integer with values 0, 1, 2 or 3.
     * @return true if the partner of the player of which the index is given has no cards left, or false otherwise.
     */
    bool partnerHasNoCardsLeft(int playerIndex);

    /**
     * Checks whether the other three players (apart from the index of the one given) have passed.
     *
     * @param playerIndex the index that indicates which player has last played and is an integer with values 0, 1, 2 or 3.
     * @return true if all other players apart from the current given one have passed.
     */
    bool otherPlayersPassed(int playerIndex);

    /**
     * Sets the ranking of the player after the cards of the player have ended.
     *
     * @param playerTurn the turn of the game, which indicates which player is the next to play,
     *                   and is an integer with values 0, 1, 2 or 3
     */
    void playerCardsHaveEnded(int playerTurn);

    /**
     * Finalizes the ranking of the players and adds the last player's hand and bucket to the
     * first player.
     */
    void endRound();

    /**
     * Returns the ranking of the players.
     *
     * @return the ranking of the players (as a dynamic table of four positions).
     */
    int* getRanking();

    /**
     * Returns the points of a team given its index. If the players of the team are first and second then
     * the team gets 200. If the players of the other team are first and second then the team gets 0. For
     * any other ranking, the points of the team are computed by summing up the points of each individual
     * player (as computed by method countBucketPoints of class Player).
     *
     * @param teamIndex the index of a team, either 0 (for players 0 and 2) or 1 (for players 1 and 3).
     * @return the points of a team given its index.
     */
    int getTeamPoints(int teamIndex);
};

#endif // GAME_H
