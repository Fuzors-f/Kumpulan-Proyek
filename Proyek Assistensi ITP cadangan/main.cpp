#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

int pospx;
int pospy;
int possavex;
int possavey;

int zeny = 10000;
int gold = 0;
int key = 3;

int posmenuy[4];
int posmenux[4];
int posflagy[4];
int posflagx[4];
int postx[6];
int posty[6];
int possilangx[150];
int possilangy[150];

int flagx[4];
int countert[6];

int jmlsilang;
int ctr = 0;

int posxawal,posxakhir,posyawal,posyakhir;
int posxawalp,posxakhirp,posyawalp,posyakhirp;

bool jalan = false;

string player = "P";
string mapbsr[52][52];
string chart[6];

int sellgold(int gold)
{
    int sell;
    sell = gold * 5000;
    return sell;
}

int buykey(int i)
{
    int harga = 0;

    if (i == 1){
        harga = 300;
    }else if (i == 2){
        harga = 500;
    }else if (i == 3){
        harga = 800;
    }
    return harga;
}

void bersih()
{
  for(int i = 0; i <= 51; i++) {
    for (int j = 0; j <= 51;j++) {
        mapbsr[i][j] = " ";
        if (i == 0 || i == 51) {
            mapbsr[i][j] = "-";
        }
        if ((j == 0 || j == 51) && i >= 1 && i <= 50) {
            mapbsr[i][j] = "|";
        }
        if (i == 25 && j == 25) {
            mapbsr[i][j] = player;
            pospx = 25;
            pospy = 25;
        }
        if (i == 15 && j == 15) {
            mapbsr[i][j] = "S";
            possavex = 15;
            possavey = 15;
        }
    }
  }

}

void bersih2()
{
  for(int i = 0; i <= 51; i++) {
    for (int j = 0; j <= 51; j++) {
        mapbsr[i][j] = " ";
        if (i == 0 || i == 51) {
            mapbsr[i][j] = "-";
        }
        if ((j == 0 || j == 51) && i >= 1 && i <= 50) {
            mapbsr[i][j] = "|";
        }
        if (i == pospy && j == pospx) {
            mapbsr[i][j] = player;
        }
        if (i == possavey && j == possavex) {
            mapbsr[i][j] = "S";
        }
    }
  }
}

void menux()
{
  bool ketemu;
  for(int i = 1; i <= 3; i++) {
    ketemu = false;
    do {
        posmenux[i] = rand() % 50 + 1;
        posmenuy[i] = rand() % 50 + 1;
        if (mapbsr[posmenuy[i]][posmenux[i]] == " ") {
            mapbsr[posmenuy[i]][posmenux[i]] = "N";
            ketemu = true;
        }
    } while (ketemu == false);
  }
}

void menux2()
{
  bool ketemu;
  for(int i = 1; i <= 3; i++) {
    ketemu = false;
    do {
        if (posmenuy[i] == pospy && posmenux[i] == pospx) {
            mapbsr[posmenuy[i]][posmenux[i]] = player;
        } else {
            mapbsr[posmenuy[i]][posmenux[i]] = "N";
        }
        ketemu = true;

    } while (ketemu == false);
  }
}

void flag()
{
  bool ketemu;
  for(int i = 1; i <= 3; i++) {
    ketemu = false;
    do {
        posflagx[i] = rand() % 48 + 2;
        posflagy[i] = rand() % 48 + 2;
        if (mapbsr[posflagy[i]-1][posflagx[i]-1] == " " &&
            mapbsr[posflagy[i]-1][posflagx[i]] == " " &&
            mapbsr[posflagy[i]-1][posflagx[i]+1] == " " &&
            mapbsr[posflagy[i]][posflagx[i]-1] == " " &&
            mapbsr[posflagy[i]][posflagx[i]] == " " &&
            mapbsr[posflagy[i]][posflagx[i]+1] == " " &&
            mapbsr[posflagy[i]+1][posflagx[i]-1] == " " &&
            mapbsr[posflagy[i]+1][posflagx[i]] == " " &&
            mapbsr[posflagy[i]+1][posflagx[i]+1] == " ")
        {
            mapbsr[posflagy[i]-1][posflagx[i]-1] = "#";
            mapbsr[posflagy[i]-1][posflagx[i]] = "#";
            mapbsr[posflagy[i]-1][posflagx[i]+1] = "#";
            mapbsr[posflagy[i]][posflagx[i]-1] = "#";
            mapbsr[posflagy[i]][posflagx[i]+1] = "#";
            mapbsr[posflagy[i]+1][posflagx[i]-1] = "#";
            mapbsr[posflagy[i]+1][posflagx[i]] = "#";
            mapbsr[posflagy[i]+1][posflagx[i]+1] = "#";
            if (i==1) {
                mapbsr[posflagy[i]][posflagx[i]] = "1";
                flagx[i] = 11;
            }
            if (i==2) {
                mapbsr[posflagy[i]][posflagx[i]] = "2";
                flagx[i] = 12;
            }
            if (i==3) {
                mapbsr[posflagy[i]][posflagx[i]] = "3";
                flagx[i] = 13;
            }
            ketemu = true;
        }
    } while (ketemu == false);
  }
}

