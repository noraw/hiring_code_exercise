

#include <uv_icosahedron.hpp>
#include <qmath.h>

UV_Icosahedron::UV_Icosahedron()
    : m_count(0)
{
    createInitialShape();
}

void UV_Icosahedron::createInitialShape()
{
    // make sure to clear out the previous data
    m_data.clear();
    m_count = 0;
    
    // Build Vertex List
    unqiueVertices.clear();
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
    
    
    // create a list of the vertices for each triangle
    triangles.clear();
    triangles.emplace_back(1,0,2);
    triangles.emplace_back(2,0,3);
    triangles.emplace_back(3,0,8);
    triangles.emplace_back(8,0,4);
    triangles.emplace_back(4,0,1);
    triangles.emplace_back(6,1,5);
    triangles.emplace_back(4,1,6);
    triangles.emplace_back(5,1,2);
    triangles.emplace_back(7,5,2);
    triangles.emplace_back(6,5,9);
    triangles.emplace_back(5,7,9);
    triangles.emplace_back(3,7,2);
    triangles.emplace_back(9,7,10);
    triangles.emplace_back(10,7,3);
    triangles.emplace_back(10,3,8);
    triangles.emplace_back(9,10,11);
    triangles.emplace_back(8,11,10);
    triangles.emplace_back(4,6,11);
    triangles.emplace_back(8,4,11);
    triangles.emplace_back(11,6,9);
    
    createShapeData();
}
    
void UV_Icosahedron::createShapeData() {
    //create all the triangles
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

void UV_Icosahedron::subdivide()
{
    std::vector<QVector3D> newTriangles;
    for (uint32_t i = 0; i < triangles.size(); ++i)
    {
        int id1 = triangles[i].x();
        int id2 = triangles[i].y();
        int id3 = triangles[i].z();
        QVector3D edge1 = splitEdge(id1, id2);
        QVector3D edge2 = splitEdge(id2, id3);
        QVector3D edge3 = splitEdge(id3, id1);
        int v1 = unqiueVertices.size();
        unqiueVertices.emplace_back(edge1);
        int v2 = unqiueVertices.size();
        unqiueVertices.emplace_back(edge2);
        int v3 = unqiueVertices.size();
        unqiueVertices.emplace_back(edge3);
        
        newTriangles.emplace_back(id1,v1,v3);
        newTriangles.emplace_back(v1,id2,v2);
        newTriangles.emplace_back(v2,id3,v3);
        newTriangles.emplace_back(v1,v2,v3);
    }
    triangles = newTriangles;
    createShapeData();
}

QVector3D UV_Icosahedron::splitEdge(int id1, int id2)
{
    QVector3D centroid = (unqiueVertices[id1] + unqiueVertices[id2])/2;
    centroid.normalize();
    centroid = centroid * radius;
    return centroid;
}

void UV_Icosahedron::setTesselation(unsigned int level)
{
    // I set the max number of sub divisions to be 6 since anything more than
    // that results in a delay with the slider. Also, at this level it already looks like a sphere.
    int maxDivisions = 6;
    int newFactor = round(level/100.0f * maxDivisions);
    if(tesselation_factor != newFactor) {
        tesselation_factor = newFactor;
        createInitialShape();
        for (uint32_t i = 0; i < tesselation_factor; ++i)
        {
            subdivide();
        }
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

