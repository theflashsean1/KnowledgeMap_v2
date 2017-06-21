//
// Created by akira on 6/17/17.
//

#ifndef KNOWLEDGEMAP_FUNCMAP_H
#define KNOWLEDGEMAP_FUNCMAP_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include "Indiv.h"
namespace kri_map{

    //std::string get_indivs_str(const std::vector<std::shared_ptr<Indiv>>& indivs);
    //std::vector<std::string> getMapKeyIndivStrs(std::string temp_map_key);

    class FuncMap{
    private:
        //example: 2_3_4_ -> [d1, d3, d8, d9]
        //i.e.  map indiv_ids -> other individuals
        std::unordered_map<std::string, std::vector<std::weak_ptr<Indiv>>> map_;

    public:
        FuncMap():map_({{}})
        {
            std::cout<<"FuncMap: created"<<std::endl;
        }
        ~FuncMap()
        {
            std::cout<<"FuncMap destroyed"<<std::endl;
        }

        void addMapping(const std::vector<std::weak_ptr<Indiv>>& src,
                        const std::vector<std::weak_ptr<Indiv>>& target);
        std::vector<std::weak_ptr<Indiv>> operator[](const std::vector<std::weak_ptr<Indiv>>&);
    };

}


#endif //KNOWLEDGEMAP_FUNCMAP_H
