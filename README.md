# Topology-API

## Introduction
‌An‌ ‌API‌ ‌library‌ ‌which‌:‌ ‌
1. Read‌s and‌ ‌write‌s ‌topologies‌ ‌to‌ ‌and‌ ‌from‌ ‌disk.‌ ‌
2. Stores‌ ‌multiple‌ ‌topologies‌ ‌in‌ ‌memory.‌ ‌
3. Execute‌s ‌various operations‌ ‌on‌ ‌topologies.‌ ‌
‌

## Topology Specification
A topology is a set of electronic components that are connected together. Topology input file samples can be found at `topology_input_files`.


## Functional Specifications
Provide the functionality to:
1. Read a topology from a given JSON file and store it in the memory.
2. Write a given topology from the memory to a JSON file.
3. Query about which topologies are currently in the memory.
4. Delete a given topology from memory.
5. Query about which devices are in a given topology.
6. Query about which devices are connected to a given netlist node in 
a given topology.


## Non-Functional Specifications
1. Implementation is done in an object-oriented manner 
(encapsulation, inheritance, polymorphism).
2. Use of managed pointers.
3. Documentation on API level.
4. Documentation on class level.
7. Automatic testing on API level.
8. Automatic testing on class level.
9. Check your code with a code analysis tool of your choice.


## Requirements to build the project
1. CMake
2. MinGW


## Running the program

```
./bin/topology_api_run
```

## Running tests

```
./bin/topology_api_test
```
