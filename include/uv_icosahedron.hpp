
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
    virtual void setTesselation(unsigned int level) override final;

private:
    float Phi() { return phi/scale; }
    
    void createInitialShape();
    void subdivide();
    void createShapeData();
    QVector3D splitEdge(int id1, int id2);
    
    void add(const QVector3D &v, const QVector3D &n);
    
    void triangle(GLfloat x1, GLfloat y1, GLfloat z1,
                  GLfloat x2, GLfloat y2, GLfloat z2,
                  GLfloat x3, GLfloat y3, GLfloat z3);
    
    int tesselation_factor = { 0 };
    float radius = {.25f};
    float phi = {((1+sqrt(5.0f))/2)};
    float scale = sqrt(1 + phi * phi) * 1/radius;
    float unit = 1/scale;
    QVector<GLfloat> m_data;
    int m_count;
    
    std::vector<QVector3D> unqiueVertices;
    std::vector<QVector3D> triangles;
};

#endif // UV_Icosahedron_H
