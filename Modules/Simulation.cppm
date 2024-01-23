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

    Simulation()
    {

    }
    void update(std::vector<Node>& nodes, std::vector<Rope>& ropes, double deltaTime, double gravity)
    {
        applyGravity(nodes, deltaTime, gravity);
        satisfyConstraints(ropes);
    }
    void applyGravity(std::vector<Node>& nodes, double deltaTime, double gravity) {
        for (Node& node : nodes) {
            if (!node.isStatic) 
            {
                node.velocity.y += gravity * deltaTime;

                node.position += node.velocity;
            }
        }
    }
    void satisfyConstraints(std::vector<Rope>& ropes)
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
                if (!startNode->isStatic) startNode->position += p; 
                if (!endNode->isStatic) endNode->position -= p;
            }
        }
    }
    void render(std::vector<Node>& nodes, std::vector<Rope>& ropes,  RenderWindow& window)
    {
        for (Rope& rope : ropes) rope.draw(window);
        for (Node& node : nodes) node.draw(window);
    }
};