#include "table.h"

Table::Table(){
    numCombinationsOnTable = 0;
	combinationsOnTable = new Combination*[numCombinationsOnTable];
}

Table::~Table(){
    for (int i = 0; i < numCombinationsOnTable; i++)
        delete combinationsOnTable[i];
    delete[] combinationsOnTable;
    numCombinationsOnTable = 0;
}

void Table::clear(){
    for (int i = 0; i < numCombinationsOnTable; i++)
        delete combinationsOnTable[i];
    delete[] combinationsOnTable;
    numCombinationsOnTable = 0;
    combinationsOnTable = new Combination*[numCombinationsOnTable];
}

int Table::getNumberOfCombinations(){
    return numCombinationsOnTable;
}

void Table::addCombinationOnTable(Combination *combination){
    numCombinationsOnTable++;
    Combination** temp = new Combination*[numCombinationsOnTable];
    for (int i = 0; i < numCombinationsOnTable - 1; i++){
        temp[i] = combinationsOnTable[i];
    }
    temp[numCombinationsOnTable - 1] = combination;
    delete[] combinationsOnTable;
    combinationsOnTable = temp;
}

Combination *Table::getTopCombination(){
    if (numCombinationsOnTable > 0)
        return combinationsOnTable[numCombinationsOnTable - 1];
    else
        return NULL;
}

Combination* Table::getCombination(int index){
    return combinationsOnTable[index];
}
