//
// Created by akira on 6/18/17.
//

#ifndef KNOWLEDGEMAP_V2_PREDMAP_H
#define KNOWLEDGEMAP_V2_PREDMAP_H

#include <unordered_map>
#include "Indiv.h"
namespace kri_map{
    class PredMap{
    private:
        //example 2_3_4_ -> True
        //map indiv_ids -> T/F
        std::unordered_map<std::string, bool> map_;
    public:
        PredMap():map_({{}})
        {
            std::cout<<"PredMap: created"<<std::endl;
        }
        ~PredMap()
        {
            std::cout<<"PredMap: destroyed"<<std::endl;
        }

        void addMapping(const std::vector<std::weak_ptr<Indiv>>& src,
                        const bool& t_f);
        bool operator[](const std::vector<std::weak_ptr<Indiv>>&);
    };
}

#endif //KNOWLEDGEMAP_V2_PREDMAP_H
