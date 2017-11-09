#ifndef CABASE_H
#define CABASE_H


#include <iostream>

//eine neue Klasse namens CAbase
class CAbase {
public:
    //Constructor
    CAbase(int Nx,  int Ny);       //Prototyp vom Konstruktor

    // Model / View
    void showCurrent();
    void showNext();

    // Setters
    void resizeGrid(int Nx, int Ny);
    void vivifyCell(int x_coord, int y_coord);//Macht Zelle lebendig
    void evolveGrid();//Wendet Regeln auf alle Zellen an

    // Getters
    int* get_current();
    int* get_next();
    int get_size();
    int get_neighbours(int cell_x, int cell_y);



private:
    int _size_x;
    int _size_y;
    int* _current;
    int* _next;

    void _printGrid(int* grid, int size_x, int size_y);
    void _resizeGrid(int* &grid, int Nx, int Ny);
    void _populateCell(int* &grid, int cell);
    int _countNeighbours(int* grid, int cell, int size_x, int size_y);
    void _setCell(int* &next_grid, int* curr_grid, int cell, int neighbours);
    void _setNext(int* &grid, int size_x, int size_y);
    void _updateCurrent(int* &curr_grid, int* next_grid, int size_x, int size_y);
};

// Funktionsdefinition vom Konstruktor
CAbase::CAbase(int Nx, int Ny) {
    std::cout << "CAbase was instantiated" << std::endl;
    _current = new int[Nx * Ny];
    _next = new int[Nx * Ny];
    _size_x = Nx;
    _size_y = Ny;
    for (int i = 0; i < (Nx * Ny); i++){
            _current[i] = 0;
            _next[i]= 0;
            /*if (_next[i] == 0) {
                std::cout << "0";
            }*/
    }
}

// private methods

void CAbase::_printGrid(int* grid, int size_x, int size_y) {
    std::cout << "_printGrid called" << std::endl;
    std::cout << std::string(2*size_x - 1, '_') << std::endl;
    for (int i = 0; i < size_x * size_y; i++) {
        if (i % size_x == 0 && i>0) {
            std::cout << std::endl;
        }
        std::cout << grid[i] << " ";
    }
    std::cout << std::endl << std::string(2*size_x - 1, '_') << std::endl;

}

void CAbase::_resizeGrid(int* &grid, int Nx, int Ny) {
    std::cout << "_resize called" << std::endl;
    int* temp = new int[Nx * Ny];
    if (Nx * Ny > _size_x * _size_y) {
        for (int i=0; i < Nx*Ny; i++) {
            temp[i] = 0;
        }
        for (int j=0; j < _size_y; j++) {
            for (int i=0; i < _size_x; i++) {
                temp[i + j*Nx] = grid[i + j*_size_x];
            }
        }
    } else {
        for (int j = 0; j < Ny; j++) {
            for (int i = 0; i < Nx; i++) {
                temp[i + j*Nx] = grid[i + j*_size_x];
            }
        }
    }

    delete [] grid;
    grid = temp;
    //curr_x = Nx;
    //curr_y = Ny;
}

void CAbase::_populateCell(int* &grid, int cell) {
    std::cout << "_populateCell called" << std::endl;
    grid[cell] = 1;
}

int CAbase::_countNeighbours(int* grid, int cell, int size_x, int size_y) {
    //std::cout << "_countNeighbours called" << std::endl;
    // iterates and counts living neighbours of cell
    // ternary operator '?' handles boundary checks
    int neighbours = 0;

    for (int dim_x = (cell%size_x != 0 ? -1 : 0); dim_x <= (cell%size_x < (size_x-1) ? 1 : 0); dim_x++) {
        for (int dim_y = (cell/size_y != 0 ? -1 : 0); dim_y <= (cell/size_y < (size_y-1) ? 1 : 0); dim_y++) {
            if (dim_x != 0 || dim_y != 0) {
                neighbours += grid[cell + dim_x + dim_y*_size_y];
            }
        }

    }
    return neighbours;
}


void CAbase::_setCell(int* &next_grid, int* curr_grid, int cell, int neighbours) {
    //std::cout << "_setCell called" << std::endl;
    switch(neighbours) {
    case 2:
        next_grid[cell] = curr_grid[cell] == 1 ? 1 : 0;
        break;
    case 3: next_grid[cell] = 1;
        break;
    default:
        next_grid[cell] = 0;
        break;
    }
}

void CAbase::_setNext(int* &grid, int size_x, int size_y) {
    std::cout << "_setNext called" << std::endl;
    for(int i=0; i < size_x * size_y; i++){
        int neighbours = _countNeighbours(_current, i, size_x, size_y);
        _setCell(grid, _current, i, neighbours);
    }
}

void CAbase::_updateCurrent(int* &curr_grid, int* next_grid, int size_x, int size_y) {
    std::cout << "_updateCurrent called" << std::endl;
    int* temp = new int[size_x * size_y];
    for (int i=0; i < size_x*size_y; i++) {
        temp[i] = next_grid[i];
    }
    delete [] curr_grid;
    curr_grid = temp;
}


// public methods

void CAbase::showCurrent() {
    _printGrid(_current, _size_x, _size_y);
}

void CAbase::showNext() {
    _printGrid(_next, _size_x, _size_y);
}

//Setters

void CAbase::resizeGrid(int Nx, int Ny) {
    // change size of grid
    _resizeGrid(_current, Nx, Ny);
    _resizeGrid(_next, Nx, Ny);

    _size_x = Nx;
    _size_y = Ny;

    _setNext(_next, _size_x, _size_y);
}






void CAbase::vivifyCell(int x_coord, int y_coord){

    int cell = x_coord + y_coord * _size_x;
    _populateCell(_current, cell);
    _setNext(_next, _size_x, _size_y);
}

void CAbase::evolveGrid(){
    _updateCurrent(_current, _next, _size_x, _size_y);

    _setNext(_next, _size_x, _size_y);
}

// Getters



int CAbase::get_neighbours(int cell_x, int cell_y) {
    int cell = cell_x + _size_x*cell_y;
    return _countNeighbours(_current, cell, _size_x, _size_y);
}

int* CAbase::get_current() {
    return _current;
}

int* CAbase::get_next() {
    return _next;
}

int CAbase::get_size() {
    return _size_x;
}


#endif // CABASE_H
