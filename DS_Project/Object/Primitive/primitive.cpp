#pragma once
#include"primitive.hpp"
#include<assert.h>
#include"../../Util/RegexUtil.hpp"

std::string Primitive::toString()const {
    return val;
}

Primitive::Primitive(const std::string& string): val{string} {
}

Type Primitive::getType()const {
    return PRIMITIVE;
}

std::pair<std::string, Object*> Primitive::getNth(const int& index) {
    return std::make_pair(val, nullptr);
}

std::string Primitive::opener()const {
    return "";
}
std::string Primitive::closer()const {
    return "";
}

void Primitive::destroy() {
    val.clear();
}

Object* Primitive::get(const std::string& query) {
    return nullptr;
}

void Primitive::remove(const std::string& str, const bool& destroyMode) {
}

void Primitive::addChild(const std::string&, Object*){
}

void Primitive::sort(){
}

void Primitive::findByKeyHelper(const std::string& key, std::vector<Object*>& results)const {
}
