// Pentomino solver
// Copyright (C) 2005 Marc Lepage

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdint>
#include <ctime>

#define ENV(VAR) (getenv(#VAR) && *getenv(#VAR) == '1')

const bool CENTER_SQUARE = ENV(CENTER_SQUARE); // only find solutions with square in center
const bool CHESS_PATTERN = ENV(CHESS_PATTERN); // only find solutions for pieces with chess patern
const bool COLOR_OUTPUT = ENV(COLOR_OUTPUT); // output colored board insted of letters
const bool SHOW_TRIES = ENV(SHOW_TRIES); // output all failure points as well
const int  HIDE = getenv("HIDE") != NULL ? atoi(getenv("HIDE")) : 0; // hide n (0-9) randomly choosen pieces - for fun

const int8_t _ = -1; // empty square V

int8_t board[8][8] = {
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
    { _, _, _, _, _, _, _, _ },
};

int8_t piece[][5][5] = {
    // Tetromino 0: no rotations, no flip
    // ##
    // ##
    {
        {  0,  0,  _,  _,  _ },
        {  0,  0,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 1: no rotations, no flip
    //  #
    // ###
    //  #
    {
        {  _,  1,  _,  _,  _ },
        {  1,  1,  1,  _,  _ },
        {  _,  1,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 2: two rotations, no flip
    // #####
    {
        {  2,  2,  2,  2,  2 },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  2,  _,  _,  _,  _ },
        {  2,  _,  _,  _,  _ },
        {  2,  _,  _,  _,  _ },
        {  2,  _,  _,  _,  _ },
        {  2,  _,  _,  _,  _ },
    },
    // Pentomino 3: two rotations, flip
    // #
    // ###
    //   #
    {
        {  3,  _,  _,  _,  _ },
        {  3,  3,  3,  _,  _ },
        {  _,  _,  3,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  3,  3,  _,  _ },
        {  _,  3,  _,  _,  _ },
        {  3,  3,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  3,  3,  _,  _,  _ },
        {  _,  3,  _,  _,  _ },
        {  _,  3,  3,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _,  3,  _,  _ },
        {  3,  3,  3,  _,  _ },
        {  3,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 4: four rotations, no flip
    // ###
    // #
    // #
    {
        {  4,  4,  4,  _,  _ },
        {  4,  _,  _,  _,  _ },
        {  4,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  4,  4,  4,  _,  _ },
        {  _,  _,  4,  _,  _ },
        {  _,  _,  4,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _,  4,  _,  _ },
        {  _,  _,  4,  _,  _ },
        {  4,  4,  4,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  4,  _,  _,  _,  _ },
        {  4,  _,  _,  _,  _ },
        {  4,  4,  4,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 5: four rotations, no flip
    //  ##
    // ##
    // #
    {
        {  _,  5,  5,  _,  _ },
        {  5,  5,  _,  _,  _ },
        {  5,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  5,  5,  _,  _,  _ },
        {  _,  5,  5,  _,  _ },
        {  _,  _,  5,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _,  5,  _,  _ },
        {  _,  5,  5,  _,  _ },
        {  5,  5,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  5,  _,  _,  _,  _ },
        {  5,  5,  _,  _,  _ },
        {  _,  5,  5,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 6: four rotations, no flip
    // ###
    //  #
    //  #
    {
        {  6,  6,  6,  _,  _ },
        {  _,  6,  _,  _,  _ },
        {  _,  6,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _,  6,  _,  _ },
        {  6,  6,  6,  _,  _ },
        {  _,  _,  6,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  6,  _,  _,  _ },
        {  _,  6,  _,  _,  _ },
        {  6,  6,  6,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  6,  _,  _,  _,  _ },
        {  6,  6,  6,  _,  _ },
        {  6,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 7: four rotations, no flip
    // ###
    // # #
    {
        {  7,  7,  7,  _,  _ },
        {  7,  _,  7,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  7,  7,  _,  _,  _ },
        {  _,  7,  _,  _,  _ },
        {  7,  7,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  7,  _,  7,  _,  _ },
        {  7,  7,  7,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  7,  7,  _,  _,  _ },
        {  7,  _,  _,  _,  _ },
        {  7,  7,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 8: four rotations, flip
    // #
    // ###
    //  #
    {
        {  8,  _,  _,  _,  _ },
        {  8,  8,  8,  _,  _ },
        {  _,  8,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  8,  8,  _,  _ },
        {  8,  8,  _,  _,  _ },
        {  _,  8,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  8,  _,  _,  _ },
        {  8,  8,  8,  _,  _ },
        {  _,  _,  8,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  8,  _,  _,  _ },
        {  _,  8,  8,  _,  _ },
        {  8,  8,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  8,  8,  _,  _,  _ },
        {  _,  8,  8,  _,  _ },
        {  _,  8,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  8,  _,  _,  _ },
        {  8,  8,  8,  _,  _ },
        {  8,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  8,  _,  _,  _ },
        {  8,  8,  _,  _,  _ },
        {  _,  8,  8,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _,  8,  _,  _ },
        {  8,  8,  8,  _,  _ },
        {  _,  8,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 9: four rotations, flip
    // ####
    //    #
    {
        {  9,  9,  9,  9,  _ },
        {  _,  _,  _,  9,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  9,  _,  _,  _ },
        {  _,  9,  _,  _,  _ },
        {  _,  9,  _,  _,  _ },
        {  9,  9,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  9,  _,  _,  _,  _ },
        {  9,  9,  9,  9,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  9,  9,  _,  _,  _ },
        {  9,  _,  _,  _,  _ },
        {  9,  _,  _,  _,  _ },
        {  9,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  9,  _,  _,  _,  _ },
        {  9,  _,  _,  _,  _ },
        {  9,  _,  _,  _,  _ },
        {  9,  9,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _,  _,  9,  _ },
        {  9,  9,  9,  9,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  9,  9,  _,  _,  _ },
        {  _,  9,  _,  _,  _ },
        {  _,  9,  _,  _,  _ },
        {  _,  9,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  9,  9,  9,  9,  _ },
        {  9,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 10: four rotations, flip
    // ####
    //   #
    {
        { 10, 10, 10, 10,  _ },
        {  _,  _, 10,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 10,  _,  _,  _ },
        {  _, 10,  _,  _,  _ },
        { 10, 10,  _,  _,  _ },
        {  _, 10,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 10,  _,  _,  _ },
        { 10, 10, 10, 10,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 10,  _,  _,  _,  _ },
        { 10, 10,  _,  _,  _ },
        { 10,  _,  _,  _,  _ },
        { 10,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 10,  _,  _,  _,  _ },
        { 10,  _,  _,  _,  _ },
        { 10, 10,  _,  _,  _ },
        { 10,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _, 10,  _,  _ },
        { 10, 10, 10, 10,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 10,  _,  _,  _ },
        { 10, 10,  _,  _,  _ },
        {  _, 10,  _,  _,  _ },
        {  _, 10,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 10, 10, 10, 10,  _ },
        {  _, 10,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 11: four rotations, flip
    // ###
    //   ##
    {
        { 11, 11, 11,  _,  _ },
        {  _,  _, 11, 11,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 11,  _,  _,  _ },
        {  _, 11,  _,  _,  _ },
        { 11, 11,  _,  _,  _ },
        { 11,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 11, 11,  _,  _,  _ },
        {  _, 11, 11, 11,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 11,  _,  _,  _ },
        { 11, 11,  _,  _,  _ },
        { 11,  _,  _,  _,  _ },
        { 11,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 11,  _,  _,  _,  _ },
        { 11,  _,  _,  _,  _ },
        { 11, 11,  _,  _,  _ },
        {  _, 11,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _,  _, 11, 11,  _ },
        { 11, 11, 11,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 11,  _,  _,  _,  _ },
        { 11, 11,  _,  _,  _ },
        {  _, 11,  _,  _,  _ },
        {  _, 11,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 11, 11, 11,  _ },
        { 11, 11,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    // Pentomino 12: four rotations, flip
    // ###
    //  ##
    {
        { 12, 12, 12,  _,  _ },
        {  _, 12, 12,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 12,  _,  _,  _ },
        { 12, 12,  _,  _,  _ },
        { 12, 12,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 12, 12,  _,  _,  _ },
        { 12, 12, 12,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 12, 12,  _,  _,  _ },
        { 12, 12,  _,  _,  _ },
        { 12,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 12,  _,  _,  _,  _ },
        { 12, 12,  _,  _,  _ },
        { 12, 12,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        {  _, 12, 12,  _,  _ },
        { 12, 12, 12,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 12, 12,  _,  _,  _ },
        { 12, 12,  _,  _,  _ },
        {  _, 12,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    },
    {
        { 12, 12, 12,  _,  _ },
        { 12, 12,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
        {  _,  _,  _,  _,  _ },
    }
};

const char pieceName[13] =      { '#','X','I','Z','V','W','T','U','F','L','Y','N','P'};
const int pieceMin[13] =        {  2,  3,  1,  3,  3,  3,  3,  2,  3,  2,  2,  2,  2 };
const int pieceMax[13] =        {  2,  3,  5,  3,  3,  3,  3,  3,  3,  4,  4,  4,  3 };
const int pieceIdx[13] =        {  0,  1,  2,  4,  8, 12, 16, 20, 24, 32, 40, 48, 56 };
const int orientMax[13] =       {  1,  1,  2,  4,  4,  4,  4,  4,  8,  8,  8,  8,  8 };
const int pieceColor[13] =      {  7,  9, 10, 11, 12, 13, 14,  1,  2,  3,  4,  5,  6 };

int pieceOrient[13] =           { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int pieceRow[13] =              { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
int pieceCol[13] =              { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };


int lastPiece = -1;
int solutionCount = 0;
int backTracksCount = 0;

const int8_t MAGIC_NUMBER = 100;
const int8_t b = 0; // black
const int8_t w = 1; // white
// blackness or whiteness of most top left corner of pieces box
const int8_t bw[] = {
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

// apply chess pattern to pieces
void applyChessPattern() {
    for (int i = 0; i < 64; ++i)
        for (int r = 0; r < 5; ++r)
            for (int c = 0; c < 5; ++c)
                if(piece[i][r][c] != _ && bw[i] == (r+c)%2)
                    piece[i][r][c] += MAGIC_NUMBER;
}

// check if board contains propper chess board (or part of it)
bool isChess() {
    int8_t ccolor; // bottom right corner color
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] == _ || board[r][c] % MAGIC_NUMBER == 0 ) // ignore empty and square
                continue;
            ccolor = board[r][c] / MAGIC_NUMBER ? b : w;
            if ((r+c)%2 != 0) {
                ccolor = !ccolor;
            }
            goto found;
        }
    }
    return true; // anything possible
    found:
    for (int r = 0; r < 8; ++r) {
        for (int c = 0; c < 8; ++c) {
            if (board[r][c] == _ || board[r][c] % MAGIC_NUMBER == 0) // ignore empty and square
                continue;
            if ((r+c)%2 == 0) { // even
                if ((board[r][c] / MAGIC_NUMBER ? b : w) != ccolor)
                    return false;
            } else { // odd
                if ((board[r][c] / MAGIC_NUMBER ? b : w) != !ccolor)
                    return false;
            }
        }
    }
    return true;
}

void printBoard() {
    bool hide[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int n = 0;
    while (n < HIDE) {
        int i = rand() % 13;
        if (!hide[i]) {
            hide[i] = true;
            ++n;
        }
    }
    
    std::cout << "╔════════════════╗" << "\n";
    for (int row = 0; row != 8; ++row) {
        std::cout << "║";
        for (int col = 0; col != 8; ++col) {
            if (board[row][col] == _ || hide[board[row][col] % MAGIC_NUMBER]){
                std::cout << "  ";
                continue;
            }
            if (COLOR_OUTPUT) {
                std::cout << "\033[";
                if (CHESS_PATTERN) {
                    std::cout << ";48;5;" << ((board[row][col] / MAGIC_NUMBER)?232:238); // bg
                }
                std::cout << ";38;5;" << pieceColor[board[row][col] % MAGIC_NUMBER] << "m"; // fg
                std::cout << "▓▓";
                std::cout << "\033[0m";
            } else {
                std::cout << " " <<  pieceName[board[row][col] % MAGIC_NUMBER];
            }
        }
        std::cout << "║\n";
    }
    std::cout << "╚════════════════╝";
    std::cout << std::endl;
}

void printSolution() {
    std::cout << pieceOrient[0] << pieceRow[0]+1 << pieceCol[0]+1;
    for (int n = 1; n != 13; ++n) {
        std::cout << '-' << pieceOrient[n] << pieceRow[n]+1 << pieceCol[n]+1;
    }
    std::cout << ' ' << solutionCount << std::endl;
}

// check whether piece is placable to given pos
bool testPiece(int row, int col, int orient) {
    for (int r = 0; r != pieceMax[lastPiece + 1]; ++r) {
        for (int c = 0; c != pieceMax[lastPiece + 1]; ++c) {
            const int8_t val = piece[pieceIdx[lastPiece + 1] + orient][r][c];
            if (val != _) {
                if (7 < row + r || 7 < col + c || board[row + r][col + c] != _) {
                    return false;
                }
            }
        }
    }

    return true;
}

void placePiece(int row, int col, int orient) {
    ++lastPiece;
    for (int r = 0; r != pieceMax[lastPiece]; ++r) {
        for (int c = 0; c != pieceMax[lastPiece]; ++c) {
            const int8_t val = piece[pieceIdx[lastPiece] + orient][r][c];
            if (val != _) {
                board[row + r][col + c] = val;
            }
        }
    }
    pieceRow[lastPiece] = row;
    pieceCol[lastPiece] = col;
    pieceOrient[lastPiece] = orient;
}

void removePiece() {
    for (int r = 0; r != pieceMax[lastPiece]; ++r) {
        for (int c = 0; c != pieceMax[lastPiece]; ++c) {
            const int8_t val = piece[pieceIdx[lastPiece] + pieceOrient[lastPiece]][r][c];
            if (val != _) {
                board[pieceRow[lastPiece] + r][pieceCol[lastPiece] + c] = _;
            }
        }
    }
    pieceRow[lastPiece] = -1;
    pieceCol[lastPiece] = -1;
    pieceOrient[lastPiece] = -1;
    --lastPiece;
}

// mark all unmarked empty consecutive squares (hole area)
int mark(int row, int col, int markVal) {
    int markCount = 0;

    if (board[row][col] == _) {
        board[row][col] = markVal;
        ++markCount;

        if (0 < row) {
            markCount += mark(row - 1, col, markVal);
        }
        if (row < 7) {
            markCount += mark(row + 1, col, markVal);
        }
        if (0 < col) {
            markCount += mark(row, col - 1, markVal);
        }
        if (col < 7) {
            markCount += mark(row, col + 1, markVal);
        }
    }

    return markCount;
}

// return true if not possible to make solution from this
bool prune() {
    bool bResult = false;
    int markVal = -2;
    int totalMarkCount = 0;

    if (CHESS_PATTERN && !isChess() ) {
        ++backTracksCount;
        bResult = true;
        goto log;
    }

    for (int row = 0; row <= 7; ++row) {
        for (int col = 0; col <= 7; ++col) {
            const int markCount = mark(row, col, markVal);
            if (markCount) {
                --markVal;
                totalMarkCount += markCount;
            } else {
                continue;
            }
            if (markCount % 5) { // cant fit pentominos to marked hole - not multiple of 5
                bResult = true; 
                ++backTracksCount;
                goto cleanup;
            }
            if (totalMarkCount + lastPiece*5 + 4 == 64) { // all holes found
                goto cleanup;
            }
        }
    }

cleanup:

    for (int row = 0; row <= 7; ++row) {
        for (int col = 0; col <= 7; ++col) {
            if (board[row][col] < _) {
                board[row][col] = _;
            }
        }
    }

log:
    if (SHOW_TRIES && bResult) { // log bad cases
        printSolution();
        printBoard();
    }

    return bResult;
}

void solvePiece(int row, int col, int orient) {
    if (!testPiece(row, col, orient)) {
        return;
    }

    placePiece(row, col, orient);

    if (lastPiece == 12) {
        ++solutionCount;
        printSolution();
        printBoard();
    }
    else {
        if (!prune()) {
            const int rowMax = 8 - pieceMin[lastPiece + 1];
            for (int orient = 0; orient < orientMax[lastPiece + 1]; ++orient) {
                for (int row = 0; row <= rowMax; ++row) {
                    for (int col = 0; col <= rowMax; ++col) {
                        solvePiece(row, col, orient);
                    }
                }
            }
        } // else back track
    }

    removePiece();
}

void solveCross(int row, int col) {
    if (!testPiece(row, col, 0)) {
        return;
    }

    placePiece(row, col, 0);

    if (!prune()) {
        const int rowMax = 8 - pieceMin[lastPiece + 1];
        for (int orient = 0; orient < orientMax[lastPiece + 1]; ++orient) {
            if (pieceRow[0] == pieceCol[0] && pieceRow[1] == pieceCol[1] && 0 < orient) {
                // Special case: if symmetric about diagonal, use only one line orientation.
                break;
            }
            for (int row = 0; row <= rowMax; ++row) {
                for (int col = 0; col <= rowMax; ++col) {
                    solvePiece(row, col, orient);
                }
            }
        }
    }

    removePiece();
}

void solveSquare(int row, int col) {
    placePiece(row, col, 0);

    if (row == 3 && col == 3) {
        // Square in centre -> cross in 1/8.
        for (int row = 0; row <= 2; ++row) {
            for (int col = 0; col <= row; ++col) {
                solveCross(row, col);
            }
        }
    } else if (row == col) {
        // Square on diagonal -> cross in 1/2.
        for (int row = 0; row <= 5; ++row) {
            for (int col = 0; col <= row; ++col) {
                solveCross(row, col);
            }
        }
    } else if (row == 3) {
        // Square on mid line -> cross in 1/2.
        for (int row = 0; row <= 2; ++row) {
            for (int col = 0; col <= 5; ++col) {
                solveCross(row, col);
            }
        }
    } else {
        // Square in interior -> cross anywhere.
        for (int row = 0; row <= 5; ++row) {
            for (int col = 0; col <= 5; ++col) {
                solveCross(row, col);
            }
        }
    }

    removePiece();
}

int main() {
    std::cout << "Pentomino solver\n";

    if (CHESS_PATTERN) {
        applyChessPattern();
    }

    std::time_t time1;
    std::time(&time1);

    if (HIDE) {
        srand(time(NULL));
    }

    if (CENTER_SQUARE) {
        // Solve square in centre only.
        solveSquare(3, 3);
    } else {
        // Solve square in 1/8.
        for (int row = 0; row <= 3; ++row) {
            for (int col = 0; col <= row; ++col) {
                solveSquare(row, col);
            }
        }
    }

    std::time_t time2;
    std::time(&time2);
    double seconds = std::difftime(time2, time1);

    std::cout << solutionCount << " solutions found (and " << backTracksCount <<  " wrong paths tried) in " << seconds << " seconds." << std::endl;

    return 0;
}
