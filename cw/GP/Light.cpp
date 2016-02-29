#include "Light.h"


void Light::Init(int gl_light_define) //which light to use e.g. GL_LIGHT0
{
	InitHelperFunction(gl_light_define);
	SetLightByTemplate(LIGHT_DEFAULT);
	light_type_ = DIRECTIONAL_LIGHT;
	
}

void Light::Init(int gl_light_define, LightType type, LightTemplate default_light)
{
	InitHelperFunction(gl_light_define);
	SetLightByTemplate(default_light);
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
void Light::SetPosition(Vector3 position)
{
	vec_pos_ = position;
	
}
void Light::SetPosition(float x, float y, float z)
{
	vec_pos_.SetX(x);
	vec_pos_.SetY(y);
	vec_pos_.SetZ(z);

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
	spot_direction_.SetX(x);
	spot_direction_.SetY(y);
	spot_direction_.SetZ(z);
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

		float position[4] = { vec_pos_.GetX(), vec_pos_.GetY(), vec_pos_.GetZ(), l_type };
		float spot_dir[3] = { spot_direction_.GetX(), spot_direction_.GetY(), spot_direction_.GetZ() };

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
void Light::SetLightByTemplate(LightTemplate default_temp)
{
	switch (default_temp) //Sets up template lights because doing this is tedious
	{
	case LIGHT_DEFAULT:
		SetAmbientColour(Colour_RGBA(0.2f, 0.2f, 0.2f, 1.0f));
		SetDiffuseColour(Colour_RGBA(0.8f, 0.8f, 0.8f, 1.0f));
		SetSpecularColour(Colour_RGBA(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	case AMBIENT:
		SetAmbientColour(Colour_RGBA(0.3f, 0.3f, 0.3f, 1.0f));
		SetDiffuseColour(Colour_RGBA(0.8f, 0.8f, 0.8f, 1.0f));
		SetSpecularColour(Colour_RGBA(0.2f, 0.2f, 0.2f, 1.0f));
		break;
	case NATURAL:
		SetAmbientColour(Colour_RGBA(0.3f, 0.3f, 0.3f, 1.0f));
		SetDiffuseColour(Colour_RGBA(1.0f, 1.0f, 1.0f, 1.0f));
		SetSpecularColour(Colour_RGBA(0.6f, 0.6f, 0.6f, 1.0f));
		break;
	case SHINY:
		SetAmbientColour(Colour_RGBA(0.2f, 0.2f, 0.2f, 1.0f));
		SetDiffuseColour(Colour_RGBA(0.8f, 0.8f, 0.8f, 1.0f));
		SetSpecularColour(Colour_RGBA(1.0f, 1.0f, 1.0f, 1.0f));
		break;
	case PURE_WHITE:
		SetAllValues(Colour_RGBA(1, 1, 1, 1));
		break;
	}
}
void Light::SetColourByTemplate(Colour colour, ColourModifier modifier)
{
	switch (colour)
	{
	case RED:
		SetAmbientColour(1.0f, 0.2f, 0.2f, 1);
		SetDiffuseColour(1.0f, 0.2f, 0.2f, 1);
		SetSpecularColour(0.7, 0.1f, 0.1f, 1);
		DisableValue(modifier);
		break;
	case BLUE:
		SetAmbientColour(0.2f, 0.2f, 1.0f, 1);
		SetDiffuseColour(0.2f, 0.2f, 1.0f, 1);
		SetSpecularColour(0.1, 0.1f, 0.7f, 1);
		DisableValue(modifier);
		break;
	case GREEN:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case PINK:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case ORANGE:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case YELLOW:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case PURPLE:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case BROWN:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case BLACK:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	case WHITE:
		/*SetAmbientColour();
		SetDiffuseColour();
		SetSpecularColour();*/
		DisableValue(modifier);
		break;
	}



}