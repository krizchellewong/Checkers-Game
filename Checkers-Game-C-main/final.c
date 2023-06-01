#include <stdio.h>

#define ROW 7
#define COL 5

void
displayBoard(char Board[][COL])
{
    /*
    VISUALIZATION OF BOARD
      1   2   3   4   5
    +---+---+---+---+---+
  1 | X |   | X |   | X |
    +---+---+---+---+---+
  2 |   | X |   | X |   |
    +---+---+---+---+---+
  3 |   |   |   |   |   |
    +---+---+---+---+---+
  4 |   |   |   |   |   |
    +---+---+---+---+---+
  5 |   |   |   |   |   |
    +---+---+---+---+---+
  6 |   | O |   | O |   |
    +---+---+---+---+---+
  7 | O |   | O |   | O |
    +---+---+---+---+---+
    */
    int row, col;
    
    // Print 7 rows
    printf ("    1   2   3   4   5\n");
    for (row = 0; row < ROW; row++)
    {
        printf ("  +---+---+---+---+---+\n");   
        // After each row, print 5 columns
        for (col = 0; col < COL; col++)
        {
            if (col == 0)
                printf ("%d | %c ", row + 1, Board[row][col]);
            else
                printf ("| %c ", Board[row][col]);
        }
        printf ("|\n"); 
    }
    printf ("  +---+---+---+---+---+\n");
}

/*
    @param Pieces[][2] is either Alpha or Beta
    @param *index is the POSITION of the piece that we're updating
*/
int
PieceCheck (int origRow, int origCol, int Pieces[][2], int *pieceNum)
{
    // Go through each piece in the player's array of pieces
    int i;
    for (i = 0; i < 5; i++)
    {
        if (Pieces[i][0] == origRow - 1 && Pieces[i][1] == origCol - 1)
        {
            // Stores the specific piece that will be moved
            *pieceNum = i; 
            return 1;
        }
    } 
    printf("Invalid piece selected!\n");
    return 0;
}

int
checkEat (int *ok, int aTurn, int nextRow, int nextCol, char Board[][COL])
{
    // If Alpha's turn and the next position has a Beta piece 'X' and "next" is element of S
    if (aTurn && Board[nextRow-1][nextCol-1] == 'X' && (nextRow % 2 == nextCol % 2))
    {
        *ok = !(*ok);
        return 1;
    }
    else if (!aTurn && Board[nextRow-1][nextCol-1] == 'O' && (nextRow % 2 == nextCol % 2))
    {
        *ok = !(*ok);
        return 1;
    }
    else
        return 0;
}

int 
checkMove(int nextRow, int nextCol, 
          int origRow, int origCol,
          int aTurn, int *ok, 
          char Board[][COL])
{
    // Check if the new position is valid
    // aTurn ^ a = c + 1 ^ (d = b v d = b + 1 v b = d + 1) -> Alpha's turn
    if (aTurn == 1 && nextRow == origRow - 1 && 
        (nextCol == origCol || nextCol == origCol-1 || nextCol == origCol+1))
    {
        *ok = !(*ok);
        // check if next is element of Free (i.e., space is ' ')
        if (Board[nextRow-1][nextCol-1] == ' ')
        {
            *ok = !(*ok);
            printf("Valid move for Alpha.\n");
            return 1;
        }
        else 
        {
            if (checkEat(ok, aTurn, nextRow, nextCol, Board))
            {
                printf("Piece eaten\n");
                return 2;
            }
            else
            {
                printf("Invalid move. Piece not Eaten.\n");
                return 0; 
            }
        }
    
    }

    // if Beta's turn
    // aTurn ^ c = a + 1 ^ (d = b v d = b + 1 v b = d + 1)
    else if (aTurn == 0 && nextRow == origRow + 1 && 
            (nextCol == origCol || nextCol == origCol-1 || nextCol == origCol+1))
    {
        *ok = !(*ok);
        if (Board[nextRow - 1][nextCol-1] == ' ')
        {
            *ok = !(*ok);
            printf("Valid move for Beta.\n");
            return 1;
        }
        else 
        {
            if (checkEat(ok, aTurn, nextRow, nextCol, Board))
            {
                printf("Piece eaten\n");
                return 2;
            }
            else
            {
                printf("Invalid move. Piece not Eaten.\n");
                return 0; 
            }
        }
    }

    printf("Invalid move (don't move backwards or more than one space)\n");
    return 0;
}

