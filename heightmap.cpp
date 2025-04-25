#include "heightmap.h"
#include "Vertex.h"
#include "stb_image.h"

HeightMap::HeightMap()
{}

void HeightMap::makeMap(std::string filename)
{
    stbi_uc* pixelData = stbi_load(filename.c_str(), &mWidth, &mHeight, &mChannels, STBI_rgb_alpha);
    if(pixelData == nullptr)
    {
        qDebug("Failed to load image!");
        return;
    }

    makeMap(pixelData, mWidth, mHeight);
    stbi_image_free(pixelData);
}

void HeightMap::makeMap(unsigned char* data, int mapWidth, int mapHeight)
{
    // spacings and placement
    float horizontalSpacing = 0.2f;
    float verticalSpacing = 0.05f;
    float heightOffset = -10.f;

    unsigned short width = mapWidth;
    unsigned short depth = mapHeight;
    //qDebug() << width;
    //qDebug() << depth;

    float vertexXStart{ 0.f - width * horizontalSpacing / 2 }; // offsetting the start to have world origin be the center of the map
    float vertexZStart{ 0.f + depth * horizontalSpacing / 2 };
    //float vertexXStart = 0.f;
    //float vertexZStart = 0.f;

    for(int d = 0; d < depth; d++)
    {
        for(int w = 0; w < width; w++)
        {
            int index = (w + d * width) * 4; // this has something to do with how the image is loaded from the file
            float heightFromBitMap = static_cast<float>(data[index]) * verticalSpacing + heightOffset;

            mVertices.emplace_back(Vertex
                                   {
                                       vertexXStart + (w * horizontalSpacing), // x
                                       heightFromBitMap,                       // y
                                       vertexZStart - (d * horizontalSpacing), // z
                                       0.5f, 0.f, 0.5f,                        // RGB
                                       w / (width - 1.f),                      // u
                                       d / (depth - 1.f)                       // v
                                   });
        }
    }


    for(int d = 0; d < depth - 1; d++)
    {
        for(int w = 0; w < width - 1; w++)
        {
            mIndices.emplace_back(w + d * width);
            //qDebug() << w + d * width;
            mIndices.emplace_back(w + d * width + width);
            mIndices.emplace_back(w + d * width + width + 1);

            mIndices.emplace_back(w + d * width);
            mIndices.emplace_back(w + d * width + width + 1);
            mIndices.emplace_back(w + d * width + 1);
            //mIndices.emplace_back(w + d * width);
            //mIndices.emplace_back(w + d * width + 1);
            //mIndices.emplace_back(w + d * width * width + 1);
            //mIndices.emplace_back(w + d * width + 1);

        }
    }
}

float HeightMap::calculateCoordinates(QVector2D& p, QVector3D& a, QVector3D& b, QVector3D& c)
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
//
//float HeightMap::getHeight(float worldX, float worldZ)
//{
//    float horizontalSpacing = 0.5f;
//
//    int gridX = static_cast<int>(worldX / horizontalSpacing); // casting the result to int
//    int gridZ = static_cast<int>(worldZ / horizontalSpacing);
//
//    if(gridX < 0 || gridZ < 0 || gridX >= mWidth - 1 || gridZ >= mHeight - 1)
//    {
//        return 0.f; // out of bounds
//    }
//
//    float xCoord = fmod(worldX, horizontalSpacing) / horizontalSpacing;
//    float zCoord = fmod(worldZ, horizontalSpacing) / horizontalSpacing;
//
//    QVector3D a, b, c;
//    int topLeftIndex = gridX + gridZ * mWidth;
//    if(xCoord + zCoord <= 1.f)
//    {
//        // Top-left triangle
//        a = QVector3D(mVertices[topLeftIndex].x, mVertices[topLeftIndex].y, mVertices[topLeftIndex].z);
//        b = QVector3D(mVertices[topLeftIndex + 1].x, mVertices[topLeftIndex + 1].y, mVertices[topLeftIndex + 1].z);
//        c = QVector3D(mVertices[topLeftIndex + mWidth].x, mVertices[topLeftIndex + mWidth].y, mVertices[topLeftIndex + mWidth].z);
//    }
//    else
//    {
//        // Bottom-left triangle
//        a = QVector3D(mVertices[topLeftIndex + 1 + mWidth].x, mVertices[topLeftIndex + 1 + mWidth].y, mVertices[topLeftIndex + 1 + mWidth].z);
//        b = QVector3D(mVertices[topLeftIndex + mWidth].x, mVertices[topLeftIndex + mWidth].y, mVertices[topLeftIndex + mWidth].z);
//        b = QVector3D(mVertices[topLeftIndex + 1].x, mVertices[topLeftIndex + 1].y, mVertices[topLeftIndex + 1].z);
//    }
//
//    QVector2D p(worldX, worldZ);
//    return calculateCoordinates(p, a, b, c);
//}
//
