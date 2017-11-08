#include <iostream>
#include <string>
#include <limits>

void printMatrix(int* A) {
    // takes dynamic array and prints it as 30*30 matrix
    std::cout << std::string(59, '_') << std::endl;
    for (int i = 0; i < 30 * 30; i++) {
        if (i % 30 == 0 && i>0) {
            std::cout << std::endl;
        }
        std::cout << A[i] << " ";
    }
    std::cout << std::endl << std::string(59, '_') << std::endl;
}

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
        std::cout << "Press: 0 to quit | 1 to change cell | 2 to reprint" << std::endl;
    } else {
        std::cout << "Invalid input! 0: quit | 1: change cell | 2: reprint" << std::endl;
    }
    std::cout << "Input: ";
    std::cin >> input;
    if (string_is_int(input)) {
        return std::stoi(input);
    } else {
        return ask_Input(false);
    }
}

int ask_Coords(bool first_call, std::string coord) {
    // input validation for matrix coordinates
    std::string str_input;
    if (first_call) {
        std::cout << "Enter " + coord + "-coordinate [0-29]" << std::endl;
    } else {
        std::cout << "Invalid input! Enter " + coord + "-coordinate [0-29]" << std::endl;
    }
    std::cout << "Input: ";
    std::cin >> str_input;
    if (string_is_int(str_input)) {
        int input = std::stoi(str_input);
        if (in_range(input, 0, 29)) {
            return input;
        } else {
            return ask_Coords(false, coord);
        }
    } else {
        return ask_Coords(false, coord);
    }
}

int ask_Value(bool first_call) {
    // input validation for new value assignment to changeCell
    std::string str_input;
    if (first_call) {
        std::cout << "Enter new value [0-9]" << std::endl;
    } else {
        std::cout << "Invalid input! Only [0-9]!" << std::endl;
    }
    std::cout << "Input: ";
    std::cin >> str_input;
    if (string_is_int(str_input)) {
        int input = std::stoi(str_input);
        if (in_range(input, 0, 9)) {
            return input;
        } else {
            return ask_Value(false);
        }
    } else {
        return ask_Value(false);
    }
}

void changeCell(int array[], int x_coord, int y_coord, int new_value) {
    // changes value at given coordinates
   int index = x_coord*30 + y_coord;
   array[index] = new_value;
}

int main() {

    // setting a flag to ensure termination of do-while (s. below)
    bool running = true;

    std::cout << "Hello World!" << std::endl;
    int input; // user input

    int A1[30][30]; // static array

    int* A2 = new int[30 * 30]; // dynamic array

    // fill A1 with random ints
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            A1[i][j] = rand() % 10;
        }
    }

    // copying elements from A1 to A2
    int j = 0;
    for (int i = 0; i < 30 * 30; i++) {
        A2[i] = A1[i / 30][j % 30];
        j++;
    }
    // declaration of situational input variables
    int x_coord;
    int y_coord;
    int new_value;

    // menu loop
    do {
        input = ask_Input(true);

        switch (input){
        case 0:
            std::cout << "Programm beendet. ";
            running = false;    // this stops the otherwise infinite loop
            break;
        case 1: // functions as declared above
            x_coord = ask_Coords(true, "x");
            y_coord = ask_Coords(true, "y");
            new_value = ask_Value(true);
            changeCell(A2, x_coord, y_coord, new_value);
            break;
        case 2:
            std::cout << "Reprint" << std::endl;
            printMatrix(A2);
            break;
        default:
            std::cout << "Error. Invalid input!" << std::endl;
            break;
        }

    } while (running);

    system("pause");

    return 0;
}
