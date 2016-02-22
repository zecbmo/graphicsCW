#pragma once

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <vector>

#define PI 3.141592653589793238462643383279502884L /* pi */

using std::vector;




namespace shapes 
{

	struct shape
	{
	public:
		vector<Vector3> vertices;
		vector<Vector3> normals;
		vector<Vector3> UVs;
		vector< vector <Vector3> > longAndLat;

		shape operator=(const shape& b)
		{
			//shape n_shape;
			this->vertices = b.vertices;
			this->normals = b.normals;
			this->UVs = b.UVs;
			this->longAndLat = b.longAndLat;
			return *this;
		}
	};

	shape getDiscShape(int resolution);
	shape getSphereShape(int resolution);

	



}

