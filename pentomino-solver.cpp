// Pentomino solver
// Copyright (C) 2005 Marc Lepage

#include <iostream>
#include <iomanip>
#include <ctime>

int board[8][8] =
{
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 },
    { -1, -1, -1, -1, -1, -1, -1, -1 }
};

int piece[][5][5] =
{
    // Tetromino 0: no rotations, no flip
    // ##
    // ##
    {
        {  0,  0, -1, -1, -1 },
        {  0,  0, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 1: no rotations, no flip
    //  #
    // ###
    //  #
    {
        { -1,  1, -1, -1, -1 },
        {  1,  1,  1, -1, -1 },
        { -1,  1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 2: two rotations, no flip
    // #####
    {
        {  2,  2,  2,  2,  2 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  2, -1, -1, -1, -1 },
        {  2, -1, -1, -1, -1 },
        {  2, -1, -1, -1, -1 },
        {  2, -1, -1, -1, -1 },
        {  2, -1, -1, -1, -1 }
    },
    // Pentomino 3: two rotations, flip
    // #
    // ###
    //   #
    {
        {  3, -1, -1, -1, -1 },
        {  3,  3,  3, -1, -1 },
        { -1, -1,  3, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  3,  3, -1, -1 },
        { -1,  3, -1, -1, -1 },
        {  3,  3, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  3,  3, -1, -1, -1 },
        { -1,  3, -1, -1, -1 },
        { -1,  3,  3, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1,  3, -1, -1 },
        {  3,  3,  3, -1, -1 },
        {  3, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 4: four rotations, no flip
    // ###
    // #
    // #
    {
        {  4,  4,  4, -1, -1 },
        {  4, -1, -1, -1, -1 },
        {  4, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  4,  4,  4, -1, -1 },
        { -1, -1,  4, -1, -1 },
        { -1, -1,  4, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1,  4, -1, -1 },
        { -1, -1,  4, -1, -1 },
        {  4,  4,  4, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  4, -1, -1, -1, -1 },
        {  4, -1, -1, -1, -1 },
        {  4,  4,  4, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 5: four rotations, no flip
    //  ##
    // ##
    // #
    {
        { -1,  5,  5, -1, -1 },
        {  5,  5, -1, -1, -1 },
        {  5, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  5,  5, -1, -1, -1 },
        { -1,  5,  5, -1, -1 },
        { -1, -1,  5, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1,  5, -1, -1 },
        { -1,  5,  5, -1, -1 },
        {  5,  5, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  5, -1, -1, -1, -1 },
        {  5,  5, -1, -1, -1 },
        { -1,  5,  5, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 6: four rotations, no flip
    // ###
    //  #
    //  #
    {
        {  6,  6,  6, -1, -1 },
        { -1,  6, -1, -1, -1 },
        { -1,  6, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1,  6, -1, -1 },
        {  6,  6,  6, -1, -1 },
        { -1, -1,  6, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  6, -1, -1, -1 },
        { -1,  6, -1, -1, -1 },
        {  6,  6,  6, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  6, -1, -1, -1, -1 },
        {  6,  6,  6, -1, -1 },
        {  6, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 7: four rotations, no flip
    // ###
    // # #
    {
        {  7,  7,  7, -1, -1 },
        {  7, -1,  7, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  7,  7, -1, -1, -1 },
        { -1,  7, -1, -1, -1 },
        {  7,  7, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  7, -1,  7, -1, -1 },
        {  7,  7,  7, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  7,  7, -1, -1, -1 },
        {  7, -1, -1, -1, -1 },
        {  7,  7, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 8: four rotations, flip
    // #
    // ###
    //  #
    {
        {  8, -1, -1, -1, -1 },
        {  8,  8,  8, -1, -1 },
        { -1,  8, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  8,  8, -1, -1 },
        {  8,  8, -1, -1, -1 },
        { -1,  8, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  8, -1, -1, -1 },
        {  8,  8,  8, -1, -1 },
        { -1, -1,  8, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  8, -1, -1, -1 },
        { -1,  8,  8, -1, -1 },
        {  8,  8, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  8,  8, -1, -1, -1 },
        { -1,  8,  8, -1, -1 },
        { -1,  8, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  8, -1, -1, -1 },
        {  8,  8,  8, -1, -1 },
        {  8, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  8, -1, -1, -1 },
        {  8,  8, -1, -1, -1 },
        { -1,  8,  8, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1,  8, -1, -1 },
        {  8,  8,  8, -1, -1 },
        { -1,  8, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 9: four rotations, flip
    // ####
    //    #
    {
        {  9,  9,  9,  9, -1 },
        { -1, -1, -1,  9, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1,  9, -1, -1, -1 },
        { -1,  9, -1, -1, -1 },
        { -1,  9, -1, -1, -1 },
        {  9,  9, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  9, -1, -1, -1, -1 },
        {  9,  9,  9,  9, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  9,  9, -1, -1, -1 },
        {  9, -1, -1, -1, -1 },
        {  9, -1, -1, -1, -1 },
        {  9, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  9, -1, -1, -1, -1 },
        {  9, -1, -1, -1, -1 },
        {  9, -1, -1, -1, -1 },
        {  9,  9, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1, -1,  9, -1 },
        {  9,  9,  9,  9, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  9,  9, -1, -1, -1 },
        { -1,  9, -1, -1, -1 },
        { -1,  9, -1, -1, -1 },
        { -1,  9, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        {  9,  9,  9,  9, -1 },
        {  9, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 10: four rotations, flip
    // ####
    //   #
    {
        { 10, 10, 10, 10, -1 },
        { -1, -1, 10, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 10, -1, -1, -1 },
        { -1, 10, -1, -1, -1 },
        { 10, 10, -1, -1, -1 },
        { -1, 10, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 10, -1, -1, -1 },
        { 10, 10, 10, 10, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 10, -1, -1, -1, -1 },
        { 10, 10, -1, -1, -1 },
        { 10, -1, -1, -1, -1 },
        { 10, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 10, -1, -1, -1, -1 },
        { 10, -1, -1, -1, -1 },
        { 10, 10, -1, -1, -1 },
        { 10, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1, 10, -1, -1 },
        { 10, 10, 10, 10, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 10, -1, -1, -1 },
        { 10, 10, -1, -1, -1 },
        { -1, 10, -1, -1, -1 },
        { -1, 10, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 10, 10, 10, 10, -1 },
        { -1, 10, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 11: four rotations, flip
    // ###
    //   ##
    {
        { 11, 11, 11, -1, -1 },
        { -1, -1, 11, 11, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 11, -1, -1, -1 },
        { -1, 11, -1, -1, -1 },
        { 11, 11, -1, -1, -1 },
        { 11, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 11, 11, -1, -1, -1 },
        { -1, 11, 11, 11, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 11, -1, -1, -1 },
        { 11, 11, -1, -1, -1 },
        { 11, -1, -1, -1, -1 },
        { 11, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 11, -1, -1, -1, -1 },
        { 11, -1, -1, -1, -1 },
        { 11, 11, -1, -1, -1 },
        { -1, 11, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, -1, 11, 11, -1 },
        { 11, 11, 11, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 11, -1, -1, -1, -1 },
        { 11, 11, -1, -1, -1 },
        { -1, 11, -1, -1, -1 },
        { -1, 11, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 11, 11, 11, -1 },
        { 11, 11, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    // Pentomino 12: four rotations, flip
    // ###
    //  ##
    {
        { 12, 12, 12, -1, -1 },
        { -1, 12, 12, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 12, -1, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 12, 12, -1, -1, -1 },
        { 12, 12, 12, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 12, 12, -1, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { 12, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 12, -1, -1, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { -1, 12, 12, -1, -1 },
        { 12, 12, 12, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 12, 12, -1, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { -1, 12, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    },
    {
        { 12, 12, 12, -1, -1 },
        { 12, 12, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 },
        { -1, -1, -1, -1, -1 }
    }
};

const int pieceMin[13] =        {  2,  3,  1,  3,  3,  3,  3,  2,  3,  2,  2,  2,  2 };
const int pieceMax[13] =        {  2,  3,  5,  3,  3,  3,  3,  3,  3,  4,  4,  4,  3 };
const int pieceIdx[13] =        {  0,  1,  2,  4,  8, 12, 16, 20, 24, 32, 40, 48, 56 };
const int orientMax[13] =       {  1,  1,  2,  4,  4,  4,  4,  4,  8,  8,  8,  8,  8 };

int pieceOrient[13] =           { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int pieceRow[13] =              { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int pieceCol[13] =              { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };

int lastPiece = -1;
int solutionCount = 0;

const int MAGIC_NUMBER = 100;
const int b = 0; // black
const int w = 1; // white
// blackness or whiteness of most top left corner of piece
const int bw[] = {
    b, // #
    b, // X
    b,b, // I
    b,b,b,b, // Z
    w,w,w,w, // V
    b,b,b,b, // W
    w,w,w,w, // T
    w,b,b,w, // U
    b,b,b,b,b,b,b,b, // F
    b,w,b,w,b,w,b,w, // L
    w,b,w,b,w,b,w,b, // Y
    w,b,w,b,w,b,w,b, // N
    b,w,w,b,b,w,w,b, // P
};

void colorizePieces(){
    for (int i = 0; i < 64; ++i)
        for (int r = 0; r < 5; ++r)
            for (int c = 0; c < 5; ++c)
                if(piece[i][r][c] != -1 && bw[i] == (r+c)%2)
                    piece[i][r][c] += MAGIC_NUMBER;
}

// check if board contains propper chess board
bool isChess(){
    int ccolor = board[7][7] >= MAGIC_NUMBER ? b : w; // bottom right corn color 
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] % MAGIC_NUMBER == 0) // square may be wrongly rotated
                continue;
            if ((r+c)%2 == 0) { // even
                if ((board[r][c] >= MAGIC_NUMBER ? b : w) != ccolor)
                    return false;
            } else { // odd
                if ((board[r][c] >= MAGIC_NUMBER ? b : w) != !ccolor)
                    return false;
            }
        }
    }
    return true;
}

void printBoard()
{
    for (int row = 0; row != 8; ++row)
    {
        for (int col = 0; col != 8; ++col)
        {
            std::cout << " " <<  "#XIZVWTUFLYNP"[(board[row][col] % MAGIC_NUMBER)];
        }
        std::cout << '\n';
    }
}

void printSolution()
{
    std::cout << pieceOrient[0] << pieceRow[0]+1 << pieceCol[0]+1;
    for (int n = 1; n != 13; ++n)
    {
        std::cout << '-' << pieceOrient[n] << pieceRow[n]+1 << pieceCol[n]+1;
    }
    std::cout << ' ' << solutionCount << std::endl;
}

bool testPiece(int row, int col, int orient)
{
    for (int r = 0; r != pieceMax[lastPiece + 1]; ++r)
    {
        for (int c = 0; c != pieceMax[lastPiece + 1]; ++c)
        {
            const int val = piece[pieceIdx[lastPiece + 1] + orient][r][c];
            if (val != -1)
            {
                if (7 < row + r || 7 < col + c || board[row + r][col + c] != -1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

void placePiece(int row, int col, int orient)
{
    ++lastPiece;
    for (int r = 0; r != pieceMax[lastPiece]; ++r)
    {
        for (int c = 0; c != pieceMax[lastPiece]; ++c)
        {
            const int val = piece[pieceIdx[lastPiece] + orient][r][c];
            if (val != -1)
            {
                board[row + r][col + c] = val;
            }
        }
    }
    pieceRow[lastPiece] = row;
    pieceCol[lastPiece] = col;
    pieceOrient[lastPiece] = orient;
}

void removePiece()
{
    for (int r = 0; r != pieceMax[lastPiece]; ++r)
    {
        for (int c = 0; c != pieceMax[lastPiece]; ++c)
        {
            const int val = piece[pieceIdx[lastPiece] + pieceOrient[lastPiece]][r][c];
            if (val != -1)
            {
                board[pieceRow[lastPiece] + r][pieceCol[lastPiece] + c] = -1;
            }
        }
    }
    pieceRow[lastPiece] = -1;
    pieceCol[lastPiece] = -1;
    pieceOrient[lastPiece] = -1;
    --lastPiece;
}

int mark(int row, int col, int markVal)
{
    int markCount = 0;

    if (board[row][col] == -1)
    {
        board[row][col] = markVal;
        ++markCount;

        if (0 < row)
        {
            markCount += mark(row - 1, col, markVal);
        }
        if (row < 7)
        {
            markCount += mark(row + 1, col, markVal);
        }
        if (0 < col)
        {
            markCount += mark(row, col - 1, markVal);
        }
        if (col < 7)
        {
            markCount += mark(row, col + 1, markVal);
        }
    }

    return markCount;
}

bool prune()
{
    bool bResult = false;
    int markVal = -2;
    int totalMarkCount = 0;

    for (int row = 0; row <= 7; ++row)
    {
        for (int col = 0; col <= 7; ++col)
        {
            const int markCount = mark(row, col, markVal);
            if (markCount)
            {
                --markVal;
                totalMarkCount += markCount;
            }
            else
            {
                continue;
            }
            if (markCount % 5)
            {
                bResult = true;
                goto cleanup;
            }
            if (totalMarkCount + lastPiece*5 + 4 == 64)
            {
                goto cleanup;
            }
        }
    }

cleanup:

    for (int row = 0; row <= 7; ++row)
    {
        for (int col = 0; col <= 7; ++col)
        {
            if (board[row][col] < 0)
            {
                board[row][col] = -1;
            }
        }
    }

    return bResult;
}

void solvePiece(int row, int col, int orient)
{
    if (!testPiece(row, col, orient))
    {
        return;
    }

    placePiece(row, col, orient);

    if (lastPiece == 12)
    {
        if(isChess()){
            ++solutionCount;
            printSolution();
            printBoard();
        }
    }
    else
    {
        if (!prune())
        {
            const int rowMax = 8 - pieceMin[lastPiece + 1];
            for (int orient = 0; orient < orientMax[lastPiece + 1]; ++orient)
            {
                for (int row = 0; row <= rowMax; ++row)
                {
                    for (int col = 0; col <= rowMax; ++col)
                    {
                        solvePiece(row, col, orient);
                    }
                }
            }
        }
    }

    removePiece();
}

void solveCross(int row, int col)
{
    if (!testPiece(row, col, 0))
    {
        return;
    }

    placePiece(row, col, 0);

    if (!prune())
    {
        const int rowMax = 8 - pieceMin[lastPiece + 1];
        for (int orient = 0; orient < orientMax[lastPiece + 1]; ++orient)
        {
            if (pieceRow[0] == pieceCol[0] && pieceRow[1] == pieceCol[1] && 0 < orient)
            {
                // Special case: if symmetric about diagonal, use only one line orientation.
                break;
            }
            for (int row = 0; row <= rowMax; ++row)
            {
                for (int col = 0; col <= rowMax; ++col)
                {
                    solvePiece(row, col, orient);
                }
            }
        }
    }

    removePiece();
}

void solveSquare(int row, int col)
{
    placePiece(row, col, 0);

    if (row == 3 && col == 3)
    {
        // Square in centre -> cross in 1/8.
        for (int row = 0; row <= 2; ++row)
        {
            for (int col = 0; col <= row; ++col)
            {
                solveCross(row, col);
            }
        }
    }
    else if (row == col)
    {
        // Square on diagonal -> cross in 1/2.
        for (int row = 0; row <= 5; ++row)
        {
            for (int col = 0; col <= row; ++col)
            {
                solveCross(row, col);
            }
        }
    }
    else if (row == 3)
    {
        // Square on mid line -> cross in 1/2.
        for (int row = 0; row <= 2; ++row)
        {
            for (int col = 0; col <= 5; ++col)
            {
                solveCross(row, col);
            }
        }
    }
    else
    {
        // Square in interior -> cross anywhere.
        for (int row = 0; row <= 5; ++row)
        {
            for (int col = 0; col <= 5; ++col)
            {
                solveCross(row, col);
            }
        }
    }

    removePiece();
}

int main(int argc, char* argv[])
{
    std::cout << "Pentomino solver\n";

    colorizePieces();

    std::time_t time1;
    std::time(&time1);

#if 1
    // Solve square in 1/8.
    for (int row = 0; row <= 3; ++row)
    {
        for (int col = 0; col <= row; ++col)
        {
            solveSquare(row, col);
        }
    }
#else
    // Solve square in centre only.
    solveSquare(3, 3);
#endif

    std::time_t time2;
    std::time(&time2);
    double seconds = std::difftime(time2, time1);

    std::cout << solutionCount << " solutions found in " << seconds << " seconds." << std::endl;

    return 0;
}
