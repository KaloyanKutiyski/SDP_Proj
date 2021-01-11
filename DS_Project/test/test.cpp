#pragma once
#define DOCTEST_CONFIG_IMPLEMENT
#include"doctest.h"
#include"../JSON_File/JsonFile.hpp"
#include<string>
#include<fstream>
#include<iostream>


TEST_CASE("test key search") {
    JsonFile json;
    json.load("jsonExample1.json");
    std::string result;
    
    SUBCASE("getAllTestNonEmpty") {
        json.getAllByKey("\"value\"", "search.json");
        std::ifstream in("search.json");
        while (in) {
            in >> result;
        }
        CHECK(result == "[\"File\",\"New\",\"Open\",\"Close\"]");
    }

    SUBCASE("getAllTestEmpty") {
        json.getAllByKey("\"none\"", "search.json");
        std::ifstream in("search.json");
        while (in) {
            in >> result;
        }
        CHECK(result == "[]");
    }

    SUBCASE("getFirst") {
        json.getNthByKey("\"value\"", 0, "search.json");
        std::ifstream in("search.json");
        while (in) {
            in >> result;
        }
        CHECK(result == "\"File\"");
    }
    SUBCASE("getSecond") {
        json.getNthByKey("\"value\"", 1, "search.json");
        std::ifstream in("search.json");
        while (in) {
            in >> result;
        }
        CHECK(result == "\"New\"");
    }   
    SUBCASE("getThird") {
        json.getNthByKey("\"value\"", 2, "search.json");
        std::ifstream in("search.json");
        while (in) {
            in >> result;
        }
        CHECK(result == "\"Open\"");
    }
    SUBCASE("getFourth") {
        json.getNthByKey("\"value\"", 3, "search.json");
        std::ifstream in("search.json");
        while (in) {
            in >> result;
        }
        CHECK(result == "\"Close\"");
    }
}

TEST_CASE("change object test") {
    JsonFile json;
    json.load("jsonExample1.json");
    std::string result;

    SUBCASE("change non-root") {
        json.changeElement("\"menu\".\"id\"", "{\"I AM NOW\":\"AN OBJECT\"}");
        json.print("\"menu\".\"id\"", result, true);
        CHECK(result == "{\"I AM NOW\":\"AN OBJECT\"}");
    }

    SUBCASE("change root") {
        json.changeElement("", "{\"LOOK AT ME\":\"I AM THE JSON NOW\"}");
        json.print("", result, true);
        CHECK(result == "{\"LOOK AT ME\":\"I AM THE JSON NOW\"}");
    }

    SUBCASE("change array") {
        json.changeElement("\"menu\".\"popup\".\"menuitem\".0", "null");
        json.print("\"menu\".\"popup\".\"menuitem\".0", result, true);
        CHECK(result == "null");

    }
}

TEST_CASE("Create object test") {
    JsonFile json;
    json.load("jsonExample1.json");
    std::string result;

    SUBCASE("to composite") {
        json.attachObjectFromString("\"some string\"", "\"menu\".\"popup\"", "\"test\"");
        json.print("\"menu\".\"popup\".\"test\"", result, true);
        CHECK(result == "\"some string\"");
    }
    SUBCASE("to array") {
        json.attachObjectFromString("1.2e3", "\"menu\".\"popup\".\"menuitem\"", "");
        json.print("\"menu\".\"popup\".\"menuitem\".3", result, true);
        CHECK(result == "1.2e3");
    }
    SUBCASE("to primitive") {
        json.attachObjectFromString("true", "\"menu\".\"id\"", "");
        json.print("\"menu\".\"id\"", result, true);
        CHECK(result == "[\"file\",true]");
    }
}

