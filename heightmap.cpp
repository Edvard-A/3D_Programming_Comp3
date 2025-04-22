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

    float vertexXStart{ 0.f - width * horizontalSpacing / 2 };            // if world origo should be at center use: {0.f - width * horisontalSpacing / 2};
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
                                       vertexXStart + (w * horizontalSpacing),
                                       heightFromBitMap,
                                       vertexZStart - (d * horizontalSpacing),
                                       0.5f, 0.f, 0.5f,
                                       w / (width - 1.f),
                                       d / (depth - 1.f)
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
