#include <component.h>

Component::Component(string ID, map<string, string> netlist) {
    this->ID = ID;
    this->netlist = netlist;
}

void Component::toJson(json* jsonFile) {
    (*jsonFile)["id"] = ID;

    nlohmann::ordered_map<string, string> n;
    for (map<string, string>::iterator i = netlist.begin(); i != netlist.end(); i++) {
        n[i->first] = i->second;
    }
    (*jsonFile)["netlist"] = n;
}

map<string, string> Component::getNetlist() {
    return netlist;
}