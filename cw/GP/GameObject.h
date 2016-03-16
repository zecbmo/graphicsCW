#pragma once
#include "Shapes.h"
#include "Materials.h"
#include "Vector3.h"
#include "SOIL.h"


class GameObject
{
public:
	GameObject() {};
	~GameObject() {};

	virtual void Init();
	virtual void Update();
	virtual void Render();

	inline void SetPosition(Vector3 pos) { position_ = pos; };
	inline Vector3 GetPosition() { return position_; };
	inline void SetRotation(float x_rot, float y_rot, float z_rot) { rotation_ = Vector3(x_rot, y_rot, z_rot); };
	inline Vector3 GetRotation() { return rotation_; };
	inline void SetScale(float x_scale, float y_scale, float z_scale) { scale_ = Vector3(x_scale, y_scale, z_scale); };
	inline Vector3 GetScale() { return scale_; };
	inline Material* GetMaterial() { return &material_; };

protected:
	GLuint LoadTexture(std::string filename);
	Vector3 position_;
	Vector3 rotation_;
	Vector3 scale_;

	GLuint texture_;
	Material material_;
	Shapes shape_;

};

