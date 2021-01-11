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
    void run();
};