#include <NMOS.h>

NMOS::NMOS(string ID, map<string, float> ml, map<string, string> netlist) : 
        Component(ID, netlist) 
        {
            this->ml = ml;
        }

void NMOS:: print() 
{
    cout << "___________________________________" << endl;
    cout << "Component Type: nmos" << endl;
    
    cout << "Component ID: " << ID << endl;
    cout << "Component Netlist: " << endl;
    for (map<string, string>::iterator i = netlist.begin(); i != netlist.end(); i++)
    {
        cout << "\t" << i->first << " --> " << i->second << endl;
    }

    cout << "m(l): " << endl;
    for (map<string, float>::iterator i = ml.begin(); i != ml.end(); i++)
    {
        cout << "\t" << i->first << " --> " << i->second << endl;
    }
    cout << "___________________________________" << endl;
}

void NMOS::toJson(json* jsonFile) {
    json* temp = new json;
    (*temp)["type"] = "nmos";
    Component::toJson(temp);

    nlohmann::ordered_map<string, float> m;
    for (map<string, float>::iterator i = ml.begin(); i != ml.end(); i++) {
        m[i->first] = i->second;
    }

    (*temp)["m(l)"] = m;
    (*jsonFile)["components"].emplace_back(*temp);
}