/**
* Menu.h (Effortless console menu making software)
* Copyright (C) 2023 by LeeTuah.
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
* @author LeeTuah (Discord: LeeTuah#2396)
* @date 2023-05-27
* @version 1.0
*/


// EPIC_MENU_UWU is created as the guard clause for the program
# ifndef EPIC_MENU_UWU
# define EPIC_MENU_UWU

# include <iostream>
# include <vector>
# include <functional>
# include <string>
# include <conio.h>

// the class for the Menu
class Menu{
    private:
        // this list stores the name of menu items, and the functions associated to them
        std::vector<std::pair<std::string, std::function<void (void)>>> names;
        // these are the pairs of colors (head color and body color) for colorizing the menu
        std::pair<std::string, std::string> colors;
        // neutral is const value with -> \033[0m to neutralize the effect of the head and body colors
        std::string neutral;
        // contains three keybinds as string format -> the up key, down key, and select key
        std::string keybinds;
        // it is the maximum characters count that the menu will extend upto. Default is 32.
        int max_string_len;
        // stores the position of the currently selected item in the menu
        std::vector<std::pair<std::string, std::function<void (void)>>>::iterator pos;

        // prints the entirity of the menu in the terminal
        void printMenu();
        // helps to print the menu field in a centered manner
        void gen_element(std::string str, std::string color);

    public:
        // default constructor for the class
        Menu();
        // constructor to initialize all non-constant values in the class
        Menu(int max_len, std::string head_color, std::string body_color, char up_key, char down_key, char sel_key);
        // default destructor for the class
        ~Menu();

        // = operator for the class
        Menu operator=(Menu m1);
        // method which acts similar to the parameterized constructor of the class
        void update(int max_len, std::string head_color, std::string body_color, char up_key, char down_key, char sel_key);
        
        // returns the max string length
        int get_max_len();
        // sets the max string length to a new value
        void set_max_len(int max_len);

        // returns the head and the body colors
        std::pair<std::string, std::string> get_colors();
        // sets the new head and body colors
        void set_colors(std::string head_color, std::string body_color);

        // returns all the keybinds
        std::string get_keybinds();
        // sets the up key
        void set_up_key(char key);
        // sets the down key
        void set_down_key(char key);
        // sets the select key
        void set_sel_key(char key);

        // adding a field to the map
        void add_field(std::string name, std::function<void (void)> func);
        // removing a field from the map
        void remove_field(std::string name);
        // if the map has a certain field
        bool has_field(std::string name);

        // it is like the main method of the class, the event loop for the menu resides here
        void run_iteration();
};

// function to clear the console
void clear(){
    // if the _WIN32 macro is defined, run "cls", else run "clear"
    # ifdef _WIN32
        system("cls");
    # else
        system("clear");
    # endif
}

Menu::Menu(){
    // setting all the values to the default values
    names = {};
    max_string_len = 32;
    colors = {};
    neutral = "\033[0m";
    keybinds = "wsq";
    pos = names.begin();
}

