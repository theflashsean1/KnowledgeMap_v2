//
// Created by akira on 6/17/17.
//

#include "Indiv.h"
using namespace kri_map;
using namespace std;
string kri_map::get_indivs_id(const vector<weak_ptr<Indiv>>& indivs){
    std::string indivs_str = string("");
    for (const auto& d:indivs){
        indivs_str = (indivs_str + (d.lock()->getID()) + "_");
    }
    return indivs_str;
}

/*
vector<string> kri_map::getMapKeyIndivStrs(string temp_map_key){
    vector<string> indiv_strs;
    size_t end_pos = temp_map_key.find("_");
    while(end_pos != string::npos){
        indiv_strs.push_back(temp_map_key.substr(0,end_pos));
        temp_map_key.replace(0, end_pos, "");
        end_pos = temp_map_key.find("_");
    }
    indiv_strs.push_back(temp_map_key);
    return indiv_strs;
}
 */