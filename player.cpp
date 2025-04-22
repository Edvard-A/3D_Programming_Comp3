#include "player.h"
#include "Vertex.h"

Player::Player()
{
    Vertex v1{1.0f, 0.0f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f};
    Vertex v2{0.5f, 1.0f, 0.0f,    1.0f, 0.0f, 0.7f,    0.0f, 0.0f};
    Vertex v3{0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f};
    Vertex v4{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f};
    Vertex v5{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f};
    Vertex v6{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f};
    Vertex v7{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f};
    Vertex v8{0.0f, 0.0f, 0.0f,    0.0f, 0.0f, 0.0f,    0.0f, 0.0f};

    mVertices.push_back(v1);
    mVertices.push_back(v2);
    mVertices.push_back(v3);

}
