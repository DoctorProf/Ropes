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
    void update(std::vector<Node>& nodes, std::vector<Rope>& ropes, float deltaTime, float gravity)
    {
        applyGravity(nodes, deltaTime, gravity);
        satisfyConstraints(ropes);
    }
    void applyGravity(std::vector<Node>& nodes, float deltaTime, float gravity) {
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
            Vector2f direction = startNode->getPosition() - endNode->getPosition();
            float distance = logic::distance(startNode->getPosition(), endNode->getPosition());
            if (distance > rope.distance)
            {
                Vector2f n = direction / distance;
                float c = distance - rope.distance;
                Vector2f p = -c * n;
                if (!startNode->isStatic) startNode->position += p;
                if (!endNode->isStatic) endNode->position -= p;
            }
        }
    }
    void render(std::vector<Node>& nodes, std::vector<Rope>& ropes,  RenderWindow& window)
    {
        for (Node& node : nodes) node.draw(window);
        for (Rope& rope : ropes) rope.draw(window);
    }
};