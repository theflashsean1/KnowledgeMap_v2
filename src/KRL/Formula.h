//
// Created by akira on 6/17/17.
//

#ifndef KNOWLEDGEMAP_FORMULA_H
#define KNOWLEDGEMAP_FORMULA_H

#include <string>
#include <memory>
#include <iostream>
#include <vector>

namespace krl_map{
    class Pred;
    class Term;
    class Var;


    class Formula{
    private:
    public:
        virtual Formula* derive(){return this;}
        //
    };

    class AtomF:public Formula{
    private:
        std::weak_ptr<Pred> p_;
        std::vector<std::weak_ptr<Term>> terms_;
    public:
        AtomF(const std::shared_ptr<Pred>& p, const std::vector<std::shared_ptr<Term>>& terms);
        ~AtomF(){printf("AtomF desctructed");}
        virtual AtomF* derive() override{ return this;}
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
