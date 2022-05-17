#include <gtest/gtest.h>
#include <resistor.h>

typedef nlohmann::ordered_json json;


TEST(Resistor__Test, JsonConversion) {
    int default_r = 150;
    int min_r = 10;
    int max_r = 1000;
    map<string, int> r = {{"default", default_r}, {"min", min_r}, {"max", max_r}};
    
    string t1 = "vdd";
    string t2 = "n1";
    map<string, string> n = {{"t1", t1}, {"t2", t2}};
    
    string ID = "res1";
    Resistor* resistor = new Resistor(ID, r, n);
    
    json* jsonFile = new json;
    resistor->toJson(jsonFile);
    json componentsArray = (*jsonFile)["components"];

    string componentType = componentsArray[0]["type"].get<string>();
    string componentID = componentsArray[0]["id"].get<string>();
    map<string, int> resistance = componentsArray[0]["resistance"].get<map<string, int>>();
    map<string, string> netlist = componentsArray[0]["netlist"].get<map<string, string>>();

    EXPECT_EQ(componentType, "resistor");
    EXPECT_EQ(componentID, ID);
    EXPECT_EQ(resistance["default"], default_r);
    EXPECT_EQ(resistance["min"], min_r);
    EXPECT_EQ(resistance["max"], max_r);
    EXPECT_EQ(netlist["t1"], t1);
    EXPECT_EQ(netlist["t2"], t2);
}
