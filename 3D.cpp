#include <bits/stdc++.h>
using namespace std;
vector<int> x; // for computer
vector<int> y; // for human
vector<int> corner_edgecentre;
vector<int> surface_centre;
int x_score = 0, y_score = 0; // both scores initialized as 0
int user_move;
int N = 3;

struct axis
{
  int x, y, z;
};
axis coord;
unordered_map<int, axis> vertice;
int magic_cube[3][3][3];
string game_board[3][3][3];

/************************FUNCTION TO CHECK COLLINEARITY**************************************/

bool check_collinear(int p1, int p2, int p3)
{
  cout << endl;
  float a1, a2, a3, b1, b2, b3, c1, c2, c3;
  a1 = vertice[p1].x;
  b1 = vertice[p1].y;
  c1 = vertice[p1].z;
  a2 = vertice[p2].x;
  b2 = vertice[p2].y; // Assigned values from the unordered map to check collinearity
  c2 = vertice[p2].z;
  a3 = vertice[p3].x;
  b3 = vertice[p3].y;
  c3 = vertice[p3].z;
  if (((a3 - a1 == 0) and (a2 - a1 == 0) and (b3 - b1 == 0) and (b2 - b1 == 0)) or ((a3 - a1 == 0) and (a2 - a1 == 0) and (c3 - c1 == 0) and (c2 - c1 == 0)) or ((c3 - c1 == 0) and (c2 - c1 == 0) and (b3 - b1 == 0) and (b2 - b1 == 0)))
  {
    return true;
  }

  if ((a3 - a1 != 0) and (a2 - a1 != 0) and (b2 - b1 != 0) and (b3 - b1 != 0) and (c2 - c1 != 0) and (c3 - c1 != 0))
  {
    if ((a2 - a1) / (a3 - a1) == (b2 - b1) / (b3 - b1) && (c2 - c1) / (c3 - c1) == (b2 - b1) / (b3 - b1))
      return true;
  }
  if ((a3 - a1 == 0) && (a2 - a1 == 0))
  {
    if (((c2 - c1) / (c3 - c1)) == ((b2 - b1) / (b3 - b1)))
      return true;
  }
  if ((b3 - b1 == 0) && (b2 - b1 == 0))
  {
    if (((c2 - c1) / (c3 - c1)) == ((a2 - a1) / (a3 - a1)))
      return true;
  }
  if ((c3 - c1 == 0) && (c2 - c1 == 0))
  {
    if (((a2 - a1) / (a3 - a1)) == ((b2 - b1) / (b3 - b1)))
    {
      return true;
    }
  }

  return false;
}

/************************FUNCTION TO DISPLAY INBOARD GAME***********************************/

void ingame_board()
{
  int a = 3;
  cout << endl;
  for (int i = 0; i < N; i++)
  {
    for (int k = 0; k < N; k++)
    {
      cout << setw(a);
      for (int j = 0; j < N; j++)
      {
        cout << "  "
             << "[" << game_board[i][k][j] << "]"; // Displays the game board
      }
      cout << endl;
    }
    cout << setw(a + 8) << "layer no:" << i + 1 << endl; // Displays the layer no.

    a += 12;
    cout << endl;
    //ijk , kji , kij
  }
}

/*******************COUNT FUNCTION FOR COUNTING SCORE*************************************/

int score_count(vector<int> moves)
{

  if (moves.size() > 2) // if the player has played more than 2 moves
  {
    cout << endl
         << "score count me aaya" << endl;
    int temp_count = 0;
    for (int i = 1; i < moves.size() - 1; i++)
    {
      for (int j = 0; j < i; j++) // makes all the pairs of 3 possible in the vector
      {
        if (moves[i] + moves[j] + (moves[moves.size() - 1]) == 42) // checks sum 42
        {
          bool check = check_collinear(moves[i], moves[j], moves[moves.size() - 1]); // checks the collinearity
          if (check)
          {
            cout << endl;
            temp_count++; // increases count if conditions satisfied
          }
          else
            continue;
        }
        else
          continue;
      }
    }
    return temp_count;
  }
  return 0;
}

/********************NEXT MOVE FUNCTION FOR COMPUTER********************************/

