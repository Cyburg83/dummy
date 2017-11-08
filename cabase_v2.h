#ifndef CABASE_H
#define CABASE_H


#include <iostream>

//eine neue Klasse namens CAbase
class CAbase {
public:              //"öffentliche" Methoden
    CAbase(int Nx,  int Ny);       //Prototyp vom Konstruktor
    CAbase& setField(int Nx, int Ny); //Ändert die Größe des Felds
    CAbase& setCell(int cellx, int celly);//Überprüft den Zustand einer Zelle und speichert den neuen Zustand
    CAbase& aliveCell(int cellx, int celly);//Macht Zelle lebendig
    CAbase& evolveallCells();//Wendet Regeln auf alle Zellen an

private:
    int size_x;
    int size_y;
    int* _current;
    int* _next;
    //Field _board[8][8]; // ein array namens _board (der unterstrich ist zur kennzeichnung von privatem;)
};

// Funktionsdefinition vom Konstruktor
CAbase::CAbase(int Nx, int Ny) {
    std::cout << "CAbase was instantiated" << std::endl;
    _current = new int[Nx * Ny];
    _next = new int[Nx * Ny];
    for (int i = 0; i < (Nx * Ny); i++){
            _current[i] = 0;
            _next[i]= 0;
            if (_next[i] == 0) {
                std::cout << "0";
            }
    }
    size_x = Nx;
    size_y = Ny;
}

CAbase &CAbase::setField(int Nx, int Ny){
    std::cout << "setField was called" << std::endl;
    for (int i = 0; i < (Nx * Ny); i++){
        if(_current[i] = 0){
            _current[i] = 0;
            _next[i]= 0;
        }else{
            _current[i] = 1;
            _next[i]= 1;
        }
            if (_next[i] == 0 || _next[i] == 1) {
                std::cout << "0";
            }
   }
}

CAbase &CAbase::setCell(int cellx, int celly){
    std::cout << "setCell was called" << std::endl;
    int cellindex=30*cellx + celly;
    int cellneighbours = _current[30*(cellx+1) + celly]+_current[30*(cellx+1) + celly+1]
                        +_current[30*(cellx+1) + celly-1]+_current[30*cellx + celly+1]
                        +_current[30*cellx + celly-1]+_current[30*(cellx-1) + celly+1]
                        +_current[30*(cellx-1) + celly]+_current[30*(cellx-1) + celly+1];
    switch(_current[cellindex]){
    case 0: if(cellneighbours=3){
            _next[cellindex]=1;
            break;
        }
    case 1: if(cellneighbours>=2 && cellneighbours<=3){
            _next[cellindex]=1;
            break;
        }else{
            _next[cellindex]=0;
            break;
        }
    }

}

CAbase &CAbase::aliveCell(int cellx, int celly){
    std::cout << "aliveCell was called" << std::endl;
    int cellindex = 30*cellx+celly;
    _current[cellindex]=1;
    std::cout << _current[cellindex];
}

CAbase &CAbase::evolveallCells(){
    std::cout << "evolveallCells was called" << std::endl;
    for(int i=0; i<size_x; i++){
        for(int j=0; j<size_y; j++){
            setCell(i,j);
        }
    }

    _current = _next;
}


#endif // CABASE_H
