//
// Created by akira on 6/17/17.
//

#include "Term.h"
using namespace std;
using namespace krl_map;


Expr::Expr(const std::size_t & id,
           const std::weak_ptr<Func>& f,
           const vector<weak_ptr<Term>>& terms)
        :Term(id), f_(f)
{
    cout<<"Expr: "<< f.lock()->getName() << " created" << endl;
    for(const weak_ptr<Term>& t:terms){
        weak_ptr<Term> temp = t;
        this->terms_.push_back(move(temp));
    }
}