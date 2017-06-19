//
// Created by akira on 6/17/17.
//

#ifndef KNOWLEDGEMAP_TERM_H
#define KNOWLEDGEMAP_TERM_H

#include <memory>
#include <vector>
#include "PrimitiveSymbol.h"
namespace krl_map{
    class Term{
    private:
        std::size_t id_;
    public:
        Term()
        {
        }
        Term(size_t id)
                :id_(id)
        {
        }
        virtual Term* derive()
        {
            return this;
        }
        virtual std::string getType()
        {
            return "Term";
        }
        std::string getID() const
        {
            return std::to_string(id_);
        }
    };

    class ConstExpr:public Term{
    private:
        std::weak_ptr<Const> c_;
    public:
        ConstExpr(const std::size_t& id, const std::shared_ptr<Const>& c)
                :Term(id), c_(c)
        {
            std::cout<<"ConstExpr: "<< c_.lock()->getName() <<" created"<<std::endl;
        }
        ~ConstExpr()
        {
            std::cout<<"ConstExpr: "<< c_.lock()->getName() <<" destroyed"<<std::endl;
        }
        virtual std::string getType()
        {
            return "ConstExpr";
        }
        std::string getSymbolStr() const
        {
            return (this->c_.lock())->getName();
        }
    };

    class Var:public Term{
    private:
        std::string symbol_;
    public:
        Var(const std::size_t& id, std::string symbol)
                :Term(id),symbol_(symbol)
        {
        }
        ~Var()
        {
            std::cout<<"Var destructed"<<std::endl;
        }
        virtual Var* derive() override
        {
            return this;
        }

        virtual std::string getType() override
        {
            return "Var";
        }
    };

    class Expr:public Term{
    private:
        std::weak_ptr<Func> f_;
        std::vector<std::weak_ptr<Term>> terms_;
    public:

        Expr(const std::size_t & id,
             const std::weak_ptr<Func>& f,
             const std::vector<std::weak_ptr<Term>>& terms);
        ~Expr()
        {
            std::cout<<"Expr: "<< f_.lock()->getName() <<" destroyed"<<std::endl;
        }
        virtual Expr* derive() override {
            std::cout<<"derived"<<std::endl;
            Expr* temp = dynamic_cast<Expr *>(this);
            return temp;
        }
        virtual std::string getType() override
        {
            return "Expr";
        }
        std::string getSymbolStr() const
        {
            return (this->f_.lock())->getName();
        }
        std::string getFuncId() const
        {
            return (this->f_.lock())->getID();
        }
        std::vector<std::weak_ptr<Term>> getTerms() const
        {
            return this->terms_;
        }
    };

}


#endif //KNOWLEDGEMAP_TERM_H
