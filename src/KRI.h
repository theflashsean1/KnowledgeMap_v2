//
// Created by Akira on 2017-06-03.
//
#ifndef KNOWLEDGEMAP_KRI_H
#define KNOWLEDGEMAP_KRI_H
#include <vector>
#include <unordered_map>
#include <string>
#include <tuple>
#include <iostream>
#include <memory>
#include <algorithm>
#include "KRL.h"
#include "KRI/Indiv.h"
#include "KRI/FuncMap.h"
#include "KRI/PredMap.h"
#include "KRI/VarAssign.h"
namespace kri_map{
    class KRI {
    private:
        std::weak_ptr<krl_map::KRL> krl_;

        std::vector<std::shared_ptr<Indiv>> domain_;
        std::unordered_map<std::string, std::weak_ptr<Indiv>> indiv_by_name;

        //"const expr(term) id" -> Individual
        std::unordered_map<std::string, std::weak_ptr<Indiv>> const_id_to_indiv;

        //func_id -> FuncMap ,        FuncMap(indivs -> indivs)
        std::unordered_map<std::string, std::shared_ptr<FuncMap>> func_maps_;

        //pred_id -> PredMap          PredMap(indivs -> T/F)
        std::unordered_map<std::string, std::shared_ptr<PredMap>> pred_maps_;

        //"Var (term)
        //std::unordered_map<std::string, VarAssign> var_assigns_;

    public:
        static size_t next_indiv_id;
        KRI(){};
        KRI(const std::shared_ptr<krl_map::KRL>& language,
            const std::vector<std::vector<std::string>>& indivs_info);


        //Getters
        std::weak_ptr<Indiv> getIndiv(const std::size_t & id) const
        {
            return this->domain_.at(id);
        }
        std::weak_ptr<Indiv> getIndiv(const std::string & name) const
        {
            return this->indiv_by_name.at(name);
        }

        //Edit Individuals
        void updateIndivName(std::string from, std::string to);




        void addConstMap(const std::weak_ptr<krl_map::ConstExpr>& const_expr,
                         const std::weak_ptr<Indiv>& d);
        void addFuncMap(const std::weak_ptr<krl_map::Func>& function,
                        const std::vector<std::weak_ptr<Indiv>>& src,
                        const std::vector<std::weak_ptr<Indiv>>& target);
        void addPredMap(const std::weak_ptr<krl_map::Pred>& pred,
                        const std::vector<std::weak_ptr<Indiv>>& src,
                        const bool& target);

        void updateFuncMapName(std::string from, std::string to);


        bool I(const krl_map::Formula*, std::string type);
        bool I(const krl_map::AtomF*);
        bool I(const krl_map::NegatedF*);
        bool I(const krl_map::AndF*);
        bool I(const krl_map::OrF*);
        bool I(const krl_map::ExistF*);
        bool I(const krl_map::ForAllF*);

        bool I(const std::weak_ptr<krl_map::Formula>& formula, const std::string& type);
        bool I(const std::weak_ptr<krl_map::AtomF>& atom_f);

        std::vector<std::weak_ptr<Indiv>> I(const std::weak_ptr<krl_map::Term>& term, const std::string& type);
        std::vector<std::weak_ptr<Indiv>> I(const std::weak_ptr<krl_map::ConstExpr>& const_expr);
        std::vector<std::weak_ptr<Indiv>> I(const std::weak_ptr<krl_map::Var>& var);
        std::vector<std::weak_ptr<Indiv>> I(const std::weak_ptr<krl_map::Expr>& expr);

        std::vector<std::weak_ptr<Indiv>> I(krl_map::Term*, std::string type);
        std::vector<std::weak_ptr<Indiv>> I(const krl_map::ConstExpr*);
        std::vector<std::weak_ptr<Indiv>> I(const krl_map::Var*);
        std::vector<std::weak_ptr<Indiv>> I(const krl_map::Expr*);
        friend std::ostream& operator<<(std::ostream& out, const KRI &kr_i);

    };
    //size_t KRI::next_indiv_id = 0;

}

#endif //KNOWLEDGEMAP_KRI_H
