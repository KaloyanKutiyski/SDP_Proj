#pragma once
#include"../JSON_File/JsonFile.hpp"

class UI {
    bool hasFile;
    JsonFile file;
    std::string filePath;
    std::string beginMessage;
    std::string endMessage;
    std::string helpMessage;
    std::string errorMessage;


    void trim(std::string&)const;
    std::string lower(const std::string&)const;
    std::string splitOff(std::string&, const bool&)const;
    bool isAllNum(const std::string&)const;

    void save(std::string&)const;
    void print(std::string&)const;
    void keySearch(std::string&)const;
    void attachElement(std::string&);
    void changeElement(std::string&);
    void deleteElement(std::string&);
    void moveElement(std::string&);
    void sort(std::string&);

    public:
    UI();
    void parseCommand(std::string&);
    void run();
};