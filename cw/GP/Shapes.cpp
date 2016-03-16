#include "Shapes.h"

Shapes::Shapes()
{
}

Shapes::~Shapes()
{
}

void Shapes::CreateShape(ShapesType type, float resolution)
{
	type_ = type;
	is_quad_ = false;

	switch (type_)
	{
	case DISC:
		InitDisc(resolution);
		break;
	case SPHERE:
		InitSphere(resolution);
		is_quad_ = true;
		break;
	case CUBE_ST:
		InitCube();
		is_quad_ = true;
		break;
	case CUBE_CT:
		InitCube(false);
		is_quad_ = true;
		break;
	case PLANE:
		InitPlane();
		is_quad_ = true;
		break;
	case PLANE_TILED:
		InitPlane(resolution);
		is_quad_ = true;
		break;
	case SPHERE_HALF_UV:
		InitSphere(resolution);
		is_quad_ = true;
		break;
	default:
		break;
	}
}

void Shapes::CreateCustomQuad(Vector3 a, Vector3 b, Vector3 c, Vector3 d, float depth)
{
	//this function will allow ypou to create custom shapes based on 4 points and a given depth...
	// a == bottom left corner
	// b == top left
	// c == top right
	// d == bottom right
	//with these 4 points and the depth you can create any qaud
	//based on looking down the z axis at the xy plane
	//Points must be placed in the order as described, or it could lead to rendering problems
	is_quad_ = true;

	float ax = a.GetX();
	float ay = a.GetY();
	float az = a.GetZ();

	float bx = b.GetX();
	float by = b.GetY();
	float bz = b.GetZ();

	float cx = c.GetX();
	float cy = c.GetY();
	float cz = c.GetZ();

	float dx = d.GetX();
	float dy = d.GetY();
	float dz = d.GetZ();

	vertices_ =
	{
		//front face
		ax, ay, az,//bottom left		
		bx, by, bz, //top left
		cx, cy, cz,  //top right
		dx, dy, dz,	//bottom right

		//back face
		dx, dy, dz - depth,	//bottom right	
		cx, cy, cz - depth,  //top right
		bx, by, bz - depth, //top left
		ax, ay, az - depth,//bottom left		
						

		//left face
		ax, ay, az - depth,//bottom left		
		bx, by, bz - depth, //top left
		bx, by, bz, //top left
		ax, ay, az,//bottom left

		//right face
		dx, dy, dz,	//bottom right	
		cx, cy, cz,  //top right
		cx, cy, cz - depth,  //top right	
		dx, dy, dz - depth,	//bottom right	
		

	   //top face
		bx, by, bz, //top left		
		bx, by, bz - depth, //top left
		cx, cy, cz - depth,  //top right
		cx, cy, cz,  //top right


					//bottom face
		ax, ay, az - depth,//bottom left			
		dx, dy, dz - depth,	//bottom right
		dx, dy, dz, //bottom left
		ax, ay, az,//bottom left	


	};

	for (int i = 0; i < 6; i++)
	{
		UVs_.push_back(0);
		UVs_.push_back(1);
		UVs_.push_back(0);
		UVs_.push_back(0);
		UVs_.push_back(1);
		UVs_.push_back(0);
		UVs_.push_back(1);
		UVs_.push_back(1);
	}

	//front face normals
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(0);
		normals_.push_back(1);

	}

	//back face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(0);
		normals_.push_back(-1);

	}

	//left face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(-1);
		normals_.push_back(0);
		normals_.push_back(0);

	}
	//right face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(1);
		normals_.push_back(0);
		normals_.push_back(0);

	}
	//top face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(-1);
		normals_.push_back(0);

	}
	//bottom face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(1);
		normals_.push_back(0);

	}
}

void Shapes::Draw()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertices_.data());
	glTexCoordPointer(2, GL_FLOAT, 0, UVs_.data());
	glNormalPointer(GL_FLOAT, 0, normals_.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (is_quad_)
	{
		glDrawArrays(GL_QUADS, 0, vertices_.size() / 3); //vertex size / 3
	}
	else
	{
		glDrawArrays(GL_TRIANGLES, 0, vertices_.size() / 3); //vertex size / 3
	}
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);





}

