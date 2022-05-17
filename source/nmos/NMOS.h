#pragma once

#include <component.h>
#include <string>
#include <map>
#include <json/json.hpp>

typedef nlohmann::ordered_json json;



class NMOS: public Component 
{
private:

    /**
     * @brief The m(l) of the NMOS transistor
     */
    map<string, float> ml;

public:

    /**
     * Construct a new NMOS object and sets its parameters and the Component parameters with the sent parameters
     * @brief Creates a new NMOS object
     * @param ID The ID of the NMOS component
     * @param ml The m(l) of the NMOS component
     * @param netlist The netlist of the NMOS componet
     */
    NMOS(string ID, map<string, float> ml, map<string, string> netlist);

    /**
     * @brief Prints the attributes of the NMOS object in the console window
     */
    virtual void print();

    /**
     * @brief This function sets the m(l) of the NMOS object and calls Component::toJson(jsonFile) to convert the other parameters to a JSON object
     * @param jsonFile A pointer to the JSON object that is used to convert the component to JSON object  
     */
    virtual void toJson(json* jsonFile);
};