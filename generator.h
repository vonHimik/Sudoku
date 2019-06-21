#ifndef GENERATOR_H
#define GENERATOR_H

// A class containing tools for generating a puzzle.
class Generator
{
public:
    bool CheckRow (int x, int y);
    bool CheckColumn (int x, int y);
    bool CheckBlock (int x, int y);
    bool AllValuesChecking (int i, int j);
    bool CheckRepeated (int i, int j);
    void MoveBack (int& i, int& j);
    void WriteInArrayForTesting (int i, int j);
    void ArrayForTestsClearing();
    void CreateMask();
};

#endif // GENERATOR_H
