#include <cstdlib>
#include <iostream>
#include "player.h"
#include "shuffler.h"

Player::Player(int index){
    team = "";
	hand = new Hand();
	status = HASNTPLAYED;
	this->index = index;
	if (index==0) name = "Player 1";
	else if (index==1) name = "Player 2";
	else if (index==2) name = "Player 3";
	else if (index==3) name = "Player 4";
    bucketSize = 0;
	bucket = new Card*[56];
}

Player::~Player(){
    delete hand;
    delete[] bucket;
}

void Player::setStatus(PlayerStatus status){
    this->status = status;
}

PlayerStatus Player::getStatus(){
    return status;
}

bool Player::hasStatus(PlayerStatus status){
    return this->status == status;
}

string Player::getName(){
    return name + (team == "" ? "" : " [" + team + "]");
}

int Player::getNumberOfCards(){
    return hand->getCardCount();
}

bool Player::hasNoCardsLeft(){
    return hand->getCardCount() == 0;
}

bool Player::hasMahJong(){
    for (int i = 0; i < hand->getCardCount(); i++){
        if (hand->getCard(i)->hasSuit(MAHJONG))
            return true;
    }
    return false;
}

bool Player::hasPhoenix(){
    for (int i = 0; i < hand->getCardCount(); i++){
        if (hand->getCard(i)->hasSuit(PHOENIX))
            return true;
    }
    return false;
}

void Player::addCardToHand(Card* card){
    hand->addCard(card);
}

void Player::removeCombinationFromHand(Combination* combination){
    hand->removeCombination(combination);
}

void Player::addCombinationToBucket(Combination* combination){
	for (int i = 0; i < combination->getNumberOfCards(); i++)
		bucket[bucketSize + i] = combination->getCard(i);
    bucketSize += combination->getNumberOfCards();
}

void Player::addCardsToBucket(Card** cards, int numberOfCards){
	for (int i = 0; i < numberOfCards; i++)
		bucket[bucketSize + i] = cards[i];
    bucketSize += numberOfCards;
}

void Player::createHandCombinations(){
    hand->clearHand();
    hand->createAllCombinations();
}

int Player::findNumberOfPlayableCombinations(Combination* combination){
	int numPlayableCombinations = 0;
    for (int i = 0; i < hand->getNumberOfCombinations(); i++){
        if (hand->getCombination(i)->canBePlayed(combination))
            numPlayableCombinations++;
    }
    return numPlayableCombinations;
}

Combination** Player::findPlayableCombinations(Combination* combination, int &numPlayableCombinations){
    numPlayableCombinations = (combination == NULL) ? hand->getNumberOfCombinations() : findNumberOfPlayableCombinations(combination);
    int j = 0;
    Combination** playableCombinations = new Combination*[numPlayableCombinations];
	for (int i = 0; i < hand->getNumberOfCombinations(); i++){
		if (combination == NULL || hand->getCombination(i)->canBePlayed(combination))
		    playableCombinations[j++] = hand->getCombination(i);
	}
    return playableCombinations;
}

void Player::setTheValueOfThePhoenix(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer){
    hand->setPhoenixValue(-1);
    Combination* lastCombinationOnTable = (table->getNumberOfCombinations() == 0) ? NULL : table->getTopCombination();
    int choice = setPhoenixValue(table, playerStatuses, numberOfCardsPerPlayer, lastCombinationOnTable);
	if (choice >= 1 && choice <= 14)
        hand->setPhoenixValue(choice);
    else{
        cout << name << " did not correctly set the Phoenix.. Exiting" << endl;
        std::exit(0);
    }
}

