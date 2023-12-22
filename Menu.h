/**
* Menu.h (Effortless console menu making software)
* Copyright (C) 2023 by LeeTuah (Discord: leetuah).
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


# ifndef EPIC_MENU_UWU__
# define EPIC_MENU_UWU__

# include <iostream>
# include <vector>
# include <functional>
# include <string>
# include <fstream>
# include <sstream>
# include "conio.h"


class Menu{
    // Read thw following comments above the variables and functions
    // to get a brief idea of what they do
    private:
        // this list stores the name of menu items, and the functions associated to them
        std::vector<std::pair<std::string, std::function<void (void)>>> names;
        // these are the pairs of colors (head color and body color) for colorizing the menu
        std::pair<std::string, std::string> colors;
        // neutral is const value with -> \033[0m to neutralize the effect of the head and body colors
        std::string neutral;
        // contains three keybinds as string format -> the up key, down key, and select key
        std::string keybinds;
        // stores the heading of the menu
        std::string heading;
        // it is the maximum characters count that the menu will extend upto. Default is 32.
        int max_string_len;
        // stores the position of the currently selected item in the menu
        std::vector<std::pair<std::string, std::function<void (void)>>>::iterator pos;
        // stores whether the program will wait after the function has completed running
        // for any random user input before next iteration of the menu
        bool waitForNextIteration;
        // required by conio.h
        Console console;

        // prints the entirity of the menu in the terminal
        void printMenu();
        // helps to print the menu field in a centered manner
        void gen_element(std::string str, std::string color);

    public:
        // default constructor for the class
        Menu();
        // constructor to initialize all non-constant values in the class
        Menu(
            int max_len, std::string header, std::string head_color, std::string body_color,
            char up_key, char down_key, char sel_key
        );
        // default destructor for the class
        ~Menu();

        // = operator for the class
        Menu operator=(Menu m1);

        // returns the max string length
        int get_max_len();
        // sets the max string length to a new value
        void set_max_len(int max_len);

        // returns the heading of the class
        std::string get_heading();
        // sets the new heading for the class
        void set_heading(std::string header);

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
        // editing a currently existing field
        void edit_field(std::string old_name, std::string new_name, std::function<void (void)> new_func);
        // if the map has a certain field
        bool has_field(std::string name);

        // sets whether the program will stop for a random user input after the 
        // given user function has completed running
        void set_iteration_state(bool waitForNextIteration);
        // returns the current iteration state
        bool get_iteration_state();

        // saves the current menu settings in a .txt file
        // void save(std::string fname = "menu-savefile");
        // loads menu settings from a .txt file
        // void load(std::string fname = "menu-savefile");

        // it is like the main method of the class, the event loop for the menu resides here
        void run_menu();
};

void __clear(){
    # ifdef _WIN32
        system("cls");
    # else
        system("clear");
    # endif
}

Menu::Menu(){
    names = {};
    max_string_len = 32;
    colors = {};
    neutral = "\033[0m";
    waitForNextIteration = true;
    keybinds = "wsq";
    heading = "MENU";
    colors.first = "\033[0;31m";
    pos = names.begin();
}

Menu::Menu(int max_len, std::string header, std::string head_color, std::string body_color, 
char up_key, char down_key, char sel_key){
    if(max_len <= 0){
        std::cout << "Error: Max String Length is set to 0.";
        return;
    }

    max_string_len = max_len;

    if(head_color.size() != 2){
        std::cout << "Error: Head Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    if(body_color.size() != 2){
        std::cout << "Error: Body Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    colors.first = "\033[0;" + head_color + "m";
    colors.second = "\033[0;" + body_color + "m";
    neutral = "\033[0m";
    heading = header;
    keybinds[0] = up_key;
    keybinds[1] = down_key;
    keybinds[2] = sel_key;
    pos = names.begin();
}

Menu Menu::operator=(Menu m1){
    this->max_string_len = m1.max_string_len;
    this->names = m1.names;
    this->colors = m1.colors;
    this->pos = m1.pos;
    this->keybinds = m1.keybinds;
    this->waitForNextIteration = m1.waitForNextIteration;

    return *this;
}

int Menu::get_max_len(){
    return max_string_len;
}

void Menu::set_max_len(int max_len){
    if(max_len <= 0){
        std::cout << "Error: Max String Length is set to 0.";
        return;
    }

    max_string_len = max_len;
}

std::string Menu::get_heading(){
    return heading;
}

void Menu::set_heading(std::string header){
    heading = header;
}

std::pair<std::string, std::string> Menu::get_colors(){
    return colors;
}

void Menu::set_colors(std::string head_color, std::string body_color){
    if(head_color.size() != 2){
        std::cout << "Error: Head Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    if(body_color.size() != 2){
        std::cout << "Error: Body Color must contain only two characters in ANSI Color Code form.";
        return;
    }

    colors.first = "\033[0;" + head_color + "m";
    colors.second = "\033[0;" + body_color + "m";
}

std::string Menu::get_keybinds(){
    return keybinds;
}

void Menu::set_up_key(char key){
    keybinds[0] = key;
}

void Menu::set_down_key(char key){
    keybinds[1] = key;
}

void Menu::set_sel_key(char key){
    keybinds[2] = key;
}

void Menu::add_field(std::string name, std::function<void ()> func){
    names.push_back(std::pair(name, func));
    pos = names.begin();
}

void Menu::remove_field(std::string name){
    for(auto itr = names.begin(); itr != names.end(); itr++){
        if(itr->first == name){
            names.erase(itr);
            pos = names.begin();
            return;
        }
    }

    std::cout << "Error: Entry doesn\'t exist in the first place.";
}

void Menu::edit_field(std::string old_name, std::string new_name, std::function<void (void)> new_func){
    for(int itr = 0; itr != (int)names.size(); itr++){
        if(names[itr].first == old_name){
            names[itr] = {new_name, new_func};
            pos = names.begin();
            return;
        }
    }

    std::cout << "Error: Entry doesn\'t exist in the first place.";
}

bool Menu::has_field(std::string name){
    for(auto itr = names.begin(); itr != names.end(); itr++){
        if(itr->first == name) return true;
    }

    return false;
}

void Menu::set_iteration_state(bool waitForNextIteration){
    this->waitForNextIteration = waitForNextIteration;
}

bool Menu::get_iteration_state(){
    return this->waitForNextIteration;
}

void Menu::gen_element(std::string str, std::string color){
    int space_size = (max_string_len - ((int)str.size()))/2;

    for(int i = 1; i <= max_string_len; i++){
        if(i <= space_size || i > space_size + (int)str.size()) std::cout << " ";
        else std::cout << color << str[i - space_size - 1] << neutral;
    }
}

void Menu::printMenu(){
    if(max_string_len <= 0){
        std::cout << "Error: Invalid Max String Length provided.";
        return;
    }
    
    std::cout << std::string(max_string_len + 2, '=') << std::endl << "|";
    gen_element(heading, colors.first);
    std::cout << "|" << std::endl << std::string(max_string_len + 2, '=') << std::endl;

    for(auto itr = names.begin(); itr != names.end(); itr++){
        std::cout << ((itr != pos)? "|": "<");
        gen_element(itr->first, ((itr == pos)? colors.first : colors.second));
        std::cout << ((itr != pos)? "|": ">") << std::endl;
    }

    std::cout << std::string(max_string_len + 2, '=') << std::endl;
}

void Menu::run_menu(){
    char choice;
    bool run = true;
    pos = names.begin();

    this->add_field("Exit", __clear);

    while(run){
        __clear();
        std::cout << "Press " << keybinds[0] << " and " << keybinds[1] << " to move up and down the menu." << std::endl;
        std::cout << "Press " << keybinds[2] << " to select an item." << std::endl;
        printMenu();
        choice = console.getch();

        if(choice == keybinds[0]){
            if(pos != names.begin()) pos--;
        }

        else if(choice == keybinds[1]){
            if(pos != prev(names.end())) pos++;
        }

        else if(choice == keybinds[2]){
            if(pos == prev(names.end())){
                run = false;
                break;
            }

            __clear();
            pos->second();
            console.getch();
        }
    }

    names.pop_back();
}

Menu::~Menu(){
    names = {};
    max_string_len = 0;
    colors = {};
    neutral = "";
    keybinds = "";
    pos = names.end();
}

# endif