void nextmove()
{
  int m_diff;
  if (x.size() == 0)
  {
    x.push_back(14);

    game_board[1][1][1] = 'X';
    return;
  }
  else if (x.size() == 1)
  {
    x.push_back(corner_edgecentre.back());
    int i = vertice[corner_edgecentre.back()].x;
    int j = vertice[corner_edgecentre.back()].y;
    int k = vertice[corner_edgecentre.back()].z;
    game_board[i][j][k] = 'X';
    corner_edgecentre.pop_back();
    return;
  }
  else
  {
    //for checking if x is winning a point
    for (int i = 1; i < x.size(); i++)
    {
      for (int j = 0; j < i; j++)
      {
        m_diff = (42 - (x[i] + x[j]));
        if ((m_diff < 1) || (m_diff > 27))
          ;
        else if (std::find(x.begin(), x.end(), m_diff) != x.end())
          ;
        else if (std::find(y.begin(), y.end(), m_diff) != y.end())
          ;
        else
        {
          //checking collinearity now for winning a point
          bool check = check_collinear(x[i], x[j], m_diff);
          if (check)
          {
            corner_edgecentre.erase(std::remove(corner_edgecentre.begin(), corner_edgecentre.end(), m_diff), corner_edgecentre.end());
            surface_centre.erase(std::remove(surface_centre.begin(), surface_centre.end(), m_diff), surface_centre.end());
            x.push_back(m_diff);
            int p = vertice[m_diff].x;
            int q = vertice[m_diff].y;
            int r = vertice[m_diff].z;
            game_board[p][q][r] = 'X';
            // ingame_board();
            x_score += score_count(x);
            return;
          }
        }
      }
    }
    // for blocking human
    for (int i = 1; i < y.size(); i++)
    {
      for (int j = 0; j < i; j++)
      {
        m_diff = (42 - (y[i] + y[j]));
        cout << "42-" << y[i] << "+" << y[j] << "=" << m_diff << endl;
        if ((m_diff < 1) || (m_diff > 27))
          ;
        else if (std::find(x.begin(), x.end(), m_diff) != x.end())
          ;
        else if (std::find(y.begin(), y.end(), m_diff) != y.end())
          ;
        else
        {
          //checking collinearity now if y can win a point , and block it
          bool check = check_collinear(y[i], y[j], m_diff);
          if (check)
          {
            corner_edgecentre.erase(std::remove(corner_edgecentre.begin(), corner_edgecentre.end(), m_diff), corner_edgecentre.end());
            surface_centre.erase(std::remove(surface_centre.begin(), surface_centre.end(), m_diff), surface_centre.end());
            x.push_back(m_diff);
            int p = vertice[m_diff].x;
            int q = vertice[m_diff].y;
            int r = vertice[m_diff].z;
            game_board[p][q][r] = 'X';
            // ingame_board();
            return;
          }
        }
      }
    }

    if (!corner_edgecentre.empty())
    {
      x.push_back(corner_edgecentre.back());
      int i = vertice[corner_edgecentre.back()].x;
      int j = vertice[corner_edgecentre.back()].y;
      int k = vertice[corner_edgecentre.back()].z;
      game_board[i][j][k] = 'X';
      corner_edgecentre.pop_back();
    }
    else if (!surface_centre.empty())
    {
      x.push_back(surface_centre.back());
      int i = vertice[surface_centre.back()].x;
      int j = vertice[surface_centre.back()].y;
      int k = vertice[surface_centre.back()].z;
      game_board[i][j][k] = 'X';
      surface_centre.pop_back();
    }
  }
  return;
}

/****************************WRAPPING FUNCTION*************************************************/

void arrange(int &a, int &b, int &c)
{
  int N = 3;
  if (a == -1)
    a = N - 1; // if any of the coordinates go out of bound
  if (b == -1) // perform wrapping
    b = N - 1;
  if (c == -1)
    c = N - 1;
  /*if(c==-2)
      c=1;*/
  if (c == N)
    c = 0;
  if (a == N)
    a = 0;
  if (b == N)
    b = 0;
}

/************************************CREATE MAGIC CUBE************************/

