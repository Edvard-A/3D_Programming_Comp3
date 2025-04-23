#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "VisualObject.h"
#include "Vertex.h"
#include <vector>

class CollisionHandler : public VisualObject
{
public:
    CollisionHandler();

    bool checkIntersection(std::vector<Vertex> VerticesA, std::vector<Vertex> VerticesB);
    void projectVertices(std::vector<Vertex> vertices, Vertex axis, float& min, float& max);

};

#endif // COLLISIONHANDLER_H
