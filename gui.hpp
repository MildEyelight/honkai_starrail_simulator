#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
enum pullChoice{ONE_PULL = 1,TEN_PULL = 2};
enum inputEvent{UP = 38, DOWN = 40, ENTER = 13 ,OTHER = 0};

class choiceGUI{
public:
    uint32_t xingqiong;
    uint32_t tongpiao;
    pullChoice user_choice;
    choiceGUI(uint32_t xq = 0, uint32_t tp = 0 ,pullChoice uc = pullChoice::ONE_PULL):xingqiong(xq),tongpiao(tp),user_choice(uc){
    }

    pullChoice get_user_choice() const{
        return this->user_choice;
    }
    inputEvent get_user_input();
    
    void render(const uint32_t xingqiong = 0,const uint32_t tongpiao = 0){
        cout << "Remain xingqiong" << xingqiong << " Remaining Tongpiao" << tongpiao <<std::endl;
        while(true){
            if(this->user_choice == pullChoice::ONE_PULL){
                cout << "->pull once" <<endl;
                cout << "  pull ten times" <<endl; 
            }
            else{
                cout << "  pull once" <<endl;
                cout << "->pull ten times" <<endl; 
            }
            inputEvent user_input = this->get_user_input();
            //system("clear");
            if(user_input == UP || DOWN){
                this->user_choice = pullChoice((this->user_choice + 1) % 2);
            }
            else if(user_input == ENTER){
                break;
            }

        }
    }
};
// #ifdef _WIN32
// #include <conio>

// #elif __linux__
// #include <termio.h>
// inputEvent choiceGUI::get_user_input(){
//     inputEvent keyboard_event = OTHER;
//     while(keyboard_event == OTHER){
//         auto input = getch();
//         if(input == UP || input == DOWN || input == ENTER){
//             keyboard_event = inputEvent(input);
//         }
//         else {
//             keyboard_event = OTHER;
//         }
//     }
//     return keyboard_event;
// }

// #endif
