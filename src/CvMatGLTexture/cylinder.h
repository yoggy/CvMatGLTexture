#pragma once

#include <vector>

class Vector2f {
public:
	Vector2f() : x(0.0), y(0.0) {}
	Vector2f(const double &_x, const double &_y) : x(_x), y(_y) {}

	double x;
	double y;
};

class Vector3f {
public:
	Vector3f() : x(0.0), y(0.0), z(0.0) {}
	Vector3f(const double &_x, const double &_y, const double &_z) : x(_x), y(_y), z(_z) {}

	double x;
	double y;
	double z;
};

class TriangleIndex {
public:
	TriangleIndex() {
		idx[0] = -1;
		idx[1] = -1;
		idx[2] = -1;
	}
	
	TriangleIndex(const int &idx0, const int &idx1, const int &idx2) {
		idx[0] = idx0;
		idx[1] = idx1;
		idx[2] = idx2;
	}

	int operator[](const unsigned int &i) {
		return idx[i];
	}

	int idx[3];
};

class Mesh 
{
public:
	Mesh();
	virtual ~Mesh();

	void clear();

	virtual void draw();

protected:
	virtual void build_mesh_() = 0;

protected:
	std::vector<Vector3f> vertices_;
	std::vector<Vector2f> uv_;
	std::vector<TriangleIndex> triangles_;
};

class Cylinder : public Mesh
{
public:
	Cylinder();
	virtual ~Cylinder();
	
protected:
	virtual void build_mesh_();

protected:
	int div_x_;
	int div_y_;
	double r_;
	double height_;
};

