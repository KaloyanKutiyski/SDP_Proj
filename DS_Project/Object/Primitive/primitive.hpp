#pragma once
#include"../object.hpp"
class Primitive: public Object {
    std::string val;

    public:
    Primitive() = default;
    Primitive(const std::string&);
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
};