//
// Created by Akira on 2017-06-03.
//

#ifndef KNOWLEDGEMAP_KRL_H
#define KNOWLEDGEMAP_KRL_H

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include <typeinfo>
#include <unordered_map>
#include "KRL/Term.h"
#include "KRL/Formula.h"
namespace krl_map{
    class KRL {
    private:
        std::unordered_map<std::string,std::shared_ptr<Const>> constants;
        std::unordered_map<std::string,std::shared_ptr<Func>> functions;
        std::unordered_map<std::string,std::shared_ptr<Pred>> predicates;

        std::unordered_map<std::string,std::shared_ptr<Term>> terms;
        std::unordered_map<std::string,std::shared_ptr<Formula>> formulas;
    public:
        static size_t next_symbol_id;
        static size_t next_term_id;
        static size_t next_formula_id;
        KRL(){}
        void addConst(const std::string &c_name); //TODO: Include string para?
        void addFunc(const std::string &f_name, const std::size_t &f_arity);
        void addPred(const std::string &p_name, const std::size_t& p_arity);

        void addTerm(std::string term_name,
                     std::string term_type,
                     std::vector<std::string> content_keys
        );

        void addFormula(std::string formula_name,
                        std::string formula_type,
                        std::vector<std::string> content_keys
        );


        std::weak_ptr<Func> getFunc(const std::string name) const
        {
            return (this->functions).at(name);
        }
        std::weak_ptr<Pred> getPred(const std::string name) const
        {
            return (this->predicates).at(name);
        }

        //cautious about object slicing?
        std::weak_ptr<Term> getTerm(const std::string name) const
        {
            return (this->terms).at(name);
        }

        std::weak_ptr<Formula> getFormula(const std::string name) const
        {
            return (this->formulas).at(name);
        }

    };

    //size_t KRL::next_symbol_id = 0;
    //size_t KRL::next_term_id = 0;
    //size_t KRL::next_formula_id = 0;
    std::ostream& operator<<(std::ostream& out, const Const &c);
    std::ostream& operator<<(std::ostream& out, const Func &f);
    std::ostream& operator<<(std::ostream& out, const Pred &p);

}


#endif //KNOWLEDGEMAP_KRL_H
