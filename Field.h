#include "Cell.h"
#include <iostream>
#include <cmath>

using namespace std;

class Field{
private:
    char chYes = '.';
    char chLiveCell = 'x';
public:
    int iFieldWidth, iFieldHeight;
    Cell **pGField;
       Field(int Width, int Height){
           iFieldWidth = Width;
           iFieldHeight = Height;

           //---------------------------------------------------------------------------
           // Создание массива для поля
           //---------------------------------------------------------------------------
           this->pGField = new Cell* [iFieldHeight];
           // строки в массиве
           for (int count = 0; count < iFieldHeight; count++)
               this->pGField[count] = new Cell [iFieldWidth]; // и столбцы
           //  где this->pGField  – массив указателей на выделенный участок памяти под массив

           //---------------------------------------------------------------------------
           // Нумерование клеток
           //---------------------------------------------------------------------------

   //        Cell pEdge;
   //        pEdge.bIsCell = false;
   //        pEdge.bIsAlive = false;

           for (int y = 0; y < iFieldHeight; y++ )
           {
               for (int x = 0; x < iFieldWidth; x++)
               {

                   // # . .
                   // . . .
                   // . . .

                   if (((x - 1) < 0) && ((y - 1) < 0)) {
                       this->pGField[y][x].pUL = &this->pGField[iFieldHeight - 1][iFieldWidth - 1];
                       this->pGField[y][x].pU = &this->pGField[iFieldHeight - 1][x];
                       this->pGField[y][x].pUR = &this->pGField[iFieldHeight - 1][x + 1];
                       this->pGField[y][x].pL = &this->pGField[y][iFieldWidth - 1];
                       this->pGField[y][x].pR = &this->pGField[y][x + 1];
                       this->pGField[y][x].pDL = &this->pGField[y + 1][iFieldWidth - 1];
                       this->pGField[y][x].pD = &this->pGField[y + 1][x];
                       this->pGField[y][x].pDR = &this->pGField[y + 1][x + 1];
                   }
                   else {

                       // . # .
                       // . . .
                       // . . .

                       if ((y - 1) < 0) {
                           this->pGField[y][x].pUL = &this->pGField[iFieldHeight - 1][x - 1];
                           this->pGField[y][x].pU = &this->pGField[iFieldHeight - 1][x];
                           this->pGField[y][x].pUR = &this->pGField[iFieldHeight - 1][x + 1];
                           this->pGField[y][x].pL = &this->pGField[y][x - 1];
                           this->pGField[y][x].pR = &this->pGField[y][x + 1];
                           this->pGField[y][x].pDL = &this->pGField[y + 1][x - 1];
                           this->pGField[y][x].pD = &this->pGField[y + 1][x];
                           this->pGField[y][x].pDR = &this->pGField[y + 1][x + 1];
                       }

                       // . . .
                       // # . .
                       // . . .

                       if ((x - 1) < 0) {
                           this->pGField[y][x].pUL = &this->pGField[y - 1][iFieldWidth - 1];
                           this->pGField[y][x].pU = &this->pGField[y - 1][x];
                           this->pGField[y][x].pUR = &this->pGField[y - 1][x + 1];
                           this->pGField[y][x].pL = &this->pGField[y][iFieldWidth - 1];
                           this->pGField[y][x].pR = &this->pGField[y][x + 1];
                           this->pGField[y][x].pDL = &this->pGField[y + 1][iFieldWidth - 1];
                           this->pGField[y][x].pD = &this->pGField[y + 1][x];
                           this->pGField[y][x].pDR = &this->pGField[y + 1][x + 1];
                       }
                   }

                   // . . .
                   // . . .
                   // . . #

                   if (((x + 1) > iFieldWidth - 1) && ((y + 1) > iFieldHeight - 1)){
                       this->pGField[y][x].pUL = &this->pGField[y - 1][x - 1];
                       this->pGField[y][x].pU = &this->pGField[y - 1][x];
                       this->pGField[y][x].pUR = &this->pGField[y - 1][0];
                       this->pGField[y][x].pL = &this->pGField[y][x - 1];
                       this->pGField[y][x].pR = &this->pGField[y][0];
                       this->pGField[y][x].pDL = &this->pGField[0][x - 1];
                       this->pGField[y][x].pD = &this->pGField[0][x];
                       this->pGField[y][x].pDR = &this->pGField[0][0];
                   }
                   else {
                       // . . .
                       // . . #
                       // . . .

                       if ((x + 1) > iFieldWidth - 1) {
                           this->pGField[y][x].pUL = &this->pGField[y - 1][x - 1];
                           this->pGField[y][x].pU = &this->pGField[y - 1][x];
                           this->pGField[y][x].pUR = &this->pGField[y - 1][0];
                           this->pGField[y][x].pL = &this->pGField[y][x - 1];
                           this->pGField[y][x].pR = &this->pGField[y][0];
                           this->pGField[y][x].pDL = &this->pGField[y + 1][x - 1];
                           this->pGField[y][x].pD = &this->pGField[y + 1][x];
                           this->pGField[y][x].pDR = &this->pGField[y + 1][0];
                       }

                       // . . .
                       // . . .
                       // . # .

                       if ((y + 1) > iFieldHeight - 1){
                           this->pGField[y][x].pUL = &this->pGField[y - 1][x - 1];
                           this->pGField[y][x].pU = &this->pGField[y - 1][x];
                           this->pGField[y][x].pUR = &this->pGField[y - 1][x + 1];
                           this->pGField[y][x].pL = &this->pGField[y][x - 1];
                           this->pGField[y][x].pR = &this->pGField[y][x + 1];
                           this->pGField[y][x].pDL = &this->pGField[0][x - 1];
                           this->pGField[y][x].pD = &this->pGField[0][x];
                           this->pGField[y][x].pDR = &this->pGField[0][x + 1];
                       }

                   }

                   // . . #
                   // . . .
                   // . . .

                   if (((x + 1) > iFieldWidth - 1) && ((y - 1) < 0)){
                       this->pGField[y][x].pUL = &this->pGField[iFieldHeight - 1][x - 1];
                       this->pGField[y][x].pU = &this->pGField[iFieldHeight - 1][x];
                       this->pGField[y][x].pUR = &this->pGField[iFieldHeight - 1][0];
                       this->pGField[y][x].pL = &this->pGField[y][x - 1];
                       this->pGField[y][x].pR = &this->pGField[y][0];
                       this->pGField[y][x].pDL = &this->pGField[y + 1][x - 1];
                       this->pGField[y][x].pD = &this->pGField[y + 1][x];
                       this->pGField[y][x].pDR = &this->pGField[y + 1][0];
                   }

                   // . . .
                   // . . .
                   // # . .

                   if (((x - 1) < 0) && ((y + 1) > iFieldHeight - 1)){
                       this->pGField[y][x].pUL = &this->pGField[y - 1][iFieldWidth - 1];
                       this->pGField[y][x].pU = &this->pGField[y - 1][x];
                       this->pGField[y][x].pUR = &this->pGField[y - 1][x + 1];
                       this->pGField[y][x].pL = &this->pGField[y][iFieldWidth - 1];
                       this->pGField[y][x].pR = &this->pGField[y][x + 1];
                       this->pGField[y][x].pDL = &this->pGField[0][iFieldWidth - 1];
                       this->pGField[y][x].pD = &this->pGField[0][x];
                       this->pGField[y][x].pDR = &this->pGField[0][x + 1];
                   }

                   // . . .
                   // . # .
                   // . . .

                   if (((x - 1) >= 0) && ((y - 1) >= 0) && ((x + 1) <= iFieldWidth - 1) && ((y + 1) <= iFieldHeight - 1)){
                       this->pGField[y][x].pUL = &this->pGField[y - 1][x - 1];
                       this->pGField[y][x].pU = &this->pGField[y - 1][x];
                       this->pGField[y][x].pUR = &this->pGField[y - 1][x + 1];
                       this->pGField[y][x].pL = &this->pGField[y][x - 1];
                       this->pGField[y][x].pR = &this->pGField[y][x + 1];
                       this->pGField[y][x].pDL = &this->pGField[y + 1][x - 1];
                       this->pGField[y][x].pD = &this->pGField[y + 1][x];
                       this->pGField[y][x].pDR = &this->pGField[y + 1][x + 1];
                   }



   //                cout << "[" << y << "][" << x << "] " << &this->pGField[y][x] << '\n';
   //                cout << this->pGField[y][x].pUL << " | " << this->pGField[y][x].pU << " | " << this->pGField[y][x].pUR << " | " << this->pGField[y][x].pL << " | " << this->pGField[y][x].pR << " | " << this->pGField[y][x].pDL << " | " << this->pGField[y][x].pD << " | " << this->pGField[y][x].pDR << " | " << '\n';

                   //this->pGField[y][x].ulId = y * iFieldWidth + x;

   //                this->pGField[y][x].bIsAlive = false;

               }
           }

       }


    void drawField(){
        cout << '\n' << "Drawing" << '\n';

        for (int y = 0; y < iFieldHeight; y++ )
        {
            for (int x = 0; x < iFieldWidth; x++)
            {
//                if(this->pGField[y][x].bIsCell) {
//                    if(this->pGField[y][x].bIsAlive) cout << chLiveCell;
//                    else cout << chYes;
//                }
//                else cout << chNo;

                if(this->pGField[y][x].bIsAlive) cout << chLiveCell;
                else cout << chYes;

                cout << ' ';
            }
            cout << '\n';
        }

    }

    void makeAlive(int x, int y){
        this->pGField[y][x].bIsAlive = true;
    }

    void killCell(int x, int y){
        this->pGField[y][x].bIsAlive = false;
    }

    Cell** returnField(){
        return this->pGField;
    }

    ~Field(){
        for (int count = 0; count < iFieldHeight; count++)
            delete []this->pGField[count];
    }

};
