#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

void losowanie(string tablicaS[4][4]){
   fstream plik;
   string linia;
   int liczba = 0;

   plik.open("slowa.txt");
   while(getline(plik, linia)){
      for(int i = 0; i < 2; i++){
            tablicaS[liczba/4][liczba%4] = linia;
            liczba++;
      }
   }
   plik.close();

   srand(time(0));
   for(int i = 0; i < 10; i++){
      int x1 = rand()%4;
      int y1 = rand()%4;
      int x2 = rand()%4;
      int y2 = rand()%4;
      string kontener = tablicaS[x1][y1];
      tablicaS[x1][y1] = tablicaS[x2][y2];
      tablicaS[x2][y2] = kontener;
   }
}

void kartyNaStole(string tablicaS[4][4], bool tablicaB[4][4]){
    int licznik = 1;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(tablicaB[i][j] == true){
                cout << " { " << tablicaS[i][j] << " } ";
                licznik++;
            }else{
                cout << " { " << licznik << " } ";
                licznik++;
            }
        }
        cout << endl;
        cout << endl;
    }
}

void obracanie(int liczba, bool tablicaB[4][4]){
    int temp = liczba - 1;
    if(tablicaB[temp/4][temp%4] == false){
        tablicaB[temp/4][temp%4] = true;
    }else{
      cout << "Karta juz zostala odwrocona" << endl;
      exit;
    }
}

void zakrywanie(int liczba, bool tablicaB[4][4]){
    int temp = liczba - 1;
    tablicaB[temp/4][temp%4] = false;
}

bool sprawdzWynik(int pierwszy, int drugi, string tablica[4][4]){
    int liczbaP = pierwszy - 1;
    int liczbaD = drugi - 1;
    if(tablica[liczbaP/4][liczbaP%4] == tablica[liczbaD/4][liczbaD%4]){
        return true;
    }else{
        return false;
    }
}

int main(){
   int pierwszy;
   int drugi;
   int wynik = 0;
   int licznik = 0;
   int start;
   cout << "Witaj w grze!" << endl;
   cout << "Twoim zadaniem jest znalezienie par identycznych znakow. Powodzenia!" << endl;
   bool tablicaB[4][4] = {
      {false, false, false, false},
      {false, false, false, false},
      {false, false, false, false},
      {false, false, false, false}
   };

   string tablicaS[4][4];
   losowanie(tablicaS);
   kartyNaStole(tablicaS, tablicaB);

   while(licznik < 8){
      cout << "Pierwszy odkryty:";
      cin >> pierwszy;

      cout << "Drugi odkryty: ";
      cin >> drugi;

      if (pierwszy == drugi){
         cout << "Ta karta zostala juz odkryta!" << endl;
         cout << "Drugi odkryty: ";
         cin >> drugi;
      }

      obracanie(pierwszy, tablicaB);
      obracanie(drugi, tablicaB);
      kartyNaStole(tablicaS, tablicaB);

      bool spr = sprawdzWynik(pierwszy, drugi, tablicaS);
      if(spr == true){
         cout << "Dobrze!" << endl;
         licznik++;
         wynik++;
      }else{
         cout << "Pudlo! Sprobuj jeszcze raz." << endl;
         wynik++;
         zakrywanie(pierwszy, tablicaB);
         zakrywanie(drugi, tablicaB);
      }
   };
   cout << "Wygrana! Twoj wynik to: " << wynik << " ruchy(ow)." << endl;
}
