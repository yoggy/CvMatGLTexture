#include "StdAfx.h"
#include "cylinder.h"

#pragma warning(disable : 4005)
#define _USE_MATH_DEFINES
#include "math.h"

Cylinder::Cylinder(void)
	: div_x_(40), div_y_(5), r_(2.0), height_(2.0)
{
	build_mesh_();
}

Cylinder::~Cylinder(void)
{

}

void Cylinder::build_mesh_()
{
	vertices_.clear();
	uv_.clear();
	triangles_.clear();

	int w = div_x_ + 1;
	int h = div_y_ + 1;

	vertices_.resize(w * h);
	uv_.resize(w * h);
	triangles_.resize(div_x_ * div_y_ * 2);

	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {	
			int idx = x + y * w;

			double px = x / (double)div_x_;
			double py = 1.0 - y / (double)div_y_;

			double th = 2.0 * M_PI * px;

			double vx = r_ * sin(th);
			double vy = height_ * py - height_ / 2;
			double vz = r_ * cos(th);

			vertices_[idx] = Vector3f(vx, vy, vz);

			double u = px;
			double v = 1.0 - py;
			uv_[idx] = Vector2f(u, v);
		}
	}

	int idx = 0;
	for (int y = 0; y < div_y_; ++y) {
		for (int x = 0; x < div_x_; ++x){	
			int base_idx = x + y * w;
			triangles_[idx ++] = TriangleIndex(base_idx, base_idx + 1, base_idx + w + 1);				
			triangles_[idx ++] = TriangleIndex(base_idx + w + 1, base_idx + w, base_idx); 
		}
	}
}

void Cylinder::draw()
{
	int t_count = 0;
	std::vector<TriangleIndex>::const_iterator t;
	for (t = triangles_.begin(); t != triangles_.end(); ++t, ++t_count) {

		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < 3; ++i) {
			int idx = t->idx[i];

			Vector2f uv = uv_[idx];
			glTexCoord2d(uv.x, uv.y);

			Vector3f v = vertices_[idx];
			glVertex3d(v.x, v.y, v.z); 
		}
		glEnd();
	}
}
