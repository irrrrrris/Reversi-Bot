//
// Author: Iris Wang
//

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

char oppositeColour(char colour) 
{
   char oppositeColour;
   if (colour == 'W') 
   {
      oppositeColour = 'B';
   } 
   else 
   {
      oppositeColour = 'W';
   }
   return oppositeColour;
}

bool positionInBounds(int n, int row, int col) 
{
    if(row < n && row >=0 && col < n && col >=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void printBoard(char board[][26], int n) 
{
    //print row header "abcd..."
    printf("  ");
    for(int i = 97; i < 97 + n; i++)
    {
        printf("%c", i);
    }
    printf("\n");

    //print the board 
    for(int i = 0; i < n; i++)
    {
        //print the column header "abcd..."
        printf("%c ", i + 97);
        for(int j = 0; j < n; j++)
        {
            printf("%c", board[i][j]);
        }
    
        printf("\n");      
    }
}

bool checkLegalInDirection(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol) 
{
int count = 0;
int countNoSkipping = 0;
int RowIWantToCheck = row + deltaRow;
int ColIWantToCheck = col + deltaCol;
   
while (board[RowIWantToCheck][ColIWantToCheck] != 'U' && positionInBounds(n, RowIWantToCheck, ColIWantToCheck)) 
{
    char oppositeColour;
    if (colour == 'W') 
    {
      oppositeColour = 'B';
    } 
    else 
    {
      oppositeColour = 'W';
    }

    if (board[RowIWantToCheck][ColIWantToCheck] == oppositeColour) 
    {
        count++;
    } 
    else if (count != 0 && board[RowIWantToCheck][ColIWantToCheck] == colour && count == countNoSkipping) 
    {
        return true;
    }
    countNoSkipping++;
    RowIWantToCheck += deltaRow;
    ColIWantToCheck += deltaCol;    
}
   
return false;

}

int FScore(char board[][26], int n, int row, int col, char colour, int deltaRow, int deltaCol)
{
    int count = 0;
    int countNoSkipping = 0;
    int RowIWantToCheck = row + deltaRow;
    int ColIWantToCheck = col + deltaCol;

    while (board[RowIWantToCheck][ColIWantToCheck] != 'U' && positionInBounds(n, RowIWantToCheck, ColIWantToCheck)) 
    {
        char colour2 = oppositeColour(colour);

        if (board[RowIWantToCheck][ColIWantToCheck] == colour2) 
        {
            count++;
        } 
        else if (count != 0 && board[RowIWantToCheck][ColIWantToCheck] == colour && count == countNoSkipping) 
        {
            return count;
        }
        countNoSkipping++;
        RowIWantToCheck += deltaRow;
        ColIWantToCheck += deltaCol;    
    }
   
    return 0;
}

//Star positions
int cornerScore(char board[][26], int n, int row, int col, char colour)
{
    if (((row == (n-1) && col == (n-1)) || (row == (n-1) && col ==0) || (row == 0 && col == 0) || (row == 0 && col == (n-1))))
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

//Tick positions
int edgeScore(char board[][26], int n, int row, int col, char colour)
{
    if( (row == (n-1) && (col != 1 || col != (n-2))) || 
        (col == (n-1) && (row != 1 || row != (n-2))) || 
        (row == 0 && (col != 1 || col != (n-2))) || 
        (col == 0 && (row != 1 || row != (n-2))) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void flipInThisDir(char colour, char board[][26], int n, int row, int col, int rowDir, int colDir)
{
    for(int i = 1; i < n; i++)
    {
        if(((row + i* rowDir) >=0) && ((row + i* rowDir) < 26) && ( (col + i * colDir) >=0) && ((col + i * colDir) < 26))
        {
            if(colour == 'W')
            {
                if(board[row + i * rowDir][col + i * colDir] == 'B')
                {
                    board[row + i * rowDir][col + i * colDir] = 'W';
                }
                else
                {
                    return;
                }
            }
            else if(colour == 'B')
            {
                if(board[row + i * rowDir][col + i * colDir] == 'W')
                {
                    board[row + i * rowDir][col + i * colDir] = 'B';
                }
                else
                {
                    return;
                }
            }
        }
    }   
}

void updateBoard(int rowIntended, int colIntended, char colour, char board[][26], int n)
{
    int row = rowIntended;
    int col = colIntended;

    board[row][col] = colour; //drop the white/black dot

    if (checkLegalInDirection(board, n, row, col, colour, -1, 0))
    {
        flipInThisDir(colour, board, n, row, col, -1, 0);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, -1))
    {
        flipInThisDir(colour, board, n, row, col, -1, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, -1))
    {
        flipInThisDir(colour, board, n, row, col, 0, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, -1))
    {
        flipInThisDir(colour, board, n, row, col, 1, -1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 0))
    {
        flipInThisDir(colour, board, n, row, col, 1, 0);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 1, 1))
    {
        flipInThisDir(colour, board, n, row, col, 1, 1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, 0, 1))
    {
        flipInThisDir(colour, board, n, row, col, 0, 1);
    }
    if (checkLegalInDirection(board, n, row, col, colour, -1, 1))
    {
        flipInThisDir(colour, board, n, row, col, -1, 1);
    }
}

int numberOfEliminatedOpponentMove(char board[][26], int n, char colour, int rowIntended, int colIntended)
{
    int temp1 = 0;
    int temp2 = 0;
    char copy[26][26]; //create a copy of the board

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {   
            copy[i][j] = board[i][j];
        }
    }
    updateBoard(rowIntended, colIntended, colour, copy, n);

    int opponentColour = oppositeColour(colour);
    for(int row = 0; row < n; row++)
        {
            for(int col = 0; col < n; col++)
            {   
                if(board[row][col] == 'U')
                {
                    int totalScore = 0;
                    totalScore = FScore(board, n, row, col, opponentColour, -1, 0) + FScore(board, n, row, col, opponentColour, -1, -1) + FScore(board, n, row, col, opponentColour, 0, -1) + FScore(board, n, row, col, opponentColour, 1, -1) + FScore(board, n, row, col, opponentColour, 1, 0) + FScore(board, n, row, col, opponentColour, 1, 1) + FScore(board, n, row, col, opponentColour, 0, 1) + FScore(board, n, row, col, opponentColour, -1, 1);
                    if (totalScore > 0)
                    {
                        temp1++;
                    }
                }
            }
        }
    int numberOfOpponentAvailableMovesBefore = temp1;

    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {   
            if(copy[row][col] == 'U' )
            {
                int totalScore = 0;
                totalScore = FScore(copy, n, row, col, opponentColour, -1, 0) + FScore(copy, n, row, col, opponentColour, -1, -1) + FScore(copy, n, row, col, opponentColour, 0, -1) + FScore(copy, n, row, col, opponentColour, 1, -1) + FScore(copy, n, row, col, opponentColour, 1, 0) + FScore(copy, n, row, col, opponentColour, 1, 1) + FScore(copy, n, row, col, opponentColour, 0, 1) + FScore(copy, n, row, col, opponentColour, -1, 1);
                if (totalScore > 0)
                {
                    temp2++;
                }
            }
        }
    }
    int numberOfOpponentAvailableMovesAfter = temp2;

    int numberOfEliminatedMove = numberOfOpponentAvailableMovesBefore - numberOfOpponentAvailableMovesAfter;

    return numberOfEliminatedMove;
}

int numberOfMoveCreated(char board[][26], int n, char colour, int rowIntended, int colIntended)
{
    int numberOfAvailableMoves = 0;
    char copy[26][26]; //create a copy of the board

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {   
            copy[i][j] = board[i][j];
        }
    }
    updateBoard(rowIntended, colIntended, colour, copy, n);

    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {   
            if(copy[row][col] == 'U' )
            {
                int totalScore = 0;
                totalScore = FScore(copy, n, row, col, colour, -1, 0) + FScore(copy, n, row, col, colour, -1, -1) + FScore(copy, n, row, col, colour, 0, -1) + FScore(copy, n, row, col, colour, 1, -1) + FScore(copy, n, row, col, colour, 1, 0) + FScore(copy, n, row, col, colour, 1, 1) + FScore(copy, n, row, col, colour, 0, 1) + FScore(copy, n, row, col, colour, -1, 1);
                if (totalScore > 0)
                {
                    numberOfAvailableMoves++;
                }
            }
        }
    }

    return numberOfAvailableMoves;
}