Combination* Player::playCombinationOrPass(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer){
    int numPlayableCombinations;
    Combination* lastCombinationOnTable = (table->getNumberOfCombinations() == 0) ? NULL : table->getTopCombination();
    Combination** playableCombinations = findPlayableCombinations(lastCombinationOnTable, numPlayableCombinations);
    int choice = decideAndPlay(playableCombinations, numPlayableCombinations, table, playerStatuses, numberOfCardsPerPlayer, lastCombinationOnTable);
	if (choice >= 0 && choice <= numPlayableCombinations - 1){
        Combination* combinationToPlay = playableCombinations[choice];
        delete[] playableCombinations;
        return combinationToPlay;
	}
	else if (choice == -1){
        if (lastCombinationOnTable == NULL){
            cout << name << " did not choose a combination although the table has NO combination.. Exiting" << endl;
            std::exit(0);
        }
        delete[] playableCombinations;
        return NULL;
	}
	else{
        cout << name << " did not correctly choose a playable combination.. Exiting" << endl;
        std::exit(0);
    }
}

string Player::toString(){
    return name + " (" + hand->numberOfCardsToString() + " cards left)";// + hand->toString();
}

void Player::getHandAndBucketFromPlayer(Player* otherPlayer){
    int numCards = otherPlayer->bucketSize;
	for (int i = 0; i < numCards; i++){
		bucket[bucketSize + i] = otherPlayer->bucket[i];
	}
    bucketSize += numCards;
    otherPlayer->bucketSize = 0;

    numCards = otherPlayer->hand->getCardCount();
	for (int i = numCards - 1; i >= 0; i--){
		bucket[bucketSize + i] = otherPlayer->hand->getCard(i);
		otherPlayer->hand->removeCard(bucket[bucketSize + i]);
	}
    bucketSize += numCards;
}

int Player::countBucketPoints(){
	int points = 0;
	for (int i = 0; i < bucketSize; i++)
	    points += bucket[i]->getPoints();
	return points;
}

ComputerPlayer::ComputerPlayer(int index) : Player(index){

}

int ComputerPlayer::setPhoenixValue(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable){
    return rand() % 14 + 1;
}

int ComputerPlayer::decideAndPlay(Combination** playableCombinations, int numPlayableCombinations, Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable){
    if (lastCombinationOnTable != NULL){
        // The player does not have to play if it is not desired
        // So, decide with a 75-25 probability (player plays 3 out of 4 times)
        int prob = rand() % 100 + 1; // random number between 1 and 100
        if (prob > 75)
            return -1;
    }

	// Select randomly a combination from 0 to number of playable combinations
    return rand() % numPlayableCombinations;
}

HumanPlayer::HumanPlayer(int index) : Player(index){

}

int HumanPlayer::setPhoenixValue(Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable){
    cout << "Hand:" << hand->toString() << endl;
    int choice = -1;
    cout << "Enter the value of the Phoenix (1 to 14, where 11=J, 12=Q, 13=K, 14=A): ";
    cin >> choice;
    while((cin.fail()) || (choice < 1) || (choice > 14)){
        cout << "Enter the value of the Phoenix (1 to 14, where 11=J, 12=Q, 13=K, 14=A): ";
        cin.clear(); cin.ignore(256,'\n');
        cin >> choice;
    }
    return choice;
}


int HumanPlayer::decideAndPlay(Combination** playableCombinations, int numPlayableCombinations, Table* table, PlayerStatus* playerStatuses, int* numberOfCardsPerPlayer, Combination* lastCombinationOnTable){
    // Print all playable combinations
    cout << "Hand:" << hand->toString() << endl;
    cout << "Possible combinations:";
    for (int i = 0; i < numPlayableCombinations; i++)
	    cout << endl << (i+1) << " - " << playableCombinations[i]->toString();
    cout << endl;

    // Get choice from user input
    int choice = -1;
    cout << "Enter a number from 1 to " << numPlayableCombinations << (lastCombinationOnTable != NULL ? " or enter 0 to pass: " : ": ");
    cin >> choice;
    while((cin.fail()) || (choice < 0) || (choice > numPlayableCombinations) || (lastCombinationOnTable == NULL && choice == 0)){
        cout << "Enter a number from 1 to " << numPlayableCombinations << (lastCombinationOnTable != NULL ? " or enter 0 to pass: " : ": ");
        cin.clear(); cin.ignore(256,'\n');
        cin >> choice;
    }

    // Return pass if choice equals 0 or an index (from 0 to numPlayableCombinations-1) if choice greater than zero
    return (choice == 0) ? -1 : choice - 1;
}
