#include <stdio.h>

#define ROW 7
#define COL 5

/* 
    This function displays the instructions before the 
    game begins
*/
void
displayInstructions()
{
    printf("\n                   CHECKERS MECHANICS\n");
    printf("-------------------------------------------------------\n");
    printf("MAKING A MOVE\n\n");
    printf("Players Alpha (O) and Beta (X) will take turns in\n");
    printf("moving one of their pieces. When it is a player's\n");
    printf("turn to make a move, they will first have to input\n");
    printf("the (y,x) coordinates of the piece they want to move.\n\n");
    printf("They will then input the (y,x) coordinates they wish\n");
    printf("to move the piece to.\n");
    printf("-------------------------------------------------------\n");
    printf("VALID MOVES\n\n");
    printf("Pieces are only allowed to move one square at a time.\n");
    printf("They can move vertically or diagonally forward, but\n");
    printf("NOT backward or to the side.\n\n");
    printf("Should an opponent's piece be in the square where\n");
    printf("the player wishes to move to, the opponent's piece\n");
    printf("will be eaten if the new square is DIAGONAL to the\n");
    printf("origin square. Otherwise, the move is invalid\n\n");
    printf("A player MAY NOT eat their own piece.\n");
    printf("-------------------------------------------------------\n");
    printf("HOW TO WIN\n\n");
    printf("A player must either eat all of their opponent's\n");
    printf("pieces OR have all their current pieces make it to the\n");
    printf("other side of the board, positioned in the original\n");
    printf("coordinates their opponent started with.\n\n");
    printf("In case of a tie wherein there are no possible moves\n");
    printf("left, the program will have to be manually terminated.\n");
    printf("-------------------------------------------------------\n");
    printf("\n                 YOU MAY NOW BEGIN PLAYING\n");


}
/*
    This function displays the board with 
    an updated placement of moving Alpha and Beta pieces.

    @param Board[][COL] is the board where the pieces are located.
    @param Alpha[][2] contains updated pieces of Alpha (denoted by 'O');
    @param Beta[][2] contains updated pieces of Beta (denoted by 'X');
*/
void
displayBoard(char Board[][COL], int Alpha[][2], int Beta[][2])
{
    /*
    VISUALIZATION OF BOARD
      1   2   3   4   5
    +---+---+---+---+---+
  1 | X |   | X |   | X | O - Alpha
    +---+---+---+---+---+
  2 |   | X |   | X |   | X = Beta
    +---+---+---+---+---+
  3 |   |   |   |   |   |
    +---+---+---+---+---+
  4 |   |   |   |   |   | Available Pieces:
    +---+---+---+---+---+
  5 |   |   |   |   |   | Alpha - 
    +---+---+---+---+---+
  6 |   | O |   | O |   | Beta  - 
    +---+---+---+---+---+
  7 | O |   | O |   | O |
    +---+---+---+---+---+
    */
    int row, col, i;
    
    // Print 7 rows
    printf ("\n\n    1   2   3   4   5\n");
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
        /* Display legend and available pieces for Alpha and Beta  */
        if (row == 0)
        {
            printf("|\tO = Alpha");
        }
        else if (row == 1)
        {
            printf("|\tX = Beta");
        }
        else if (row == 3)
        {
            printf("|\tAvailable Pieces:");
        }
        else if (row == 4)
        {
            printf("|\tAlpha -");
            for (i = 0; i < COL; i++)
            {
                if (Alpha[i][0] != -1 && Alpha[i][1] != -1)
                    printf(" (%d,%d) ", Alpha[i][0]+1, Alpha[i][1]+1);
            }
        }
        else if (row == 5)
        {
            printf("|\tBeta  -");
            for (i = 0; i < COL; i++)
            {
                if (Beta[i][0] != -1 && Beta[i][1] != -1)
                printf(" (%d,%d) ", Beta[i][0]+1, Beta[i][1]+1);
            }
        }
        else
        {
            printf("|");
        }
        printf ("\n"); 
    }
    printf ("  +---+---+---+---+---+\n\n");
}

/*
    This functions checks if the piece selected by the player is valid.

    @param origRow is the user's row input for the position of the piece he wishes to move.
    @param origCol is the user's column input for the position of the piece he wishes to move.
    @param Pieces[][2] is either Alpha or Beta pieces.
    @param *pieceNum is the POSITION of the piece that we're updating
    
    return 1 if the piece selected is found
           0 if the piece selected is invalid
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

/*
    This function checks if the piece can be eaten or not. 

    @param *ok is a state variable that indicates if the program can proceed to next turn
    @param aTurn determines if it is Alpha or Beta's turn
    @param nextRow is the users' row input for the position of the piece he wants to move it to
    @param nextCol the users' column input for the position of the piece he wants to move it to
    @param Board[][COL] is the board where the pieces are located

    return 1 if piece can be eaten
           0 if piece cannot be eaten
*/

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