void flag2()
{
  bool ketemu;
  for(int i = 1; i <= 3; i++) {
    ketemu = false;
    do {
        if (flagx[i] != 0) {
            if (flagx[i] == 11 || flagx[i] == 12 || flagx[i] == 13) {
                mapbsr[posflagy[i]-1][posflagx[i]-1] = "#";
                mapbsr[posflagy[i]-1][posflagx[i]] = "#";
                mapbsr[posflagy[i]-1][posflagx[i]+1] = "#";
                mapbsr[posflagy[i]][posflagx[i]-1] = "#";
                mapbsr[posflagy[i]][posflagx[i]+1] = "#";
                mapbsr[posflagy[i]+1][posflagx[i]-1] = "#";
                mapbsr[posflagy[i]+1][posflagx[i]] = "#";
                mapbsr[posflagy[i]+1][posflagx[i]+1] = "#";
            }
            if (i==1 && (flagx[i] == 1 || flagx[i] == 11) ) {
                mapbsr[posflagy[i]][posflagx[i]] = "1";

            }
            if (i==2 && (flagx[i] == 2 || flagx[i] == 12)) {
                mapbsr[posflagy[i]][posflagx[i]] = "2";
            }
            if (i==3 && (flagx[i] == 3 || flagx[i] == 13)) {
                mapbsr[posflagy[i]][posflagx[i]] = "3";
            }
            ketemu = true;
        }
        else {
            ketemu = true;
        }
    } while (ketemu == false);
  }
}

void bintang(){
    srand(time(0));
    bool ketemu;
    for(int i = 1; i <= 5; i++) {
        ketemu = false;
            do {
                postx[i] = rand() % 11 + 20;
                posty[i] = rand() % 11 + 20;
                if (mapbsr[posty[i]][postx[i]] == " ") {
                    chart[i] = "*";
                    mapbsr[posty[i]][postx[i]] = chart[i];
                    ketemu = true;
                }
            }while (ketemu == false);
    }
}

void bintang2(){
    srand(time(0));
    bool ketemu;
    for(int i=1;i<=5;i++) {
        if (postx[i] == pospx && posty[i]==pospy) {
            mapbsr[posty[i]][postx[i]] = player;
        } else {
            //if (countert[i] > 100){
              mapbsr[posty[i]][postx[i]] = chart[i];
            //}
        }
    }
}

void silang2(){
    srand(time(0));
    bool ketemu;
    for(int i = 1; i <= jmlsilang; i++) {
        if (possilangx[i] == pospx && possilangy[i]==pospy) {
            mapbsr[possilangy[i]][possilangx[i]] = player;
        } else {
            mapbsr[possilangy[i]][possilangx[i]] = "X";
        }


    }
}

void save(string &nama, int &gold, int &zeny, int &key, int &pospx, int &pospy, int &possavex, int &possavey, int posmenux[4], int posmenuy[4]
          , int posflagy[4], int posflagx[4], string &player)
{

    ofstream savefile;
    string file = nama+".txt";
    savefile.open(file.c_str());
    savefile << nama << endl;
    savefile << gold << endl;
    savefile << zeny << endl;
    savefile << key << endl;
    savefile << pospx<< endl;
    savefile << pospy<< endl;
    savefile << possavex << endl;
    savefile << possavey << endl;
    savefile << posxawal << endl;
    savefile << posxakhir << endl;
    savefile << posyawal << endl;
    savefile << posyakhir << endl;
    savefile << posxawalp << endl;
    savefile << posxakhirp << endl;
    savefile << posyawalp << endl;
    savefile << posyakhirp << endl;
    for (int i=0; i <3; i++)
    {
        savefile << posmenux[i] << endl;
        savefile << posmenuy[i] << endl;

    }
     for (int i=0; i <3; i++)
    {
        savefile << posflagx[i] << endl;
        savefile << posflagy[i] << endl;

    }

    for (int i=0; i<3; i++){
        savefile << flagx[i] << endl;
    }
    savefile << player << endl;


    savefile.close();

}

