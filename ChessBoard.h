//Qusay Edkymish
//Oct/16th/2024
//ChessBoard Class modified for BattleShip game. Updated


#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Ship.h"

class ChessBoard
{
private:
    Ship* board[ROWS][COLS];    //Non-owning: which ship covers a square, nullptr = open water.
                                //One ship is aliased by every square it covers, so this array
                                //must never be mutated to record a shot.
    char shots[ROWS][COLS];     //What the player has fired at: ' ' untouched, 'X' hit, 'O' miss.
    int totalShipParts;         //Total number of ship parts placed
    int totalShips;             //Number of whole ships remaining

public:
    ChessBoard();                                    //Constructor
    void displayBoard(bool showShips);               //Displays the board
    void resetBoard();                               //Resets the board
    bool hitOrMiss(int row, int col);                //Process hit or miss
    void placeShip(Ship& ship);                      //Places a ship on the board
    int getRemainingShips() const { return totalShips; } //Return total ships
};

#endif //!CHESSBOARD_H
