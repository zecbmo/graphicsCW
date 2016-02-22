#include "Light.h"


void Light::Init(int glLightDefine) //which light to use e.g. GL_LIGHT0
{
	gl_light_num_ = glLightDefine;
	SetAllValues(ColourValues(0.5f, 0.5f, 0.5f, 1.0f));
	vec_pos_ = Vector3(1.0f, 1.0f, 0.0f);
    light_type_ =  DIRECTIONAL_LIGHT;
	is_spot_light_ = false;
	spot_direction_ = Vector3(0.0f, 1.0f, 0.0f);
	spot_cutoff_ = 45.0f;
	spot_exponent_ = 0; 
	constant_attenuation_ = 1.0f;
	linear_attenuation_ = 0.2f;
	quadratic_attenuation_ = 0.0f;
	on_ = true;
}

void Light::Init(int glLightDefine, LightType type, LightTemplate default_light)
{
	gl_light_num_ = glLightDefine;
	LightTemplateHelperFunction(default_light);
	vec_pos_ = Vector3(1.0f, 1.0f, 0.0f);
	light_type_ = type;
	if (light_type_ == SPOT_LIGHT)
	{
		is_spot_light_ = true;
	}
	else
	{
		is_spot_light_ = false;
	}
	spot_direction_ = Vector3(0.0f, 1.0f, 0.0f);
	spot_cutoff_ = 45.0f;
	spot_exponent_ = 0;
	constant_attenuation_ = 1.0f;
	linear_attenuation_ = 0.2f;
	quadratic_attenuation_ = 0.0f;
	on_ = true;
}
void Light::SetAllValues(ColourValues ambient, ColourValues diffuse, ColourValues specular)
{
	SetAmbientColour(ambient);
	SetDiffuseColour(diffuse);
	SetSpecularColour(specular);
}
void Light::SetAllValues(ColourValues defaults)
{
	SetAmbientColour(defaults);
	SetDiffuseColour(defaults);
	SetSpecularColour(defaults);
}
void Light::SetAmbientColour(float r, float g, float b, float a)
{
	ambient_[0] = r;
	ambient_[1] = g;
	ambient_[2] = b;
	ambient_[3] = a;
}
void Light::SetAmbientColour(ColourValues colour_values)
{
	ambient_[0] = colour_values.r;
	ambient_[1] = colour_values.g;
	ambient_[2] = colour_values.b;
	ambient_[3] = colour_values.a;
}
ColourValues Light::GetAmbientColour()
{
	float r = ambient_[0];
	float g = ambient_[1];
	float b = ambient_[2];
	float a = ambient_[3];
	return ColourValues(r, g, b, a);
}

void Light::SetDiffuseColour(float r, float g, float b, float a)
{

}
void Light::SetDiffuseColour(ColourValues colour_values)
{

}
ColourValues Light::GetDiffuseColour()
{

}

void Light::SetSpecularColour(float r, float g, float b, float a)
{

}
void Light::SetSpecularColour(ColourValues colour_values)
{

}
ColourValues Light::GetDiffuseColour()
{

}
void Light::SetPosition(Vector3 position)
{

}
void Light::SetPosition(float x, float y, float z)
{

}
Vector3 Light::GetPosition()
{

}

void Light::SetType(LightType type)
{

}
LightType Light::GetType()
{

}
void Light::UpdateValues()
{

}

void Light::Render()
{

}
void Light::LightTemplateHelperFunction(LightTemplate default_light)
{
	switch (default_light)
	{
	case DEFAULT:	SetAmbientColour(ColourValues(0.2f, 0.2f, 0.2f, 1.0f));
					SetDiffuseColour(ColourValues(0.8f, 0.8f, 0.8f, 1.0f));
					SetSpecularColour(ColourValues(0.5f, 0.5f, 0.5f, 1.0f));
					break;
	case AMBIENT:	SetAmbientColour(ColourValues(0.3f, 0.3f, 0.3f, 1.0f));
					SetDiffuseColour(ColourValues(0.8f, 0.8f, 0.8f, 1.0f));
					SetSpecularColour(ColourValues(0.0f, 0.0f, 0.0f, 0.0f));
					break;
	case NATURAL:	SetAmbientColour(ColourValues(0.3f, 0.3f, 0.3f, 1.0f));
					SetDiffuseColour(ColourValues(1.0f, 1.0f, 1.0f, 1.0f));
					SetSpecularColour(ColourValues(0.6f, 0.6f, 0.6f, 1.0f));
					break;
	case SHINY:		SetAmbientColour(ColourValues(0.2f, 0.2f, 0.2f, 1.0f));
					SetDiffuseColour(ColourValues(0.8f, 0.8f, 0.8f, 1.0f));
					SetSpecularColour(ColourValues(1.0f, 1.0f, 1.0f, 1.0f));
					break;
	}
}