void Shapes::InitDisc(float resolution)
{
	//creates a disc based on the parametric equation of a sphere
	float interval = (2 * PI) / resolution;
	float angle = 0;

	float x, y, z, u, v;
	
	x = cos(angle);
	u = (cos(angle) / 2) + 0.5;
	y = sin(angle);
	v = (sin(angle) / 2) + 0.5;
	z = 0;

	for (int i = 0; i < resolution; i++)
	{


		//push back centre
		vertices_.push_back(0);
		vertices_.push_back(0);
		vertices_.push_back(0);

		UVs_.push_back(0.5);
		UVs_.push_back(0.5);

		//push back the point at side of disc
		vertices_.push_back(x);
		vertices_.push_back(y);
		vertices_.push_back(z);

		UVs_.push_back(u);
		UVs_.push_back(v);


		//push back next point on the disc... as pushing all 3 points of the face on to the vertex array 
		//it was easier to simply calculate the next point
		if (i == resolution)
		{
			//wraps to 0 if it is the final point
			x = cos(0);
			u = (cos(0) / 2) + 0.5;
			y = sin(0);
			v = (sin(0) / 2) + 0.5;
			z = 0;
		}
		else
		{
			angle += interval;

			x = cos(angle);
			u = (cos(angle) / 2) + 0.5;
			y = sin(angle);
			v = (sin(angle) / 2) + 0.5;
			z = 0;
		}
		//push back next point
		vertices_.push_back(x);
		vertices_.push_back(y);
		vertices_.push_back(z);

		UVs_.push_back(u);
		UVs_.push_back(v);

		for (int j = 0; j < 3; j++) //all normals are the same so pushed all at once
		{
			normals_.push_back(0);
			normals_.push_back(0);
			normals_.push_back(1);
		}

		
	}
}

void Shapes::InitSphere(float resolution)
{
	//loops arround longitude and latitude creating a vector of 3d points (vector3)
	//once done it loops trough the vector of 3d points pushing them on to the vertex array in the correct order

	float t_interval = (2 * PI) / resolution;
	float d_interval = PI / resolution;	

	float delta = 0;
	float theta = 0;

	longAndLat_.resize(resolution + 1);

	float x, y, z, u, v;

	//Loop and create first, the vector of 3d points
	for (int i = 0; i < resolution + 1; i++)
	{

		for (int j = 0; j < resolution; j++)
		{
			x = cos(theta)*sin(delta);
			y = cos(delta);
			z = sin(theta)*sin(delta);

			longAndLat_[i].push_back(Vector3(x, y, z));
			
			theta += t_interval;
		}
		delta += d_interval;
		theta = 0;
	}
	//second loop to put 3d points in correct order in vertex array
	for (int i = 0; i < resolution; i++)
	{
		for (int j = 0; j < resolution; j++)
		{
			int offset = 1;
			int offset2 = 1;

			if (j + 1 >= resolution)
			{
				offset = 0 - j;
			}
					
			float x1 = longAndLat_[i][j].GetX();
			float x2 = longAndLat_[i+ offset2][j].GetX();
			float x3 = longAndLat_[i][j+ offset].GetX();
			float x4 = longAndLat_[i+ offset2][j+ offset].GetX();


			float y1 = longAndLat_[i][j].GetY();
			float y2 = longAndLat_[i+ offset2][j].GetY();
			float y3 = longAndLat_[i][j + offset].GetY();
			float y4 = longAndLat_[i + offset2][j + offset].GetY();

			float z1 = longAndLat_[i][j].GetZ();
			float z2 = longAndLat_[i + offset2][j].GetZ();
			float z3 = longAndLat_[i][j + offset].GetZ();
			float z4 = longAndLat_[i + offset2][j + offset].GetZ();
			
			//pushing points back
			vertices_.push_back(x1);
			vertices_.push_back(y1);
			vertices_.push_back(z1);

			//get the uv points based on the x,y,z values
			float u1 = GetUSphere(x1, z1);
			float v1 = GetVSphere(y1);


			vertices_.push_back(x3);
			vertices_.push_back(y3);
			vertices_.push_back(z3);

			float u3 = GetUSphere(x3, z3);
			float v3 = GetVSphere(y3);

			vertices_.push_back(x4);
			vertices_.push_back(y4);
			vertices_.push_back(z4);

			float u4 = GetUSphere(x4, z4);
			float v4 = GetVSphere(y4);

			vertices_.push_back(x2);
			vertices_.push_back(y2);
			vertices_.push_back(z2);

			float u2 = GetUSphere(x2, z2);
			float v2 = GetVSphere(y2);

			//the following safety checks are for wrapping the sphere at the edges
			if (type_ == SPHERE)
			{
				if (u4 < 0.75 && u1 > 0.75)
				{
					u4 += 1.0;
				}
				else if (u4 > 0.75 && u1 < 0.75)
				{
					u4 -= 1.0;
				}

				if (u3 < 0.75 && u1 > 0.75)
				{
					u3 += 1.0;
				}
				else if (u3 > 0.75 && u1 < 0.75)
				{
					u3 -= 1.0;
				}
			}
			else
			{
				float compare = 1.5;
				float value = 2;
				if (u4 < compare && u1 > compare)
				{
					u4 += value;
				}
				else if (u4 > compare && u1 < compare)
				{
					u4 -= value;
				}

				if (u3 < compare && u1 > compare)
				{
					u3 += value;
				}
				else if (u3 > compare && u1 < compare)
				{
					u3 -= value;
				}
			}
			//push all uvs back after the safety checks
			UVs_.push_back(u1);
			UVs_.push_back(v1);
			UVs_.push_back(u3);
			UVs_.push_back(v3);
			UVs_.push_back(u4);
			UVs_.push_back(v4);
			UVs_.push_back(u2);
			UVs_.push_back(v2);
		}
	}
	normals_ = vertices_;
}

