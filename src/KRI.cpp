//
// Created by Akira on 2017-06-03.
//

#include "KRI.h"
using namespace std;
using namespace kri_map;

/////////////////
//Utility funcs//
/////////////////
std::ostream& kri_map::operator<<(std::ostream& out, const Indiv &d){
    out << d.getName() << "(Type: " << d.getType() <<")" << std::endl;
    return out;
}
string kri_map::operator+(const string& s, const Indiv& indiv){
    return indiv.getName()+s;
}
string kri_map::operator+(const Indiv& indiv, const string& s){
    return indiv.getName()+s;
}



///////////////////
//Methods for KRI//
///////////////////
KRI::KRI(const shared_ptr<krl_map::KRL>& krl,
         const vector<vector<string>>& indivs_info)
        :krl_(krl)
{
    for(const vector<string>& info:indivs_info){
        this->domain_.push_back(make_shared<Indiv>(this->next_indiv_id, info[0], info[1]));
        this->indiv_by_name[info[0]] = this->domain_[this->next_indiv_id];
        ++(this->next_indiv_id);
    }
};

//////////////////////////////////////
//           Indiv Edit             //
//////////////////////////////////////
void KRI::updateIndivName(std::string from, std::string to)
{
    std::string d_id = this->indiv_by_name[from].lock()->getID();
    this->domain_[stoi(d_id)]->setName(to);
}

//////////////////////////////////////
//       Add mapping info           //
//////////////////////////////////////
void KRI::addConstMap(const std::weak_ptr<krl_map::ConstExpr>& const_expr,
                      const std::weak_ptr<Indiv>& d){
    this->const_id_to_indiv[const_expr.lock()->getID()] = d;
}

void KRI::addFuncMap(const weak_ptr<krl_map::Func>& function,
                     const vector<weak_ptr<Indiv>>& src,
                     const vector<weak_ptr<Indiv>>& target)
{
    std::string func_id(function.lock()->getID());
    if(this->func_maps_.find(func_id) == this->func_maps_.end()){
        //if func does not exis
        this->func_maps_[func_id] = std::make_shared<FuncMap>(); //Change this to shared ptr.
    }
    this->func_maps_[func_id]->addMapping(src, target);
}
void KRI::addPredMap(const std::weak_ptr<krl_map::Pred>& pred,
                const std::vector<std::weak_ptr<Indiv>>& src,
                const bool& target)
{
    std::string pred_id(pred.lock()->getID());
    if(this->pred_maps_.find(pred_id) == this->pred_maps_.end()){
        this->pred_maps_[pred_id] = std::make_shared<PredMap>();
    }
    this->pred_maps_[pred_id]->addMapping(src, target);
}
//////////////////////////////////////
//Methods for each I(term) Interpret//
//////////////////////////////////////
vector<weak_ptr<Indiv>> KRI::I(const krl_map::ConstExpr* const_expr){
    return {this->const_id_to_indiv[const_expr->getID()]};
}
vector<weak_ptr<Indiv>> KRI::I(const krl_map::Expr* expr){
    //
    /*
    std::string indivs_key("");
    for(weak_ptr<krl_map::Term> & e:expr->getTerms()){
        weak_ptr<Indiv> d = I((e.lock()).get(),(e.lock())->getType()); //recursion
        indivs_key = indivs_key + d.lock()->getName() + "_";
    }
    indivs_key.pop_back();
    */
    vector<weak_ptr<Indiv>> indivs;
    for(weak_ptr<krl_map::Term>& term:expr->getTerms()){
        vector<weak_ptr<Indiv>> temp_indivs = I(term.lock().get(),term.lock()->getType());
        for(weak_ptr<Indiv>& d:temp_indivs){
            indivs.push_back(d);
        }
    }
    //
    //Recursively interpret all the term/expr into individuals
    //concatenate names into one string and use as "key"
    return (*(this->func_maps_[expr->getFuncId()]))[indivs]; //expr has an id????
}
vector<weak_ptr<Indiv>> KRI::I(const krl_map::Var* var){

}
vector<weak_ptr<Indiv>> KRI::I(krl_map::Term* t, string type){
    if (type=="ConstExpr"){
        return this->I(dynamic_cast<krl_map::ConstExpr *>(t)); //IS THIS SAFE?
    }else if(type=="Expr"){
        return this->I(dynamic_cast<krl_map::Expr *>(t)); //IS THIS SAFE?
    }else if(type=="Var"){
        return this->I(dynamic_cast<krl_map::Var *>(t)); //
    }
}


////////////////////////////////////
// Smart ptr version I(term)      //
////////////////////////////////////
vector<weak_ptr<Indiv>> KRI::I(const weak_ptr<krl_map::Term>& term, const std::string& type)
{
    if (type=="ConstExpr"){
        return this->I(dynamic_pointer_cast<krl_map::ConstExpr>(term.lock())); //IS THIS SAFE?
    }else if(type=="Expr"){
        return this->I(dynamic_pointer_cast<krl_map::Expr>(term.lock())); //IS THIS SAFE?
    }else if(type=="Var"){
        return this->I(dynamic_pointer_cast<krl_map::Var>(term.lock())); //
    }
}
vector<weak_ptr<Indiv>> KRI::I(const weak_ptr<krl_map::ConstExpr>& const_expr)
{
    return {this->const_id_to_indiv[const_expr.lock()->getID()]};
}
vector<weak_ptr<Indiv>> KRI::I(const weak_ptr<krl_map::Var>& var){

}
vector<weak_ptr<Indiv>> KRI::I(const weak_ptr<krl_map::Expr>& expr){
    vector<weak_ptr<Indiv>> indivs;
    for(weak_ptr<krl_map::Term>& term:expr.lock()->getTerms()){
        vector<weak_ptr<Indiv>> temp_indivs = this->I(term, term.lock()->getType());
        for(weak_ptr<Indiv>& d:temp_indivs){
            indivs.push_back(d);
        }
    }
    return (*(this->func_maps_[expr.lock()->getFuncId()]))[indivs];
}

////////////////////////////////////
// Smart ptr version I(formula)   //
////////////////////////////////////
bool KRI::I(const weak_ptr<krl_map::Formula>& formula, const string& type)
{
    if(type == "AtomF"){
        return this->I(dynamic_pointer_cast<krl_map::AtomF>(formula.lock()));
    }
}
bool KRI::I(const weak_ptr<krl_map::AtomF>& atom_f)
{
    vector<weak_ptr<Indiv>> indivs;
    for(weak_ptr<krl_map::Term>& term:atom_f.lock()->getTerms()){
        vector<weak_ptr<Indiv>> temp_indivs = this->I(term, term.lock()->getType());
        for(weak_ptr<Indiv>& d:temp_indivs){
            indivs.push_back(d);
        }
    }
    return (*(this->pred_maps_[atom_f.lock()->getPredId()]))[indivs];
}
