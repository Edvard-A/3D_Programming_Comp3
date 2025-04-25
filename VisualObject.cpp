#include "VisualObject.h"

VisualObject::VisualObject()
{
    mMatrix.setToIdentity();
}

void VisualObject::move(float x, float y, float z)
{
    mMatrix.translate(x, y, z);
    //mPosition.x() += x;
    float newX = static_cast<float>(mPosition.x()) + x;
    float newY = static_cast<float>(mPosition.y()) + y;
    float newZ = static_cast<float>(mPosition.z()) + z;
    mPosition.setX(newX);
    mPosition.setY(newY);
    mPosition.setZ(newZ);
}

void VisualObject::scale(float s)
{
    mMatrix.scale(s);
}

void VisualObject::rotate(float t, float x, float y, float z)
{
    mMatrix.rotate(t, x, y, z);
}

float VisualObject::calculateCoordinates(QVector2D& p, QVector3D& a, QVector3D& b, QVector3D& c)
{
    QVector2D aTo2D(a.x(), a.z()); // Fetching the x and z coordinate of the 3D vector
    QVector2D bTo2D(b.x(), b.z());
    QVector2D cTo2D(c.x(), c.z());

    QVector2D v0 = bTo2D - aTo2D; // Getting the distance between each point and a as per barycentric coordinate calculations
    QVector2D v1 = cTo2D - aTo2D;
    QVector2D v2 = p - aTo2D;

    float d00 = QVector2D::dotProduct(v0, v0);
    float d01 = QVector2D::dotProduct(v0, v1);
    float d11 = QVector2D::dotProduct(v1, v1);
    float d20 = QVector2D::dotProduct(v2, v0);
    float d21 = QVector2D::dotProduct(v2, v1);

    float v = ((d11 * d20) - (d01 * d21));
    float w = ((d00 * d21) - (d01 * d20));
    float u = 1.f - v - w;                  // the sum of all three points equals 1, we only need two points to calculate all of them

    return u * a.y() + v * b.y() + w *c.y();
}

float VisualObject::getHeight(float worldX, float worldZ, int mapWidth, int mapHeight, std::vector<Vertex> mapVertices)
{
    float horizontalSpacing = 0.2f;

    int gridX = static_cast<int>((worldX / horizontalSpacing) + ((mapWidth - 1) / 2)); // casting the result to int
    int gridZ = static_cast<int>((worldZ / horizontalSpacing) + ((mapHeight - 1) / 2));

    qDebug() << "gridX: " << gridX;
    qDebug() << "gridZ: " << gridZ;

    //if(gridX < 0 || gridZ < 0 || gridX >= mapWidth - 1 || gridZ >= mapHeight - 1)
    //
    //    return 0.f; // out of bounds
    //}

    float xCoord = fmod(worldX, horizontalSpacing) / horizontalSpacing;
    float zCoord = fmod(worldZ, horizontalSpacing) / horizontalSpacing;



    QVector3D a, b, c;
    int topLeftIndex = gridX + gridZ * mapWidth;

    qDebug() << "topLeftIndex: " << topLeftIndex;

    if(xCoord + zCoord <= 1.f)
    {
        qDebug() << "Map Vertex Count: " << mapVertices.size();
        //for(int i{0}; i < mapVertices.size(); i++)
        //{
        //    qDebug() << mapVertices[i].x;
        //}
        //qDebug() << mapVertices;
        // Top-left triangle
    //    a = QVector3D(mapVertices[topLeftIndex].x, mapVertices[topLeftIndex].y, mapVertices[topLeftIndex].z);
    //    b = QVector3D(mapVertices[topLeftIndex + 1].x, mapVertices[topLeftIndex + 1].y, mapVertices[topLeftIndex + 1].z);
    //    c = QVector3D(mapVertices[topLeftIndex + mapWidth].x, mapVertices[topLeftIndex + mapWidth].y, mapVertices[topLeftIndex + mapWidth].z);
    }
    //else
    //{
    //    // Bottom-left triangle
    //    a = QVector3D(mapVertices[topLeftIndex + 1 + mapWidth].x, mapVertices[topLeftIndex + 1 + mapWidth].y, mapVertices[topLeftIndex + 1 + mapWidth].z);
    //    b = QVector3D(mapVertices[topLeftIndex + mapWidth].x, mapVertices[topLeftIndex + mapWidth].y, mapVertices[topLeftIndex + mapWidth].z);
    //    b = QVector3D(mapVertices[topLeftIndex + 1].x, mapVertices[topLeftIndex + 1].y, mapVertices[topLeftIndex + 1].z);
    //}

    //QVector2D p(worldX, worldZ);
    //return calculateCoordinates(p, a, b, c);
    return 1.f;
}
