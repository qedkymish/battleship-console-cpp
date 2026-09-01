//Qusay Edkymish
//Oct/16th/2024
//ChessBoard Class modified for BattleShip game. Updated


#include "ChessBoard.h"
#include <iostream>
#include <iomanip>  //For setw()
#include <cstdlib>  //For random ship placement
using namespace std;

//Constructor to initialize the board
ChessBoard::ChessBoard()
{
    //Initialize the counters before resetBoard() touches the grids
    totalShips = 0;
    totalShipParts = 0;

    resetBoard();
}

//Reset the board to empty spaces (initialize with nullptr)
void ChessBoard::resetBoard()
{
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            board[r][c] = nullptr;  //No ship covers this square
            shots[r][c] = ' ';      //Nothing has been fired at it yet
        }
    }
}

//Display the board
void ChessBoard::displayBoard(bool showShips = false)
{
    //Display total ships above the board
    cout << "Total Remaining Ships: " << totalShips << "\n\n";

    //Print column headers (A to J)
    cout << "   ";
    for (char c = 'A'; c <= 'J'; c++)
    {
        cout << setw(2) << c << " "; //Increase spacing for better alignment
    }
    cout << endl;

    //Print the board row by row
    for (int r = 0; r < ROWS; r++)
    {
        //Print row numbers (handle single and double digits)
        cout << (r + 1 < 10 ? " " : "") << r + 1 << " ";
        for (int c = 0; c < COLS; c++)
        {
            if (shots[r][c] != ' ')
            {
                cout << setw(2) << shots[r][c] << " ";          //Show hit or miss
            }
            else if (showShips && board[r][c] != nullptr)
            {
                cout << setw(2) << board[r][c]->symbol << " ";  //Reveal the ship
            }
            else
            {
                cout << setw(2) << '~' << " ";                  //Unknown water
            }
        }
        cout << endl;
    }
}

//Process hits and misses
bool ChessBoard::hitOrMiss(int row, int col)
{
    //Already fired at this square
    if (shots[row][col] != ' ')
    {
        cout << "\nAlready attacked this position.\n\n";
        return false;
    }

    //Open water
    if (board[row][col] == nullptr)
    {
        shots[row][col] = 'O';
        cout << "\nIt's a miss!\n\n";
        return false;
    }

    //A ship covers this square. Record the shot on the square, not on the ship,
    //so the other squares that ship covers stay hidden.
    Ship* hitShip = board[row][col];
    shots[row][col] = 'X';
    cout << "\nYou hit the " << hitShip->name << "!\n\n";

    //Decrease totalShips only the first time this ship is hit
    if (!hitShip->hasBeenHit)
    {
        hitShip->hasBeenHit = true;
        totalShips--;
    }
    return true;
}

//Place a ship on the board
void ChessBoard::placeShip(Ship& ship)
{
    bool placed = false;

    while (!placed)
    {
        ship.isVertical = rand() % 2;  //Randomly set the direction (vertical/horizontal)
        int row = rand() % 10;         //Random row
        int col = rand() % 10;         //Random column
        bool spaceFree = true;

        //Check if the ship can fit without going out of bounds or overlapping
        if (ship.isVertical) //Vertical placement
        {
            if (row + ship.size > ROWS) continue; //Ensure ship fits
            for (int i = 0; i < ship.size; i++)
            {
                if (board[row + i][col] != nullptr) //Check if space is occupied
                {
                    spaceFree = false;
                    break;
                }
            }
        }
        else //Horizontal placement
        {
            if (col + ship.size > COLS) continue; //Ensure ship fits
            for (int i = 0; i < ship.size; i++)
            {
                if (board[row][col + i] != nullptr) //Check if space is occupied
                {
                    spaceFree = false;
                    break;
                }
            }
        }

        //Place the ship if space is free
        if (spaceFree)
        {
            if (ship.isVertical)
            {
                for (int i = 0; i < ship.size; i++)
                {
                    board[row + i][col] = &ship;
                }
            }
            else
            {
                for (int i = 0; i < ship.size; i++)
                {
                    board[row][col + i] = &ship;
                }
            }
            totalShipParts += ship.size; //Count total ship parts
            totalShips++;  //Count total ships
            placed = true;
        }
    }
}
