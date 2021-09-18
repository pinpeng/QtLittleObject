#include "gamedata.h"
#include <random>
#include <ctime>
#include <cstring>

GameData::GameData()
{
  srand(time(0));
}

void GameData::InitGameData(int columnCount, int lineCount, int boomCount)
{
  memset(cell,0,sizeof cell);

  this->columnCount = columnCount;
  this->lineCount = lineCount;
  this->boomCount = boomCount;
  nowCount = 0;

  for(int i=0;i<boomCount;){
      int x = rand()%lineCount;
      int y = rand()%columnCount;
      if(cell[x][y]==0){
          cell[x][y] = 9;
          i++;
        }
    }

  for(int i=0;i<lineCount;i++){
      for(int j=0;j<columnCount;j++){
          if(cell[i][j]!=9) cell[i][j] = GetBoomCount(i,j);
        }
    }
}

int GameData::GetBoomCount(int x, int y)
{
  int ans = 0;

  for(int i = std::max(x-1,0);i<std::min(x+2,lineCount);i++){
      for(int j = std::max(y-1,0);j<std::min(y+2,columnCount);j++){
          if(i==x&&y==j) continue;
          if(cell[i][j]==9) ans++;
        }
    }

  return ans;
}
