#pragma once

#include <component.h>
#include <string>
#include <map>
#include <json/json.hpp>

typedef nlohmann::ordered_json json;


class Resistor: public Component 
{
private:

    /**
     * @brief The reistance of the Resistor
     */
    map<string, int> resistance;

public:
    
    /**
     * Construct a new Resistor object and sets its parameters and the Component parameters with the sent parameters
     * @brief Creates a new Resistor object
     * @param ID The ID of the Reistor component
     * @param resistance The resistance of the Resistor component
     * @param netlist The netlist of the resistor component
     */
    Resistor(string ID, map<string, int> resistance, map<string, string> netlist);

    /**
     * @brief Prints the attributes of the Resistor object in the console window
     */
    virtual void print();

    /**
     * @brief This function sets the resistance of the Resistance object and calls Component::toJson(jsonFile) to convert the other parameters to a JSON object
     * @param jsonFile A pointer to the JSON object that is used to convert the component to JSON object  
     */
    virtual void toJson(json* jsonFile);
};