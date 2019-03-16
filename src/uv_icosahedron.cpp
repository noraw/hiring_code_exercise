

#include <uv_icosahedron.hpp>
#include <qmath.h>

UV_Icosahedron::UV_Icosahedron()
    : m_count(0)
{

    // Build Vertex List
    std::vector<QVector3D> vertices;    
    std::vector<QVector3D> unqiueVertices;
    unqiueVertices.emplace_back(0.0f, unit, Phi());
    unqiueVertices.emplace_back(unit, Phi(), 0.0f);
    unqiueVertices.emplace_back(Phi(), 0.0f, unit);
    
    unqiueVertices.emplace_back(0.0f, -unit, Phi());
    unqiueVertices.emplace_back(-unit, Phi(), 0.0f);
    unqiueVertices.emplace_back(Phi(), 0.0f, -unit);
    
    unqiueVertices.emplace_back(0.0f, unit, -Phi());
    unqiueVertices.emplace_back(unit, -Phi(), 0.0f);
    unqiueVertices.emplace_back(-Phi(), 0.0f, unit);
    
    unqiueVertices.emplace_back(0.0f, -unit, -Phi());
    unqiueVertices.emplace_back(-unit, -Phi(), 0.0f);
    unqiueVertices.emplace_back(-Phi(), 0.0f, -unit);
    
    std::vector<QVector3D> triangles;
    triangles.emplace_back(0,1,2);
    triangles.emplace_back(0,2,3);
    triangles.emplace_back(0,3,8);
    triangles.emplace_back(0,8,4);
    triangles.emplace_back(0,4,1);
    triangles.emplace_back(1,6,5);
    triangles.emplace_back(1,4,6);
    triangles.emplace_back(1,5,2);
    triangles.emplace_back(5,7,2);
//    triangles.emplace_back(5,9,6);
//    triangles.emplace_back(5,9,7);
//    triangles.emplace_back(7,3,2);
//    triangles.emplace_back(7,9,10);
//    triangles.emplace_back(7,3,10);
//    triangles.emplace_back(10,3,8);
//    triangles.emplace_back(10,9,11);
//    triangles.emplace_back(10,8,11);
//    triangles.emplace_back(4,6,11);
//    triangles.emplace_back(4,11,8);
//    triangles.emplace_back(6,11,9);
    
    
    for (uint32_t i = 0; i < triangles.size(); ++i)
    {
        int id1 = triangles[i].x();
        int id2 = triangles[i].y();
        int id3 = triangles[i].z();
        triangle(unqiueVertices[id1].x(), unqiueVertices[id1].y(), unqiueVertices[id1].z(),
                 unqiueVertices[id2].x(), unqiueVertices[id2].y(), unqiueVertices[id2].z(),
                 unqiueVertices[id3].x(), unqiueVertices[id3].y(), unqiueVertices[id3].z());
    }

            
}



void UV_Icosahedron::add(const QVector3D &v, const QVector3D &n)
{
    m_data.push_back(v.x());    
    m_data.push_back(v.y());   
    m_data.push_back(v.z());    
    m_data.push_back(n.x());    
    m_data.push_back(n.y());    
    m_data.push_back(n.z());
    m_count += 6;    
}


void UV_Icosahedron::triangle(GLfloat x1, GLfloat y1, GLfloat z1,
                         GLfloat x2, GLfloat y2, GLfloat z2,
                         GLfloat x3, GLfloat y3, GLfloat z3)
{
    QVector3D n = QVector3D::normal(QVector3D(x2 - x1, y2 - y1, z2 - z1), QVector3D(x3 - x1, y3 - y1, z3 - z1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
}

