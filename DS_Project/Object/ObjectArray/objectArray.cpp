#pragma once
#include"objectArray.hpp"
#include<regex>
#include<algorithm>

std::string ObjectArray::toString()const {
    return "";
}

void ObjectArray::addChild (const std::string& str, Object* obj) {
    subObjects.push_back(obj);
}

Type ObjectArray::getType()const {
    return ARRAY;
}

std::pair<std::string, Object*> ObjectArray::getNth(const int& index) {
    if (index < subObjects.size()) {
        return std::make_pair("", subObjects[index]);
    }
    return std::make_pair("", nullptr);
}

std::string ObjectArray::opener()const {
    return "[";
}
std::string ObjectArray::closer()const {
    return "]";
}

void ObjectArray::destroy() {
    for (Object* elem : subObjects) {
        elem->destroy();
        delete elem;
    }
    subObjects.clear();
}

Object* ObjectArray::get(const std::string& query) {
    std::regex number("0|([1-9]\\d*)");
    if (std::regex_match(query, number)) {
        int index = std::stoi(query);
        if (index < subObjects.size()) {
            return subObjects[index];
        }
        return nullptr;
    }
    return nullptr;
}

void ObjectArray::remove(const std::string& str, const bool& destroyMode) {
    if (get(str)) {
        if (destroyMode) {
            get(str)->destroy();
            delete get(str);
        }
        subObjects.erase(subObjects.begin() + std::stoi(str));
    }
}

void ObjectArray::sort() {
    if (subObjects.size() < 2
        || !Object::allArePrimitive(this)
        || !(Object::allAreBooleans(this)
        || Object::allAreStrings(this)
        || Object::allAreNumbers(this))) {
        return;
    }
    std::sort(subObjects.begin(), subObjects.end(), Object::valueComparator);
}

void ObjectArray::findByKeyHelper(const std::string& key, std::vector<Object*>& results)const {
    for (Object* subObject : subObjects) {
        subObject->findByKeyHelper(key, results);
    }
}
