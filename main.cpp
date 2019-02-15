#include<iostream>
#include<stdlib.h>
#include<unistd.h>

int board[12][12];
int open = 0;
int closed = -1;
int knight = 0;

//Initialize the empty board
void load_board(int board[12][12], int n)
{
  for(int i=0; i < n+4; ++i)
  {
    for(int j=0; j < n+4; ++j)
    {
      if ((i < 2 || j < 2))
      {
        board[i][j] = closed;
      }
      else if (i > n+1 || j > n+1)
      {
        board[i][j] = closed;
      }
      else
      {
        board[i][j] = open;
      }
    }
  }
}

//Print the board state to the terminal
void print_board(int board[12][12],int &counter, int n){
  std::cout << "[0;0H\n";
  for(int i=2; i < n+2; ++i)
  {
    for(int j=2; j < n+2; ++j)
    {
      if (board[i][j] < 10 && board[i][j] > -1)
        std::cout << ' ' << board[i][j] << ' ';
      else
        std::cout << board[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << "Move " << counter << std::endl;
}

//
void move(int posx, int posy, int &counter, bool &done, int n)
{
  //usleep(1000);

  //If the board is completed (determined in the last move), return
  if (done)
  {
    return;
  }

  //Check that the space we're trying to move to is empty. If not, return.
  int current = board[posx][posy];
  if (current != 0)
  {
    return;
  }


    //Nothing wrong with the move, the knight jumps
    knight++;
    counter++;
    board[posx][posy] = knight;

    //print_board(board, counter);

    //check if the board is complete

    if (knight == n*n)
    {
      done = true;
      return;
    }
    if (done) {return;}
    /*
    done = true;
    for(int i=2; i < 10; ++i)
    {
      for(int j=2; j < 10; ++j)
      {
        if (board[i][j] == 0)
        {
          done = false;
        }
      }
    }
    */

    //Prepare next jump
    move(posx-1, posy-2, counter, done, n);
    move(posx+1, posy-2, counter, done, n);
    move(posx+2, posy-1, counter, done, n);
    move(posx+2, posy+1, counter, done, n);
    move(posx+1, posy+2, counter, done, n);
    move(posx-1, posy+2, counter, done, n);
    move(posx-2, posy-1, counter, done, n);
    move(posx-2, posy+1, counter, done, n);
    if (done){return;}
    counter--;
    knight--;
    board[posx][posy] = open;
    //std::cout << "X";
    return;
}

int main()
{
  int counter = 0;
  int size=5;
  bool done = false;

  //Load the board
  load_board(board, size);
  print_board(board, counter, size);

  //Place the knight at the first square
  int startx = 0;
  int starty = 0;
  do{
  std::cout << "\nEnter starting x position for the knight - top left corner is 0,0" << std::endl;
  std::cin >> starty;
  std::cout << "Enter starting y position for the knight." << std::endl;
  std::cin >> startx;}
  while (startx > size || startx < 0 || starty > size || starty < 0);

  //Get the solution
  move(startx+2,starty+2,counter, done, size);
  if (done)
  {
    print_board(board, counter, size);
    std::cout << "Finished!\n\n\n\n" << std::endl;
  }
  if (counter == 0)
  {
    std::cout << "Cannot complete (Hint: on a 5x5 board, not all squares are possible.)\n\n\n\n" << std::endl;
  }
  return 0;
}

/*
~~~~~~~~~~~~~~~~~~~~~~



~~~~~~~~~~~~~~~~~~~~~~~

I'm doing this in class, here are my notes (unrelated)
(*sp).b is sp->b is st.b
the arrow thing says to dereference the first thing and go to what it points to (star dot is arrow)

Java does its own memory garbage collection,
which is nice sometimes but also makes it slower unpredictably.
You can't use garbage collection on a system that needs to be in real time.

malloc, calloc (memory allocate and malloc w/ count)









char board[12][12];
char knight = 'K';
char open = 'O';
char closed = '#';
char visited = '-';

//Initialize the empty board
void load_board(char board[12][12])
{
  for(int i=0; i < 12; ++i)
  {
    for(int j=0; j < 12; ++j)
    {
      if ((i < 2 || j < 2))
      {
        board[i][j] = closed;
      }
      else if (i > 9 || j > 9)
      {
        board[i][j] = closed;
      }
      else
      {
        board[i][j] = open;
      }
    }
  }
}

//Print the board state to the terminal
void print_board(char board[12][12],int &counter){
  std::cout << "[0;0H\n";
  for(int i=0; i < 12; ++i)
  {
    for(int j=0; j < 12; ++j)
    {
      std::cout << board[i][j] << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << counter << std::endl;
}

//
void move(int posx, int posy, int &counter,bool &done)
{
  usleep(100000);
  char current = board[posx][posy];
  if (current == closed  || current == visited)
  {
    return;
  }

    //Nothing wrong with the move, the knight jumps
    board[posx][posy] = knight;
    counter++;
    print_board(board, counter);
    //Prepare next jump
    board[posx][posy] = visited;
    move(posx-1, posy-2, counter, done);
    move(posx+1, posy-2, counter, done);
    move(posx+2, posy-1, counter, done);
    move(posx+2, posy+1, counter, done);
    move(posx+1, posy+2, counter, done);
    move(posx-1, posy+2, counter, done);
    move(posx-2, posy+1, counter, done);
    move(posx-2, posy+1, counter, done);
    counter--;
    board[posx][posy] = open;
    //std::cout << "X";
    return;


    if (counter == 64)
    {
      return;
    }

    done = true;
    for(int i=2; i < 10; ++i)
    {
      for(int j=2; j < 10; ++j)
      {
        if (board[i][j] == open)
        {
          done = false;
        }
      }
    }


    if (done)
    {
      return;
    }

    for(int i=2; i < 10; ++i)
    {
      for(int j=2; j < 10; ++j)
      {
        if (
      (board[i+2][j+1] == closed || board[i+2][j+1] == visited) &&
      (board[i+2][j-1] == closed || board[i+2][j-1] == visited) &&
      (board[i-2][j+1] == closed || board[i-2][j+1] == visited) &&
      (board[i-2][j-1] == closed || board[i-2][j-1] == visited) &&
      (board[i+1][j+2] == closed || board[i+1][j+2] == visited) &&
      (board[i+1][j-2] == closed || board[i+1][j-2] == visited) &&
      (board[i-1][j+2] == closed || board[i-1][j+2] == visited) &&
      (board[i-1][j-2] == closed || board[i-1][j-2] == visited)
      )
      {
        return;
      }
      }
    }

    if (
  (board[posx+2][posy+1] == closed || board[posx+2][posy+1] == visited) &&
  (board[posx+2][posy-1] == closed || board[posx+2][posy-1] == visited) &&
  (board[posx-2][posy+1] == closed || board[posx-2][posy+1] == visited) &&
  (board[posx-2][posy-1] == closed || board[posx-2][posy-1] == visited) &&
  (board[posx+1][posy+2] == closed || board[posx+1][posy+2] == visited) &&
  (board[posx+1][posy-2] == closed || board[posx+1][posy-2] == visited) &&
  (board[posx-1][posy+2] == closed || board[posx-1][posy+2] == visited) &&
  (board[posx-1][posy-2] == closed || board[posx-1][posy-2] == visited)
  )
  {
    done = true;
    return;
  }
  */
/*
int main()
{
  int counter = 0;
  bool done = false;
  load_board(board);
  print_board(board, counter);
  move(2,6,counter, done);
  std::cout << "Finished!" << std::endl;
*/
