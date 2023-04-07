#ifndef TABLE_H
#define TABLE_H

#include "combination.h"

/**
 * Class that implements the table of the game.
 */
class Table
{
private:
	int numCombinationsOnTable;
	Combination** combinationsOnTable;

public:
    /**
     * Initializes a tichu table with no combinations.
     */
	Table();

    /**
     * Deletes the table by deleting its combinations. This method deletes
     * all combinations before deleting the combinations array.
     */
    ~Table();

    /**
     * Removes all combinations from the table.
     */
	void clear();

    /**
     * Adds a combination to the table.
     *
     * @param combination the combination to be added to the table.
     */
	void addCombinationOnTable(Combination* combination);

    /**
     * Returns the top combination, i.e. the last combination added to the table.
     *
     * @return the last combination added on the table.
     */
	Combination* getTopCombination();

    /**
     * Returns the number of combinations that are currently on the table.
     *
     * @return the number of combinations on the table.
     */
    int getNumberOfCombinations();

    /**
     * Returns a combination of the table given its index.
     *
     * @param index the index of the combination to be returned.
     * @return a combination of the table given its index.
     */
    Combination* getCombination(int index);
};

#endif // TABLE_H
