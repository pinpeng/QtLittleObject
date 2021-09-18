#ifndef GAMEDATA_H
#define GAMEDATA_H


class GameData
{
public:
  GameData();
  void InitGameData(int columnCount,int lineCount,int boomCount);
public:
  int columnCount,lineCount;
  int cell[100][100];
  int boomCount,nowCount;
private:
  int GetBoomCount(int x,int y);
};

#endif // GAMEDATA_H
