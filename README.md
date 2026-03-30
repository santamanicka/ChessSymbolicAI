# Chess AI (2000)

A chess engine with minimax search and alpha-beta pruning, written in Turbo C++ for DOS in June-July 2000.

## What It Does

- Full chess game with graphical board rendered using Turbo C BGI graphics
- Human vs. computer play (choose Black or White)
- AI opponent using **minimax search with alpha-beta pruning** (depth 5)
- Legal move validation for all piece types
- Check detection and prevention of illegal moves
- Piece capture with material-based position evaluation
- Keyboard-driven UI: arrow keys to navigate, Delete to select a piece, Insert to place it

## Architecture

### Board Representation

An `int board[8][8]` array where piece values encode both type and color:

| Piece  | Value | Encoding |
|--------|-------|----------|
| Pawn   | 1     | +1 (white), -1 (black) |
| Knight | 5     | +5 / -5 |
| Bishop | 10    | +10 / -10 |
| Rook   | 20    | +20 / -20 |
| Queen  | 35    | +35 / -35 |
| King   | 50    | +50 / -50 |

Piece values double as material scores for the evaluation function -- capturing a piece adds its value to the position score.

### AI: Minimax with Alpha-Beta Pruning

The `think()` function implements a depth-5 minimax search with alpha-beta pruning (negamax variant):

1. Generate all legal moves for the current player
2. For each move, make it on the board, check for self-check, then recurse
3. Use negamax sign-flipping: `think(!who, depth+1, board, best, temp, -pass, -use)`
4. Prune branches where `pass >= use` (alpha-beta cutoff)
5. At depth 0, record the best move found

The search evaluates positions purely by material balance -- no positional heuristics.

### Graphics

All rendering uses Turbo C **BGI (Borland Graphics Interface)**:
- Each chess piece is drawn line-by-line and arc-by-arc (pawn, rook, bishop, knight, king, queen)
- The board alternates white (color 15) and brown (color 6) squares with a 3D border effect
- Selected squares flash with random colors until a key is pressed
- Computer moves are accompanied by a `sound(200)` beep

## File Structure

```
src/
  chessfinal.cpp    Main game: board setup, AI search, game loop (Jul 29, 2000)
  board.cpp         Graphics: board drawing and all piece rendering
  legalmov.cpp      Move validation: scan() for path obstacles, verify() for legal moves
  looknfee.cpp      UI: cursor blinking, square selection, rectangle redrawing
```

## Technical Notes

- Written for **Turbo C++ 3.0** on DOS
- Uses `graphics.h` (BGI), `conio.h`, `dos.h` -- DOS-specific headers
- Will not compile on modern systems without a Turbo C emulator (e.g., DOSBox + Turbo C)
- Original file dates: June 20 - July 29, 2000
