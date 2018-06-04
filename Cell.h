#ifndef CELL_H
#define CELL_H

struct Cell{
public:
//    bool bIsCell = true;   // Является ли ячейка клеткой?
    bool bIsAlive = false;  // Жива ли клетка?
    Cell *pUL;      // Указатели на соседние клетки
    Cell *pU;
    Cell *pUR;
    Cell *pL;
    Cell *pR;
    Cell *pDL;
    Cell *pD;
    Cell *pDR;
};

#endif
