#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "VisualObject.h"
#include <string>

class HeightMap : public VisualObject
{
public:
    HeightMap();

    void makeMap(std::string filename);
    void makeMap(unsigned char* data, int width, int height);
    float calculateCoordinates(QVector2D& p, QVector3D& a, QVector3D& b, QVector3D& c);
    float getHeight(float worldX, float worldZ);

private:
    int mWidth{0};
    int mHeight{0};
    int mChannels{0};
};

#endif // HEIGHTMAP_H