int positionToConsiderFirst(char board[][26], int n, char turn, int row, int col)
//the inner ring should be filled first
{
    for (int col1 = -2; col1 < 2; col1++) 
    {
		if (row == (n/2 - 2) && col == (col1 + n/2)) 
        {
			return 1;
		}
		if (row == (n/2 + 1) && col == (col1 + n/2)) 
        {
			return 1;
		}
	}

	    if (row == (n/2 - 1) && (col == (n/2 - 2) || col == (n/2 + 1))) 
        {
			return 1;
	    }
        else if ( (row == (n/2)) && (col == (n/2 - 2) || col == (n/2 + 1)) )
        {
			return 1;
		}
        else 
        {
		    return 0;
	    }

	return 0;
}

bool boolPositionToConsiderFirst(char board[][26], int n, char turn, int row, int col)
//the inner ring should be filled first
{
    for (int col1 = -2; col1 < 2; col1++) 
    {
		if (row == (n/2 - 2) && col == (col1 + n/2)) 
        {
			return true;
		}

		if (row == (n/2 + 1) && col == (col1 + n/2)) 
        {
			return true;
		}
	}
	    if (row == (n/2 - 1) && (col == (n/2 - 2) || col == (n/2 + 1))) 
        {
			return true;
	    }
        else if ( (row == (n/2)) && (col == (n/2 - 2) || col == (n/2 + 1)) )
        {
			return true;
		}
        else 
        {
		    return false;
	    }
	return false;
}

