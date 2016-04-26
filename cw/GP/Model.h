#ifndef _MODEL_H_
#define _MODEL_H_


// INCLUDES //
#include <Windows.h>
#include <fstream>
#include <gl/gl.h>
#include <gl/glu.h>
using namespace std;


// MY CLASS INCLUDES //
#include "TokenStream.h"
#include <vector>
#include "Vector3.h"
#include "SOIL.h"
#include "GameObject.h"

class Model : public GameObject
{

public:
	
	bool Load(char*  modelFilename, char* textureFilename);
	void Render();
	
private:
	
	void LoadTextureMod(char*);
	bool LoadModel(char*);
	
	int m_vertexCount;
	

	int numOfPolygons;
	vector<float> vertex, normals, texCoords;
	
};

#endif