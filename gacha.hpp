#pragma once
#include <iostream>
#include <random>
#include <string>
#include <array>
#include <ctime>
#include <vector>
#include "videoEngine.hpp"
#include "gui.hpp"

using std::vector;
using std::string;
using std::array;

#define NUM_CHANGZHU 7
struct gachaHistoryItem{
    time_t time_stamp;
    string items;
    gachaHistoryItem()=default;
    gachaHistoryItem(time_t a,const string& b):time_stamp(a),items(b){};
    gachaHistoryItem& operator=(const gachaHistoryItem& a){
        this->time_stamp = a.time_stamp;
        this->items = a.items;
        return *this;
    }
};

class gachaMain{
private:
    string gentei_character;
    static array<string,NUM_CHANGZHU> normal_character;
    bool guarant; 
    uint32_t total_gacha_times;
    uint32_t gacha_times_since_guarant;
    vector<gachaHistoryItem> gacha_history;

    uint32_t xing_qiong;
    uint32_t zhuanpiao;
    static const uint32_t guarant_begins = 74;
    static const uint32_t basic_probability = 6; // 1/1000
    static std::default_random_engine random_generator;
    static std::uniform_int_distribution<uint32_t> distribution;
    static const string junk;

    static videoEngine videoplay;
    choiceGUI gacha_gui;
public:
    gachaMain():gentei_character("Silver Wolf"),
                guarant(false),
                total_gacha_times(0),
                gacha_times_since_guarant(0),
                gacha_history(vector<gachaHistoryItem>()),
                xing_qiong(0),
                zhuanpiao(0)
    {};
    gachaMain(const gachaMain& a) = delete;
    bool is_5_rank_character() const {
        uint32_t total_probability = this->basic_probability;
        if(this->gacha_times_since_guarant >= this->guarant_begins){
             total_probability += (this->gacha_times_since_guarant-this->guarant_begins)*60;
        }
        uint32_t random_number = this->distribution(this->random_generator);
        if(random_number <= total_probability) return true;
        else return false;
    };
    bool is_gentei() const {
        uint32_t random_number = this->distribution(this->random_generator);
        if(this->guarant || random_number/500) return true;
        else return false;
    };
    string choose_a_normal_5_rank_character(){
        static std::uniform_int_distribution<uint32_t> distribution(0,NUM_CHANGZHU-1);
        uint32_t random_number = distribution(this->random_generator);
        return this->normal_character[random_number];
    };
    vector<gachaHistoryItem> pull(const uint32_t pull_times){
        this->total_gacha_times += pull_times;
        for(int i = 0;i<pull_times;i++){
            this->gacha_times_since_guarant += 1;
            if(this->is_5_rank_character()){
                if(this->is_gentei()){
                    this->guarant = false;
                    this->gacha_history.push_back(gachaHistoryItem(time(0),gentei_character));
                }
                else{
                    this->guarant = true;
                    auto chara = this->choose_a_normal_5_rank_character();
                    this->gacha_history.push_back(gachaHistoryItem(time(0),chara));
                }
                this->gacha_times_since_guarant = 0;
            }
            else{
                this->gacha_history.push_back(gachaHistoryItem(time(0),this->junk));
            }
        }
        //Show result
        uint32_t count = 0;
        vector<gachaHistoryItem> result(pull_times);
        for(auto iter = this->gacha_history.rbegin()+pull_times-1;count<pull_times;iter--){
            result[count] = (*iter);
            count++;
        }
        return std::move(result);
    };
    void show_result(const vector<gachaHistoryItem>& result){
        char skip_animation;
        cout<<"skip animation?[Y/n]: ";
        cin>> skip_animation;
        while(skip_animation!='Y'&&skip_animation!='y'
              &&skip_animation!='N'&&skip_animation!='n'){
            cout<<"Input y or n: ";
            cin>>skip_animation;
        }
        if(skip_animation=='N'||skip_animation=='n'){
            vector<string> a;
            for (auto iter = result.begin(); iter != result.end(); iter++){
                a.push_back((*iter).items);
            }
            this->videoplay.play(a);
        }
        else{
            int count = 1;
            for(auto& tmp:result){
                cout << "Result "<<count <<": "<< tmp.items<<endl;
                count++;
            }
        }
    }
    // void interact() {
    //     this->gacha_gui.render();
    //     auto choice = gacha_gui.get_user_choice();
    //     if(choice == pullChoice::ONE_PULL){
    //         this->pull(1);
    //     }
    //     else{
    //         pull(10);
    //     }
    // }
};

//static data.
std::uniform_int_distribution<uint32_t> gachaMain::distribution = std::uniform_int_distribution<uint32_t>(1,1000);
const string gachaMain::junk = "junk";
std::default_random_engine gachaMain::random_generator = std::default_random_engine(time(0));
array<string,7> gachaMain::normal_character{"Yanqing","Welt","Clara","Bailu","Gepard","Bronya","Himeko"};
videoEngine gachaMain::videoplay("./text_image_source/");

