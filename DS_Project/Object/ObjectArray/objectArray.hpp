#pragma once
#include"../object.hpp"

class ObjectArray: public Object {
    std::vector<Object*> subObjects;

    public: 
    ObjectArray() = default;
    std::string toString()const;
    void addChild (const std::string&, Object*);
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