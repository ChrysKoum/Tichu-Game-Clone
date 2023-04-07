#include <iostream>
#include "game.h"

using namespace std;

Game::Game(Table* table, Deck* deck, Player** players){
    this->table = table;
    this->deck = deck;
    this->players = players;
    rankingIndex = 0;
    ranking = new int[4];
}

Game::~Game(){
    delete[] ranking;
}

int Game::startRound(){
    // Deal the cards
    deck->shuffleCards();
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 14; j++){
            Card* card = deck->deal();
            players[i]->addCardToHand(card);
        }
    }

    for (int i = 0; i < 4; i++){
        if (players[i]->hasMahJong())
            return i; // the id of the player that plays first
    }

    return -1; // this should never be returned
}

void Game::printState(){
    for (int i = 0; i < 4; i++){
        cout << players[i]->toString() << endl;
    }
}

bool Game::partnerHasNoCardsLeft(int playerIndex){
    return players[(playerIndex + 2) % 4]->hasNoCardsLeft();
}

bool Game::otherPlayersPassed(int playerTurn){
    return ((players[(playerTurn + 1) % 4]->hasStatus(PASSED)) &&
            (players[(playerTurn + 2) % 4]->hasStatus(PASSED)) &&
            (players[(playerTurn + 3) % 4]->hasStatus(PASSED)));
}

void Game::playerCardsHaveEnded(int playerTurn){
    ranking[rankingIndex++] = playerTurn;
}

void Game::endRound(){
    // Get first and last player
    for (int i = 0; i < 4; i++){
        if (!players[i]->hasNoCardsLeft())
            ranking[rankingIndex++] = i;
    }
    Player* firstPlayer = players[ranking[0]];
    Player* lastPlayer = players[ranking[3]];
    // Add last player's bucket and hand to first player
    firstPlayer->getHandAndBucketFromPlayer(lastPlayer);
}

int* Game::getRanking(){
    return ranking;
}

int Game::getTeamPoints(int teamIndex){
	if ((ranking[0] + ranking[1]) % 2 == 0){
        if ((teamIndex == 0 && (ranking[0] == 0 || ranking[0] == 2)) ||
                (teamIndex == 1 && (ranking[0] == 1 || ranking[0] == 3)))
            return 200;
        else
            return 0;
	}
	else{
        if (teamIndex == 0)
            return players[0]->countBucketPoints() + players[2]->countBucketPoints();
        else
            return players[1]->countBucketPoints() + players[3]->countBucketPoints();
	}
}
