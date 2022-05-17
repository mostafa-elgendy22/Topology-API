#include <gtest/gtest.h>
#include <API.h>


TEST(API__Test, TopologiesList) {
    API* api = new API();
    EXPECT_EQ(0, api->queryTopologies()->size());
    EXPECT_FALSE(api->queryTopologies() == nullptr);
}

TEST(API__Test, ReadInputTopology) {
    API* api = new API();
    bool result;

    result = api->readJSON("topology1.json");
    EXPECT_EQ(1, api->queryTopologies()->size());
    EXPECT_TRUE(result);

    result = api->readJSON("topology1.json");
    EXPECT_EQ(1, api->queryTopologies()->size());
    EXPECT_FALSE(result);

    result = api->readJSON("topology2.json");
    EXPECT_EQ(2, api->queryTopologies()->size());
    EXPECT_TRUE(result);
}

TEST(API__Test, WriteOutputTopology) {
    API* api = new API();
    string topologyID;
    bool result;

    api->readJSON("topology1.json");
    EXPECT_EQ(1, api->queryTopologies()->size());
    
    topologyID = api->queryTopologies()->front()->getID();
    result = api->writeJSON(topologyID);
    EXPECT_TRUE(result);
    
    topologyID = "wrongID";
    result = api->writeJSON(topologyID);
    EXPECT_FALSE(result);

    result = api->readJSON("topology2.json");
    EXPECT_TRUE(result);

    topologyID = api->queryTopologies()->back()->getID();
    result = api->writeJSON(topologyID);
    EXPECT_TRUE(result);
}

TEST(API__Test, DeleteTopology) {
    API* api = new API();
    string topologyID;
    bool result;

    api->readJSON("topology1.json");
    api->readJSON("topology2.json");
    EXPECT_EQ(2, api->queryTopologies()->size());
    
    topologyID = api->queryTopologies()->front()->getID();
    result = api->deleteTopology(topologyID);
    EXPECT_TRUE(result);
    EXPECT_EQ(1, api->queryTopologies()->size());

    result = api->readJSON("topology1.json");
    EXPECT_TRUE(result);
    EXPECT_EQ(2, api->queryTopologies()->size());

    topologyID = "wrongID";
    result = api->deleteTopology(topologyID);
    EXPECT_FALSE(result);
    EXPECT_EQ(2, api->queryTopologies()->size());

    topologyID = api->queryTopologies()->front()->getID();
    result = api->deleteTopology(topologyID);
    topologyID = api->queryTopologies()->front()->getID();
    result = api->deleteTopology(topologyID);
    EXPECT_EQ(0, api->queryTopologies()->size());
}

TEST(API__Test, QueryComponents) {
    API* api = new API();
    string topologyID;
    bool result;

    api->readJSON("topology1.json");
    api->readJSON("topology2.json");

    topologyID = api->queryTopologies()->front()->getID();
    EXPECT_FALSE(api->queryComponents(topologyID) == nullptr);
    EXPECT_FALSE(api->queryComponents(topologyID)->size() == 0);

    topologyID = api->queryTopologies()->back()->getID();
    EXPECT_FALSE(api->queryComponents(topologyID) == nullptr);
    EXPECT_FALSE(api->queryComponents(topologyID)->size() == 0);

    topologyID = "wrongID";
    EXPECT_TRUE(api->queryComponents(topologyID) == nullptr);
}


TEST(API__Test, QueryComponentsWithNetlistNode) {
    API* api = new API();
    string topologyID, netlistNodeID;
    map<string, string> netlist;
    bool result;

    api->readJSON("topology1.json");
    api->readJSON("topology2.json");


    list<Topology*>* topologies = api->queryTopologies();
    for (list<Topology*>::iterator it = (*topologies).begin(); it != (*topologies).end(); it++) {
        topologyID = (*it)->getID();
        list<Component*>* components = (*it)->getComponents();
        for (list<Component*>::iterator j = (*components).begin(); j != (*components).end(); j++) {
            netlist = (*j)->getNetlist();
            for (map<string, string>::iterator k = netlist.begin(); k != netlist.end(); k++) {
                netlistNodeID = k->second;
                EXPECT_FALSE(api->queryComponentsWithNetlistNode(topologyID, netlistNodeID) == nullptr);
                EXPECT_FALSE(api->queryComponentsWithNetlistNode(topologyID, netlistNodeID)->size() == 0);
            }
        }

    } 

    topologyID = "wrongID";
    netlistNodeID = "wrongID";
    EXPECT_TRUE(api->queryComponentsWithNetlistNode(topologyID, netlistNodeID) == nullptr);
}