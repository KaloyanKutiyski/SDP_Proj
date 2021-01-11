#pragma once
#include"object.hpp"
#include"../Util/RegexUtil.hpp"
#include<cassert>

bool Object::allArePrimitive(Object* object) {
    if (object->getType() == PRIMITIVE) {
        return false;
    }
    int index = 0;
    while (object->getNth(index).second != nullptr) {
        if (object->getNth(index).second->getType() != PRIMITIVE) {
            return false;
        }
        index++;
    }
    return true;
}

bool Object::allAreBooleans(Object* object) {
    int index = 0;
    while (object->getNth(index).second != nullptr) {
        if (!(object->getNth(index).second->toString() == "true"
            || object->getNth(index).second->toString() == "false"
            || object->getNth(index).second->toString() == "null")) {
            return false;
        }
        index++;
    }
    return true;
}

bool Object::allAreNumbers(Object* object) {
    int index = 0;
    while (object->getNth(index).second != nullptr) {
        char first = object->getNth(index).second->toString().front();
        if (!(first == '-') && !isdigit(first) && !(object->getNth(index).second->toString() == "null")) {
            return false;
        }
        index++;
    }
    return true;
}

bool Object::allAreStrings(Object* object) {
    int index = 0;
    while (object->getNth(index).second != nullptr) {
        if (!(object->getNth(index).second->toString()[0] == '\"'
            || object->getNth(index).second->toString() == "null")) {
            return false;
        }
        index++;
    }
    return true;
}

bool Object::valueComparator(const Object* first, const Object* second) {
    std::string left = first->toString();
    std::string right = second->toString();

    //!nulls get pushed at the end of an array;
    if (right == "null") {
        return true;
    } else if (left == "null") {
        return right == "null";
    }

    else if (left == "false" || right == "true") {
        return true;
    } else if (left == "true" && right == "false") {
        return false;
    }
    
    else if (left.front() == '\"') {
        return strcmp(left.c_str(), right.c_str()) <= 0; 
    }
    
    else if (isdigit(left.front()) || left.front() == '-') {
        return RegexUtil::valueOfNumericString(left) <= RegexUtil::valueOfNumericString(right);
    }

    return true;
}