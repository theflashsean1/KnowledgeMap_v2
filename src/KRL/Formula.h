//
// Created by akira on 6/17/17.
//

#ifndef KNOWLEDGEMAP_FORMULA_H
#define KNOWLEDGEMAP_FORMULA_H

#include <string>
#include <memory>
#include <iostream>
#include <vector>
#include "PrimitiveSymbol.h"
namespace krl_map{
    class Term;
    class Var;

    class Formula{
    private:
        std::size_t id_;
    public:
        Formula()
        {
        }
        Formula(size_t id)
                :id_(id)
        {
        }
        virtual Formula* derive()
        {
            return this;
        }
        virtual std::string getType() const
        {
            return "Formula";
        }
        std::string  getID() const
        {
            return std::to_string(id_);
        }
    };

    class AtomF:public Formula{
    private:
        std::weak_ptr<Pred> p_;
        std::vector<std::weak_ptr<Term>> terms_;
    public:
        AtomF(const std::size_t & id,
              const std::weak_ptr<Pred>& p,
              const std::vector<std::weak_ptr<Term>>& terms
        );
        ~AtomF()
        {
            std::cout << "AtomF: destroyed" << std::endl;
        }
        virtual AtomF* derive() override
        {
            return this;
        }
        virtual std::string getType() const override
        {
            return "AtomF";
        }
        std::string getPredId() const
        {
            return this->p_.lock()->getID();
        }
        std::vector<std::weak_ptr<Term>> getTerms() const
        {
            return this->terms_;
        }
    };

    class NegatedF:public Formula{
    private:
        std::weak_ptr<Formula> f_;
    public:
        NegatedF(const std::shared_ptr<Formula>& f):f_(f)
        {
        }
        ~NegatedF(){printf("NegatedF destructed");}
        virtual NegatedF* derive() override{ return this;}
    };
    std::shared_ptr<NegatedF> operator!(const std::shared_ptr<Formula> &f);

    class AndF:public Formula{
    private:
        std::weak_ptr<Formula> f1_;
        std::weak_ptr<Formula> f2_;
    public:
        AndF(const std::shared_ptr<Formula> &f1, const std::shared_ptr<Formula> &f2):
                f1_(f1), f2_(f2)
        {
        }
        ~AndF(){printf("AndF destructed");}
        virtual AndF* derive() override {return this;}
    };
    std::shared_ptr<AndF> operator&&(const std::shared_ptr<Formula>& f1, const std::shared_ptr<Formula>& f2);


    class OrF:public Formula{
    private:
        std::weak_ptr<Formula> f1_;
        std::weak_ptr<Formula> f2_;
    public:
        OrF(const std::shared_ptr<Formula>& f1, const std::shared_ptr<Formula>& f2):
                f1_(f1), f2_(f2)
        {
        }
        ~OrF(){printf("OrF destrcuted");}
        virtual OrF* derive() override {return this;}
    };
    std::shared_ptr<OrF> operator||(const std::shared_ptr<Formula> &f1, const std::shared_ptr<Formula> &f2);


    class ExistF:public Formula{
    private:
        std::weak_ptr<Formula> f1_;
        std::weak_ptr<Var> V_;
    public:
        virtual ExistF* derive() override {return this;}
    };

    class ForAllF:public Formula{
    private:
        std::weak_ptr<Formula> f1_;
        std::weak_ptr<Var> V_;
    public:
        virtual ForAllF* derive() override {return this;}
    };


}
#endif //KNOWLEDGEMAP_FORMULA_H
