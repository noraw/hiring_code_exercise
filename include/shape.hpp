#ifndef SHAPE_H
#define SHAPE_H

#include <qopengl.h>
#include <QVector>
#include <QVector3D>

class Shape
{
public:
    virtual ~Shape() = default;    
    virtual const GLfloat *constData() const = 0;    
    virtual int count() const = 0;    
    virtual int vertexCount() const = 0;    
    virtual void setTesselation(unsigned int level) = 0;        
};

#endif // SHAPE_H