void
movePiece (int aTurn, int nextRow,
            int nextCol, int origRow,
            int origCol, int Pieces[][2], 
            char Board[][COL], int pieceNum)
{
    // Move the piece into the new location on the board
    if (aTurn)
        Board[nextRow-1][nextCol-1] = 'O';
    else if (!aTurn)
        Board[nextRow-1][nextCol-1] = 'X';
    Board[origRow-1][origCol-1] = ' '; // make original position empty

    // Update the coordinate of the piece to the new location (i.e., Alpha/Beta = ({Alpha/Beta - {prev}) U {next}})
    Pieces[pieceNum][0] = nextRow - 1; // row position of piece (y-axis)
    Pieces[pieceNum][1] = nextCol - 1; // col position of piece (x-axis)
}

void
eatPiece(int aTurn, int nextRow,
         int nextCol, int Eaten[][2], 
         int *nElem)
{
    int pieceNum;
    // Go through each piece in Eaten
    for (pieceNum = 0; pieceNum < COL; pieceNum++)
    {
        // Found the piece to be eaten
        if (Eaten[pieceNum][0] == nextRow - 1 && Eaten[pieceNum][1] == nextCol - 1)
        {
            Eaten[pieceNum][0] = -1;
            Eaten[pieceNum][1] = -1;
            (*nElem)--;
        }
    }
}

int
makeMove(char Board[][COL], int aTurn, int Pieces[][2], int *ok, int *nextRow, int *nextCol, int *origRow, int *origCol, int *pieceNum)
{
    int checkMoveVal;
    
    if (aTurn)
        printf("It's Alpha's move!\n");
    else
        printf("It's Beta's move!\n");

    do 
    {
        printf("Choose the piece you want to move (y, x):");
        scanf("%d %d", origRow, origCol);

        // Input validation
        if (*origRow > 7)
            printf("Row input is too high\n");
        else if (*origRow < 1)
            printf("Row input is too low\n");
            
        if (*origCol > 5)
            printf("Column input is too high\n");
        else if (*origCol < 1)
            printf("Column input is too low\n");

    } while(PieceCheck(*origRow, *origCol, Pieces, pieceNum) == 0
            || *origRow > 7 || *origRow < 1 || *origCol > 5 || *origCol < 1); 
    
    do 
    {
        printf ("Where do you want to move it (y, x): ");
        scanf ("%d %d", nextRow, nextCol);
        
        checkMoveVal = checkMove(*nextRow, *nextCol, *origRow, *origCol, aTurn, ok, Board);
        // return 0 - invalid, 1 - normal move, 2 - eat piece
    } while (checkMoveVal == 0);

    return checkMoveVal;
}


/* Check if either Alpha or Beta has won yet */
int
checkWin(int aTurn, int nElemA, int nElemB, int E[][2], int Y[][2], int Alpha[][2], int Beta[][2])
{
    // If it's Alpha's turn and Beta has no more pieces
    int i, j, nFound = 0; 
    if (aTurn == 1 && nElemB == 0)
    {
        printf ("Alpha Wins\n");
        return 1;
    }
    else if (aTurn == 1 && nElemA >= 1)
    {
        // For each piece in Alpha
        for (i = 0; i < 5; i++)
            // Check if the piece hasn't been eaten
            if (Alpha[i][0] != -1 && Alpha[i][1] != -1)
                // For each piece in Y
                for (j = 0; j < 5; j++)
                {
                    
                    // Check if the Alpha piece reached a Y coordinate
                    if (Alpha[i][0] == Y[j][0] && Alpha[i][1] == Y[j][1])
                    {
                        printf("nFound: = %d, nElemA = %d. \n", nFound, nElemA);
                        nFound++;
                    }
                }
        
        if (nFound == nElemA)
        {
            printf ("Alpha Wins\n");
            return 1;
        }
    }
    
    // If it's Beta's turn and Alpha has no more pieces
    else if (aTurn == 0 && nElemA == 0)
    {
        printf ("Beta Wins\n");
        return 1;
    }
    else if (aTurn == 0 && nElemB >= 1)
    {
        // For each piece in Beta
        for (i = 0; i < 5; i++)
            // Check if the piece hasn't been eaten
            if (Beta[i][0] != -1 && Beta[i][1] != -1)
                // For each piece in E
                for (j = 0; j < 5; j++)
                    // Check if the Beta piece reached a Y coordinate
                    if (Beta[i][0] == E[j][0] && Beta[i][1] == E[j][1])
                    {
                        printf("nFound: = %d, nElemB = %d. \n", nFound, nElemB);
                        nFound++;
                    }
        
        if (nFound == nElemB)
        {
            printf ("Beta Wins\n");
            return 1;
        }
    }
    
    return 0;
}

