#ifndef CABASE_H
#define CABASE_H


#include <iostream>

class CAbase {
    //custom CAbase class
public:

    CAbase(int Nx, int Ny) {
        std::cout << "CAbase was instantiated" << std::endl;
        _current = new int[Nx * Ny];
        _next = new int[Nx * Ny];
        _currentView = new char[Nx * Ny];
        _nextView = new char[Nx * Ny];
        _size_x = Nx;
        _size_y = Ny;
        for (int i = 0; i < (Nx * Ny); i++){
                _current[i] = 0;
                _next[i]= 0;

                _currentView[i] = ' ';
                _nextView[i] = ' ';
        }
    }


    // Destructor

    ~CAbase() {
        std::cout << "CAbase was destroyed" << std::endl;
        delete[] _current;
        delete[] _next;
        delete[] _currentView;
        delete[] _nextView;
    }
    // Model / View
    void printCurrentView() {
        // updates grid view from grid model and prints it
        _getView(_currentView, _current, _size_x, _size_y);
        _printGrid(_currentView, _size_x, _size_y);
    }


    // Setters
    void resizeGrid(int Nx, int Ny) {
        // change size of grid models and grid views
        _resizeGrid(_current, _currentView, Nx, Ny);
        _resizeGrid(_next, _nextView, Nx, Ny);

        // new sizes are allocated
        _size_x = Nx;
        _size_y = Ny;

        // next evolution step is computed again
        _setAllNextCells(_next, _size_x, _size_y);
    }


    void setAliveCell(int x_coord, int y_coord){
        // Current model cell is set to 'alive' at given coordinates
        int cell = x_coord + y_coord * _size_x;
        _setAliveCurrentCell(_current, cell);
        // Next model is updated accordingly
        _setAllNextCells(_next, _size_x, _size_y);
    }
    void evolveGrid(){
        // Current model is overwritten with Next model
        _evolveCurrent(_current, _next, _size_x, _size_y);
        // Next model is updated accordingly
        _setAllNextCells(_next, _size_x, _size_y);
    }

    // Getters
    int* get_current() {
        return _current;
    }


    int* get_next() {
        return _next;
    }


    int get_size() {
        return _size_x;
    }


    int get_neighbours(int cell_x, int cell_y) {
        int cell = cell_x + _size_x*cell_y;
        return _getNeighbours(_current, cell, _size_x, _size_y);
    }



private:
    // universe size
    int _size_x;
    int _size_y;
    // universe model
    int* _current;
    int* _next;
    // universe view
    char* _currentView;
    char* _nextView;

    // private methods (see definitions below)
    void _printGrid(char* grid, int size_x, int size_y) {
        // prints grid view
        std::cout << "_printGrid called" << std::endl;
        for (int i = 0; i <= size_x+1; i++) {
            std::cout << ". ";
        }
        std::cout << std::endl;
        for (int i = 0; i < size_x * size_y; i++) {
            if(i == 0) {
                std::cout << ". ";
            }
            if (i % size_x == 0 && i>0) {
                std::cout << "." << std::endl << ". ";
            }
            std::cout << grid[i] << " ";
        }
        std::cout << "." << std::endl;
        for (int i = 0; i <= size_x+1; i++) {
            std::cout << ". ";
        }
    }


    void _resizeGrid(int* &grid, char* &grid_view, int Nx, int Ny) {
        // de-/increase current grid size
        std::cout << "_resize called" << std::endl;
        int* temp = new int[Nx * Ny];
        char* temp_view = new char[Nx * Ny];
        if (Nx * Ny > _size_x * _size_y) {          // if increase size
            for (int i=0; i < Nx*Ny; i++) {
                temp[i] = 0;
                temp_view[i] = ' ';
            }
            for (int j=0; j < _size_y; j++) {
                for (int i=0; i < _size_x; i++) {
                    temp[i + j*Nx] = grid[i + j*_size_x];
                    temp_view[i + j*Nx] = grid_view[i + j*_size_x];
                }
            }
        } else {                                    // if decrease size
            for (int j = 0; j < Ny; j++) {
                for (int i = 0; i < Nx; i++) {
                    temp[i + j*Nx] = grid[i + j*_size_x];
                    temp_view[i + j*Nx] = grid_view[i + j*_size_x];
                }
            }
        }

        delete [] grid;
        grid = temp;

        delete [] grid_view;
        grid_view = temp_view;
    }


    // private Getters
    void _getView(char *&grid_view, int *grid, int Nx, int Ny) {
        // updates grid view from grid model
        std::cout << "_getView called" << std::endl;
        char* temp = new char[Nx * Ny];
        for (int i = 0; i < Nx * Ny; i++) {
            temp[i] = grid[i] == 0 ? ' ' : '*';
        }

        delete[] grid_view;
        grid_view = temp;
    }


    int _getNeighbours(int* grid, int cell, int size_x, int size_y) {
        //std::cout << "_getNeighbours called" << std::endl;
        // iterates and counts living neighbours of given cell
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


    //private Setters
    void _setAliveCurrentCell(int* &grid, int cell) {
        // sets given cell to 'alive'
        std::cout << "_populateCell called" << std::endl;
        grid[cell] = 1;
    }


    void _setNextCell(int* &next_grid, int* curr_grid, int cell, int neighbours) {
        //std::cout << "_setCell called" << std::endl;
        // computes state of given cell in next evolution step according to game rules
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


    void _setAllNextCells(int* &grid, int size_x, int size_y) {
        std::cout << "_setNext called" << std::endl;
        // computes state of all cells in next evolution step according to game rules
        for(int i=0; i < size_x * size_y; i++){
            int neighbours = _getNeighbours(_current, i, size_x, size_y);
            _setNextCell(grid, _current, i, neighbours);
        }
    }


    void _evolveCurrent(int* &curr_grid, int* next_grid, int size_x, int size_y) {
        std::cout << "_updateCurrent called" << std::endl;
        // overwrites current grid model with next grid model
        int* temp = new int[size_x * size_y];
        for (int i=0; i < size_x*size_y; i++) {
            temp[i] = next_grid[i];
        }
        delete [] curr_grid;
        curr_grid = temp;
    }

};

#endif // CABASE_H
