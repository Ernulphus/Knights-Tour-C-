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

//Determine the moves for the knight
void move(int posx, int posy, int &counter, bool &done, int n, int &knight)
{
  usleep(5000);

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

    print_board(board, counter, n);

    //check if the board is complete

    if (knight == n*n)
    {
      done = true;
      return;
    }
    if (done) {return;}

    //Prepare next jump
    move(posx-1, posy-2, counter, done, n, knight);
    move(posx+1, posy-2, counter, done, n, knight);
    move(posx+2, posy-1, counter, done, n, knight);
    move(posx+2, posy+1, counter, done, n, knight);
    move(posx+1, posy+2, counter, done, n, knight);
    move(posx-1, posy+2, counter, done, n, knight);
    move(posx-2, posy-1, counter, done, n, knight);
    move(posx-2, posy+1, counter, done, n, knight);
    if (done){return;}
    counter--;
    knight--;
    board[posx][posy] = open;
    return;
}

//Determine the moves for the knight as quick as possible, i.e. without animation
void quick_move(int posx, int posy, int &counter, bool &done, int n)
{
  //usleep(5000); No sleeping on the job!

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

    //print_board(board, counter, n); Spare me the details!

    //check if the board is complete
    if (knight == n*n)
    {
      done = true;
      return;
    }
    if (done) {return;}

    //Prepare next jump
    quick_move(posx-1, posy-2, counter, done, n);
    quick_move(posx+1, posy-2, counter, done, n);
    quick_move(posx+2, posy-1, counter, done, n);
    quick_move(posx+2, posy+1, counter, done, n);
    quick_move(posx+1, posy+2, counter, done, n);
    quick_move(posx-1, posy+2, counter, done, n);
    quick_move(posx-2, posy-1, counter, done, n);
    quick_move(posx-2, posy+1, counter, done, n);
    if (done){return;}
    counter--;
    knight--;
    board[posx][posy] = open;
    return;
}

//Cycle through each starting point and show the step-by-step solution for each.
void tv_mode()
{
  while(true){
    for (int i = 0; i < 5; i++)
    {
      for (int j = 0; j < 5; j++)
      {
        int knight = 0;
        int counter = 0;
        int size=5;
        bool done = false;

        load_board(board, size);
        print_board(board, counter, size);
        std::cout << "Current starting square: " << j << "," << i << std::endl;
        int startx = i;
        int starty = j;
        move(startx+2,starty+2,counter, done, size, knight);
        if (done)
        {
          print_board(board, counter, size);
          std::cout << "Finished!!" << std::endl;
        }
        if (counter == 0)
        {
          std::cout << "Can't Beat" << std::endl;
        }
        usleep(10000);
      }
    }
  }
}

int main()
{
  int counter = 0;
  int size=5;
  bool done = false;

  //Load the board
  do{
  std::cout << "\n\n\n\n\n\n\nGenerating the empty board of size NxN. Enter N." << std::endl;
  std::cin >> size;
}while((size < 5 || size > 8) && size > 0);
  if(size < 1)
  {
    std::cout << "\n\n\n\n\nSecret tv mode activated. Hit ctrl+c to exit." << std::endl;
    std::cout << "In this mode you can watch the computer try every possible move for each starting position.\nIt'll take a while." << std::endl;
    tv_mode();
  }
  else{
  load_board(board, size);
  print_board(board, counter, size);

  //Place the knight at the first square
  int startx = 0;
  int starty = 0;
  do{
  std::cout << "\n\n\n\n\n\n\nEnter starting x position for the knight - top left corner is 0,0" << std::endl;
  std::cin >> starty;
  std::cout << "Enter starting y position for the knight." << std::endl;
  std::cin >> startx;}
  while (startx > size || startx < 0 || starty > size || starty < 0);

  //Get the solution
  quick_move(startx+2,starty+2,counter, done, size);
  if (done)
  {
    print_board(board, counter, size);
    std::cout << "Finished!\n\n\n\n" << std::endl;
  }
  if (counter == 0)
  {
    std::cout << "Cannot complete (Hint: on a 5x5 board, not all squares are possible.)\n\n\n\n" << std::endl;
  }
  }
  return 0;
}
