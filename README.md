# Super Tic-Tac-Toe
Super tic-tac-toe is a board game composed of nine tic-tac-toe boards arranged in a 3 × 3 grid.
<br>Players take turns playing on the smaller tic-tac-toe boards until one of them wins on the larger board.

<h2>Rules</h2>

<p>Just like in regular tic-tac-toe, the two players (X and O) take turns, starting with X.
<br>The game starts with X playing wherever they want in any of the 81 empty spots.
<br>Next the opponent plays, however they are forced to play in the small board indicated by the relative location of the previous move.
<br>For example, if X plays in the top right square of a small (3 × 3) board,
<br>then O has to play in the small board located at the top right of the larger board.
<br>Playing any of the available spots decides in which small board the next player plays.
<br><br>
  
<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/5/51/Super_tic-tac-toe_rules_example_-_simple.png/330px-Super_tic-tac-toe_rules_example_-_simple.png">
<br>

<br>If a move is played so that it is to win a small board by the rules of normal tic-tac-toe,
<br>then the entire small board is marked as won by the player in the larger board.
<br>Once a small board is won by a player or it is filled completely, no more moves may be played in that board.
<br>If a player is sent to such a board, then that player may play in any other board.
<br>Game play ends when either a player wins the larger board or there are no legal moves remaining,
<br>in which case the game is a draw.
<br>

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/7/7d/Super_tic-tac-toe_rules_example.png/330px-Super_tic-tac-toe_rules_example.png">
</p>

# Compiling
g++ main.cpp src/TicTacToe.cpp -o main

### Using the Makefile to compile:
- Windows:
  - mingw32-make.exe
- Linux:
  - make   
