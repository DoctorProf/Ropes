
#include "../Headers/Simulation.h"

Simulation::Simulation(std::vector<Node>& nodes, std::vector<Rope>& ropes, double deltaTime, int& radius)
    : nodes(nodes), ropes(ropes), deltaTime(deltaTime), radius(radius)
{
    this->gravity = Vector2<double>(0.0, 1500.0);
}

void Simulation::update()
{
    applyGravity();
    applyAirFriction();
    updatePositions();
    satisfyConstraints();
    updateDerivatives();
}

void Simulation::applyGravity()
{
    for (Node& node : nodes) {
        node.forces += gravity;
        if (node.type == 2)
        {
            node.angle += 0.1;
            Vector2<double> forces;
            forces.x = std::cos(node.angle);
            forces.y = std::sin(node.angle);
            node.forces += forces * 10000.0;
        }
    }
}

void Simulation::applyAirFriction()
{
    double friction_coef = 0.2f;
    for (Node& node : nodes) {
        node.forces -= node.velocity * friction_coef;
    }
}

void Simulation::updatePositions()
{
    for (Node& node : nodes) {
        node.update(deltaTime);
    }
}

void Simulation::updateDerivatives()
{
    for (Node& node : nodes) {
        node.updateDerivatives(deltaTime);
    }
}

void Simulation::satisfyConstraints()
{
    for (Rope& rope : ropes)
    {
        Node* startNode = rope.startNode;
        Node* endNode = rope.endNode;

        Vector2<double> direction = startNode->getPosition() - endNode->getPosition();
        double distance = logic::distance(startNode->getPosition(), endNode->getPosition());

        double maxSize{};
        double minSize{};
        if (!rope.type)
        {
            maxSize = rope.distance;
            minSize = rope.distance;
        }
        else
        {
            maxSize = rope.maxSize;
            minSize = rope.minSize;
        }
        if (distance > maxSize)
        {
            Vector2<double> normalizeVector = direction / distance;
            double c = distance - maxSize;
            Vector2<double> p = -c * normalizeVector * 0.5;

            if (startNode->type != 1) startNode->move(p);
            if (endNode->type != 1) endNode->move(-p);
        }
        else if (distance < minSize)
        {
            Vector2<double> normalizeVector = direction / distance;
            double c = minSize - distance;
            Vector2<double> p = c * normalizeVector * 0.5;

            if (startNode->type != 1) startNode->move(p);
            if (endNode->type != 1) endNode->move(-p);
        }
    }
}

void Simulation::render(std::vector<Node>& nodes, std::vector<Rope>& ropes, RenderWindow& window)
{

    for (Rope& rope : ropes) rope.draw(window);
    for (Node& node : nodes) node.draw(window);
}

void Simulation::saveStruct()
{
    json data;

    json jsonNodes;
    json jsonGlobal;

    jsonGlobal =
    {
        {"radius", radius}
    };

    data["global"] = jsonGlobal;

    for (Node& node : nodes) 
    {
       
        json jsonNode = 
        {
            {"id", node.id},
            {"type", node.type},
            {"pos", {node.getPosition().x, node.getPosition().y}}
        };
        jsonNodes.push_back(jsonNode);
    }
    data["points"] = jsonNodes;

    json jsonRopes;
    for (Rope& rope : ropes)
    {
        json jsonRope = 
        {
            {"type", rope.type},
            {"nodes", {rope.startNode->id, rope.endNode->id}}
        };
        jsonRopes.push_back(jsonRope);
    }
    data["ropes"] = jsonRopes;

    std::ofstream file("save.json");
    if (file.is_open())
    {
        file << data.dump(4);
        file.close();
    }
}
void Simulation::loadStruct()
{
    nodes.clear();
    ropes.clear();
    std::ifstream file("save.json");

    json world = json::parse(file);

    radius = world["global"]["radius"];

    for (int i = 0; i < world["points"].size(); i++) 
    {
        nodes.push_back(Node(world["points"][i]["id"], world["points"][i]["pos"][0], world["points"][i]["pos"][1], radius));
        nodes[i].type = world["points"][i]["type"];
    }
    for (int i = 0; i < world["ropes"].size(); i++) 
    {
        Node* startNode{};
        Node* endNode{};
        for (int j = 0; j < nodes.size(); j++)
        {
            if (world["ropes"][i]["nodes"][0] == nodes[j].id) startNode = &nodes[j];
            if (world["ropes"][i]["nodes"][1] == nodes[j].id) endNode = &nodes[j];
        }
        double distance = logic::distance(startNode->getPosition(), endNode->getPosition());
        ropes.push_back(Rope(startNode, endNode, distance, world["ropes"][i]["type"]));
    }
}