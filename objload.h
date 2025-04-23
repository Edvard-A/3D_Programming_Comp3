#ifndef OBJLOAD_H
#define OBJLOAD_H

#include "VisualObject.h"
#include <string>

class ObjLoad : public VisualObject
{
public:
    ObjLoad(const std::string& filename);

private:
    bool readObjFile(const std::string& filename);
};

#endif // OBJLOAD_H
