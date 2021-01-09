#include"JSON_File/JsonFile.hpp"
#include"Util/RegexUtil.hpp"
#include"UI/UI.hpp"

int main() {
    JsonFile json;
    json.load("json.json");
    std::ofstream out("jason.json");
    json.print("", out, true);
    // UI ui;
    // ui.run();

    return 0;
}