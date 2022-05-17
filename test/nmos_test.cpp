#include <gtest/gtest.h>
#include <NMOS.h>

typedef nlohmann::ordered_json json;


TEST(NMOS__Test, JsonConversion) {
    float default_m = 1.5;
    float min_m = 1;
    float max_m = 2;
    map<string, float> m = {{"default", default_m}, {"min", min_m}, {"max", max_m}};
    
    string drain = "n1";
    string gate = "v1";
    string source = "vss";
    map<string, string> n = {{"drain", drain}, {"gate", gate}, {"source", source}};
    
    string ID = "nmos1";
    NMOS* nmos = new NMOS(ID, m, n);
    
    json* jsonFile = new json;
    nmos->toJson(jsonFile);
    json componentsArray = (*jsonFile)["components"];

    string componentType = componentsArray[0]["type"].get<string>();
    string componentID = componentsArray[0]["id"].get<string>();
    map<string, float> resistance = componentsArray[0]["m(l)"].get<map<string, float>>();
    map<string, string> netlist = componentsArray[0]["netlist"].get<map<string, string>>();

    EXPECT_EQ(componentType, "nmos");
    EXPECT_EQ(componentID, ID);
    EXPECT_EQ(resistance["default"], default_m);
    EXPECT_EQ(resistance["min"], min_m);
    EXPECT_EQ(resistance["max"], max_m);
    EXPECT_EQ(netlist["drain"], drain);
    EXPECT_EQ(netlist["gate"], gate);
    EXPECT_EQ(netlist["source"], source);
}
