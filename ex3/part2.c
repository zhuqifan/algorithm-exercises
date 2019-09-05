#include <stdio.h>

void init(int col, int row, int chessboard[row][col])
{
        for(int i=0;i<row;i++)
        {
          for(int j=0;j<=col;j++)
          {
             if(i%2==j%2)
              chessboard[i][j] = 1;
             else
              chessboard[i][j] = 0;

             printf("%d", chessboard[i][j]);
           }
           printf("\n");
        }
        printf("\n");
}
int main()
{
  int chessboard[10][10];
  init(10,10,chessboard);
  return 0;
}
