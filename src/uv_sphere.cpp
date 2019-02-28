

#include <uv_sphere.hpp>
#include <qmath.h>

UV_Sphere::UV_Sphere()
    : m_count(0)
{

    // Build Vertex List
    std::vector<QVector3D> vertices;    
    vertices.emplace_back(0.0f, Radius(), 0.0f);
	for (uint32_t j = 0; j < Parallels() - 1; ++j)
	{
		double const polar = M_PI * double(j+1) / double(Parallels());
		double const sp = std::sin(polar);
		double const cp = std::cos(polar);
		for (uint32_t i = 0; i < Meridians(); ++i)
		{
			double const azimuth = 2.0 * M_PI * double(i) / double(Meridians());
			double const sa = std::sin(azimuth);
			double const ca = std::cos(azimuth);
			double const x = sp * ca * Radius();
			double const y = cp * Radius();
			double const z = sp * sa * Radius();
			vertices.emplace_back(x, y, z);
		}
	}
	vertices.emplace_back(0.0f, -Radius(), 0.0f);

    
	for (uint32_t i = 0; i < Meridians(); ++i)
	{
		uint32_t const a = i + 1;
		uint32_t const b = (i + 1) % Meridians() + 1;
		triangle(vertices[0].x(), vertices[0].y(), vertices[0].z(),
                 vertices[b].x(), vertices[b].y(), vertices[b].z(),
                 vertices[a].x(), vertices[a].y(), vertices[a].z());
	}

	for (uint32_t j = 0; j < Parallels() - 2; ++j)
	{
		uint32_t aStart = j * Meridians() + 1;
		uint32_t bStart = (j + 1) * Meridians() + 1;
		for (uint32_t i = 0; i < Meridians(); ++i)
		{
			const uint32_t a = aStart + i;
			const uint32_t a1 = aStart + (i + 1) % Meridians();
			const uint32_t b = bStart + i;
			const uint32_t b1 = bStart + (i + 1) % Meridians();
            quad(vertices[a].x(), vertices[a].y(), vertices[a].z(),
                 vertices[a1].x(), vertices[a1].y(), vertices[a1].z(),
                 vertices[b1].x(), vertices[b1].y(), vertices[b1].z(),
                 vertices[b].x(), vertices[b].y(), vertices[b].z());
		}
	}

	for (uint32_t i = 0; i < Meridians(); ++i)
	{
		uint32_t const a = i + Meridians() * (Parallels() - 2) + 1;
		uint32_t const b = (i + 1) % Meridians() + Meridians() * (Parallels() - 2) + 1;
        triangle(vertices[vertices.size() - 1].x(), vertices[vertices.size() - 1].y(), vertices[vertices.size() - 1].z(),
                 vertices[a].x(), vertices[a].y(), vertices[a].z(),
                 vertices[b].x(), vertices[b].y(), vertices[b].z());
	}
            
}



void UV_Sphere::add(const QVector3D &v, const QVector3D &n)
{
    m_data.push_back(v.x());    
    m_data.push_back(v.y());   
    m_data.push_back(v.z());    
    m_data.push_back(n.x());    
    m_data.push_back(n.y());    
    m_data.push_back(n.z());
    m_count += 6;    
}

void UV_Sphere::quad(GLfloat x1, GLfloat y1, GLfloat z1,
                     GLfloat x2, GLfloat y2, GLfloat z2,
                     GLfloat x3, GLfloat y3, GLfloat z3,
                     GLfloat x4, GLfloat y4, GLfloat z4)
{
    QVector3D n = QVector3D::normal(QVector3D(x2 - x1, y2 - y1, z2 - z1), QVector3D(x4 - x1, y4 - y1, z4 - z1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x4, y4, z4), n);

    add(QVector3D(x3, y3, z3), n);
    add(QVector3D(x4, y4, z4), n);
    add(QVector3D(x2, y2, z2), n);
}

void UV_Sphere::triangle(GLfloat x1, GLfloat y1, GLfloat z1,
                         GLfloat x2, GLfloat y2, GLfloat z2,
                         GLfloat x3, GLfloat y3, GLfloat z3)
{
    QVector3D n = QVector3D::normal(QVector3D(x2 - x1, y2 - y1, z2 - z1), QVector3D(x3 - x1, y3 - y1, z3 - z1));

    add(QVector3D(x1, y1, z1), n);
    add(QVector3D(x2, y2, z2), n);
    add(QVector3D(x3, y3, z3), n);
}

