//
// Created by akira on 6/18/17.
//

#include "PredMap.h"
using namespace kri_map;
using namespace std;


void PredMap::addMapping(
        const vector<weak_ptr<Indiv>>& src,
        const bool& t_f)
{
    string indivs_id = get_indivs_id(src);
    this->map_[indivs_id] = t_f;
}
bool PredMap::operator[](const vector<weak_ptr<Indiv>>& indivs)
{
    return this->map_[get_indivs_id(indivs)];
}