void create_magic_cube()
{
  int first_position = 0;
  if (first_position == 1)
  {
    // n-1 , n/2 , n/2
    int a, b, c;
    a = N / 2; // starting point
    b = N / 2;
    c = 0;
    //  int chance = rand() % 4;
    int mc = (N * ((N * N * N) + 1)) / 2;
    //cout << mc;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        for (int k = 0; k < N; k++)
        {
          magic_cube[i][j][k] = 0; // initialize the magic cube.
        }
      }
    }
    magic_cube[a][b][c] = 1;
    for (int num = 2; num <= N * N * N;)
    {

      a--; //Rule1 to find empty grid
      c--;
      arrange(a, b, c);
      if (magic_cube[a][b][c] == 0)
      {
        magic_cube[a][b][c] = num; // if empty grid found then print the element in that grid
        coord.x = a;
        coord.y = b;
        coord.z = c;
        vertice[num] = coord;

        num++;
        continue;
      }
      else
      {
        a++; // if not found empty then revert to original values
        c++;
        arrange(a, b, c);
      }
      a--;
      b--; // Rule2 to find empty grid
      c++;
      arrange(a, b, c);

      if (magic_cube[a][b][c] == 0)
      {
        magic_cube[a][b][c] = num; // if grid found empty print the element.
        coord.x = a;
        coord.y = b;
        coord.z = c;
        vertice[num] = coord;

        num++;
        continue;
      }
      else
      {
        a++;
        b++; // revert to original values
        c--;
        arrange(a, b, c);
      }
      c += 1; // regulate the value of c
      arrange(a, b, c);
      // if (magic_cube[a][b][c] == 0)

      magic_cube[a][b][c] = num;
      coord.x = a; // if grid empty then print the element
      coord.y = b;
      coord.z = c;
      vertice[num] = coord;

      num++;
    }
  }
  else
  {

    int a, b, c;
    a = 0; // starting point
    b = 0;
    c = 0;
    //  int chance = rand() % 4;
    int mc = (N * ((N * N * N) + 1)) / 2;
    //cout << mc;
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        for (int k = 0; k < N; k++)
        {
          magic_cube[i][j][k] = 0; // initialize the magic cube.
        }
      }
    }
    magic_cube[a][b][c] = 1;
    for (int num = 2; num <= N * N * N;)
    {

      a--; //Rule1 to find empty grid
      c--;
      arrange(a, b, c);
      if (magic_cube[a][b][c] == 0)
      {
        magic_cube[a][b][c] = num; // if empty grid found then print the element in that grid
        coord.x = a;
        coord.y = b;
        coord.z = c;
        vertice[num] = coord;

        num++;
        continue;
      }
      else
      {
        a++; // if not found empty then revert to original values
        c++;
        arrange(a, b, c);
      }
      a++;
      b--; // Rule2 to find empty grid
      c--;
      arrange(a, b, c);

      if (magic_cube[a][b][c] == 0)
      {
        magic_cube[a][b][c] = num; // if grid found empty print the element.
        coord.x = a;
        coord.y = b;
        coord.z = c;
        vertice[num] = coord;

        num++;
        continue;
      }
      else
      {
        a--;
        b++; // revert to original values
        c++;
        arrange(a, b, c);
      }
      a++;
      b++;
      c++; // regulate the value of c
      arrange(a, b, c);
      // if (magic_cube[a][b][c] == 0)

      magic_cube[a][b][c] = num;
      coord.x = a; // if grid empty then print the element
      coord.y = b;
      coord.z = c;
      vertice[num] = coord;
      num++;
    }

  } //KIJ FOR FIRST TWO N/2 i,j
  // ijk :: kij
  //PRINTING
  int a = 3;

  cout << "This is the magic cube:" << endl
       << endl;
  for (int i = 0; i < N; i++)
  {
    for (int k = 0; k < N; k++)
    {
      cout << setw(a);
      for (int j = 0; j < N; j++)
      {
        cout << "  "
             << "[" << magic_cube[i][k][j] << "]"; // Displays the magic cube
      }
      cout << endl;
    }
    cout << setw(a + 8) << "layer no:" << i + 1 << endl; // Displays the layer no.

    a += 12;
    cout << endl;
  }
  //ijk , kji , kij
}

/*******************FUNCTION TO CHECK WHEN THE GAME ENDS*************************************************/
bool game_end()
{
  if (x_score >= 10)
  {
    cout << "Computer Wins" << endl; // computer makes 10 collinear lines first
    return true;
  }
  if (y_score >= 10)
  {
    cout << "Human Wins" << endl; // human makes 10 collinear lines first
    return true;
  }
  if (x.size() == 14 && (x_score < 10) && (y_score < 10)) // if all the grids are filled
  {
    if (x_score > y_score)
    {
      cout << "Computer Wins" << endl; // computer scores more than human
      return true;
    }
    else if (y_score > x_score)
    {
      cout << "Human Wins" << endl; // human scores more than computer.
      return true;
    }
    else
    {
      cout << "Draw" << endl; // human scores more than computer.
      return true;
    }
  }
  return false;
}

/************************FUNCTION TO PRINT VECTOR ELEMENTS******************/

void printVector(std::vector<int> const &a)
{
  cout << endl;
  for (int i = 0; i < a.size(); i++)
  {
    if (i == a.size() - 1)
    {
      std::cout << a.at(i); // prints all the elements in a vector
      cout << endl;
    }
    else
      std::cout << a.at(i) << "->"; // prints all the elements in a vector
  }
}

