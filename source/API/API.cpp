#include <API.h>

Topology* API::getTopologyFromID(string topologyID) {
    for (list<Topology*>::iterator it = (*topologies).begin(); it != (*topologies).end(); it++) {
        if (strcmp((*it)->getID().c_str(), topologyID.c_str()) == 0) {
            return *it;
        }
    }
    return nullptr;
}


API::API() {
    topologies = new list<Topology*>;
}


bool API::readJSON(string fileName) {
    json* jsonFile = new json;
    ifstream inputFile("topology_input_files/" + fileName);
    inputFile >> *jsonFile;

    string topologyID = (*jsonFile)["id"].get<string>();
    if (getTopologyFromID(topologyID)) {
        return false;
    }
    json componentsArray = (*jsonFile)["components"];
    list<Component*>* components = new list<Component*>;
    for (int i = 0; i < componentsArray.size(); i++) {
        
        string componentType = componentsArray[i]["type"].get<string>();
        string componentID = componentsArray[i]["id"].get<string>();
        map<string, string> componentNetlist = componentsArray[i]["netlist"].get<map<string, string>>();

        if (strcmp(componentType.c_str(), "resistor") == 0) {
            map<string, int> resistance = componentsArray[i]["resistance"].get<map<string, int>>();
            components->push_back(new Resistor(componentID, resistance, componentNetlist));
        } else if (strcmp(componentType.c_str(), "nmos") == 0) {
            map<string, float> ml = componentsArray[i]["m(l)"].get<map<string, float>>();
            components->push_back(new NMOS(componentID, ml, componentNetlist));
        }
    }
    topologies->push_back(new Topology(topologyID, components));
    delete jsonFile;
    return true;
}


bool API::writeJSON(string topologyID) {
    Topology* topology = getTopologyFromID(topologyID);
    if (!topology) {
        return false;
    }

    json* jsonFile = new json;
    (*jsonFile)["id"] = topology->getID();
    (*jsonFile)["components"] = json::array();
    for (list<Component*>::iterator i = topology->getComponents()->begin(); i != topology->getComponents()->end(); i++) {
        (*i)->toJson(jsonFile);
    }
    ofstream outputFile("topology_output_files/" + topologyID + ".json");
    outputFile << *jsonFile;
    delete jsonFile;
    return true;
}


list<Topology*>* API::queryTopologies() {
    return topologies;
}


bool API::deleteTopology(string topologyID) {
    for (list<Topology*>::iterator it = (*topologies).begin(); it != (*topologies).end(); it++) {
        if (strcmp((*it)->getID().c_str(), topologyID.c_str()) == 0) {
            delete *it;
            topologies->erase(it);
            return true;
        }
    }
    return false;
}


list<Component*>* API::queryComponents(string topologyID) {
    Topology* topology = getTopologyFromID(topologyID);
    if (topology) {
        return topology->getComponents();
    }
    return nullptr;
}


list<Component*>* API::queryComponentsWithNetlistNode(string topologyID, string netlistNodeID) {
    Topology* topology = getTopologyFromID(topologyID);
    list<Component*>* resultComponents = new list<Component*>;
    
    if (topology) {
        list<Component*>* components = topology->getComponents();
        for (list<Component*>::iterator j = (*components).begin(); j != (*components).end(); j++) {
            map<string, string> netlist = (*j)->getNetlist();
            for(map<string, string>::iterator k = netlist.begin(); k != netlist.end(); k++) {
                if (strcmp(k->second.c_str(), netlistNodeID.c_str()) == 0) {
                    resultComponents->push_back(*j);
                }
            }
        }
        return resultComponents;
    }
    
    return nullptr;
}


API::~API() {
    for (list<Topology*>::iterator i = (*topologies).begin(); i != (*topologies).end(); i++) {
        delete *i;
    }
    topologies->clear();
    topologies = nullptr;
}