Menu::Menu(int max_len, std::string head_color, std::string body_color, char up_key, char down_key, char sel_key){
    // setting all the variables with the parameters

    // if the maximum length provided is 0
    if(max_len <= 0){
        std::cout << "Error: Max String Length is set to 0.";
        return;
    }

    max_string_len = max_len;

    // if the head color size is not 2
    if(head_color.size() != 2){
        std::cout << "Error: Head Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    // if the body color size is not 2
    if(body_color.size() != 2){
        std::cout << "Error: Body Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    // setting all the variables
    colors.first = "\033[0;" + head_color + "m";
    colors.second = "\033[0;" + body_color + "m";
    neutral = "\033[0m";
    keybinds[0] = up_key;
    keybinds[1] = down_key;
    keybinds[2] = sel_key;
    pos = names.begin();
}

void Menu::update(int max_len, std::string head_color, std::string body_color, char up_key, char down_key, char sel_key){
    // this method acts similar to the above constructor

    // if len is 0 or -ve
    if(max_len <= 0){
        std::cout << "Error: Max String Length is set to 0.";
        return;
    }
    
    max_string_len = max_len;

    // if head color size is not 2
    if(head_color.size() != 2){
        std::cout << "Error: Head Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    // if body color size is not 2
    if(body_color.size() != 2){
        std::cout << "Error: Body Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    // setting all the variables
    colors.first = "\033[0;" + head_color + "m";
    colors.second = "\033[0;" + body_color + "m";
    keybinds[0] = up_key;
    keybinds[1] = down_key;
    keybinds[2] = sel_key;
}

Menu Menu::operator=(Menu m1){
    // copying over all of the elements from the other menu
    this->max_string_len = m1.max_string_len;
    this->names = m1.names;
    this->colors = m1.colors;
    this->pos = m1.pos;
    this->keybinds = m1.keybinds;

    return *this;
}

int Menu::get_max_len(){
    // returning the maximum string len
    return max_string_len;
}

void Menu::set_max_len(int max_len){
    // if maximum length is 0 or -ve
    if(max_len <= 0){
        std::cout << "Error: Max String Length is set to 0.";
        return;
    }

    max_string_len = max_len;
}

std::pair<std::string, std::string> Menu::get_colors(){
    // returning the colors
    return colors;
}

void Menu::set_colors(std::string head_color, std::string body_color){
    // if the head color size is not 2
    if(head_color.size() != 2){
        std::cout << "Error: Head Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    // if the body color size is not 2
    if(body_color.size() != 2){
        std::cout << "Error: Body Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    // setting all the variables with respect to their ANSI keywords
    colors.first = "\033[0;" + head_color + "m";
    colors.second = "\033[0;" + body_color + "m";
}

std::string Menu::get_keybinds(){
    // returns all three keybinds
    return keybinds;
}

void Menu::set_up_key(char key){
    // sets the up key
    keybinds[0] = key;
}

void Menu::set_down_key(char key){
    // sets the down key
    keybinds[1] = key;
}

void Menu::set_sel_key(char key){
    // sets the select key
    keybinds[2] = key;
}

void Menu::add_field(std::string name, std::function<void ()> func){
    // adding the new field to the vector
    names.push_back(std::pair(name, func));
    // setting the position to the beginning of the vector
    pos = names.begin();
}

void Menu::remove_field(std::string name){
    // removing the given name from the vector
    for(auto itr = names.begin(); itr != names.end(); itr++){
        // if the name is found in iteration, erase it and update the position
        if(itr->first == name){
            names.erase(itr);
            pos = names.begin();
            return;
        }
    }

    // not found
    std::cout << "Error: Entry doesn\'t exist in the first place.";
}

bool Menu::has_field(std::string name){
    // iterating through the vector
    for(auto itr = names.begin(); itr != names.end(); itr++){
        // if the name is found in iteration, return true
        if(itr->first == name) return true;
    }

    // name is not found in iteration
    return false;
}

void Menu::gen_element(std::string str, std::string color){
    // stores the size of spaces to print on each size of the text
    int space_size = (max_string_len - ((int)str.size()))/2;

    // iterating for the maximum string length amoubt
    for(int i = 1; i <= max_string_len; i++){
        // if the iteration is not centered, then print a blank space
        if(i <= space_size || i > space_size + (int)str.size()) std::cout << " ";
        // else, the iteration is centered, print the specific character to align the string
        else std::cout << color << str[i - space_size - 1] << neutral;
    }
}

void Menu::printMenu(){
    // if the maximum string length is 0 or -ve
    if(max_string_len <= 0){
        std::cout << "Error: Max String Length is set to 0.";
        return;
    }
    
    // printing the equal signs, the menu heading, and then again equal signs
    std::cout << "|" << std::string(max_string_len, '=') << "|" << std::endl << "|";
    gen_element("MENU", colors.first);
    std::cout << "|" << std::endl << "|" << std::string(max_string_len, '=') << "|" << std::endl;

    // iterating through the vector
    for(auto itr = names.begin(); itr != names.end(); itr++){
        // printing the current vector index
        std::cout << "|";
        // if the current index is selected, print it in head color, else print it in body color
        gen_element(itr->first, ((itr == pos)? colors.second : colors.first));
        std::cout << "|" << std::endl;
    }

    // ending equal signs
    std::cout << "|" << std::string(max_string_len, '=') << "|" << std::endl;
}

void Menu::run_iteration(){
    // the user choice
    char choice;
    // the boolean value which will control the while-loop
    bool run = true;
    // setting the position to the beginning of the vector
    pos = names.begin();

    // adding the default fiend "Exit"
    this->add_field("Exit", clear);

    while(run){
        // clearing the screen, printing the instructions and then entirity of the menu
        clear();
        std::cout << "Press " << keybinds[0] << " and " << keybinds[1] << " to move up and down the menu." << std::endl;
        std::cout << "Press " << keybinds[2] << " to select an item." << std::endl;
        printMenu();
        // getting the user choice
        choice = getch();
        
        // if the user pressed up key
        if(choice == keybinds[0]){
            // if the position is not at the beginning, move back
            if(pos != names.begin()) pos--;
        }

        // if the user pressed down key
        else if(choice == keybinds[1]){
            // if the position is not at the last element, move forward
            if(pos != prev(names.end())) pos++;
        }

        // if the user pressed the select key
        else if(choice == keybinds[2]){
            // if user chose the pre-defined "Exit", break the loop
            if(pos == prev(names.end())){
                run = false;
                break;
            }

            // clear the terminal and run the function associated to the pointer
            clear();
            pos->second();
        }
    }

    // removing the default field "Exit"
    names.pop_back();
}

Menu::~Menu(){
    // destructor for the class
    names = {};
    max_string_len = 0;
    colors = {};
    neutral = "";
    keybinds = "";
    pos = names.end();
}

# endif
