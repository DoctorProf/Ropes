
#include "../Headers/Simulation.h"

Simulation::Simulation(std::vector<Node>& nodes, std::vector<Rope>& ropes, double deltaTime, int& radius, int& idNode)
    : nodes(nodes), ropes(ropes), deltaTime(deltaTime), radius(radius), idNode(idNode)
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
    double friction_coef = 0.4f;
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
        int idStart = rope.idStartNode;
        auto start = std::find_if(nodes.begin(), nodes.end(), [idStart](Node& node)
            {
                return node.id == idStart;
            });
        Node& startNode = *start;

        int idEnd = rope.idEndNode;
        auto end = std::find_if(nodes.begin(), nodes.end(), [idEnd](Node& node)
            {
                return node.id == idEnd;
            });
        Node& endNode = *end;

        Vector2<double> direction = startNode.getPosition() - endNode.getPosition();
        double distance = logic::distance(startNode.getPosition(), endNode.getPosition());

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

            if (startNode.type != 1) startNode.move(p);
            if (endNode.type != 1) endNode.move(-p);
        }
        else if (distance < minSize)
        {
            Vector2<double> normalizeVector = direction / distance;
            double c = minSize - distance;
            Vector2<double> p = c * normalizeVector * 0.5;

            if (startNode.type != 1) startNode.move(p);
            if (endNode.type != 1) endNode.move(-p);
        }
    }
}

void Simulation::render(std::vector<Node>& nodes, std::vector<Rope>& ropes, RenderWindow& window)
{

    for (Rope& rope : ropes) rope.draw(window, nodes);
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
            {"nodes", {rope.idStartNode, rope.idEndNode}},
            {"distance", rope.distance}
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
    idNode = world["points"][world["points"].size() - 1]["id"] + 1;

    for (int i = 0; i < world["points"].size(); i++) 
    {
        nodes.push_back(Node(world["points"][i]["id"], world["points"][i]["pos"][0], world["points"][i]["pos"][1], radius));
        nodes[i].type = world["points"][i]["type"];
    }
    for (int i = 0; i < world["ropes"].size(); i++) 
    {
        int idStart = world["ropes"][i]["nodes"][0];
        int idEnd = world["ropes"][i]["nodes"][1];

        auto start = std::find_if(nodes.begin(), nodes.end(), [idStart](Node& node) 
            {
                return node.id == idStart;
            });
        auto end = std::find_if(nodes.begin(), nodes.end(), [idEnd](Node& node)
            {
                return node.id == idEnd;
            });
        Node startNode =  *start;
        Node endNode = *end;
        double distance = world["ropes"][i]["distance"];
        int type = world["ropes"][i]["type"];
        ropes.push_back(Rope(startNode.id, endNode.id, distance, type));
    }
}