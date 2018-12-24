pentomino-solver: pentomino-solver.cpp
	g++ -O3 $< -o $@

run:
	./pentomino-solver

solveall: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=0 ./pentomino-solver
solvechess: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 ./pentomino-solver

game3: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=3 ./pentomino-solver
game4: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=4 ./pentomino-solver
game5: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=5 ./pentomino-solver
game6: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=6 ./pentomino-solver
game7: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=7 ./pentomino-solver
game8: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=8 ./pentomino-solver
game9: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=9 ./pentomino-solver
game10: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=10 ./pentomino-solver
game11: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=11 ./pentomino-solver
game12: pentomino-solver
	COLOR_OUTPUT=1 CHESS_PATTERN=1 HIDE=12 ./pentomino-solver

clean:
	rm -rf pentomino-solver
