#ifndef GENERATOR_H
#define GENERATOR_H

class GameMaster;

// A class containing tools for generating a puzzle.
class Generator
{
public:
    static constexpr size_t SHIFT = 1;
    static constexpr size_t NUMBER_OF_HIDDEN_CELLS_ON_EASY_DIFFICULTY = 15;
    static constexpr size_t NUMBER_OF_HIDDEN_CELLS_ON_NORMAL_DIFFICULTY = 25;
    static constexpr size_t NUMBER_OF_HIDDEN_CELLS_ON_HARD_DIFFICULTY = 35;

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
