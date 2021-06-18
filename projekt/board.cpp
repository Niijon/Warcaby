#include "board.h"


Board::Board(){
    turn = true;
    checkturn = turn;
    redPieces = 12;
    blackPieces = 12;
    blackMoves = 0;
    redMoves = 0;
    sizes = 80;
    SaveTime = 0;
    ResetTime = 0;

}

void Board::loadIntoBoard(){
    int k = 0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
        if(i<3 && (i+j) % 2  != 0){
        p[k].setTextureRect(sf::IntRect(0, 0, sizes-20, sizes-20));
        p[k].setPosition(sizes*j+10,sizes*i+10);
        k++;
        }
        else if(i>4 && (i+j) % 2  != 0){
        p[k].setTextureRect(sf::IntRect(0, 0, sizes-20, sizes-20));
        p[k].setPosition(sizes*j+10,sizes*i+10);
        k++;
        }
        }
    }
}

void Board::Tablein(){
    for(int i=0;i<24;i++){
        if(i<12) Table[i]=-1;
        else Table[i]=1;
        IsKinged[i]=false;

    }
}

string Board::CordsNote(sf::Vector2f p){
    string s = "";
    s += char((p.x-10)/sizes+97);
    s += char(7-(p.y-10)/sizes+49);
    return s;
}

sf::Vector2f Board::toCord(char a, char b){
    int x = int(a) - 97;
    int y = 7 - int(b) + 49;
    return sf::Vector2f(x * sizes + 10, y * sizes + 10);
}

void Board::SaveToFile(){
ofstream out("Data.txt", ios::trunc);

for(int i=0; i<24;i++){
    out<<CordsNote(p[i].getPosition())<<endl;;
    out<<IsKinged[i]<<endl;
}
out<<redPieces<<endl;
out<<blackPieces<<endl;
out<<redMoves<<endl;
out<<blackMoves<<endl;
out<<turn<<endl;
out<<SaveTime<<endl;
}

void Board::ReadFromFile(){
fstream plik;
string Coordinates;
string boolean;
string data;
plik.open("Data.txt", ios::in);
if(plik.good()){
    for(int i=0; i<24;i++){
        getline(plik,Coordinates);
        p[i].setPosition(toCord(Coordinates[0],Coordinates[1]));
        getline(plik,boolean);
        if(boolean[0]==49) IsKinged[i] = true;
        else IsKinged[i] = false;
   }
    getline(plik,data);
    redPieces = atoi(data.c_str());
    getline(plik,data);
    blackPieces = atoi(data.c_str());
    getline(plik,data);
    redMoves = atoi(data.c_str());
    getline(plik,data);
    blackMoves = atoi(data.c_str());
    getline(plik,boolean);
    if(boolean[0]==49) turn = true;
    else turn = false;
    getline(plik,data);
    SaveTime = atoi(data.c_str());
}
}
void Board::RestartGame(){
fstream plik;
string Coordinates;
string boolean;
string data;
plik.open("Default.txt", ios::in);
if(plik.good()){
    for(int i=0; i<24;i++){
        getline(plik,Coordinates);
        p[i].setPosition(toCord(Coordinates[0],Coordinates[1]));
        getline(plik,boolean);
        if(boolean[0]==49) IsKinged[i] = true;
        else IsKinged[i] = false;
   }
    getline(plik,data);
    redPieces = atoi(data.c_str());
    getline(plik,data);
    blackPieces = atoi(data.c_str());
    getline(plik,data);
    redMoves = atoi(data.c_str());
    getline(plik,data);
    blackMoves = atoi(data.c_str());
    getline(plik,boolean);
    if(boolean[0]==49) turn = true;
    else turn = false;
    }
}

void Board::SaveData(int numberofmoves, int timeme){
ofstream out("AllScores.txt", ios::app);
out<<"Czas: "<<timeme<<endl;
out<<"Ilość ruchow: "<<numberofmoves<<endl;
}

void Board::SetTextures(sf::Texture t2, sf::Texture t3){
    for(int i=0;i<24;i++){
        if(i<12)    p[i].setTexture(t3);
        else p[i].setTexture(t2);

    }
}

bool Board::CheckIfEmpty(sf::Vector2f newP){
for(int i=0; i<24; i++)
    if(p[i].getPosition() == newP)
        return false;
return true;
}

int Board::CanKill(sf::Vector2f curr ,int id){
    bool spott = false;
        for (int x = -1; x <= 1; x += 2)
        {
        for(int y = -1; y <= 1; y += 2){
            sf::Vector2f check = sf::Vector2f(curr.x + x * sizes, curr.y + y * sizes);
            for(int i=0; i<24; i++)
            {
                sf::Vector2f acc = p[i].getPosition();
                if(acc.x!=10 && acc.x!=570 && acc.y!= 10 && acc.y!=570){
                    if(check == acc && Table[id] != Table[i] )
                    {
                        spott = true;
                        sf::Vector2f check2 = sf::Vector2f(curr.x + 2 * x * sizes, curr.y + 2 * y * sizes);
                        for(int j=0; j<24; j++){
                        sf::Vector2f acc2 = p[j].getPosition();
                        if(check2 == acc2)
                            spott = false;
                        }

                    }

                }
                if(spott) return id;
            }
            }
            }
            return -1;
        }

void Board::move(string str){
    sf::Vector2f oldPos = toCord(str[0],str[1]);
    sf::Vector2f newPos = toCord(str[2], str[3]);
    sf::Vector2f diff = sf::Vector2f(oldPos.x + (newPos.x - oldPos.x)/2.0, oldPos.y + (newPos.y - oldPos.y)/2.0);
        for(int i=0; i<24; i++){
        sf::Vector2f pieceCords = p[i].getPosition();
        if(pieceCords==diff){
                p[i].setPosition(-100,-100);
         }
     }
}
