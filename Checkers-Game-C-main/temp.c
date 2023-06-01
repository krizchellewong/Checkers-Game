#include <stdio.h>

#define ROW 7
#define COL 5


/* Display the board and the location of the pieces
   
    @param Board - 2D array of the board indicating which cells have pieces and which are empty 
 */

void displayBoard(char Board[][COL])
{
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

/* Checks if the piece exists in the given coordinate on the board 
    @param origX - user-given x-coordinate of the piece
    @param origY - user-given y-coordinate of the piece
    @param Pieces - either Alpha or Beta array that shows all 
                    coordinates
    @param nElem - number of pieces available in the set

    @return if coordinate exists in set, return 1, if not, return 0

*/

int checkPiece(int origX, int origY, int Pieces[][2], int nElem)
{
    int row;

    for (row = 0; row < nElem; row++)
    {   
        // subtract 1 since the array index starts from 0 while  coordinates start from 1
        if (Pieces[row][0] == origY - 1 && Pieces[row][1] == origX - 1)
        {
            return 1;
        }
    }

    return 0;
}

/* Check if the next move will eat a piece */
int checkEat()
{

}

/* Check if the next move is valid */
int checkMove()
{

}

/* move piece to new coordinate */
void movePiece()
{

}

/* eat the piece and move player's piece to that location */
void eatPiece()
{

}

/* Change the set of coordinates for all of Alpha or Beta's pieces */
int changeSet()
{

}

/* Update how many pieces Alpha or Beta has */

int updatePiece()
{

}

/* Check if either Alpha or Beta has won yet */
int checkWin()
{

}

/* Gets the coordinates of the piece and where to move it 


*/
int makeMove()
{
    int origX, origY, moveX, moveY;
    do 
    {
        printf("Choose the piece you want to move (y, x):");
        scanf("%d %d", &origY, &origX);

    } while (checkPiece(origX, origY, Coordinates, aTurn, &row) == 0);

    do
    {
        printf ("Where do you want to move it (y, x): ");
        scanf ("%d %d", &moveY, &moveX);
    } while (checkMove())

    if (checkEat())
    {

    }

}




int main()
{
    // System initialization
    int over = 0;
    int ok = 0;
    int aTurn = 1;

    // Coordinates with pieces {row, column}
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

    // Initial board display
    char Board[7][5] = {{'X', ' ', 'X', ' ', 'X'}, // beta pieces
                    {' ', 'X', ' ', 'X', ' '}, // beta pieces
                    {' ', ' ', ' ', ' ', ' '}, 
                    {' ', ' ', ' ', ' ', ' '}, 
                    {' ', ' ', ' ', ' ', ' '},  
                    {' ', 'O', ' ', 'O', ' '}, //alpha pieces
                    {'O', ' ', 'O', ' ', 'O'}}; // alpha pieces


    // Start and continue game until over == 1, signaling game over
    do
    {
        // For every move, display the board 
        displayBoard(Board);

        // Alpha's turn
        if (aTurn)
        {
            // make the move
            NextPlayerMove(Board, aTurn, Alpha);


            // Switch to Beta's turn
            aTurn = 0;
        }

        // Beta's turn
        else if (!aTurn)
        {
            makeMove(Board, aTurn, Beta);
            aTurn = 1;
        }
        
        printf("Next turn!\n");

    } while (over == 0);

    return 0;

}
