#include"JSON_File/JsonFile.hpp"
#include"Util/RegexUtil.hpp"
#include"UI/UI.hpp"

int main() {
    // JsonFile json;
    // json.load("json.json");
    // std::ofstream out("jason.json");
    // std::ofstream out1("johnson.json");
    // json.print("", out, true);
    // json.print("", out1, false);
    // UI ui;
    // ui.run();

    JsonFile jsonTest;
    jsonTest.load("test/jsonExample1.json");
    jsonTest.attachObjectFromString("\"check\"", "\"menu\".\"popup\"", "\"name\"");
    jsonTest.print("", false);

    return 0;
}