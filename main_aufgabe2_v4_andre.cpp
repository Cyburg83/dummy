#include <iostream>
#include <string>
#include "cabase_v2.h"


bool string_is_int(std::string input) {
    // check if string consists only of integers
    if (input.find_first_not_of("0123456789") == std::string::npos) {
        return true;
    } else {
        return false;
    }
}

bool in_range(int input, int lower_bound, int upper_bound) {
    // check if input value is in given range
    if (input >= lower_bound && input <= upper_bound) {
        return true;
    } else {
        return false;
    }
}

int ask_Input(bool first_call) {
    // input validation for menu
    // first call is true, any further call is false (i.e. triggered by wrong input)
    std::string input;
    if (first_call) {
        std::cout << "Commands:" << std::endl;
    } else {
        std::cout << "Invalid input!" << std::endl;
    }
    std::cout << "1 to view current state" << std::endl;
    std::cout << "2 to preview next state" << std::endl;
    std::cout << "3 to populate sector" << std::endl;
    std::cout << "4 to evolve universe" << std::endl;
    std::cout << "5 to resize universe" << std::endl;
    std::cout << "9 to quit" << std::endl;
    std::cout << "Command Input: ";
    std::cin >> input;
    if (string_is_int(input)) {
        return std::stoi(input);
    } else {
        return ask_Input(false);
    }
}

int ask_Coords(bool first_call, std::string coord, int size) {
    // input validation for matrix coordinates
    std::string str_input;
    if (first_call) {
        std::cout << "Enter " + coord + "-coordinate [0-" + std::to_string(size-1) + "]" << std::endl;
    } else {
        std::cout << "Invalid input! Enter " + coord + "-coordinate [0-" + std::to_string(size-1) + "]" << std::endl;
    }
    std::cout << "Input: ";
    std::cin >> str_input;
    if (string_is_int(str_input)) {
        int input = std::stoi(str_input);
        if (in_range(input, 0, size-1)) {
            return input;
        } else {
            return ask_Coords(false, coord, size);
        }
    } else {
        return ask_Coords(false, coord, size);
    }
}

int ask_Size(bool first_call) {
    // input validation for resizing between 2 and 30
    std::string str_input;
    if (first_call) {
        std::cout << "Enter new size [2-30]" << std::endl;
    } else {
        std::cout << "Invalid input! Enter new size [2-30]" << std::endl;
    }
    std::cout << "Input: ";
    std::cin >> str_input;
    if (string_is_int(str_input)) {
        int input = std::stoi(str_input);
        if (in_range(input, 2, 30)) {
            return input;
        } else {
            return ask_Size(false);
        }
    } else {
        return ask_Size(false);
    }
}


int main() {

    bool running = true;

    CAbase start(10, 10);

    int curr_size = start.get_size();

    int x_coord;
    int y_coord;
    int new_size;

    std::cout << "Length: " << curr_size;
    std::cout << "\tWidth: " << curr_size <<std::endl;
    start.showCurrent();

    // menu loop
    do {
        int input = ask_Input(true);

        switch (input){
        case 1:
            std::cout << "Current state\t";
            std::cout << "Length: " << curr_size;
            std::cout << "\tWidth: " << curr_size <<std::endl;
            start.showCurrent();
            break;
        case 2:
            std::cout << "Next state\t";
            std::cout << "Length: " << curr_size;
            std::cout << "\tWidth: " << curr_size <<std::endl;
            start.showNext();
            break;
        case 3:
            x_coord = ask_Coords(true, "x", curr_size);
            y_coord = ask_Coords(true, "y", curr_size);
            start.vivifyCell(x_coord, y_coord);
            start.showCurrent();
            break;
        case 4:
            start.evolveGrid();
            start.showCurrent();
            break;
        case 5:
            new_size = ask_Size(true);
            start.resizeGrid(new_size, new_size);
            curr_size = start.get_size();
            start.showCurrent();
            break;
        case 9:
            std::cout << "Ok, bye." << std::endl;
            running = false;
            break;
        default:
            std::cout << "Error. Invalid input!" << std::endl;
            break;
        }

    } while (running);

    system("pause");

    return 0;


}
