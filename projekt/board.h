#ifndef BOARD_H
#define BOARD_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <fstream>

using namespace std;

class Board{
private:



public:
    sf::Sprite p[24];
    int SaveTime;
    int ResetTime;
    bool IsKinged[24];
    int Table[24];
    bool turn = true;
    bool checkturn = turn;
    int redPieces;
    int blackPieces;
    int blackMoves;
    int redMoves;
    float sizes;

    Board();
    void loadIntoBoard();

    void Tablein();

    string CordsNote(sf::Vector2f);

    sf::Vector2f toCord(char, char);

    void SaveToFile();

    void ReadFromFile();

    void RestartGame();

    void SaveData(int , int);

    void SetTextures(sf::Texture, sf::Texture);

    bool CheckIfEmpty(sf::Vector2f);

    int CanKill(sf::Vector2f,int);

    void move(string);


};


#endif // BOARD_H
