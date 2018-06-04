#include "Cell.h"

class Game{
public:
    int iFieldWidth, iFieldHeight;
    Cell **pGFieldTemp;

        Game(int width, int height){
            iFieldWidth = width;
            iFieldHeight = height;

            this->pGFieldTemp = new Cell* [iFieldHeight];

            for (int count = 0; count < iFieldHeight; count++)
                this->pGFieldTemp[count] = new Cell [iFieldWidth]; // и столбцы

        }

        void start(Field *pGField, bool states[3][9]){
    //        Cell **pGField = field.returnField();
            for (int s=0; s<3; s++){
                for (int num=0; num<9; num++){
                    std::cout<<states[s][num]<<' ';
                }
                std::cout<<"\n";
            }
            std::cout<<"\n---------------\n";
                for (int y = 0; y < iFieldHeight; y++) {
                    for (int x = 0, iCellCounter = 0; x < iFieldWidth; x++) {

    //                    cout << &pGField->returnField[y][x] << '\n';

                        //--------------------------------------------------------------------
                        // Анализ соседних клеток
                        //--------------------------------------------------------------------

                        // #..
                        // ...
                        // ...

                        if(pGField->returnField()[y][x].pUL->bIsAlive) iCellCounter++;

                        // .#.
                        // ...
                        // ...

                        if(pGField->returnField()[y][x].pU->bIsAlive) iCellCounter++;

                        // ..#
                        // ...
                        // ...

                        if(pGField->returnField()[y][x].pUR->bIsAlive) iCellCounter++;

                        // ...
                        // #..
                        // ...

                        if(pGField->returnField()[y][x].pL->bIsAlive) iCellCounter++;

                        // ...
                        // ..#
                        // ...

                        if(pGField->returnField()[y][x].pR->bIsAlive) iCellCounter++;

                        // ...
                        // ...
                        // #..

                        if(pGField->returnField()[y][x].pDL->bIsAlive) iCellCounter++;

                        // ...
                        // ...
                        // .#.

                        if(pGField->returnField()[y][x].pD->bIsAlive) iCellCounter++;

                        // ...
                        // ...
                        // ..#

                        if(pGField->returnField()[y][x].pDR->bIsAlive) iCellCounter++;


                        //--------------------------------------------------------------------
                        // Определение состояния
                        //--------------------------------------------------------------------
                        if (pGField->returnField()[y][x].bIsAlive){
                            if (states[1][iCellCounter]){
                                this->pGFieldTemp[y][x].bIsAlive = false;
                            }
                            if (states[2][iCellCounter]){
                                this->pGFieldTemp[y][x].bIsAlive = true;
                            }
                        }
                        else {
                            if (states[0][iCellCounter]) {
                                this->pGFieldTemp[y][x].bIsAlive = true;
                            }
                        }
                        iCellCounter = 0;

                    } // Горизонтальные поля
                } // Вертикальные поля

                for (int y = 0; y < iFieldHeight; y++){
                    for (int x = 0; x < iFieldWidth; x++){
                        if (this->pGFieldTemp[y][x].bIsAlive)
                            pGField->makeAlive(x,y);
                        else
                            pGField->killCell(x,y);
                    }
                }
        }


    ~Game(){
        for (int count = 0; count < iFieldHeight; count++)
            delete []this->pGFieldTemp[count];
    }
};
