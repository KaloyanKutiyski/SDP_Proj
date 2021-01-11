#pragma once
#include"../Object/object.hpp"
#include<fstream>
#include<stack>

class JsonFile {
    Object* root;

    //!correct indentation for non-concise printing
    void printNTabs(const size_t&, std::ostream&)const;
    
    //!used to make sure that files and strings are propperly balanced in terms of brackets and quotes
    bool sourceIsBalanced(std::istream&)const;
    bool fileIsBalanced(const std::string&)const;
    bool stringIsBalanced(const std::string&)const;
    
    Object* get(Object*, const std::string&)const;
    Object* get(const std::string&)const;
    
    //!generates objects from input. deletes allocated memory and throws and exception in case of invalid input.
    Object* parse(std::istream&);

    //!helper method to parse. keeps track of quotations and escaped symbols
    void addToBucket(std::string&, const char&, bool&, bool&);

    //!creates a new object from the bucket in the method parse when there is enough data
    bool tryToCreateNewObject(std::string&, std::stack<Object*>&);

    //!generates a vector of those elements written under the given key
    std::vector<Object*> findByKey(const std::string& key)const;

    //!called by the public overloads
    void print(Object*, std::ostream&, const bool&)const;

    //!creates an array out of a primitive, preserving its old value under index 0.
    //!used when objects are added to a primitive
    void upliftPrimitive(Object*, const std::string&);

    //!carries the extra data needed by the public overload
    void createFromIndex(Object*, const std::string&, const std::string&);


    public:
    JsonFile();
    ~JsonFile();
    void load(const std::string&);
    
    //!parses the string into an object and adds it to a selected element using a specified key
    void attachObjectFromString(const std::string&, const std::string&, const std::string&);

    //!removes a subtree. can preserve the dynamic memory if the subtree is meing moved, otherwise it is deleted
    void removeElement(const std::string&, const bool&);
    
    //!moves the subtree of an element to another subtree. can be added with a (in case of the ui) user specified name
    void moveElement(const std::string&, const std::string&, const std::string&);

    //!sorts a specified single type array of primitives
    void sortArray(const std::string&);

    //!saves/prints all elenments with a certain name
    void getAllByKey(const std::string&, const std::string&)const;
    //!saves/prints one element of a given name
    void getNthByKey(const std::string&, const int&, const std::string&)const;

    //!replaces the given element with what is parsed from the string
    void changeElement(const std::string&, const std::string&);

    //!bonus feature. generates composites based off a key;
    void createFromIndex(const std::string&);

    //!print to file
    void print(const std::string&, std::ostream&, const bool&)const;
    //!print to console
    void print(const std::string&, const bool&)const;
    //!print to string. used for tests
    void print(const std::string&, std::string&, const bool&)const;
};