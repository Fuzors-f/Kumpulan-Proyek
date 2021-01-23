#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>

using namespace std;

struct notes
{
    string nama;
    string nama1;
    string pesan[20];
    int jmlpesan;
};

notes penting[50];
int jmlnote = 0;

void save()
{
     ofstream simpannotes ("Tugas Praktikum.txt", ios::ate);
        if (simpannotes.is_open())
        {
            for (int j = 1; j <= jmlnote; j++)
            {
                if (j > 1) {
                    simpannotes << endl;
                }
                simpannotes << "Notes " << j << ":" << endl;
                simpannotes << penting[j].nama << endl;
                simpannotes << penting[j].nama1;
                for (int k=1 ; k<=penting[j].jmlpesan; k++) {
                    simpannotes <<endl;
                    simpannotes << penting[j].pesan[k];
                }
            }
        }
}

void load ()
{
    ifstream load("Tugas Praktikum.txt");
    int status = 1;
    while (!load.eof())
    {
        string tampung;
        getline(load,tampung);
        if (tampung.substr(0,5) == "Notes") {
            jmlnote++;
            penting[jmlnote].jmlpesan = 0;
            status = 1;
        } else if (status == 1) {
            penting[jmlnote].nama = tampung;
            status++;
        } else if (status == 2) {
            penting[jmlnote].nama1 = tampung;
            status++;
        } else if (status == 3) {
            penting[jmlnote].jmlpesan++;
            penting[jmlnote].pesan[penting[jmlnote].jmlpesan] = tampung;
        }
    }
    load.close();
}

int main()
{
    int pil,pil2;
    bool notebaru;
    int tambah;
    string pesan1,tempnama,tempnama1,temppesan;

    do{
        system("CLS");
        cout << "Menu" << endl;
        cout << "====" << endl;
        cout << "1. Buat notes" << endl;
        cout << "2. Lihat semua notes" << endl;
        cout << "3. Save notes" << endl;
        cout << "4. Load notes" << endl;
        cout << "Pilih menu: ";
        cout << endl;
        cin >>pil;
            if (pil == 1) {
                cout << "Penulis: ";
                cin.ignore();
                getline (cin,tempnama);
                cout << "Tujuan: ";
                getline (cin,tempnama1);
                cout << "Pesan: ";
                getline (cin,temppesan);
                notebaru = true;
                for (int j=1;j<=jmlnote;j++) {
                    if (penting[j].nama == tempnama && penting[j].nama1 == tempnama1 && notebaru) {
                        penting[j].jmlpesan++;
                        penting[j].pesan[penting[j].jmlpesan] = temppesan;
                        notebaru = false;
                    }
                }

                if (notebaru) {
                    jmlnote++;
                    penting[jmlnote].jmlpesan = 1;
                    penting[jmlnote].nama = tempnama;
                    penting[jmlnote].nama1 = tempnama1;
                    penting[jmlnote].pesan[penting[jmlnote].jmlpesan] = temppesan;
                }
            } else if (pil == 2) {

                do{
                    system("CLS");
                    for (int j = 1; j <= jmlnote; j++)
                    {
                        cout << "Notes " << j << endl;
                        cout << "Penulis: " << penting[j].nama << endl;
                        cout << "Tujuan: " << penting[j].nama1 << endl;
                        for (int k=1;k<=penting[j].jmlpesan;k++) {
                            cout << "Pesan: " << penting[j].pesan[k] << endl;
                        }
                        cout << endl;
                    }
                    cout << endl;
                    cout << "1. Tambah  pesan" << endl;
                    cout << "2. Back to menu" << endl;
                    cout << "Pilih menu: ";
                    cin >> pil2;
                    if (pil2 == 1)
                    {
                        cout << "Tambah ke notes: ";
                        cin >> tambah;
                        penting[tambah].jmlpesan++;
                        cout << "Pesan: ";
                        cin.ignore();
                        getline(cin,penting[tambah].pesan[penting[tambah].jmlpesan]);
                    }
                }while(pil2 != 2);

            } else if (pil  == 3)
            {
               save();
            } else if (pil  == 4)
            {
               load();
            }

    }while (pil != 5);
    return 0;
}
