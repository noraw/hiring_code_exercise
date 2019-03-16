
#ifndef UV_ICOSAHEDRON_H
#define UV_ICOSAHEDRON_H

#include <shape.hpp>
#include <qmath.h>

class UV_Icosahedron : public Shape
{
public:
    UV_Icosahedron();
    virtual const GLfloat *constData() const override final { return m_data.constData(); }
    virtual int count() const override final { return m_count; }
    virtual int vertexCount() const override final { return m_count / 6; }
    virtual void setTesselation(unsigned int level) override final { tesselation_factor = level; }  

private:
    float Phi() { return phi; }
    
            
    
    void add(const QVector3D &v, const QVector3D &n);
    
    void triangle(GLfloat x1, GLfloat y1, GLfloat z1,
                  GLfloat x2, GLfloat y2, GLfloat z2,
                  GLfloat x3, GLfloat y3, GLfloat z3);
    
    int tesselation_factor = { 5 };
    int min_parallels = { 3 };
    int min_meridians = { 4 };
    float scale = 10.0f;
    float unit = 1/scale;
    float phi = {((1+sqrt(5.0f))/2)/scale};
    QVector<GLfloat> m_data;
    int m_count;
    
    std::vector<QVector3D> unqiueVertices;
    std::vector<QVector3D> triangles;
};

#endif // UV_Icosahedron_H