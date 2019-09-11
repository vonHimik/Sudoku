#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

// The class that implements the game settings storage.
class GameSettings
{
public:

    // Difficulty level
    enum Difficult
    {
        easy,
        normal,
        hard
    };

    Difficult difficult;
};

#endif // GAMESETTINGS_H
