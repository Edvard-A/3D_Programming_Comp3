#ifndef VISUALOBJECT_H
#define VISUALOBJECT_H

#include <QVulkanWindow>
#include <vector>
#include "Vertex.h"
#include "Utilities.h"

class VisualObject
{
public:
    VisualObject();

    void move(float x, float y = 0.0f, float z = 0.0f);
    void scale(float s);
    void rotate(float t, float x, float y, float z);

	//Setters and Getters
    inline std::vector<Vertex> getVertices() { return mVertices; }
    inline VkBuffer& getVBuffer() { return mVertexBuffer.mBuffer; }
    inline VkDeviceMemory& getVBufferMemory() { return mVertexBuffer.mBufferMemory; }
	inline VkDeviceMemory& getIBufferMemory() { return mIndexBuffer.mBufferMemory; }
    inline void setVBuffer(VkBuffer bufferIn) { mVertexBuffer.mBuffer = bufferIn; }
    inline void setVBufferMemory(VkDeviceMemory bufferMemoryIn) { mVertexBuffer.mBufferMemory = bufferMemoryIn; }
    inline VkBuffer& getIBuffer() { return mIndexBuffer.mBuffer; }
    inline void setIBuffer(VkBuffer bufferIn) { mIndexBuffer.mBuffer = bufferIn; }
    inline void setIBufferMemory(VkDeviceMemory bufferMemoryIn) { mIndexBuffer.mBufferMemory = bufferMemoryIn; }
    inline void setName(std::string name) { mName = name; }
    inline std::string getName() const { return mName; }
    inline int getDrawType() const { return drawType; }
    inline QMatrix4x4 getMatrix() const {return mMatrix;}
	inline std::vector<Vertex> getVertices() const { return mVertices; }
	inline std::vector<uint32_t> getIndices() const { return mIndices; }
    inline QVector3D getPosition() { return mPosition; }

    float calculateCoordinates(QVector2D& p, QVector3D& a, QVector3D& b, QVector3D& c);
    float getHeight(float worldX, float worldZ, int mapWidth, int mapHeight, std::vector<Vertex> mapVertices);

protected:
    std::vector<Vertex> mVertices;
    std::vector<uint32_t> mIndices;
    QMatrix4x4 mMatrix;
    std::string mName;
    QVector3D mPosition;

	BufferHandle mVertexBuffer;
	BufferHandle mIndexBuffer;
    //VkPrimitiveTopology mTopology{ VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST }; //not used

    int drawType{ 0 }; // 0 = fill, 1 = line
};

#endif // VISUALOBJECT_H

