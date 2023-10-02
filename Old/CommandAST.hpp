#ifndef COMANDAST_HPP
#define COMANDAST_HPP

#include <string>
#include <vector>

#include "CommandRegistry.hpp"

enum class ValueType {
    INTEGER,
    DOUBLE,
    BOOL,
    NONE
};

struct Value {
    ValueType type;
    union {
        int intValue;
        double doubleValue;
        bool boolValue;
    };
};

struct OperatorTreeNode {
    OperandTreeNode* left;
    OperandTreeNode* right;


};

struct OperandTreeNode {

};

class CommandAST {


};

#endif