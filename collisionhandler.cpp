#include "collisionhandler.h"

CollisionHandler::CollisionHandler() {}

bool CollisionHandler::checkIntersection(std::vector<Vertex> VerticesA, std::vector<Vertex> VerticesB)
{
    for(int i = 0; i < sizeof(VerticesA); i++)
    {
        Vertex va = VerticesA[i];
        Vertex vb = VerticesB[(i + 1) % sizeof(VerticesA)];

        Vertex edge;
        edge.x = vb.x - va.x;
        edge.y = vb.y - va.y;
        edge.z = vb.z - va.z;

        Vertex axis = {-edge.y, edge.x, edge.z,  0, 0, 0,  0, 0};
    }



    return true;
}

void CollisionHandler::projectVertices(std::vector<Vertex> vertices, Vertex axis, float& min, float& max)
{
    min = static_cast<float>(maxValue);
    max = static_cast<float>(minValue);

    for(int i = 0; i < sizeof(vertices); i++)
    {
        Vertex tempV = vertices[i];
        QVector2D vertVec(tempV.x, tempV.y);
        QVector2D axisVec(axis.x, axis.y);

        //QVector2D vToA = axisVec - vertVec;

        float proj = QVector2D::dotProduct(vertVec, axisVec); // Placeholder, need to find out what to use as second parameter

    }
}