void Shapes::InitCube(bool single_texture)
{
	float x = 0.5;
	float y = 0.5;
	float z = 0.5;
	
	vertices_ =
	{
		//front face
		-x, -y, z,//bottom left		
		-x, y, z, //top left
		x, y, z,  //top right
		x, -y, z,	//bottom right

		//back face
		x, -y, -z,	//bottom right
		x, y, -z,  //top right
		-x, y, -z, //top left
		- x, -y, -z,//bottom left			

		//left face
		-x, -y, -z,//bottom left		
		-x, y, -z, //top left
		-x, y, z,  //top right
		-x, -y, z,	//bottom right

		//right face
		x, -y, z,	//bottom right
		x, y, z,  //top right
		x, y, -z, //top left
		x, -y, -z,//bottom left		
		
		//top face
		-x, y, z,//bottom left		
		-x, y, -z, //top left
		x, y, -z,  //top right
		x, y, z,	//bottom right
		

		//bottom face
		x, -y, z,	//bottom right
		x, -y, -z,  //top right
		-x, -y, -z, //top left
		-x, -y, z,//bottom left		
		

	};

	//match the uv for each face
	if (single_texture)
	{
		for (int i = 0; i < 6; i++)
		{
			UVs_.push_back(0);
			UVs_.push_back(1);
			UVs_.push_back(0);
			UVs_.push_back(0);
			UVs_.push_back(1);
			UVs_.push_back(0);
			UVs_.push_back(1);
			UVs_.push_back(1);
		}
	}
	else
	{
		float a = 0;
		float b = 0.25;
		float c = 0.5;
		float d = 0.75;
		float e = 1;
		float f = 0;
		float g = 1.0 / 3.0;
		float h = 1.0 / 1.5;
		float i = 1;
		


		UVs_ =
		{
			//front face
			b,h,
			b,g,
			c,g,
			c,h,
			
			//back face
			d,h,
			d,g,
			e,g,
			e,h,
			
			//left face
			a,h,
			a,g,
			b,g,
			b,h,		

			//right face
			c,h,
			c,g,
			d,g,
			d,h,

			//top face
			b,g,
			b,f,
			c,f,
			c,g,

			//bottom face
			c,h,
			c,i,
			b,i,
			b,h,
		};
	}
	//front face normals
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(0);
		normals_.push_back(1);

	}

	//back face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(0);
		normals_.push_back(-1);

	}

	//left face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(-1);
		normals_.push_back(0);
		normals_.push_back(0);

	}
	//right face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(1);
		normals_.push_back(0);
		normals_.push_back(0);

	}
	//top face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(-1);
		normals_.push_back(0);

	}
	//bottom face
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(1);
		normals_.push_back(0);

	}

}
void Shapes::InitPlane(float resolution)
{
	float x = 0.5;
	float y = 0.5;
	float z = 0;

	vertices_ = 
	{		
		-x, -y, z,//bottom left		
		-x, y, z, //top left
		x, y, z,  //top right
		x, -y, z	//bottom right
	};

	UVs_ =
	{
		0, 1 * resolution, //bottom left	
		0, 0, //top left
		1 * resolution, 0, //top right
		1 * resolution, 1 * resolution, //bottom right
	};
	//add normals to each of the 4 corners
	for (int i = 0; i < 4; i++)
	{
		normals_.push_back(0);
		normals_.push_back(0);
		normals_.push_back(1);

	}

}



float Shapes::GetUSphere(float x, float z)
{
	float num = 0;

	if (type_ == SPHERE)
	{
		num = 0.5 + (atan2(z, x) / (2 * PI));
	}
	else
	{
		num = (0.5 + (atan2(z, x) / (2 * PI)))*2;
	}
	return num;
}

float Shapes::GetVSphere(float y)
{
	return 0.5 + (asin(y) / PI);
}
