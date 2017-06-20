//
// Created by Akira on 2017-06-03.
//

#include "KRL.h"
using namespace std;
using namespace krl_map;
/*
ostream& operator<<(ostream& out, const Const &c){
    out << "Constant: " << c.name_ << endl;
}

ostream& krl_map::operator<<(ostream& out, const Func &f){
    out  << "Function: " << f.name_ << "(" << f.arity_ << "-ary)" << endl;
    return out;
}
ostream& krl_map::operator<<(ostream& out, const Pred &p){
    out << "Predicate: " << p.name_ << "(" << p.arity_ << "-ary)" << endl;
    return out;
}
*/
//std::shared_ptr<Const>&& constant
void KRL::addConst(const std::string& c_name){
    shared_ptr<Const> c = make_shared<Const>(this->next_symbol_id, c_name);
    this->constants[c_name] = c;
    ++(this->next_symbol_id);
}
void KRL::addFunc(const std::string& f_name, const size_t& f_arity) {
    shared_ptr<Func> f = make_shared<Func>(this->next_symbol_id, f_name, f_arity);
    this->functions[f_name] = f;
    ++(this->next_symbol_id);
}
void KRL::addPred(const std::string& predicate, const size_t& p_arity) {
    shared_ptr<Pred> p = make_shared<Pred>(this->next_symbol_id, predicate, p_arity);
    this->predicates[predicate] = p;
    ++(this->next_symbol_id);
}
void KRL::addTerm(std::string term_name,
                  std::string term_type,
                  std::vector<std::string> content_keys)
{
    if(term_type == "ConstExpr"){
        this->terms[term_name] = make_shared<ConstExpr>(this->next_term_id,this->constants[content_keys[0]]);
    }
    else if(term_type == "Var" ){
        int a = 0;
    }
    else if(term_type == "Expr"){
        vector<weak_ptr<Term>> terms;
        for(auto it=content_keys.begin()+1; it!=content_keys.end(); ++it){
            weak_ptr<Term>term = this->terms[*it];
            terms.push_back(term);
        }
        this->terms[term_name] = make_shared<Expr>(this->next_term_id,this->functions[content_keys[0]],terms);
    }else{
        cout<<"Error";
        return;
    }
    ++(this->next_term_id);
}

void addFormula(std::string formula_name,
                std::string formula_type,
                std::vector<std::string> content_keys)
{

}
