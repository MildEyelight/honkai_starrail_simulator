#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class videoEngine{
public:
    string source_file_path;
    uint32_t weight;
    uint32_t height;
    uint32_t fps;
    videoEngine():source_file_path(string()),weight(192),height(108),fps(30){}
    videoEngine(const string& a,uint32_t w=0,uint32_t h=0):source_file_path(a),weight(w),height(h),fps(30){}
    void play_train_video()const{
        system("bash ./text_image_source/train/train.out");
        system("clear");
    }
    void play_chara_video(const string& chara) const {
        string file_path = this->source_file_path + chara;
        std::ifstream infile;
        infile.open(file_path);
        if(!infile.is_open()){
            cout<<"Error Open"<<endl;
        }
        // infile>>buff;
        // cout<<buff<<endl;
        string line;
        while(getline(infile,line)){
            cout<<line<<endl;
        }
        getchar();
        system("clear");
    }
    void play(const vector<string>& pull_result)const{
        this->play_train_video();
        int count = 1;
        for(auto& result:pull_result){
            cout << "Result "<<count <<": "<< result<<endl;
            count++; 
            this->play_chara_video(result);
        }
    }
};
