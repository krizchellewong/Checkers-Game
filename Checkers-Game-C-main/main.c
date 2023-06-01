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

int
PieceCheck (int moveX, int moveY, int origX, int origY, int Pieces[][2], int *index)
{
    int row;
    
    for (row = 0; row < 5; row++)
        if (Pieces[row][0] == origX - 1 && Pieces[row][1] == origY - 1)
        {
            *index = row; 
            return 1;
        }
    return 0;
}

int 
checkValidMove(int moveX, int moveY, 
               int origX, int origY,
               int Coordinates[][2],
               int aTurn, int *index)
{
    
    if (aTurn == 1 && moveX == origX - 1 && 
        (moveY == origY || moveY == origY-1 || moveY == origY+1))
    {
        printf("It's Alpha's move!\n");
        //check if in Coordinate
        if (PieceCheck(moveX, moveY, origX, origY, Coordinates, index))
        {
            printf("Checking the piece!\n");
            if (origX % 2 == origY % 2)
            {
                printf("Valid\n");
                return 1;
            }
            else
            {
                printf("Invalid!\n");
                return 0;
            }
        }
        else
            printf("Invalid piece selected!\n");
    }

    else if (aTurn == 0 && moveX == origX + 1 && 
             (moveY == origY || moveY == origY-1 || moveY == origY+1))
    {
        printf("It's Beta's move!");
        //check if in Coordinate
        if (PieceCheck(moveX, moveY, origX, origY, Coordinates, index))
        {
            printf("Checking the piece2!\n");
            if (origX % 2 == origY % 2)
            {
                printf("Valid2\n");
                return 1;
            }
            else
            {
                printf("Invalid2!\n");
                return 0;
            }
        }

        else
            printf("hi fail\n");
    }
    else
        return 0;
}

void
makeMove (char Board [][COL], int aTurn, int Coordinates[][2])
{
    int origX, origY, moveX, moveY, row;
    
    do 
    {
        printf("Choose the piece you want to move:");
        scanf("%d %d", &origX, &origY);

        printf("origX: %d origY: %d\n", origX, origY);

        printf ("Where do you want to move it: ");
        scanf ("%d %d", &moveX, &moveY);


    } while (checkValidMove(moveX, moveY, origX, origY, Coordinates, aTurn, &row) == 0);


    // Move the piece into the new location on the board
    if (aTurn)
        Board[moveX-1][moveY -1] = 'O';
    else if (!aTurn)
        Board[moveX-1][moveY -1] = 'X';
    Board[origX-1][origY-1] = ' ';
    
    // Checks if the user selected a valid piece to move
    if (PieceCheck(moveX, moveY, origX, origY, Coordinates, &row))
    {
        // Update the coordinate of the piece to the new location
        Coordinates[row][0] = moveX;
        Coordinates[row][1] = moveY;
    }
        
}

// void
// checkBoard (char Board[][COL], int *over)
// {
    
// }

int main()
{
    int over = 0,
        ok = 0,
        aTurn = 1;

    
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

    // Start the game, and keep going until over is True (1)
    do
    {
        displayBoard(Board);
        if (aTurn)
        {
            makeMove(Board, aTurn, Alpha);
            aTurn = 0;
        }
        else if (!aTurn)
        {
            makeMove(Board, aTurn, Beta);
            aTurn = 1;
        }
        
        printf("Next turn!\n");
    } while (over == 0);
    
    // print who is the winner (Player 1 or Player 2)
    return 0;
}
