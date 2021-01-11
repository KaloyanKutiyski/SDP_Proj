#pragma once
#include"composite.hpp"
#include<set>
#include"../../Util/RegexUtil.hpp"
#include<algorithm>

std::string Composite::toString()const {
    return "";
}

void Composite::addChild(const std::string& str, Object* obj) {
    insertionOrder.push_back(str);
    subObjects.insert(std::make_pair(str, obj));
}

Type Composite::getType()const {
    return COMPOSITE;
}

std::pair<std::string, Object*> Composite::getNth(const int& index) {
    if (index < subObjects.size()) {
        std::string key = insertionOrder[index];
        return std::make_pair(key + ":", subObjects.at(key));
    }
    return std::make_pair("", nullptr);
}

std::string Composite::opener()const {
    return "{";
}

std::string Composite::closer()const {
    return "}";
}

void Composite::destroy() {
    for (std::pair<std::string, Object*> pair : subObjects) {
        pair.second->destroy();
        delete pair.second;
    }
    subObjects.clear();
    insertionOrder.clear();
}

Object* Composite::get(const std::string& query) {
    if (subObjects.find(query) != subObjects.end()) {
        return subObjects.at(query);
    }
    return nullptr;
}

void Composite::remove(const std::string& str, const bool& destroyMode) {
    if (subObjects.find(str) != subObjects.end()) {

        if (destroyMode) {
            subObjects.find(str).operator*().second->destroy();
            delete subObjects.find(str).operator*().second;
        }
        subObjects.erase(str);

        int indexToDelete;
        for (int i = 0; i < insertionOrder.size(); i++) {
            if (insertionOrder[i] == str) {
                indexToDelete = i;
                break;
            }
        }
        insertionOrder.erase(insertionOrder.begin() + indexToDelete);
    }
}

void Composite::sort() {
}

void Composite::findByKeyHelper(const std::string& key, std::vector<Object*>& results)const {
    for (std::string subObjectKey : insertionOrder) {
        if (subObjectKey == key) {
            results.push_back(subObjects.at(key));
        }
        subObjects.at(subObjectKey)->findByKeyHelper(key, results);
    }
}

int Composite::getSize()const {
    return subObjects.size();
}
