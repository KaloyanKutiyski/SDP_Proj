#pragma once
#include<vector>
#include<string>
#include<iostream>

enum Type {COMPOSITE, PRIMITIVE, ARRAY};

class Object {
    public:
    virtual std::string toString()const = 0;
    virtual ~Object() {};
    virtual void addChild(const std::string&, Object*) = 0;
    virtual Type getType()const = 0;
    virtual std::pair<std::string, Object*> getNth(const int&) = 0;
    virtual std::string opener()const = 0;
    virtual std::string closer()const = 0;
    virtual void destroy() = 0;
    virtual Object* get(const std::string&) = 0;
    virtual void remove(const std::string&, const bool&) = 0;
    virtual void sort() = 0;
    virtual void findByKeyHelper(const std::string&, std::vector<Object*>&)const = 0;

    static bool allArePrimitive(Object*);
    static bool allAreBooleans(Object*);
    static bool allAreNumbers(Object*);
    static bool allAreStrings(Object*);
    static bool valueComparator(const Object*, const Object*);
};
