//
// Created by akira on 6/17/17.
//

#ifndef KNOWLEDGEMAP_INDIV_H
#define KNOWLEDGEMAP_INDIV_H

#include <iostream>
#include <string>
#include <memory>
#include <vector>
namespace kri_map{
    //Terms always denote individuals under an interpretation I
    //In other words, I(Term*) = Indiv
    class Indiv{
    private:
        std::string name_;
        std::string type_;
        std::size_t id_;
    public:
        Indiv(std::size_t id,std::string name, std::string type)
                :id_(id),name_(name),type_(type)
        {
            std::cout<<"Indiv: "<< name<<" created"<<std::endl;
        }
        ~Indiv()
        {
            std::cout<<"Indiv: "<<name_<<" destroyed"<<std::endl;
        }
        std::string setName(const std::string& name)
        {
            std::cout<<name_<<" is renamed as "<<name<<std::endl;name_=name;
        }
        std::string getName() const
        {
            return name_;
        }
        std::string getType() const
        {
            return type_;
        }
        std::string getID() const
        {
            return std::to_string(id_);
        }
    };


    std::ostream& operator<<(std::ostream& out, const Indiv &d);
    std::string operator+(const std::string& s, const Indiv& indiv);
    std::string operator+(const Indiv& indiv, const std::string& s);

    std::string get_indivs_id(const std::vector<std::weak_ptr<Indiv>>& indivs);

}

#endif //KNOWLEDGEMAP_INDIV_H
