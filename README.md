# Tichu Game Clone Documentation

## School of Electrical & Computer Engineering - AUTh
### 2nd Semester, Aristotle University, 2020
### Object-Oriented Programming Project - Tichu
### Built with C++

The Tichu game project has been divided into four parts

## Table of contents

- [Overview](#overview)
  - [Part One](#part-one)
  - [Part Two](#part-two)
  - [Part Three](#part-three)
  - [Part Four](#part-four)
- [Author](#author)

## Part One: Class diagram in UML

The first deliverable requires the creation of a UML Class Diagram for the Tichu game. The diagram should include all basic entities involved in the problem to be modeled, with the variables and methods that comprise them. It should also map out all the relationships that occur between the identified classes/concepts, characterizing them with verbs and plurals.

## Part Two: Basic Classes and Functions in C++

The second part involves the creation of core game classes for Tichu, specifically, the Card, Combination, Player, and Hand classes. In addition to the functionality specified for each of these classes, all classes should also include initialization functions.

An additional requirement is to implement functions in the helpers.cpp file: numberOfPlayersThatHaveNoCardsLeft and lastThreePlayersPassedOrHaveNoCardsLeft. These functions perform essential checks regarding the game and players' statuses.

## Part Three: C++ Arrays and Pointer Functions

In this section, you will be developing multidimensional classes for the Tichu game combinations. This includes classes for Combination, Single, Pair, ThreeOfAKind, Stairs, FullHouse, Straight, FourOfAKind, and StraightFlush. These classes, which handle various types of card combinations, should include initialization functions and appropriate methods to handle their use cases.

Additionally, implement the following Player class functions in the player.cpp file: CombinationsCanBePlayed and CountBucketPoints function. These are responsible for checking if a new combination can be played and calculating the points of the cards a player has collected on the game board, respectively.

## Part Four: Virtual Functions and Generic Classes in C++

The final part of the project focuses on implementing the Tichu's custom card classes: SimpleCard and SpecialCard. These classes should have a constructor and implement the virtual functions canBeInCombination, canBeInBomb, and getPoints.

Also, you're required to implement generic template functions for shuffling (Shuffle) and "cutting leaves" (Cut function) in the shuffler.h file.

## Author

- Website - [Chrysostomos Koumides](https://chryskoum.github.io/ChrysK/)
- Frontend Mentor - [@ChrysKoum](https://www.frontendmentor.io/profile/ChrysKoum)
