#pragma once
#include<vector>
#include<string>
#include<iostream>

enum Type {COMPOSITE, PRIMITIVE, ARRAY};

class Object {
    public:
    //!used for retrieving data from primitive objects;
    virtual std::string toString()const = 0;

    virtual ~Object() {};
    virtual void addChild(const std::string&, Object*) = 0;
    virtual Type getType()const = 0;

    //!used for printing arrays' and composites' subelements in correct order. returns pair of name and value
    virtual std::pair<std::string, Object*> getNth(const int&) = 0;

    virtual std::string opener()const = 0;
    virtual std::string closer()const = 0;
    virtual void destroy() = 0;

    //!accesses subobjects from composites by key and from arrays by index
    virtual Object* get(const std::string&) = 0;

    //!removes a subobject. has a soft deletion mode where the dynamic memory is not deleted. soft mode used only in moving objects.
    virtual void remove(const std::string&, const bool&) = 0;

    //!sorts arrays containing only primitives of the same type;
    virtual void sort() = 0;
    //!if a composite has a subobject with the selected key it is added to the vector
    virtual void findByKeyHelper(const std::string&, std::vector<Object*>&)const = 0;
    virtual int getSize()const = 0;

    //!these static methods are used for sorting arrays

    static bool allArePrimitive(Object*);
    static bool allAreBooleans(Object*);
    static bool allAreNumbers(Object*);
    static bool allAreStrings(Object*);
    static bool valueComparator(const Object*, const Object*);
};