void load(string nama)
{
    int i = 0;
    string tampung[100];
    ifstream loadfile;
    string name= nama+".txt";
    loadfile.open(name.c_str());
    while(!loadfile.eof()){
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >> tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    loadfile >>  tampung[i];
        i++;
    for (int j=0; j <3; j++)
    {
        loadfile >> tampung[i];
        i++;
        loadfile >> tampung[i];
        i++;

    }
     for (int j=0; j <3; j++)
    {
        loadfile >> tampung[i];
        i++;
        loadfile >> tampung[i];
        i++;
    }
    for (int j=0; j<3; j++){
        loadfile >> tampung[i];
        i++;
    }
    loadfile >> tampung[i];
    i++;

    loadfile.close();

    nama= tampung[0];
    stringstream(tampung[1]) >> gold;
    stringstream(tampung[2]) >> zeny;
    stringstream(tampung[3]) >> key;
    stringstream(tampung[4]) >> pospx;
    stringstream(tampung[5]) >> pospy;
    stringstream(tampung[6]) >> possavex;
    stringstream(tampung[7]) >> possavey;
    stringstream(tampung[8]) >> posxawal;
    stringstream(tampung[9]) >> posxakhir;
    stringstream(tampung[10]) >> posyawal;
    stringstream(tampung[11]) >> posyakhir;
    stringstream(tampung[12]) >> posxawalp;
    stringstream(tampung[13]) >> posxakhirp;
    stringstream(tampung[14]) >> posyawalp;
    stringstream(tampung[15]) >> posyakhirp;
    stringstream(tampung[16]) >> posmenux[0];
    stringstream(tampung[17]) >> posmenuy[0];
    stringstream(tampung[18]) >> posmenux[1];
    stringstream(tampung[19]) >> posmenux[1];
    stringstream(tampung[20]) >> posmenux[2];
    stringstream(tampung[21]) >> posmenux[2];
    stringstream(tampung[22]) >> posflagx[0];
    stringstream(tampung[23]) >> posflagy[0];
    stringstream(tampung[24]) >> posflagx[1];
    stringstream(tampung[25]) >> posflagy[1];
    stringstream(tampung[26]) >> posflagx[2];
    stringstream(tampung[27]) >> posflagy[2];
    stringstream(tampung[28]) >> flagx[0];
    stringstream(tampung[29]) >> flagx[1];
    stringstream(tampung[30]) >> flagx[2];
    player = tampung[31];

    }
}

void cutscene(int &pospxscene, int &pospyscene, char &b, int&x, char &z)
{


    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){

            if(i==0 || i==9) {
                mapbsr[i][j] = "-";
            }
            else if(j == 0 || j== 9)
            {
                mapbsr[i][j] = "|";
            }
            else{
                mapbsr[i][j] = " ";
            }

             if(x==5){
                mapbsr[1][1]=z;
                 mapbsr[4][5] = "X";
            }

            if(x==4){
                mapbsr[4][5]= b;
            }


        }
    }
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
            if(i == pospyscene && j == pospxscene)
                {
                   mapbsr[pospyscene][pospxscene] = "P";
                }

                cout << mapbsr[i][j];
            }
            cout << endl;
        }

}


