#pragma once
#include"../JSON_File/JsonFile.hpp"

class UI {
    bool hasFile;
    JsonFile file;

    static const std::string beginMessage;
    static const std::string endMessage;
    static const std::string helpMessage;

    //!used for saving changes to the same file
    std::string filePath;

    //!removes leading and trailing whitespaces
    void trim(std::string&)const;
    std::string lower(const std::string&)const;
    
    //! used to separate a word from the beginning of a string without using stringstreams
    std::string splitOff(std::string&, const bool&)const;
    
    bool isAllNum(const std::string&)const;

    void save(std::string&)const;
    void savePart(std::string&)const;
    void print(std::string&)const;
    void find(std::string&)const;
    void create(std::string&);
    void change(std::string&);
    void remove(std::string&);
    void move(std::string&);
    void sort(std::string&);
    void generate(std::string&);

    public:
    UI();
    void parseCommand(std::string&);
    //!will run accept commands until 'quit' input
    void run();
};