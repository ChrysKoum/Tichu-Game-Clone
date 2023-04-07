#include <iostream>
#include <cstdlib>
#include <ctime>
#include "table.h"
#include "deck.h"
#include "player.h"
#include "game.h"

using namespace std;

int main(){
    // Initialize game
    srand(time(NULL));
    Table* table = new Table();
    Deck* deck = new Deck();
    Player** players = new Player*[4];
    players[0] = new ComputerPlayer(0);
    players[1] = new ComputerPlayer(1);
    players[2] = new ComputerPlayer(2);
    players[3] = new ComputerPlayer(3);
    Game* game = new Game(table, deck, players);

    // Deal and start round
    int playerTurn = game->startRound();
    Player* currentPlayer = players[playerTurn];
    int idOfLastPlayerThatHasPlayed = -1;
    bool dogHasBeenPlayed = false;
    currentPlayer->setStatus(WONTHETRICK);

    game->printState();
    cout << "NEW TRICK" << endl;
    do{
        currentPlayer = players[playerTurn];

        // Check if last three players passed
        if (game->otherPlayersPassed(idOfLastPlayerThatHasPlayed) &&
                players[idOfLastPlayerThatHasPlayed]->hasStatus(PLAYED)){
            cout << players[idOfLastPlayerThatHasPlayed]->getName() << " won the trick" << endl;

            Player* playerToGetTheCardsOfTheTable = players[idOfLastPlayerThatHasPlayed];
            if (table->getTopCombination()->getCard(0)->hasSuit(DRAGON)){
                // If the player has won the trick with a dragon then the trick must be given to an opponent
                Player* opponent1 = players[(playerTurn + 1) % 4];
                Player* opponent2 = players[(playerTurn + 3) % 4];
                // The cards are given to the opponent with the most cards in hand
                playerToGetTheCardsOfTheTable = (opponent1->getNumberOfCards() > opponent2->getNumberOfCards()) ?
                                                opponent1 : opponent2;
            }
            for (int j = 0; j < table->getNumberOfCombinations(); j++){
                Combination *temp = table->getCombination(j);
                playerToGetTheCardsOfTheTable->addCombinationToBucket(temp);
            }
            table->clear();

            if (players[idOfLastPlayerThatHasPlayed]->hasNoCardsLeft())
                players[idOfLastPlayerThatHasPlayed]->setStatus(HASNTPLAYED); // The player that won the trick has no cards left
            else{
                players[idOfLastPlayerThatHasPlayed]->setStatus(WONTHETRICK); // The player that won the trick has cards left
                for (int i = 0; i < 4; i++){
                    if (i != idOfLastPlayerThatHasPlayed)
                        players[i]->setStatus(HASNTPLAYED);
                }
            }

            cout << endl << "NEW TRICK" << endl;
        }
        cout << "Turn of " << currentPlayer->toString() << endl;

        if (currentPlayer->hasNoCardsLeft()){
            cout << currentPlayer->getName() << " has no cards left" << endl;
            currentPlayer->setStatus(PASSED);
        }
        else{
            // In each turn the player can see the combinations of the table, the statuses
            // of all players and the number of cards of all players
            PlayerStatus* playerStatuses = new PlayerStatus[4];
            int* playerCards = new int[4];
            for (int i = 0; i < 4; i++){
                playerStatuses[i] = players[i]->getStatus();
                playerCards[i] = players[i]->getNumberOfCards();
            }
            // Play a combination or pass
            // Get the last combination of the table (or NULL if the table has no combinations)
            Combination *lastComb = (table->getNumberOfCombinations() == 0) ? NULL : table->getTopCombination();
            Combination *currentComb = NULL;
            if (currentPlayer->hasPhoenix()) // set the value of the phoenix if the player has it
                currentPlayer->setTheValueOfThePhoenix(table, playerStatuses, playerCards);
            currentPlayer->createHandCombinations(); // create all possible combinations for the player
            // Check if the player has to play and if the player can play
            if (table->getNumberOfCombinations() == 0 || currentPlayer->findNumberOfPlayableCombinations(lastComb) > 0){
                currentComb = currentPlayer->playCombinationOrPass(table, playerStatuses, playerCards);
            }
            delete[] playerStatuses;

            if (currentComb != NULL){ // Player has played
                dogHasBeenPlayed = currentComb->getCard(0)->hasSuit(DOG); // check if dog has been played
                // check if phoenix has been played as a single
                if (currentComb->hasType(SINGLE) && currentComb->getCard(0)->hasSuit(PHOENIX)){
                    // set phoenix to the value of the last single card
                    if (dogHasBeenPlayed || table->getNumberOfCombinations() == 0)
                        ((Single*)currentComb)->setValue(1);
                    else
                        ((Single*)currentComb)->setValue(table->getTopCombination()->getCard(0)->getValue());
                }

                currentPlayer->removeCombinationFromHand(currentComb);
                table->addCombinationOnTable(currentComb);
                cout << currentPlayer->getName() << " played: " << currentComb->toString() << endl;
                currentPlayer->setStatus(PLAYED);
                idOfLastPlayerThatHasPlayed = playerTurn;
                for (int i = 0; i < 4; i++){
                    if (i != idOfLastPlayerThatHasPlayed)
                        players[i]->setStatus(HASNTPLAYED);
                }
            }
            else{ // Player has passed
                cout << currentPlayer->getName() << " passed" << endl;
                currentPlayer->setStatus(PASSED);
            }

            // Check if player has no cards left
            if (currentPlayer->hasNoCardsLeft()){
                cout << currentPlayer->getName() << " has no cards left" << endl;
                game->playerCardsHaveEnded(playerTurn);
                // If the partner of the player has no cards left then get the trick and game over
                if (game->partnerHasNoCardsLeft(playerTurn)){
                    // Get the rest of the cards
                    for (int j = 0; j < table->getNumberOfCombinations(); j++){
                        Combination *temp = table->getCombination(j);
                        currentPlayer->addCombinationToBucket(temp);
                    }
                    table->clear();

                    cout << endl << "Game Over!" << endl;
                    break;
                }
            }
        }

        if (dogHasBeenPlayed){
            currentPlayer->setStatus(HASNTPLAYED);
            playerTurn = (playerTurn + 2) % 4; // if the dog has been played then the partner plays
            idOfLastPlayerThatHasPlayed = playerTurn;
            players[playerTurn]->setStatus(PLAYED);
            dogHasBeenPlayed = false;
        }
        else
            playerTurn = (playerTurn + 1) % 4; // else the next player plays
    }
    while(true);

    game->endRound();

    // Print ranking
    int* ranking = game->getRanking();
    cout << endl << "Ranking: " << endl;
    for (int i = 0; i < 4; i++){
        cout << players[ranking[i]]->getName() << endl;
    }

    // Print score
    cout << endl << "Score: " << endl;
    cout << players[0]->getName() << " and " << players[2]->getName() << " - " << game->getTeamPoints(0) << endl;
    cout << players[1]->getName() << " and " << players[3]->getName() << " - " << game->getTeamPoints(1) << endl;

    // Delete all objects
    delete table;
    delete deck;
    for (int i = 0; i < 4; i++)
        delete players[i];
    delete[] players;
    delete game;

    return 0;
}