int avoidCornerPosition(int row, int col, int n, char board[][26])
{
    //top-left corner 
    if ( (board[0][0] == 'U') && ( ((row == 0)&&(col == 1)) || ((row == 1)&&(col == 0)) || ((row == 1)&&(col == 1)) ))
    {
        return 1;
    }
    //top-right corner
    if ( (board[0][n-1] == 'U') && ( ((row == 0)&&(col == n-2)) || ((row == 1)&&(col == n-1)) || ((row == 1)&&(col == n-2)) ))
    {
        return 1;
    }
    //bottom-right corner
    if ( (board[n-1][n-1] == 'U') && ( ((row == n-1)&&(col == n-2)) || ((row == n-2)&&(col == n-1)) || ((row == n-2)&&(col == n-2)) ))
    {
        return 1;
    }
    //bottom-left corner
    if ( (board[n-1][0] == 'U') && ( ((row == n-1)&&(col == 1)) || ((row == n-2)&&(col == 0)) || ((row == n-2)&&(col == 1)) ))
    {
        return 1;
    }
    else
    {
        return 0;
    } 
    
}

int avoidEdgePosition(int row, int col, int n, char board[][26])
{
    for(int i = 2; i < n - 2; i++)
    {
        if( (board[0][i] == 'U') && ((row == 1)&&(col == i)))
        {
            return 1;
        }
        if( (board[n-1][i] == 'U') && ((row == n-2)&&(col == i)))
        {
            return 1;
        }
        if( (board[i][0] == 'U') && ((row == i)&&(col == 1)))
        {
            return 1;
        }
        if( (board[i][n-1] == 'U') && ((row == i)&&(col == n-2)))
        {
            return 1;
        }
    }
    return 0;
}

