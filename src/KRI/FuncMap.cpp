//
// Created by akira on 6/17/17.
//

#include "FuncMap.h"
using namespace kri_map;
using namespace std;
////////////////////////////
//Methods for each FuncMap//
////////////////////////////
void FuncMap::addMapping(const vector<weak_ptr<Indiv>>& src, const vector<weak_ptr<Indiv>>& target){
    //this method adds a mapping to EXISTING funcmap
    string indivs_id = get_indivs_id(src);
    this->map_[indivs_id] = target;
}

std::vector<std::weak_ptr<Indiv>> FuncMap::operator[](const std::vector<std::weak_ptr<Indiv>>& indivs){
    return this->map_[get_indivs_id(indivs)];
}

/*
void FuncMap::delMapping(const vector<shared_ptr<Indiv>>& indivs, const shared_ptr<Indiv>& indiv){
    string indivs_str = get_indivs_str(indivs);
    if(this->map_.find(indivs_str) != this->map_.end()){
        this->map_.erase(indivs_str);

        //Delete lookup table vals
        for (const auto& d:indivs){
            //Copy is needed to preserver order after deletion
            vector<string> strs = this->used_in_[d->getName()];
            for (string& compound_name:strs){
                if(compound_name == indivs_str){
                    this->used_in_[d->getName()].erase(strs.begin()+(&compound_name - &strs[0]));
                    break; //no need to search for the rest
                }
            }
        }
    } else{
        printf("No such func mapping.");
    }
}

void FuncMap::updateIndivName(const string from, const string to){
    for(auto & map_key:this->used_in_[from]){
        //gives all the compounded strings in which substring needs to be replaced "from" -> "to"
        string new_map_key(map_key);
        string temp_map_key(map_key);
        size_t start_pos = map_key.find(from);
        if(start_pos == string::npos)
            printf("No Keyword found in this.");
        new_map_key.replace(start_pos, from.length(), to);
        temp_map_key.replace(start_pos, from.length(), string(""));
        if(start_pos == temp_map_key.length() && temp_map_key.length()!=0){
            temp_map_key.replace(start_pos-1, 1, string(""));
        }else{
            temp_map_key.replace(start_pos, 1, string(""));
        }
        vector<string> other_indiv_strs = getMapKeyIndivStrs(temp_map_key);


        //Update map_
        this->map_[new_map_key] = move(this->map_[map_key]);
        (this->map_).erase(map_key); //TODO Check index change

        //Update used_in_
        for(const auto & indiv_str:other_indiv_strs){
            //need to update each of these corresponding
            vector<string>& target_strs = this->used_in_[indiv_str];
            target_strs.erase(std::remove(target_strs.begin(), target_strs.end(), map_key ),target_strs.end());
            target_strs.push_back(new_map_key);
        }

        //Update map_
        map_key = new_map_key;
        //get the other indiv strings from compund map_key

    }
}
*/
