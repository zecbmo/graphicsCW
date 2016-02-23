#include "Light.h"


void Light::Init(int glLightDefine) //which light to use e.g. GL_LIGHT0
{
	InitHelperFunction(glLightDefine);
	LightTemplateHelperFunction(DEFAULT);
	light_type_ = DIRECTIONAL_LIGHT;
	
}

void Light::Init(int glLightDefine, LightType type, LightTemplate default_light)
{
	InitHelperFunction(glLightDefine);
	LightTemplateHelperFunction(default_light);
	light_type_ = type;
	if (light_type_ == SPOT_LIGHT)
	{
		spot_cutoff_ = 45.0f;
	}
	else
	{
		spot_cutoff_ = 180.0f;
	}
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
	diffuse_[0] = r;
	diffuse_[1] = g;
	diffuse_[2] = b;
	diffuse_[3] = a;
}
void Light::SetDiffuseColour(ColourValues colour_values)
{
	diffuse_[0] = colour_values.r;
	diffuse_[1] = colour_values.g;
	diffuse_[2] = colour_values.b;
	diffuse_[3] = colour_values.a;
}
ColourValues Light::GetDiffuseColour()
{
	float r = diffuse_[0];
	float g = diffuse_[1];
	float b = diffuse_[2];
	float a = diffuse_[3];
	return ColourValues(r, g, b, a);
}

void Light::SetSpecularColour(float r, float g, float b, float a)
{
	specular_[0] = r;
	specular_[1] = g;
	specular_[2] = b;
	specular_[3] = a;
}
void Light::SetSpecularColour(ColourValues colour_values)
{
	specular_[0] = colour_values.r;
	specular_[1] = colour_values.g;
	specular_[2] = colour_values.b;
	specular_[3] = colour_values.a;
}
ColourValues Light::GetSpecularColour()
{
	float r = specular_[0];
	float g = specular_[1];
	float b = specular_[2];
	float a = specular_[3];
	return ColourValues(r, g, b, a);
}
void Light::SetPosition(Vector3 position)
{
	vec_pos_ = position;
	
}
void Light::SetPosition(float x, float y, float z)
{
	vec_pos_.setX(x);
	vec_pos_.setY(y);
	vec_pos_.setZ(z);

}
Vector3 Light::GetPosition()
{
	return vec_pos_;
}

void Light::SetType(LightType type)
{
	light_type_ = type;
	if (light_type_ == SPOT_LIGHT)
	{
		spot_cutoff_ = 45; //best that a default is set as values won't remain on switching to other types
	}
	else
	{
		spot_cutoff_ = 180; //resets the cuttoff to 180 (So it won't act like a spot light if it is a point light)
	}
}
LightType Light::GetType()
{
	return light_type_;
}
void Light::SetSpotDirection(Vector3 direction)
{
	spot_direction_ = direction;
}
void Light::SetSpotDirection(float x, float y, float z)
{
	spot_direction_.setX(x);
	spot_direction_.setY(y);
	spot_direction_.setZ(z);
}
Vector3 Light::GetSpotDirection()
{
	return spot_direction_;
}

void Light::Render()
{
	if (!on_)
	{
		glDisable(gl_light_num_);
	}
	else
	{
		glEnable(gl_light_num_);
		
		float l_type = light_type_; //passed in as the last element within the lights position
		if (light_type_ == SPOT_LIGHT) //Spot light and point light both should = 1
		{
			l_type = 1;
		}

		float position[4] = { vec_pos_.getX(), vec_pos_.getY(), vec_pos_.getZ(), l_type };
		float spot_dir[3] = { spot_direction_.getX(), spot_direction_.getY(), spot_direction_.getZ() };

		if ((spot_cutoff_ != 180) && (spot_cutoff_ > 90 || spot_cutoff_ < 0))
		{
			//throw error here!
			error::ValueError(id_, "spot light cutoff out of range",spot_cutoff_);
			//Make sure to keep cut off within bounds
		}


		glLightfv(gl_light_num_, GL_AMBIENT, ambient_);
		glLightfv(gl_light_num_, GL_DIFFUSE, diffuse_);
		glLightfv(gl_light_num_, GL_SPECULAR, specular_);
		glLightfv(gl_light_num_, GL_POSITION, position);
		glLightfv(gl_light_num_, GL_SPOT_DIRECTION, spot_dir);
		glLightfv(gl_light_num_, GL_SPOT_EXPONENT, &spot_exponent_);	//passed as reference as not glfloats
		glLightfv(gl_light_num_, GL_CONSTANT_ATTENUATION, &constant_attenuation_);
		glLightfv(gl_light_num_, GL_LINEAR_ATTENUATION, &linear_attenuation_);
		glLightfv(gl_light_num_, GL_QUADRATIC_ATTENUATION, &quadratic_attenuation_);
	}

}
void Light::LightTemplateHelperFunction(LightTemplate default_light)
{
	switch (default_light) //Sets up template lights because doing this is tedious
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
void Light::InitHelperFunction(float glLightDefine) //defaults for either init functions
{
	gl_light_num_ = glLightDefine;
	vec_pos_ = Vector3(0.0f, 0.0f, 0.0f);
	spot_direction_ = Vector3(0.0f, 1.0f, 0.0f);
	spot_cutoff_ = 180.0f;
	spot_exponent_ = 0;
	constant_attenuation_ = 1.0f;
	linear_attenuation_ = 0.2f;
	quadratic_attenuation_ = 0.0f;
	on_ = true;
	SetID();

}
void Light::SetID()
{
	switch (gl_light_num_)
	{
	case GL_LIGHT0:		id_ = "GL_LIGHT0";
						break;
	case GL_LIGHT1:		id_ = "GL_LIGHT1";
						break; 
	case GL_LIGHT2:		id_ = "GL_LIGHT2";
						break; 
	case GL_LIGHT3:		id_ = "GL_LIGHT3";
						break; 
	case GL_LIGHT4:		id_ = "GL_LIGHT4";
						break; 
	case GL_LIGHT5:		id_ = "GL_LIGHT5";
						break;
	case GL_LIGHT6:		id_ = "GL_LIGHT6";
						break; 
	case GL_LIGHT7:		id_ = "GL_LIGHT7";
						break;
	}
}