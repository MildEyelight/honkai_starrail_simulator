#include "gacha.hpp"
#include <iostream>
using std::cin;
using std::cout;
int main(){
    gachaMain gacha_program;
    int pull_times = 1;
    while(true){
        cin >> pull_times;
        getchar();
        auto result = gacha_program.pull(pull_times);
        gacha_program.show_result(result);
    }
    return 0;
}