TEST_CASE("delete object") {
    JsonFile json;
    json.load("jsonExample1.json");
    std::string result;

    SUBCASE("from composite") {
        json.removeElement("\"menu\".\"popup\"", true);
        json.print("\"menu\"", result, true);
        CHECK(result == "{\"id\":\"file\",\"value\":\"File\"}");
    }
    SUBCASE("from array") {
        json.removeElement("\"menu\".\"popup\".\"menuitem\".1", true);
        json.print("\"menu\".\"popup\".\"menuitem\"", result, true);
        CHECK(result == "[{\"value\":\"New\",\"onclick\":\"CreateNewDoc()\"},{\"value\":\"Close\",\"onclick\":\"CloseDoc()\"}]");
    }
    SUBCASE("empty composite") {
        json.removeElement("\"menu\".\"popup\"", true);
        json.removeElement("\"menu\".\"id\"", true);
        json.removeElement("\"menu\".\"value\"", true);
        json.print("\"menu\"", result, true);
        CHECK(result == "{}");
    }
    SUBCASE("empty array") {
        json.removeElement("\"menu\".\"popup\".\"menuitem\".1", true);
        json.removeElement("\"menu\".\"popup\".\"menuitem\".1", true);
        json.removeElement("\"menu\".\"popup\".\"menuitem\".0", true);
        json.print("\"menu\".\"popup\".\"menuitem\"", result, true);
        CHECK(result == "[]");
    }
}

TEST_CASE("move element") {
    JsonFile json;
    json.load("jsonExample1.json");
    std::string result;

    SUBCASE("to array") {
        json.moveElement("\"menu\".\"id\"", "\"menu\".\"popup\".\"menuitem\"", "");
        json.print("\"menu\".\"popup\".\"menuitem\"", result, true);
        CHECK(result == "[{\"value\":\"New\",\"onclick\":\"CreateNewDoc()\"},{\"value\":\"Open\",\"onclick\":\"OpenDoc()\"},{\"value\":\"Close\",\"onclick\":\"CloseDoc()\"},\"file\"]");
    }

    SUBCASE("to composite") {
        json.moveElement("\"menu\".\"popup\".\"menuitem\"", "\"menu\"", "\"table\"");
        json.print("\"menu\".\"popup\"", result, true);
        CHECK(result == "{}");
        result.clear();
        json.print("\"menu\".\"table\"", result, true);
        CHECK(result == "[{\"value\":\"New\",\"onclick\":\"CreateNewDoc()\"},{\"value\":\"Open\",\"onclick\":\"OpenDoc()\"},{\"value\":\"Close\",\"onclick\":\"CloseDoc()\"}]");
    }
    SUBCASE("to primitive") {
        json.moveElement("\"menu\".\"value\"", "\"menu\".\"id\"", "");
        json.print("\"menu\".\"id\"", result, true);
        CHECK(result == "[\"file\",\"File\"]");
    }
}

TEST_CASE("sort test") {
    JsonFile json;
    json.load("sortTest.json");
    std::string result;

    SUBCASE("booleans test") {
        json.sortArray("0");
        json.print("0", result, true);
        CHECK(result == "[false,true,true,null]");
    }
    SUBCASE("numbers test") {
        json.sortArray("1");
        json.print("1", result, true);
        CHECK(result == "[-33.132,-1,0,2.3,4.2e3,null]");
    }
    SUBCASE("strings test") {
        json.sortArray("2");
        json.print("2", result, true);
        CHECK(result == "[\"bottom text\",\"hello world\",null]");
    }
}

TEST_CASE("create from key test") {
    JsonFile json;
    json.load("jsonExample1.json");
    std::string result;

    json.createFromIndex("\"menu\".\"popup\".\"menuitem\".\"newObj\"");
    json.print("\"menu\".\"popup\".\"menuitem\".3", result, true);
    CHECK(result == "{}");

    result.clear();
    json.createFromIndex("\"menu\".\"id\".\"newObj\"");
    json.print("\"menu\".\"id\".1", result, true);
    CHECK(result == "{}");
}

int main() {
    doctest::Context().run();
    return 0;
}