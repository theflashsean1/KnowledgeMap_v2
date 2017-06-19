//
// Created by akira on 6/17/17.
//

#ifndef KNOWLEDGEMAP_PRIMITIVESYMBOL_H
#define KNOWLEDGEMAP_PRIMITIVESYMBOL_H

#include <string>
#include <iostream>
namespace krl_map{
    class PrimitiveSymbol{
    private:
        std::string name_;
        std::size_t id_;
    public:
        PrimitiveSymbol(std::size_t id,std::string name)
                :name_(name), id_(id)
        {
        }
        std::string getID() const //TODO CONST
        {
            return std::to_string(id_);
        }
        std::string getName() const
        {
            return name_;
        }
    };
    class Const:public PrimitiveSymbol{
    public:
        Const():PrimitiveSymbol(0, "Unknown"){}
        Const(std::size_t id,std::string name)
                :PrimitiveSymbol(id, name)
        {
            std::cout<<"Const: " << name <<" created"<<std::endl;
        }
        ~Const()
        {
            std::cout<<"Const: "<<this->getName()<<" destroyed"<<std::endl;
        }
        friend std::ostream& operator<<(std::ostream& out, const Const &c);
    };
    class Func:public PrimitiveSymbol{
    private:
        unsigned short arity_;
    public:
        Func():PrimitiveSymbol(0,"Unknown"){}
        Func(std::size_t id,std::string name, unsigned short arity)
                :PrimitiveSymbol(id,name), arity_(arity)
        {
            std::cout<<"Func: "<<name <<" created"<<std::endl;
        }
        ~Func()
        {
            std::cout << "Func: " << this->getName() << " destroyed"<<std::endl;
        }
        friend std::ostream& operator<<(std::ostream& out, const Func &f);
    };
    class Pred:public PrimitiveSymbol{
    private:
        unsigned short arity_;
    public:
        Pred():PrimitiveSymbol(0,"Unknown"){}
        Pred(std::size_t id, std::string name, unsigned short arity)
                :PrimitiveSymbol(id,name), arity_(arity)
        {
        }
        friend std::ostream& operator<<(std::ostream& out, const Pred &p);
    };

}

#endif //KNOWLEDGEMAP_PRIMITIVESYMBOL_H
