//
// Created by akira on 6/17/17.
//

#include "Formula.h"
using namespace std;
using namespace krl_map;
AtomF::AtomF(const shared_ptr<Pred>& p, const std::vector<std::shared_ptr<Term>>& terms):p_(p){
    printf("AtomF created");
    for(const shared_ptr<Term>& t:terms){
        std::weak_ptr<Term> temp = t;
        this->terms_.push_back(std::move(temp));
    }
}
shared_ptr<NegatedF> operator!(const shared_ptr<Formula> &f){
    printf("NegatedF created");
    return std::make_shared<NegatedF>(f);
}

shared_ptr<AndF> operator&&(const shared_ptr<Formula> &f1, const shared_ptr<Formula> &f2){
    printf("AndF created");
    return std::make_shared<AndF>(f1,f2);
}

shared_ptr<OrF> operator||(const  shared_ptr<Formula> &f1, const shared_ptr<Formula> &f2){
    printf("OrF created");
    return std::make_shared<OrF>(f1,f2);
}