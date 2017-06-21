//
// Created by akira on 6/17/17.
//

#include "Formula.h"
using namespace std;
using namespace krl_map;
AtomF::AtomF(const std::size_t & id,
      const std::weak_ptr<Pred>& p,
      const std::vector<std::weak_ptr<Term>>& terms)
        :Formula(id), p_(p)
{
    cout<<"AtomF: "<<p.lock()->getName() << " created"<<endl;
    for(const weak_ptr<Term>& t:terms){
        weak_ptr<Term> temp = t;
        this->terms_.push_back(move(temp));
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