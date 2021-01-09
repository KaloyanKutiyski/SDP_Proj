#pragma once
#include"../Object/object.hpp"
#include<fstream>
#include<stack>

class JsonFile {
    Object* root;

    void printNTabs(const size_t&, std::ostream&)const;
    bool fileIsBalanced(const std::string&)const;
    bool sourceIsBalanced(std::istream&)const;
    bool stringIsBalanced(const std::string&)const;
    Object* get(Object*, const std::string&)const;
    Object* get(const std::string&)const;
    Object* parse(std::istream&);
    std::vector<Object*> findByKey(const std::string& key)const;
    void print(Object*, std::ostream&, const bool&)const;
    void upliftPrimitive(Object*, const std::string&);
    void addToBucket(std::string&, const char&, bool&, bool&);
    void tryToCreateNewObject(std::string&, std::stack<Object*>&);


    public:
    JsonFile();
    ~JsonFile();
    void load(const std::string&);
    
    void attachObjectFromString(const std::string&, const std::string&, const std::string&);
    void removeElement(const std::string&, const bool&);
    void moveElement(const std::string&, const std::string&);
    void sortArray(const std::string&);
    void getAllByKey(const std::string&, const std::string&)const;
    void getNthByKey(const std::string&, const int&, const std::string&)const;
    void changeElement(const std::string&, const std::string&);

    void print(const std::string&, std::ostream&, const bool&)const;
    void print(const std::string&, const bool&)const;
    void print(const std::string&, std::string&, const bool&)const;
};