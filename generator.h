#ifndef GENERATOR_H
#define GENERATOR_H

class GameMaster;

// A class containing tools for generating a puzzle.
class Generator
{
public:
    bool CheckRow (int x, int y, const GameMaster &gameMaster) const;
    bool CheckColumn (int x, int y, const GameMaster &gameMaster) const;
    bool CheckBlock (int x, int y, const GameMaster &gameMaster) const;
    bool AllValuesChecking (int i, int j, const GameMaster &gameMaster) const;
    bool CheckRepeated (int i, int j, const GameMaster &gameMaster) const;
    void MoveBack (int &i, int &j, GameMaster &gameMaster);
    void WriteInArrayForTesting (int i, int j, GameMaster &gameMaster);
    void ArrayForTestsClearing(GameMaster &gameMaster);
    void CreateMask(GameMaster &gameMaster);
    void PlayFieldClearing(GameMaster &gameMaster);
};

#endif // GENERATOR_H
