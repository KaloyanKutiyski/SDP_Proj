#pragma once
#include<unordered_map>
#include"../object.hpp"
class Composite: public Object {
    std::unordered_map<std::string, Object*> subObjects;
    std::vector<std::string> insertionOrder;
    void constructorHelper(const std::string&);

    public:
    Composite() = default;
    std::string toString()const;
    void addChild(const std::string&, Object*);
    Type getType()const;
    std::pair<std::string, Object*> getNth(const int&);
    std::string opener()const;
    std::string closer()const;
    void destroy();
    Object* get(const std::string&);
    void remove(const std::string&, const bool&);
    void sort();
    void findByKeyHelper(const std::string&, std::vector<Object*>&)const;
    int getSize()const;

};