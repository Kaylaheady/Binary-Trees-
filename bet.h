#ifndef BET_H
#define BET_H

#include <string>

class BET {
private:
    struct BinaryNode {
        std::string element;
        BinaryNode* left;
        BinaryNode* right;

        BinaryNode(const std::string& e, BinaryNode* l = nullptr, BinaryNode* r = nullptr)
                : element(e), left(l), right(r) {}
    };

    BinaryNode* root;

    void printInfixExpression(BinaryNode* n);
    void makeEmpty(BinaryNode* &t);
    BinaryNode* clone(BinaryNode* t);
    void printPostfixExpression(BinaryNode* n);
    size_t size(BinaryNode *t);
    size_t leaf_nodes(BinaryNode *t);

public:
    BET();
    explicit BET(const std::string& postfix);
    BET(const BET&);
    ~BET();
    bool buildFromPostfix(const std::string& postfix);
    BET& operator=(const BET&);
    void printInfixExpression();
    void printPostfixExpression();
    size_t size();
    size_t leaf_nodes();
    bool empty();
};
#include "bet.hpp"
#endif /* BET_H */
