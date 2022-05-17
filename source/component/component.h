#pragma once

#include <iostream>
#include <string>
#include <map>
#include <json/json.hpp>
using namespace std;

typedef nlohmann::ordered_json json;

class Component
{
protected:

    /**
     * @brief The ID of the component
     */
    string ID;

    /**
     * @brief The netlist of the component
     */
    map<string, string> netlist;

public:

    /** Construct a new component object and sets its parameters with the sent parametrs
     * @brief Creates a new Component object
     * @param ID The ID of the component
     * @param netlist The netlist of the component
     */
    Component(string ID, map<string, string> netlist);

    /**
     * @brief Gets the Netlist of the component
     * @return The netlist of the component
     */
    map<string, string> getNetlist();

    /** 
     * This function converts the component to a JSON to be used in the API, it is overriden by the derived classes (Resistor & NMOS) because they have different attributes to be converted to JSON object
     * @brief The function sets the ID and the netlist of the component in the JSON object (because all the derived classes share those attributes), this function is called by derived classes to set the common attributes
     * @param jsonFile A pointer to the JSON object that is used to convert the component to JSON object 
     */
    virtual void toJson(json* jsonFile);
    virtual void print() = 0;
};