int main()
{
    srand(time(0));
    char z= char(030);
    char pil,pil2,pilmenu, pil22;
    string nama, nama1;

    bool jalan = true;
    bool menu = true;
    int randposty[5],randpostx[5],dapat,dapat1;

    int posflagy2;
    int posflagx2;
    int posflagy3;
    int posflagx3,i;
    char b='*';
    int posxawalkotak,posxakhirkotak,posyawalkotak,posyakhirkotak;

    bool ketemu;

    char gerak;
    char gscene;
    int x=0;
    int pospxscene = 5;
    int pospyscene = 5;

    bersih();
    jmlsilang = 0;

    do {

        if (menu){
                system("CLS");
            cout << "---DUNGEON LOST GAME---" << endl;
            cout << "       Created by      " << endl;
            cout << "   Fendy S./218116752  " << endl;
            cout << "Michael S. W./218116765" << endl;
            cout << endl;
            cout << "          Menu         " << endl;
            cout << "=======================" << endl;
            cout << "=       1. Start      =" << endl;
            cout << "=       2. Load       =" << endl;
            cout << "=       3. Exit       =" << endl;
            cout << "=======================" << endl;
            pil=getch();
        }

        if (pil=='1'){
            cout << "Masukkan nama: ";
            getline(cin,nama);
            cout << "Hello, " << nama << endl;
            cout << "Want to start game? [Y] or [N]";
            cout << endl;
            pil2 = getch();
            if (pil2 == 'y' || pil2 == 'Y'){
                do{
                    system("CLS");
                    cutscene(pospxscene,pospyscene,b,x,z);
                    gscene = getch();
                    if(ctr==0){
                        cout<< "Welcome players, untuk pertama kita mulai" << endl;
                        cout << "Coba tekan tombol w untuk kontrol ke atas, sekali" << endl;
                        cout<< "Tekan a untuk kontrol ke kiri, sekali" << endl;
                        cout << "Tekan s untuk kontrol bawah, sekali" << endl;
                        cout << "Tekan d untuk kontrol kanan, sekali" << endl;
                        cout <<"Jika keluar '*' menujulah ke sana dan pencet spasi untuk menggali" << endl;
                        getch();
                    }
                    if(x < 4){
                        if(gscene == 'w'){
                            pospyscene--;
                            if(pospyscene<1) pospyscene++;
                            ctr=1;
                            x=x+0;
                            cout << "Ingat! Hanya sekali :)";
                        getch();


                        }if(gscene == 'a'){
                            pospxscene--;
                            if(pospxscene<1) pospxscene++;
                            ctr=ctr*1;
                            x=x+0;
                            cout << "Ingat! Hanya sekali :)";
                        getch();


                        }if(gscene == 's'){
                            pospyscene++;
                            if(pospyscene>8)pospyscene--;
                            ctr=ctr*-1;
                            x=x+0;
                            cout << "Ingat! Hanya sekali :)";
                        getch();


                        }if(gscene == 'd'){
                            pospxscene++;
                            if(pospxscene>8) pospxscene--;
                            ctr=ctr*-4;
                            x=x+4;
                            ctr++;
                        cout << "Ingat! Hanya sekali :)";
                        getch();

                        }
                    } else{
                    if(gscene == 'w'){
                            pospyscene--;
                        }if(gscene == 'a'){
                            pospxscene--;
                        }if(gscene == 's'){
                            pospyscene++;
                        }if(gscene == 'd'){
                            pospxscene++;
                        }
                    }

                    if(gscene==' '){
                        if(pospyscene==4 && pospxscene==5){
                                x=x+1;
                        }
                        cout<< "Menuju portal";
                        getch();
                    }
                    if(x==5 &&pospyscene==1 &&pospxscene==1){
                        ctr=6;
                    }
                }while(ctr <6);

                if(ctr == 6){
                bersih();
                menux();
                flag();
                bintang();

                for (int i=1;i<=5;i++) {
                    countert[i] = 0;
                }

                do{
//                    for (int i=1;i<=5;i++) {
//                        countert[i]++;
//                        if (countert[i]==300){
//                            countert[i] = 0;
//                        }
//                    }
                    //Sleep(10);
                    system("CLS");
                    posyawal = pospy - 5;
                    posyakhir = pospy + 5;
                    posxawal = pospx - 5;
                    posxakhir = pospx +5;
                    if (posyawal < 0 ) {
                        posyakhir = posyakhir - posyawal + 1;
                        posyawal = 0;
                    }
                    if (posyakhir > 51 ) {
                        posyawal = posyawal - (posyakhir-51);
                        posyakhir = 51;
                    }
                    if (posxawal < 0 ) {
                        posxakhir = posxakhir - posxawal + 1;
                        posxawal = 0;
                    }
                    if (posxakhir > 51 ) {
                        posxawal = posxawal - (posxakhir-51);
                        posxakhir = 51;
                    }

                    for (int i=1;i<=3;i++){
                        if(flagx[i] != 0 && pospx == posflagx[i] && pospy == posflagy[i]) {
                            flagx[i]=0;
                            key++;
                        }
                    }
                        if(key == 3){
                            jalan = false;
                            system("CLS");
                            cout << "Selamat Atas Perjalanan Anda yang Panjang, Anda Menang!" << endl;
                            cout << "GAME OVER";
                        }

                    if (jmlsilang >0) {
                        i = 0;
                        do{
                            i++;
                            if (possilangx[i]<posxawal+1 || possilangx[i]>posxawal+10 || possilangy[i]<posyawal+1 || possilangy[i]>posyawal+10) {
                                for (int j=i+1;j<=jmlsilang;j++){
                                    possilangx[j-1] = possilangx[j];
                                    possilangy[j-1] = possilangy[j];
                                }
                                jmlsilang--;
                                i=0;
                            }
                        }while (i< jmlsilang);
                    }

                    for (int i = 1;i<=5;i++) {
                        if (postx[i]<posxawal+1) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = posxawal+10;
                                posty[i] = rand() % 9 + posyawal +1;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        } else
                        if (postx[i]>posxawal+10) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = posxawal+1;
                                posty[i] = rand() % 9 + posyawal +1;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        } else
                        if (posty[i]<posyawal+1) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = rand() % 9 + posxawal +1;
                                posty[i] = posyawal+10;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        } else
                        if (posty[i]>posyawal+10) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = rand() % 9 + posxawal +1;
                                posty[i] = posyawal+1;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        }
                    }

                    posyawalp = pospy - 2;
                    posyakhirp = pospy + 2;
                    posxawalp = pospx - 2;
                    posxakhirp = pospx + 2;
                    if (posyawalp < 0 ) {
                        posyawalp = 0;
                    }
                    if (posyakhirp > 51 ) {
                        posyakhirp = 51;
                    }
                    if (posxawalp < 0 ) {
                        posxawalp = 0;
                    }
                    if (posxakhirp > 51 ) {
                        posxakhirp = 51;
                    }

                    posyawalkotak = pospy - 3;
                    posyakhirkotak = pospy + 3;
                    posxawalkotak = pospx - 3;
                    posxakhirkotak = pospx + 3;


                    for (int i = posyawal;i<=posyakhir;i++) {
                        for (int j = posxawal;j<=posxakhir;j++){
                            if (i == 0 || i == 51 || j == 0 || j == 51) {
                                cout << mapbsr[i][j];
                            } else if (i >= posyawalp && i <= posyakhirp && j >= posxawalp && j <= posxakhirp) {
                                cout << mapbsr[i][j];
                            } else if ((i == posyawalkotak || i == posyakhirkotak) && j >= posxawalkotak && j <= posxakhirkotak && j != 0 && j != 51) {
                                cout << "-"; //mapbsr[i][j];
                            } else if ((j == posxawalkotak || j == posxakhirkotak) && i >= posyawalkotak && i <= posyakhirkotak && i != 0 && i != 51) {
                                cout << "|";//mapbsr[i][j];
                            }else {
                                cout << " "; //mapbsr[i][j];
                            }
                        }
                        cout << endl;
                    }
                    cout << "STATUS PLAYER" << endl;
                    cout << "-------------" << endl;
                    cout << nama << endl;
                    cout << "ZENY: " << zeny << endl;
                    cout << "GOLD: " << gold << endl;
                    cout << "KEY: " << key << endl;


                    //if (kbhit()) {
                      gerak = getch();
                    //1}

                    if (gerak == 'w' || gerak == 'W') {
                        mapbsr[pospy][pospx] = " ";
                        pospy--;
                        if (pospy < 1) {
                            pospy = 1;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospy++;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == 'd' || gerak == 'D') {
                        mapbsr[pospy][pospx] = " ";
                        pospx++;

                        if (pospx > 50) {
                            pospx = 50;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospx--;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == 's' || gerak == 'S') {
                        mapbsr[pospy][pospx] = " ";
                        pospy++;

                        if (pospy > 50) {
                            pospy = 50;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospy--;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == 'a' || gerak == 'A') {
                        mapbsr[pospy][pospx] = " ";
                        pospx--;

                        if (pospx < 1) {
                            pospx = 1;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospx++;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == ' ') {
                        ketemu = false;
                        for (int i=1;i<=5;i++) {
                            if (postx[i] == pospx && posty[i] == pospy && chart[i] == "*") {
                                chart[i] = "X";
                                gold = gold + 1;
                                ketemu = true;
                            }
                        }
                        if (ketemu == false) {
                            jmlsilang++;
                            possilangx[jmlsilang] = pospx;
                            possilangy[jmlsilang] = pospy;

                        }
                    }
                    if (gerak == 'h'|| gerak == 'H'){
                        string help;
                        cout << "Masukkan kode rahasia: ";
                        cin >> help;

                        if(help == "help"){
                            cout << "Koordinat save x: " << possavex << endl;
                            cout << "Koordinat save y: " << possavey << endl;
                            cout << "Koordinat player x: " << pospx << endl;
                            cout << "Koordinat player y: " << pospy << endl;
                            for(int i = 1; i <=3; i++){
                                cout << "Koordinat merchantx ke - " << i << ": " << posmenux[i] << endl;
                                cout << "Koordinat merchanty ke - " << i << ": " << posmenuy[i] << endl;
                            }
                            for(int i = 1; i <=3; i++){
                                cout << posflagx[i] << endl;
                                cout << posflagy[i] << endl;
                            }

                        }
                        else if(help == "cheat"){
                            string jmlh;
                            cin >> jmlh;
                            if(jmlh == "5ug1h"){
                                gold = 999;
                            }
                            else if(jmlh == "g4nt1"){
                                player = char(146);
                            }
                        }
                                getch();
                    }
                    for (int i=1;i<=3;i++) {
                        if (pospy == posmenuy[i] && pospx == posmenux[i]) {
                        cout << "MENU" << endl;
                        cout << "Merchant ke-" << i << endl;
                        cout << "1. Buy Key" << endl;
                        cout << "2. Sell gold" << endl;
                        cout << "Pilih menu: ";
                        cin >> pilmenu;
                            if (pilmenu == '1'){
                                if(zeny >= 300){
                                    if (flagx[i] == 10+i){
                                      zeny = zeny - buykey(i);
                                      flagx[i]=i;
                                    }
                                }else{
                                    cout << "Uang tidak mencukupi";
                                }
                            }else if (pilmenu == '2'){
                                zeny = zeny + sellgold(gold);
                                gold = 0;
                            }
                        }
                    }
                    if (pospx== possavex-1 && pospy== possavey || pospx== possavex+1 && pospy== possavey|| pospx== possavex && pospy== possavey+1 ||pospx== possavex && pospy== possavey-1){
                        system("CLS");
                        cout<< "Game saved! " << endl;
                        getch();
                        save (nama,gold,zeny,key,pospx,pospy,possavex,possavey,posmenux, posmenuy,posflagy,posflagx,player);
                    }

                    bersih2();
                    menux2();
                    flag2();
                    bintang2();
                    silang2();
                    gerak = 'p';

                }while(jalan);
                }

            } else if (pil2 == 'n' || pil2 == 'N'){
                system ("CLS");
                menu = true;
            }
        } else if (pil == '2'){
            cout << "Masukkan nama: ";
            getline(cin,nama1);
            cout << "Hello, " << nama1 << endl;
            cout << "Want to load game? [Y] or [N]";
            cout << endl;
            pil22 = getch();
             if (pil22 == 'y' || pil22 == 'Y'){
                load (nama1);
                bersih2();
                menux2();
                flag2();
                bintang2();
                silang2();
                for (int i=1;i<=5;i++) {
                    countert[i] = 0;
                }

                do{
//                    for (int i=1;i<=5;i++) {
//                        countert[i]++;
//                        if (countert[i]==300){
//                            countert[i] = 0;
//                        }
//                    }
                    //Sleep(10);
                    system("CLS");
                    posyawal = pospy - 5;
                    posyakhir = pospy + 5;
                    posxawal = pospx - 5;
                    posxakhir = pospx +5;
                    if (posyawal < 0 ) {
                        posyakhir = posyakhir - posyawal + 1;
                        posyawal = 0;
                    }
                    if (posyakhir > 51 ) {
                        posyawal = posyawal - (posyakhir-51);
                        posyakhir = 51;
                    }
                    if (posxawal < 0 ) {
                        posxakhir = posxakhir - posxawal + 1;
                        posxawal = 0;
                    }
                    if (posxakhir > 51 ) {
                        posxawal = posxawal - (posxakhir-51);
                        posxakhir = 51;
                    }

                    for (int i=1;i<=3;i++){
                        if(flagx[i] != 0 && pospx == posflagx[i] && pospy == posflagy[i]) {
                            flagx[i]=0;
                            key++;
                        }
                    }
                        if(key == 3){
                           jalan = false;
                            system("CLS");
                            cout << "Selamat Atas Perjalanan Anda yang Panjang, Anda Menang!" << endl;
                            cout << "GAME OVER";
                        }

                    if (jmlsilang > 0) {
                        i = 0;
                        do{
                            i++;
                            if (possilangx[i]<posxawal+1 || possilangx[i]>posxawal+10 || possilangy[i]<posyawal+1 || possilangy[i]>posyawal+10) {
                                for (int j=i+1;j<=jmlsilang;j++){
                                    possilangx[j-1] = possilangx[j];
                                    possilangy[j-1] = possilangy[j];
                                }
                                jmlsilang--;
                                i=0;
                            }
                        }while (i< jmlsilang);
                    }

                    for (int i = 1;i<=5;i++) {
                        if (postx[i]<posxawal+1) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = posxawal+10;
                                posty[i] = rand() % 9 + posyawal +1;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        } else
                        if (postx[i]>posxawal+10) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = posxawal+1;
                                posty[i] = rand() % 9 + posyawal +1;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        } else
                        if (posty[i]<posyawal+1) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = rand() % 9 + posxawal +1;
                                posty[i] = posyawal+10;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        } else
                        if (posty[i]>posyawal+10) {
                            ketemu = false;
                            mapbsr[posty[i]][postx[i]] = " ";
                            do {
                                postx[i] = rand() % 9 + posxawal +1;
                                posty[i] = posyawal+1;
                                if (mapbsr[posty[i]][postx[i]] == " " && postx[i] >= 1 && postx[i] <= 50 && posty[i] >= 1 && posty[i] <= 50) {
                                    chart[i] = "*";
                                    mapbsr[posty[i]][postx[i]] = chart[i];
                                    ketemu = true;
                                }
                            }while (ketemu == false);
                        }
                    }

                    posyawalp = pospy - 2;
                    posyakhirp = pospy + 2;
                    posxawalp = pospx - 2;
                    posxakhirp = pospx + 2;
                    if (posyawalp < 0 ) {
                        posyawalp = 0;
                    }
                    if (posyakhirp > 51 ) {
                        posyakhirp = 51;
                    }
                    if (posxawalp < 0 ) {
                        posxawalp = 0;
                    }
                    if (posxakhirp > 51 ) {
                        posxakhirp = 51;
                    }

                    posyawalkotak = pospy - 3;
                    posyakhirkotak = pospy + 3;
                    posxawalkotak = pospx - 3;
                    posxakhirkotak = pospx + 3;


                    for (int i = posyawal;i<=posyakhir;i++) {
                        for (int j = posxawal;j<=posxakhir;j++){
                            if (i == 0 || i == 51 || j == 0 || j == 51) {
                                cout << mapbsr[i][j];
                            } else if (i >= posyawalp && i <= posyakhirp && j >= posxawalp && j <= posxakhirp) {
                                cout << mapbsr[i][j];
                            } else if ((i == posyawalkotak || i == posyakhirkotak) && j >= posxawalkotak && j <= posxakhirkotak && j != 0 && j != 51) {
                                cout << "-"; //mapbsr[i][j];
                            } else if ((j == posxawalkotak || j == posxakhirkotak) && i >= posyawalkotak && i <= posyakhirkotak && i != 0 && i != 51) {
                                cout << "|";//mapbsr[i][j];
                            }else {
                                cout << " "; //mapbsr[i][j];
                            }
                        }
                        cout << endl;
                    }
                    cout << "STATUS PLAYER" << endl;
                    cout << "-------------" << endl;
                    cout << nama << endl;
                    cout << "ZENY: " << zeny << endl;
                    cout << "GOLD: " << gold << endl;
                    cout << "KEY: " << key << endl;
                    cout << possavex << endl;
                    cout << possavey << endl;
                    cout << "Koordinat player x: " << pospx << endl;
                    cout << "Koordinat player y: " << pospy << endl;
                    for(int i = 0; i <3; i++){
                        cout << "Koordinat merchantx ke - " << i+ 1<< ": " << posmenux[i] << endl;
                        cout << "Koordinat merchanty ke - "<<i+1 << ": "<< posmenuy[i] << endl;

                    }


                    //if (kbhit()) {
                      gerak = getch();
                    //1}

                    if (gerak == 'w' || gerak == 'W') {
                        mapbsr[pospy][pospx] = " ";
                        pospy--;
                        if (pospy < 1) {
                            pospy = 1;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospy++;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == 'd' || gerak == 'D') {
                        mapbsr[pospy][pospx] = " ";
                        pospx++;

                        if (pospx > 50) {
                            pospx = 50;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospx--;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == 's' || gerak == 'S') {
                        mapbsr[pospy][pospx] = " ";
                        pospy++;

                        if (pospy > 50) {
                            pospy = 50;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospy--;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == 'a' || gerak == 'A') {
                        mapbsr[pospy][pospx] = " ";
                        pospx--;

                        if (pospx < 1) {
                            pospx = 1;
                        }
                        if (mapbsr[pospy][pospx] == "#" || mapbsr[pospy][pospx] == "S") {
                            pospx++;
                        }
                        mapbsr[pospy][pospx] = player;
                    }
                    if (gerak == ' ') {
                        ketemu = false;
                        for (int i=1;i<=5;i++) {
                            if (postx[i] == pospx && posty[i] == pospy && chart[i] == "*") {
                                chart[i] = "X";
                                gold = gold + 1;
                                ketemu = true;
                            }
                        }
                        if (ketemu == false) {
                            jmlsilang++;
                            possilangx[jmlsilang] = pospx;
                            possilangy[jmlsilang] = pospy;

                        }
                    }
                    if (gerak == 'h'|| gerak == 'H'){
                        string help;
                        cout << "Masukkan kode rahasia: ";
                        cin >> help;

                        if(help == "help"){
                            cout << "Koordinat save x: " << possavex << endl;
                            cout << "Koordinat save y: " << possavey << endl;
                            cout << "Koordinat player x: " << pospx << endl;
                            cout << "Koordinat player y: " << pospy << endl;
                            for(int i = 1; i <=3; i++){
                                cout << "Koordinat merchantx ke - " << i << ": " << posmenux[i] << endl;
                                cout << "Koordinat merchanty ke - " << i << ": " << posmenuy[i] << endl;
                            }
                        }
                        else if(help == "cheat"){
                            string jmlh;
                            cin >> jmlh;
                            if(jmlh == "5ug1h"){
                                gold = 999;
                            }
                            else if(jmlh == "g4nt1"){
                                player = char(146);
                            }
                        }
                                getch();
                    }
                    for (int i=1;i<=3;i++) {
                        if (pospy == posmenuy[i] && pospx == posmenux[i]) {
                        cout << "MENU" << endl;
                        cout << "Merchant ke-" << i << endl;
                        cout << "1. Buy Key" << endl;
                        cout << "2. Sell gold" << endl;
                        cout << "Pilih menu: ";
                        cin >> pilmenu;
                            if (pilmenu == '1'){
                                if(zeny >= 300){
                                    if (flagx[i] == 10+i){
                                      zeny = zeny - buykey(i);
                                      flagx[i]=i;
                                    }
                                }else{
                                    cout << "Uang tidak mencukupi";
                                }
                            }else if (pilmenu == '2'){
                                zeny = zeny + sellgold(gold);
                                gold = 0;
                            }
                        }
                    }
                    if (pospx== possavex-1 && pospy== possavey || pospx== possavex+1 && pospy== possavey|| pospx== possavex && pospy== possavey+1 ||pospx== possavex && pospy== possavey-1){
                        save (nama1,gold,zeny,key,pospx,pospy,possavex,possavey,posmenux, posmenuy,posflagy,posflagx,player);

                     cout<< "Game saved! " << endl;
                    }

                }while(jalan);

             }else if (pil2 == 'n' || pil2 == 'N'){
                system ("CLS");
                menu = true;
             }
        }
    }while (pil != '3');
    return 0;
}
