#ifndef GENERATOR_H
#define GENERATOR_H

class GameMaster;

// A class containing tools for generating a puzzle.
class Generator
{
public:
    bool CheckRow (int x, int y, GameMaster &gameMaster);
    bool CheckColumn (int x, int y, GameMaster &gameMaster);
    bool CheckBlock (int x, int y, GameMaster &gameMaster);
    bool AllValuesChecking (int i, int j, GameMaster &gameMaster);
    bool CheckRepeated (int i, int j, GameMaster &gameMaster);
    void MoveBack (int &i, int &j, GameMaster &gameMaster);
    void WriteInArrayForTesting (int i, int j, GameMaster &gameMaster);
    void ArrayForTestsClearing(GameMaster &gameMaster);
    void CreateMask(GameMaster &gameMaster);
};

#endif // GENERATOR_H
