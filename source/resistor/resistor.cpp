#include <resistor.h>

Resistor::Resistor(string ID, map<string, int> resistance, map<string, string> netlist) : Component(ID, netlist) {
    this->resistance = resistance;
}

void Resistor:: print() {
    cout << "___________________________________" << endl;
    cout << "Component Type: resistor" << endl;
    cout << "Component ID: " << ID << endl;
    cout << "Component Netlist: " << endl;
    for (map<string, string>::iterator i = netlist.begin(); i != netlist.end(); i++)
    {
        cout << "\t" << i->first << " --> " << i->second << endl;
    }
    cout << "Resistance: " << endl;
    for (map<string, int>::iterator i = resistance.begin(); i != resistance.end(); ++i)
    {
        cout << "\t" << i->first << " --> " << i->second << endl;
    }
    cout << "___________________________________" << endl;
}

void Resistor::toJson(json* jsonFile) {
    json* temp = new json;
    (*temp)["type"] = "resistor";
    Component::toJson(temp);

    nlohmann::ordered_map<string, int> r;
    for (map<string, int>::iterator i = resistance.begin(); i != resistance.end(); ++i) {
        r[i->first] = i->second;
    }
    (*temp)["resistance"] = r;

    (*jsonFile)["components"].emplace_back(*temp);
}