#include <iostream>
#include "src/KRI.h"

using namespace std;
size_t kri_map::KRI::next_indiv_id = 0;
size_t krl_map::KRL::next_symbol_id = 0;
size_t krl_map::KRL::next_term_id = 0;
size_t krl_map::KRL::next_formula_id = 0;

int main() {


    //L(F, P, V)
    shared_ptr<krl_map::KRL> language = make_shared<krl_map::KRL>();
    language->addConst("son");
    language->addConst("father");
    language->addConst("grandpa");

    language->addFunc("FatherOf",1);

    ////////////Terms///////////////
    //term name, term type, content_keys
    language->addTerm("son_key", "ConstExpr", {"son"});
    language->addTerm("father_key", "ConstExpr", {"father"});
    language->addTerm("grandpa_key", "ConstExpr", {"grandpa"});

    //For Expr,        term key       term type    content "KEYS"
    language->addTerm("father_of_son_key", "Expr", {"FatherOf", "son_key"});
    language->addTerm("father_of_father_key", "Expr", {"FatherOf", "father_of_son_key"});


    ////////////Formulas/////////////
    language->addPred("like", 2);


    //I(D, Phi, Psi, v)

    //For individuals, key names are exactly the same as their names
    kri_map::KRI semantics(
            language,
            {
                    vector<string>{"sean","kid"},
                    vector<string>{"tom", "parent"},
                    vector<string>{"albert", "grandparent"}
            }
    );

    semantics.addConstMap(
            dynamic_pointer_cast<krl_map::ConstExpr>(language->getTerm("son_key").lock()),
            semantics.getIndiv("sean")
    );
    semantics.addConstMap(
            dynamic_pointer_cast<krl_map::ConstExpr>(language->getTerm("father_key").lock()),
            semantics.getIndiv("tom")
    );
    semantics.addConstMap(
            dynamic_pointer_cast<krl_map::ConstExpr>(language->getTerm("grandpa_key").lock()),
            semantics.getIndiv("albert")
    );

    semantics.addFuncMap(
            language->getFunc("FatherOf"),
            {semantics.getIndiv("sean")},
            {semantics.getIndiv("tom")}
    );

    semantics.addFuncMap(
            language->getFunc("FatherOf"),
            {semantics.getIndiv("tom")},
            {semantics.getIndiv("albert")}
    );

    //TODO State some formulas, and make I that satisfy those formulas

    weak_ptr<krl_map::Term> expr1 = language->getTerm("father_of_father_key");
    cout<<*(semantics.I(expr1.lock().get(),expr1.lock()->getType())[0].lock());

    semantics.updateIndivName("albert","kitty");
    semantics.updateIndivName("sean","kessel");
    cout<<*(semantics.I(expr1, expr1.lock()->getType())[0].lock());
    //Edit Indiv
    //When Individual name changes,
    //1. The individual that func maps to automatically updated as it is a ptr.
    //2. However, the concatenated "key" and lookup table used_in for FuncName that has this individual has to be updated.
    //d0->setName("butler");
    //sematics1.updateIndivName("sean", "butler");
    //Remove Indiv

    //Override Indiv


    //Edit Func


    //Apply Interpretation
    //auto a = (*expr1).derive();
    //krl_map::Expr *a = dynamic_cast<krl_map::Expr *>(expr1.get());
    //krl_map::Expr *a = dynamic_cast<krl_map::Var *>(expr1.get());
    //auto a = expr1->derive();
    //krl_map::Expr * a = expr1->derive();

    //Interpret an expression


    //Interpret a formula


    return 0;
}