/*
    This functions checks if the player's move is valid.

    @param nextRow is the users' row input for the position of the piece he wants to move it to
    @param nextCol the users' column input for the position of the piece he wants to move it to
    @param origRow is the user's row input for the position of the piece he wishes to move.
    @param origCol is the user's column input for the position of the piece he wishes to move.
    @param aTurn determines if it is Alpha or Beta's turn
    @param *ok is a state variable that indicates if the program can proceed to next turn
    @param Board[][COL] is the board where the pieces are located

    return 1 if it is a valid move for Alpha/Beta
    return 2 if piece can be eaten
    return 0 if it is an invalid move (piece cannot be eaten or movement is done backwards)
*/

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
                printf("Invalid move!\n");
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
                printf("Invalid move!\n");
                return 0; 
            }
        }
    }

    printf("Invalid move!\n");
    return 0;
}

/*
    This function moves the piece into a new location on the board.

    @param aTurn determines if it is Alpha or Beta's turn
    @param nextRow is the users' row input for the position of the piece he wants to move it to
    @param nextCol the users' column input for the position of the piece he wants to move it to
    @param origRow is the user's row input for the position of the piece he wishes to move.
    @param origCol is the user's column input for the position of the piece he wishes to move.
    @param Pieces[][2] is either Alpha or Beta pieces.
    @param Board[][COL] is the board where the pieces are located
    @param pieceNum is the POSITION of the piece that we're updating

    

*/
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

/*
    The function checks for the piece to be eaten and updates the value of the eaten piece to (-1,-1).
    (-1, -1) is used to indicate that that piece of Alpha/Beta has already been eaten. 

    @param aTurn determines if it is Alpha or Beta's turn
    @param nextRow is the users' row input for the position of the piece he wants to move it to
    @param nextCol the users' column input for the position of the piece he wants to move it to
    @param Eaten[][2] is either Alpha or Beta's board, depending on which piece is being eaten.
    @param *nElem updates the number of pieces left for Alpha or Beta
*/

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

/*
    The function asks for user input to move Alpa/Beta pieces to the specified user coordinates.
    
    @param Board[][COL] is the board where the pieces are located
    @param aTurn determines if it is Alpha or Beta's turn
    @param Pieces[][2] is either Alpha or Beta pieces.
    @param *ok is a state variable that indicates if the program can proceed to next turn
    @param *nextRow is the users' row input for the position of the piece he wants to move it to
    @param *nextCol the users' column input for the position of the piece he wants to move it to
    @param *origRow is the user's row input for the position of the piece he wishes to move.
    @param *origCol is the user's column input for the position of the piece he wishes to move.
    @param *pieceNum is the POSITION of the piece that we're updating

    return checkMoveVal: 
            1 if it is a valid move for Alpha/Beta
            2 if piece can be eaten
            0 if it is an invalid move (piece cannot be eaten or movement is done backwards)
*/

int
makeMove(char Board[][COL], int aTurn, 
        int Pieces[][2], int *ok, 
        int *nextRow, int *nextCol, 
        int *origRow, int *origCol, 
        int *pieceNum)
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


/* 
    This function checks if Alpha or Beta can be declared as a winner and signal the end of the game.

    @param aTurn determines if it is Alpha or Beta's turn
    @param nElemA is the number of pieces left for Alpha
    @param nElemB is the number of pieces left for Beta
    @param E[][2] is an array containing the coordinates of Alpha's pieces before the game started.
    @param Y[][2] is an array containing the coordinates of Beta's pieces before the game started.
    @param Alpha[][2] is an array containing the updated coordinates of Alpha's pieces after each move.
    @param Beta[][2] is an array containing the updated coordinates of Beta's pieces after each move.

    return 1 if Alpha or Beta wins
           0 if Alpha nor Beta has won

*/
int
checkWin(int aTurn, int nElemA, 
        int nElemB, int E[][2], 
        int Y[][2], int Alpha[][2], 
        int Beta[][2])
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

int 
main()
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
    int row, col;
    int nElemAlpha = 5;
    int nElemBeta = 5;
    
    char Board[7][5] = {{'X', ' ', 'X', ' ', 'X'}, 
                        {' ', 'X', ' ', 'X', ' '}, 
                        {' ', ' ', ' ', ' ', ' '}, 
                        {' ', ' ', ' ', ' ', ' '}, 
                        {' ', ' ', ' ', ' ', ' '},  
                        {' ', 'O', ' ', 'O', ' '}, 
                        {'O', ' ', 'O', ' ', 'O'}};

    // Arrays for Alpha and Beta's coordinates that will be updated throughout the game

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
    
    // Arrays for Alpha and Beta's original coordinates before the game has started.

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

    displayInstructions();
    // Start the game, and keep going until over is True (1)
    do
    {
        
        displayBoard(Board, Alpha, Beta);
        if (aTurn)
        {
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

    // display board after win
    printf ("\nFinal board display\n");
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
        /* Display legend and available pieces for Alpha and Beta  */
        if (row == 0)
        {
            printf("|\tO = Alpha");
        }
        else if (row == 1)
        {
            printf("|\tX = Beta");
        }
        else
        {
            printf("|");
        }
        printf ("\n"); 
    }
    printf ("  +---+---+---+---+---+\n");

    
    return 0;
}
