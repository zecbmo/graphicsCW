#include "Shapes.h"

shapes::shape shapes::getDiscShape(int resolution)
{
	float interval = (2 * PI)/resolution;
	shape tronsDisc;

	float angle = 0;

	float x, y, z, u, v;
	//Loop for number of segments
	for (int i = 0; i < resolution; i++)
	{
		//Begin sampling at angle 0
		//Calculate x, y, z
	
			x = cos(angle);
			u = (cos(angle) / 2) + 0.5;
	
			y = sin(angle);
			v = (sin(angle) / 2) + 0.5;		

			z = 0;
		
		
	
		
		tronsDisc.vertices.push_back(Vector3(x, y, z));
		tronsDisc.normals.push_back(Vector3(0, 0, 1));
		tronsDisc.UVs.push_back(Vector3(u, v, 0));
		
		
		//	Increase angle by interval
		angle += interval;

		//		(To avoid problems it is sometimes best to clamp the last value back to zero)
		//		We should then have the vertex data for the disc

	}
	
	return tronsDisc;
	
}

shapes::shape shapes::getSphereShape(int resolution)
{
	float t_interval = (2 * PI) / resolution;
	float d_interval = PI / resolution;
	shape sphere;

	float delta = 0;
	float theta = 0;

	sphere.longAndLat.resize(resolution+1);
	

	float x, y, z, u, v;
	//Loop for number of segments
	for (int i = 0; i < resolution+1; i++)
	{

		for (int j = 0; j < resolution; j++)
		{
			x = cos(theta)*sin(delta);
			y = cos(delta);
			z = sin(theta)*sin(delta);
			
			sphere.longAndLat[i].push_back(Vector3(x, y, z));
			sphere.normals.push_back(Vector3(x, y, z));
					
			theta += t_interval;			
		}
		delta += d_interval;
		theta = 0;
	}

	return sphere;

}