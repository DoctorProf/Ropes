#pragma once

#include "Node.h"
#include "Rope.h"
#include "Logic.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>


using namespace sf;
using json = nlohmann::json;

class Simulation
{
public:

    std::vector<Node>& nodes;
    std::vector<Rope>& ropes;
    double deltaTime;
    int& radius;
    int& idNode;

    Vector2<double> gravity;

    Simulation(std::vector<Node>& nodes, std::vector<Rope>& ropes, double deltaTime, int& radius, int& idNode);

    void update();

    void applyGravity();

    void applyAirFriction();

    void updatePositions();

    void updateDerivatives();

    void satisfyConstraints();

    void render(std::vector<Node>& nodes, std::vector<Rope>& ropes, RenderWindow& window);

    void saveStruct();
    void loadStruct();
};