int main()
{
    int over = 0,
        ok = 0,
        aTurn = 1,
        moveType,
        origRow,
        origCol,
        nextRow, 
        nextCol,
        pieceNum;
    
    int nElemAlpha = 5;
    int nElemBeta = 5;
    
    char Board[7][5] = {{'X', ' ', 'X', ' ', 'X'}, 
                        {' ', 'X', ' ', 'X', ' '}, 
                        {' ', ' ', ' ', ' ', ' '}, 
                        {' ', ' ', ' ', ' ', ' '}, 
                        {' ', ' ', ' ', ' ', ' '},  
                        {' ', 'O', ' ', 'O', ' '}, 
                        {'O', ' ', 'O', ' ', 'O'}};

    int Alpha[5][2] = {{5,1}, // (6, 2)
                       {5,3}, // (6, 4)
                       {6,0}, // (7, 1)
                       {6,2}, // (7, 3)
                       {6,4}}; // (7, 5)
                       
    int Beta[5][2] = {{0,0}, // (1, 1)
                      {0,2}, // (1, 3)
                      {0,4}, // (1, 5)
                      {1,1}, // (2, 2)
                      {1,3}}; // (2, 4)

    int E[5][2] = {{5,1}, // (6, 2)
                   {5,3}, // (6, 4)
                   {6,0}, // (7, 1)
                   {6,2}, // (7, 3)
                   {6,4}}; // (7, 5)
                       
    int Y[5][2] = {{0,0}, // (1, 1)
                   {0,2}, // (1, 3)
                   {0,4}, // (1, 5)
                   {1,1}, // (2, 2)
                   {1,3}}; // (2, 4)

    // Start the game, and keep going until over is True (1)
    do
    {
        int i = 0;
        displayBoard(Board);
        if (aTurn)
        {
            printf("Current pieces of Alpha: \n");
            for (i = 0; i < COL; i++)
            {
                printf("| %d %d |\n", Alpha[i][0]+1, Alpha[i][1]+1);
            }
            printf("\n");
            moveType = makeMove(Board, aTurn, Alpha, &ok, &nextRow, &nextCol, &origRow, &origCol, &pieceNum);

            // New spot is free
            if (moveType == 1)
                movePiece(aTurn, nextRow, nextCol, origRow, origCol, Alpha, Board, pieceNum);

            // Eat the piece at new spot
            else if (moveType == 2)
            {
                movePiece(aTurn, nextRow, nextCol, origRow, origCol, Alpha, Board, pieceNum);
                eatPiece(aTurn, nextRow, nextCol, Beta, &nElemBeta);
            }
            
            over = checkWin(aTurn, nElemAlpha, nElemBeta, E, Y, Alpha, Beta);
            aTurn = 0;
        }
        else if (!aTurn)
        {
            printf("Current pieces of Beta: \n");
            for (i = 0; i < COL; i++)
            {
                printf("| %d %d |\n", Beta[i][0]+1, Beta[i][1]+1);
            }
            printf("\n");
            moveType = makeMove(Board, aTurn, Beta, &ok, &nextRow, &nextCol, &origRow, &origCol, &pieceNum);
            
            // New spot is free
            if (moveType == 1)
                movePiece(aTurn, nextRow, nextCol, origRow, origCol, Beta, Board, pieceNum);

            // Eat the piece at new spot
            else if (moveType == 2)
            {
                movePiece(aTurn, nextRow, nextCol, origRow, origCol, Beta, Board, pieceNum);
                eatPiece(aTurn, nextRow, nextCol, Alpha, &nElemAlpha);
            }
            
            over = checkWin(aTurn, nElemAlpha, nElemBeta, E, Y, Alpha, Beta);
            aTurn = 1;
        }

    } while (over == 0);
    
    displayBoard(Board);
    
    return 0;
}
