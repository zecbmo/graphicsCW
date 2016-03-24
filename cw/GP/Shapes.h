#pragma once
#include <Windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
#include "Vector3.h"
#include "ErrorSystem.h"

#define PI 3.141592653589793238462643383279502884L /* pi */

enum ShapesType {DISC, SPHERE, CUBE_ST, CUBE_CT, PLANE, PLANE_TILED, SPHERE_HALF_UV};
//st = single texture: one texture laoded on to all sides of the cube
//ct = cube texture: one image has all the textures on it, layed out as an unwrapped cube

//lecture slides used as reference + http://www.cse.msu.edu/~cse872/tutorial4.html for the uv map of the sphere

//The shapes class will only contain information on vertex's, normals and uv points
//Will include the above shape "types"
//Essentially a mesh class, but limited to certain shapes

class Shapes
{
public:
	Shapes();
	~Shapes();

	void CreateShape(ShapesType type, float resolution = 20);   //the initialiser function
	void CreateCustomQuad(Vector3 a, Vector3 b, Vector3 c, Vector3 d, float depth);
	void CreateCone(float height, float resolution = 20);
	void CreateCylinder(float resolution, float height);
	void Draw();
private:
	void InitDisc(float resolution);
	void InitSphere(float resolution);
	void InitCube(bool single_texture = true);
	void InitPlane(float resolution = 1); //resolution equals one as the default plane won't tile
	

	float GetUSphere(float x, float y);
	float GetVSphere(float y);

	bool is_quad_;

	ShapesType type_; //shape type saved to 

	std::vector<float> vertices_, normals_, UVs_;
	
	std::vector< std::vector <Vector3> > longAndLat_; //used for spheres

	Shapes operator=(const Shapes& b)
	{
		//shape n_shape;
		this->vertices_ = b.vertices_;
		this->normals_ = b.normals_;
		this->UVs_ = b.UVs_;
		this->longAndLat_ = b.longAndLat_;
		return *this;
	}

};