/*************************  ASSIGNMENT FUNCTION ****************/
void assignment()
{
  corner_edgecentre.push_back(magic_cube[0][0][0]);
  corner_edgecentre.push_back(magic_cube[0][0][2]);
  corner_edgecentre.push_back(magic_cube[0][2][0]);
  corner_edgecentre.push_back(magic_cube[0][2][2]);
  corner_edgecentre.push_back(magic_cube[2][0][0]);
  corner_edgecentre.push_back(magic_cube[2][0][2]);
  corner_edgecentre.push_back(magic_cube[2][2][0]);
  corner_edgecentre.push_back(magic_cube[2][2][2]);

  corner_edgecentre.push_back(magic_cube[0][0][1]);
  corner_edgecentre.push_back(magic_cube[0][1][0]);
  corner_edgecentre.push_back(magic_cube[0][1][2]);
  corner_edgecentre.push_back(magic_cube[0][2][1]);

  corner_edgecentre.push_back(magic_cube[1][0][0]);
  corner_edgecentre.push_back(magic_cube[1][0][2]);
  corner_edgecentre.push_back(magic_cube[1][2][0]);
  corner_edgecentre.push_back(magic_cube[1][2][2]);

  corner_edgecentre.push_back(magic_cube[2][0][1]);
  corner_edgecentre.push_back(magic_cube[2][1][0]);
  corner_edgecentre.push_back(magic_cube[2][1][2]);
  corner_edgecentre.push_back(magic_cube[2][2][1]);

  surface_centre.push_back(magic_cube[0][1][1]);
  surface_centre.push_back(magic_cube[2][1][1]);
  surface_centre.push_back(magic_cube[1][0][1]);
  surface_centre.push_back(magic_cube[1][1][0]);
  surface_centre.push_back(magic_cube[1][1][2]);
  surface_centre.push_back(magic_cube[1][2][1]);
}

/*********************************MAIN FUNCTION***********************************/
int main()
{ // srand((unsigned)time(NULL));
  // int chance_1 = rand() % 4;
  // chance = chance_1;
  int flag = 0;
  create_magic_cube();
  assignment();

  // printVector(surface_centre);
  // printVector(corner_edgecentre);
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (int k = 0; k < 3; k++)
      {

        game_board[i][j][k] = to_string((magic_cube[i][j][k]));
      }
    }
  }

  while (!game_end())
  {
    flag = 0;
    cout << "before entry" << endl;
    nextmove();

    cout << "Game board  after Computer played :" << endl;
    cout << endl;
    ingame_board();
    cout << endl;
    //game_board();
    cout << "Computer has till now played on :" << endl;
    printVector(x);
    cout << endl; //prints all the moves played by computer till now
    cout << "Human has played on :" << endl;
    printVector(y); // prints human moves
    cout << endl
         << "Computer Score:" << endl;
    cout << x_score << endl;

    cout << endl
         << "Human Score:" << endl;
    cout << y_score << endl;
    cout << endl; //prints all the moves played by human till now
    if (game_end())
      break;
    do
    {
      cout << "Enter where do you want to play" << endl;
      cin >> user_move; // takes input of the location
      if (user_move < 1 or user_move > 27)
        cout << "Enter element between 1 and 27" << endl;

      else if (std::find(x.begin(), x.end(), user_move) != x.end() or std::find(y.begin(), y.end(), user_move) != y.end()) // if the element is already present in computer moves
        cout << "That position is already occupied" << endl;
      else
      {
        corner_edgecentre.erase(std::remove(corner_edgecentre.begin(), corner_edgecentre.end(), user_move), corner_edgecentre.end()); // remove the element from corner_edgecentre vector
        surface_centre.erase(std::remove(surface_centre.begin(), surface_centre.end(), user_move), surface_centre.end());             // remove element from suurface_centre vector
        y.push_back(user_move);                                                                                                       // stores the element in human moves
        int p = vertice[user_move].x;
        int q = vertice[user_move].y;
        int r = vertice[user_move].z;
        //cout << p << q << r;

        game_board[p][q][r] = 'O'; // marks the move as O for human
        cout << "Game board after you played:" << endl;
        ingame_board();            // displays gameboard
        y_score += score_count(y); // increases score count of human if conditions are met
        cout << "Computer has played on :" << endl;
        printVector(x); // prints computer moves
        cout << "Human has played on :" << endl;
        printVector(y); // prints human moves
        cout << endl
             << "Computer Score:" << endl;
        cout << x_score << endl;

        cout << endl
             << "Human Score:" << endl;
        cout << y_score << endl;
        flag = 1;
      }
    } while (!flag);
  }

  return 0;
}

// if comp isnt first

/*************************************************************/
//DEVANSH GOEL
//DG403@SNU.EDU.IN
//SOM PANDE
//DEVYANSH SEHGAL