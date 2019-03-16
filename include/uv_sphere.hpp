
#ifndef UV_SPHERE_H
#define UV_SPHERE_H

#include <shape.hpp>

class UV_Sphere : public Shape
{
public:
    UV_Sphere();
    virtual const GLfloat *constData() const override final { return m_data.constData(); }
    virtual int count() const override final { return m_count; }
    virtual int vertexCount() const override final { return m_count / 6; }
    virtual void setTesselation(unsigned int level) override final;

private:
    void createSphere();
    
    int Parallels() { return std::max(0, tesselation_factor) + min_parallels; }
    int Meridians() { return std::max(0, tesselation_factor) + min_meridians; }
    float Radius() { return radius; }
    
    void add(const QVector3D &v, const QVector3D &n);
    
    void quad(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2,
              GLfloat x3, GLfloat y3, GLfloat z3, GLfloat x4, GLfloat y4, GLfloat z4);
    void triangle(GLfloat x1, GLfloat y1, GLfloat z1,
                  GLfloat x2, GLfloat y2, GLfloat z2,
                  GLfloat x3, GLfloat y3, GLfloat z3);
    
    int tesselation_factor = { 1 };
    int min_parallels = { 3 };
    int min_meridians = { 4 };
    float radius = {0.25f};    
    QVector<GLfloat> m_data;
    int m_count;
};

#endif // UV_SPHERE_H
