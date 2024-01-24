module;

#include <iostream>
#include "SFML/Graphics.hpp"

import Node;
import Rope;
import Logic;

using namespace sf;

export module Simulation;

export class Simulation
{
public:

    std::vector<Node>& nodes;
    std::vector<Rope>& ropes;
    double deltaTime;
    Vector2<double> gravity;
    Simulation(std::vector<Node>& nodes, std::vector<Rope>& ropes, double deltaTime)
        : nodes(nodes), ropes(ropes), deltaTime(deltaTime), gravity(Vector2<double>(0.0f, 1500.0f)) {
    }
    void update()
    {
        applyGravity();
        applyAirFriction();
        updatePositions();
        satisfyConstraints();
        updateDerivatives();
    }
    void applyGravity()
    {
        for (Node& node : nodes) {
            node.forces += gravity;
        }
    }
    void applyAirFriction()
    {
        double friction_coef = 0.5f;
        for (Node& node : nodes) {
            node.forces -= node.velocity * friction_coef;
        }
    }

    void updatePositions()
    {
        for (Node& node : nodes) {
            node.update(deltaTime);
        }
    }

    void updateDerivatives()
    {
        for (Node& node : nodes) {
            node.updateDerivatives(deltaTime);
        }
    }
    void satisfyConstraints()
    {
        for (Rope& rope : ropes)
        {
            Node* startNode = rope.startNode;
            Node* endNode = rope.endNode;
            Vector2<double> direction = startNode->getPosition() - endNode->getPosition();
            double distance = logic::distance(startNode->getPosition(), endNode->getPosition());
            if (distance > rope.distance)
            {
                Vector2<double> normalizeVector = direction / distance;
                double c = distance - rope.distance;
                Vector2<double> p = -c * normalizeVector;
                if (!startNode->isStatic) startNode->move(p); 
                if (!endNode->isStatic) endNode->move(-p);
            }
        }
    }
    void render(std::vector<Node>& nodes, std::vector<Rope>& ropes,  RenderWindow& window)
    {
        
        for (Rope& rope : ropes) rope.draw(window);
        for (Node& node : nodes) node.draw(window);
    }
};