#include "bet.h"
#include <iostream>
#include <sstream>
#include <stack>

BET::BET() : root(nullptr) {}

BET::BET(const std::string& postfix) : root(nullptr) {
    buildFromPostfix(postfix);
}

BET::BET(const BET& rhs) : root(clone(rhs.root)) {}

BET::~BET() {
    makeEmpty(root);
}

bool BET::buildFromPostfix(const std::string& postfix) {
    std::stack<BinaryNode*> st;
    std::string token;
    std::istringstream iss(postfix);
    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (st.size() < 2) {
                makeEmpty(root);
                return false;
            }
            BinaryNode* right = st.top();
            st.pop();
            BinaryNode* left = st.top();
            st.pop();
            st.push(new BinaryNode(token, left, right));
        } else {
            st.push(new BinaryNode(token));
        }
    }
    if (st.size() != 1) {
        makeEmpty(root);
        return false;
    }
    root = st.top();
    return true;
}

BET& BET::operator=(const BET& rhs) {
    if (this != &rhs) {
        makeEmpty(root);
        root = clone(rhs.root);
    }
    return *this;
}

void BET::printInfixExpression() {
    printInfixExpression(root);
    std::cout << std::endl;
}

void BET::printPostfixExpression() {
    printPostfixExpression(root);
    std::cout << std::endl;
}

size_t BET::size() {
    return size(root);
}

size_t BET::leaf_nodes() {
    return leaf_nodes(root);
}

bool BET::empty() {
    return root == nullptr;
}

void BET::printInfixExpression(BinaryNode* n) {
    if (n != nullptr) {
        if (n->left != nullptr && (n->element == "*" || n->element == "/")) {
            std::cout << "(";
            printInfixExpression(n->left);
            std::cout << ")";
        } else {
            printInfixExpression(n->left);
        }

        std::cout << n->element;

        if (n->right != nullptr && (n->element == "*" || n->element == "/")) {
            std::cout << "(";
            printInfixExpression(n->right);
            std::cout << ")";
        } else {
           printInfixExpression(n->right);
        }
    }
}


void BET::makeEmpty(BinaryNode* &t) {

    if(t!=nullptr){
        makeEmpty( t-> left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

BET::BinaryNode* BET::clone(BinaryNode* t) {
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

void BET::printPostfixExpression(BinaryNode* n) {
    if (n != nullptr) {
        printPostfixExpression(n->left);
        printPostfixExpression(n->right);
        std::cout << n->element << " ";
    }
}

size_t BET::size(BinaryNode* t) {
    if (t == nullptr)
        return 0;
    else
        return 1 + size(t->left) + size(t->right);
}

size_t BET::leaf_nodes(BinaryNode* t) {
    if (t == nullptr)
        return 0;
    else if (t->left == nullptr && t->right == nullptr)
        return 1;
    else
        return leaf_nodes(t->left) + leaf_nodes(t->right);
}
