#include <iostream>
#include "Game.h"

using namespace std;

Board board;

int *TableOfIndexes(bool WhichTurn){
int *IdTable = new int [12];
if(WhichTurn){
    for(int i=12; i<24;i++){
    IdTable[i-12] = board.CanKill(board.p[i].getPosition(),i);
    }
}
else{
    for(int i=0; i<12;i++){
    IdTable[i] = board.CanKill(board.p[i].getPosition(),i);
    }
}
return IdTable;
}

bool *SearchId(int id, int *TableOfIDs){
    bool *arrray = new bool [2];
    arrray[0]=false;
    arrray[1]=false;
    for(int i=0;i<12;i++){
        if(id == TableOfIDs[i])
            arrray[0] = true;
        if(TableOfIDs[i]!=-1)
            arrray[1] = true;
    }
return arrray;
}


void Gameloop()
{
    sf::RenderWindow window(sf::VideoMode(640,637), "Hello");
    //Texture management
    sf::Texture t1;
    t1.loadFromFile("img/board.png");

    sf::Texture t2;
    t2.loadFromFile("img/blackPiece.png");

    sf::Texture t3;
    t3.loadFromFile("img/redPiece.png");

    sf::Texture t4;
    t4.loadFromFile("img/blackKing.png");

    sf::Texture t5;
    t5.loadFromFile("img/redKing.png");

    //Texture Manager END

    //SPRITES!
    sf::Sprite Brd(t1);

    //Set the textures for black and red pieces
    for(int i=0;i<24;i++){
        if(i<12)    board.p[i].setTexture(t3);
        else board.p[i].setTexture(t2);

    }

    board.loadIntoBoard();

    //SPRITES END

    //VARIABLES SECTION
    bool isMove = false;
    float dx=0,dy=0;
    int n=12;
    sf::Vector2f oldPos;
    string str;
    int *IndexesTable = new int [12];


    board.Tablein();
 //Event Handler
    sf::Event e;
    auto start = chrono::steady_clock::now();

    //Window start
    while(window.isOpen()){
    auto end = chrono::steady_clock::now();
        sf::Vector2i pos = sf::Mouse::getPosition(window);
        while(window.pollEvent(e)){
            if(e.type == sf::Event::Closed)
                window.close();
    if(e.type == sf::Event::KeyPressed)
        if(e.key.code == sf::Keyboard::S){
            board.SaveTime = chrono::duration_cast<chrono::seconds>(end - start).count() - board.ResetTime;
            board.SaveToFile();
        }

    if(e.type == sf::Event::KeyPressed)
        if(e.key.code == sf::Keyboard::O){
            board.ReadFromFile();
            board.ResetTime = chrono::duration_cast<chrono::seconds>(end - start).count();
            for(int i=0;i<24;i++){
            if(i<12){ if(!board.IsKinged[i])  board.p[i].setTexture(t3); else board.p[i].setTexture(t5);}
            else {if(!board.IsKinged[i]) board.p[i].setTexture(t2); else board.p[i].setTexture(t4);}
            }
        }

    if(e.type == sf::Event::KeyPressed)
        if(e.key.code == sf::Keyboard::R){
            board.RestartGame();
            board.ResetTime = chrono::duration_cast<chrono::seconds>(end - start).count();
            for(int i=0;i<24;i++){
            if(i<12)    board.p[i].setTexture(t3);
            else board.p[i].setTexture(t2);

            }
        }
            //Drag and Drop EVENT HANDLER
            if(board.turn)
                if(e.type == sf::Event::MouseButtonPressed)
                    if(e.key.code == sf::Mouse::Left){
                    IndexesTable = TableOfIndexes(board.turn);
                    for(int i=12;i<24;i++)
                    if(board.p[i].getGlobalBounds().contains(pos.x,pos.y)){
                        n=i;
                        isMove = true;
                        dx = pos.x - board.p[i].getPosition().x;
                        dy = pos.y - board.p[i].getPosition().y;
                        oldPos = board.p[i].getPosition();
                    }
                   else oldPos=board.p[n].getPosition();
                }

            if(!board.turn)
                if(e.type == sf::Event::MouseButtonPressed)
                    if(e.key.code == sf::Mouse::Left){
                    IndexesTable = TableOfIndexes(board.turn);
                    for(int i=0;i<12;i++)
                    if(board.p[i].getGlobalBounds().contains(pos.x,pos.y)){
                        n=i;
                        isMove = true;
                        dx = pos.x - board.p[i].getPosition().x;
                        dy = pos.y - board.p[i].getPosition().y;
                        oldPos = board.p[i].getPosition();
                    }
                    else oldPos=board.p[n].getPosition();
                }




            if(e.type == sf::Event::MouseButtonReleased)
                if(e.key.code == sf::Mouse::Left){

                    bool *CheckArray = new bool [2];
                    CheckArray = SearchId(n,IndexesTable);
                    isMove = false;
                    sf::Vector2f f = board.p[n].getPosition() + sf::Vector2f(board.sizes/2,board.sizes/2);
                    sf::Vector2f newPos = sf::Vector2f(board.sizes*int(f.x/board.sizes)+10, board.sizes*int(f.y/board.sizes)+10);
                    // Coordinates sout
                    str = board.CordsNote(oldPos) + board.CordsNote(newPos);

                    cout<<str<<endl;
                    cout<<board.blackMoves<<endl;
                    cout<<board.redMoves<<endl;
                    sf::Vector2f diff = sf::Vector2f(newPos.x - oldPos.x, newPos.y - oldPos.y);
                    /*
                    cout<<oldPos.x << " " << oldPos.y <<endl;
                    cout<<newPos.x << " " << newPos.y <<endl;
                    cout<<diff.y<<endl;
                    cout<< CheckArray[0]<< " " << CheckArray[1]<< endl;
                    for(int i=0; i<12;i++){
                        cout<<IndexesTable[i]<<endl;
                    }

*/
                                    //POSITIONING SECTION

                                    /* Dokonczyc instrukcje warunkowa sprawdzania mozliwosci zbicia */

                    int type = board.CanKill(oldPos,n);


/**/
        //KING MOVES
        if(!CheckArray[0] && !CheckArray[1]){
                    if(board.IsKinged[n]){
                        if(type < 0 && abs(diff.x) == 80 && abs(diff.y) == 80){
                        bool CanMove = board.CheckIfEmpty(newPos);
                        if(CanMove){
                        board.p[n].setPosition(newPos);
                        board.turn=!board.turn;
                        }
                         else
                            board.p[n].setPosition(oldPos);
                        }
                    }


        //STANDARD MOVE
                    if(!board.IsKinged[n]){
                    if(type < 0 && abs(diff.x) == 80 && abs(diff.y) == 80){
                    bool CanMove = board.CheckIfEmpty(newPos);
                    if(CanMove){
                        if(n<12 && (diff.y==80)){
                        board.p[n].setPosition(newPos);
                        board.turn = !board.turn;
                        //
                        //
                        if(newPos.y == 10.0 && n>11){
                        board.IsKinged[n]=true;
                        board.p[n].setTexture(t4);}
                        if(newPos.y == 570.0 && n<12) {
                        board.IsKinged[n]=true;
                        board.p[n].setTexture(t5); }
                        //
                        //
                        }
                        else if(n>11 && diff.y==-80){
                        board.p[n].setPosition(newPos);
                        board.turn = !board.turn;
                        //
                        //
                        if(newPos.y == 10.0 && n>11){
                            board.IsKinged[n]=true;
                            board.p[n].setTexture(t4);}
                        if(newPos.y == 570.0 && n<12) {
                            board.IsKinged[n]=true;
                            board.p[n].setTexture(t5); }
                        //
                        //
                        }
                        else board.p[n].setPosition(oldPos);

                    }
                    else
                        board.p[n].setPosition(oldPos);

                    }
                    }
                    if(type < 0 && (abs(diff.x) != 80 || abs(diff.y) != 80)) board.p[n].setPosition(oldPos);
        }


        if(CheckArray[0] && CheckArray[1]){
                    if(type >= 0 && abs(diff.x) == 160 && abs(diff.y) == 160){
                        bool CanMove = board.CheckIfEmpty(newPos);
                    if(CanMove){
                        board.p[n].setPosition(newPos);
                        board.move(str);
                        if(board.turn) board.redPieces--;
                        else board.blackPieces--;
                        if (board.CanKill(newPos, n)==-1) board.turn = !board.turn;

                        //
                        //
                        if(newPos.y == 10.0 && n>11){
                        board.IsKinged[n]=true;
                        board.p[n].setTexture(t4);}
                        if(newPos.y == 570.0 && n<12) {
                        board.IsKinged[n]=true;
                        board.p[n].setTexture(t5); }
                        //
                        //

                    }
                    else
                        board.p[n].setPosition(oldPos);

                    }
                    if(type >= 0 && (abs(diff.x) != 160 || abs(diff.y) != 160)) board.p[n].setPosition(oldPos);
        }
        if(!CheckArray[0] && CheckArray[1]){
            board.p[n].setPosition(oldPos);
        }


/**/
//////
                delete[] CheckArray;
                }

                if(isMove) board.p[n].setPosition(pos.x - dx, pos.y - dy);
        }
        //Event Section END

        //Counting number of moves
        if(board.checkturn == !board.turn){
                        if(!board.turn) board.blackMoves++;
                        else board.redMoves++;
                        board.checkturn = board.turn;
                    }

        // COMUNICATE SECTION
        if (board.redPieces==0 || board.blackPieces==0){
        sf::RenderWindow Display_Window(sf::VideoMode(700, 130, 32), "GRATULACJE!");
        sf::Font font;
        if(!font.loadFromFile("LemonMilk.otf")) break;
        string display_me;
        string seconds_format= "";
        string temp;
        if(((chrono::duration_cast<chrono::seconds>(end - start).count())- board.ResetTime + board.SaveTime)%60 < 10) seconds_format = "0";
        int amountMoves = 0;
        if(board.blackPieces==0) {
        temp = char(board.redMoves/100) + char(board.redMoves/10) + char(board.redMoves%10);
        display_me = "CZERWONE WYGRYWAJA W " + to_string(board.redMoves) + " RUCHACH I " + to_string(((chrono::duration_cast<chrono::seconds>(end - start).count())- board.ResetTime + board.SaveTime)/60) + ":" + seconds_format + to_string(((chrono::duration_cast<chrono::seconds>(end - start).count())- board.ResetTime + board.SaveTime)%60) + " MIN";;
        amountMoves = board.redMoves;
        }
        if(board.redPieces == 0) {
        temp = char(board.blackMoves/100) + char(board.blackMoves/10) + char(board.blackMoves%10);
        display_me = "CZARNE WYGRYWAJA W " + to_string(board.blackMoves) + " RUCHACH I " + to_string(((chrono::duration_cast<chrono::seconds>(end - start).count())-board.ResetTime+board.SaveTime)/60) + ":" + seconds_format + to_string(((chrono::duration_cast<chrono::seconds>(end - start).count())- board.ResetTime + board.SaveTime)%60) + " MIN";
        amountMoves = board.blackMoves;
        }
        sf::Event eve2;
        sf::Text Message(display_me, font, 28);
        Message.setColor(sf::Color::Black);
        Message.setPosition(10,30);
        while(Display_Window.isOpen()){
            while(Display_Window.pollEvent(eve2)){
                if(eve2.type == sf::Event::EventType::Closed){
                    Display_Window.close();
                    board.blackPieces = -1;
                    board.redPieces = -1;
                    int Saveme = chrono::duration_cast<chrono::seconds>(end - start).count() - board.ResetTime + board.SaveTime;
                    board.SaveData(amountMoves, Saveme);
                }
            }
        Display_Window.clear(sf::Color::White);
        Display_Window.draw(Message);
        Display_Window.display();
    }
    }
    //END

        //windows management
        window.clear();
        window.draw(Brd);
        for(int i=0; i<24; i++) window.draw(board.p[i]);
        window.display();
    }

    delete[] IndexesTable;
}