bool checkInputValid(int row, int col, char colour, char board[][26], int n)
{
    if (checkLegalInDirection(board, n, row, col, colour, -1, 0) ||
        checkLegalInDirection(board, n, row, col, colour, -1, -1) ||
        checkLegalInDirection(board, n, row, col, colour, 0, -1) ||
        checkLegalInDirection(board, n, row, col, colour, 1, -1) ||
        checkLegalInDirection(board, n, row, col, colour, 1, 0) ||
        checkLegalInDirection(board, n, row, col, colour, 1, 1) ||
        checkLegalInDirection(board, n, row, col, colour, 0, 1) ||
        checkLegalInDirection(board, n, row, col, colour, -1, 1)) 
    {
        return true;
    }   
    else
    {
        return false;
    }
}


int makeMove(const char board[][26], int n, char turn, int *row, int *col) 
{
    //Canshu for B

    if(turn == 'B')
    {
    float highestSuperScore = -10;
    int moveRow = 0;
    int movecol = 0;

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
			if ((board[i][j] == 'U')&& checkInputValid(i, j, turn, board,n)) 
            {
				
				if (boolPositionToConsiderFirst(board, n, turn, i, j)) 
                {	
				    //1. SUPERSCORE is made up of:
                    //   (1) fScore: score based on number of flipping tiles
                    //   (2) eScore: score when more opponent moves are eliminated 

                    float superScore = 0;

                    //(1) fScore: positive score based on number of flipping tiles
                    //            + number of flipped tiles
                    int fScore = FScore(board, n, i, j, turn, -1, 0) + FScore(board, n, i, j, turn, -1, -1) + FScore(board, n, i, j, turn, 0, -1) + FScore(board, n, i, j, turn, 1, -1) + FScore(board, n, i, j, turn, 1, 0) + FScore(board, n, i, j, turn, 1, 1) + FScore(board, n, i, j, turn, 0, 1) + FScore(board, n, i, j, turn, -1, 1);

                    //(6) eScore: positive score when more opponent moves are eliminated
                    //            number of eliminated opponent's moves
                    int eScore = numberOfEliminatedOpponentMove(board, n, turn, i, j);

                    /*//(7) mScore: score when larger number of moves are created
                    //            number of available moves created
                    int mScore = numberOfMoveCreated(board, n, turn, i, j);*/

            
                    superScore = fScore + 3*eScore;

                    if(superScore > highestSuperScore)
                    {
                        highestSuperScore = superScore;

                        moveRow = i;
                        movecol = j;
                    }
			    }			
			}
		}
	}
    if(moveRow != 0 && movecol != 0)
    {
        *row = moveRow;
	    *col = movecol;

        return 0;
    }
    
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
			if ((board[i][j] == 'U')&& checkInputValid(i, j, turn, board,n)) 
            {
                if (((i == (n-1) && j == (n-1)) || (i == (n-1) && j ==0) || (i == 0 && j == 0) || (i == 0 && j == (n-1)))) 
                {	
		            *row = i;
		            *col = j;

		            return 0;
	            } 
            }
        }
    }

    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {
            //Banned the position around the Corners
            if ((board[row][col] == 'U') && checkInputValid(row, col, turn, board,n))
            {
                //1. SUPERSCORE is made up of:
                //   (1) fScore: score based on number of flipping tiles
                //   (2) pScore: score depend on the position:
                //   (3) eScore: score when more opponent moves are eliminated 

                float superScore = 0;

                //(1) fScore: score based on number of flipping tiles
                //            + number of flipped tiles
                int fScore = FScore(board, n, row, col, turn, -1, 0) + FScore(board, n, row, col, turn, -1, -1) + FScore(board, n, row, col, turn, 0, -1) + FScore(board, n, row, col, turn, 1, -1) + FScore(board, n, row, col, turn, 1, 0) + FScore(board, n, row, col, turn, 1, 1) + FScore(board, n, row, col, turn, 0, 1) + FScore(board, n, row, col, turn, -1, 1);

                //(2) p1Score: score depend on the position:
                //            Corner/star positions(++) or edge not around corner/tick positions(+)
                //            if star position: +2
                //            if tick position: +1
                int p1Score = cornerScore(board, n, row, col, turn) + edgeScore(board, n, row, col, turn);

                //(3) p2Score: the position is in the inner ring should be consider first
                int p2Score = positionToConsiderFirst(board, n, turn, row, col);

                //(4) p3Score: deducted positions around the Corners when the Corners are empty
                int p3Score = avoidCornerPosition(row, col, n, board);

                //(5) p4Score: deducted positions around the edges when the edges are empty
                int p4Score = avoidEdgePosition(row, col, n, board);

                //(6) eScore: score when more opponent moves are eliminated
                //            number of eliminated opponent's moves
                int eScore = numberOfEliminatedOpponentMove(board, n, turn, row, col);
            
                //(7) mScore: score when larger number of moves are created
                //            number of available moves created
                int mScore = numberOfMoveCreated(board, n, turn, row, col);

                


                superScore = 1.5 * fScore + 0.15 * p1Score + 0.2 * p2Score - p3Score - p4Score + eScore/30.0 + mScore/30.0;

                if(superScore > highestSuperScore)
                {
                    highestSuperScore = superScore;

                    moveRow = row;
                    movecol = col;
                }
            }
        }
    }

    *row = moveRow;
	*col = movecol;

    return 0;
    }



    else if(turn == 'W')
    {
        float highestSuperScore = -10;
    int moveRow = 0;
    int movecol = 0;

    for(int row = 0; row < n; row++)
    {
        for(int col = 0; col < n; col++)
        {
            //Banned the position around the Corners
            if ((board[row][col] == 'U') )
            {
                //1. SUPERSCORE is made up of:
                //   (1) fScore: score based on number of flipping tiles
                //   (2) pScore: score depend on the position:
                //   (3) eScore: score when more opponent moves are eliminated 

                float superScore = 0;

                //(1) fScore: positive score based on number of flipping tiles
                //            + number of flipped tiles
                int fScore = FScore(board, n, row, col, turn, -1, 0) + FScore(board, n, row, col, turn, -1, -1) + FScore(board, n, row, col, turn, 0, -1) + FScore(board, n, row, col, turn, 1, -1) + FScore(board, n, row, col, turn, 1, 0) + FScore(board, n, row, col, turn, 1, 1) + FScore(board, n, row, col, turn, 0, 1) + FScore(board, n, row, col, turn, -1, 1);

                //(2) p1Score: positive score depend on the position:
                //            Corner/star positions(++) or edge not around corner/tick positions(+)
                //            if star position: +2
                //            if tick position: +1
                int p1Score = cornerScore(board, n, row, col, turn) + edgeScore(board, n, row, col, turn);

                //(3) p2Score: the position is in the inner ring should be consider first
                int p2Score = positionToConsiderFirst(board, n, turn, row, col);

                //(4) p3Score: deducted positions around the Corners when the Corners are empty
                int p3Score = avoidCornerPosition(row, col, n, board);

                //(5) p4Score: deducted positions around the edges when the edges are empty
                int p4Score = avoidEdgePosition(row, col, n, board);

                //(6) eScore: positive score when more opponent moves are eliminated
                //            number of eliminated opponent's moves
                int eScore = numberOfEliminatedOpponentMove(board, n, turn, row, col);

                


                superScore = 5.6 * fScore + 5.5 * p2Score - 30 * p3Score;

                if(superScore > highestSuperScore)
                {
                    highestSuperScore = superScore;

                    moveRow = row;
                    movecol = col;
                }
            }
        }
    }


    *row = moveRow;
	*col = movecol;

    return 0;
    }
}