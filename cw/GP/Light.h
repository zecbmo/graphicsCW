#ifndef LIGHTING_H_
#define LIGHTING_H_

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"

//Questions to ask paul
	//Spot lights direction - should it be normalised??

//Light.h Created by Gary McCartan 1402860
//Lecture materials and http://archive.gamedev.net/archive/reference/programming/features/superquadric/page2.html used as reference

enum LightTemplate{DEFAULT, AMBIENT, NATURAL, SHINY};
enum LightType {DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT};
enum LightColour {RED_LIGHT, BLUE_LIGHT, GREEN_LIGHT, PINK_LIGHT, ORANGE_LIGHT, YELLOW_LIGHT, WHITE_LIGHT};

struct ColourValues 
{
	//Rather than passing array values and returning them, 
	//this helper struct will allow us to pass colour values to the Light Class
	ColourValues() {} ;
	ColourValues(float r1, float g1, float b1, float a1) { r = r1; g = g1, b = b1; a = a1; };
	float r, g, b, a;
};

class Light
{
	//from this light class, you will be able to create and manage different light sources
	//on initialisation the type can be defined alongside some templates that will set up the light

public:
	Light() {};
	~Light() {};

	void Init(int glLightDefine = GL_LIGHT0); //the defualt int will set up the default lights 
	void Init(int glLightDefine, LightType type, LightTemplate default_light = DEFAULT); //passing an enum type I will have templates for different types of lights
																												
	void SetAllValues(ColourValues ambient, ColourValues diffuse, ColourValues specular);
	void SetAllValues(ColourValues defaults);

	void SetAmbientColour(float r, float g, float b, float a);
	void SetAmbientColour(ColourValues colour_values);
	ColourValues GetAmbientColour();

	void SetDiffuseColour(float r, float g, float b, float a);
	void SetDiffuseColour(ColourValues colour_values);
	ColourValues GetDiffuseColour();

	void SetSpecularColour(float r, float g, float b, float a);
	void SetSpecularColour(ColourValues colour_values);
	ColourValues GetDiffuseColour();

	void SetPosition(Vector3 position);
	void SetPosition(float x, float y, float z);
	Vector3 GetPosition();

	void SetType(LightType type);
	LightType GetType();

	void UpdateValues();

	void Render();

private:
	//helper functions
	void LightTemplateHelperFunction(LightTemplate default_light);

	//member variables
	int gl_light_num_;
						
	float ambient_[4]; //reminders:: comes from everywhere - minimum light value
	float diffuse_[4]; //from a particular direction - calculated using light and surface normal
	float specular_[4]; //Bounces off shape - shiny shiny
	

	float position_[4]; //rather than manipulating the position array which contains the light type
	Vector3 vec_pos_; //a vector 3 position will be stored and the values passed in when updating the light
	LightType light_type_; //contains the last info for the position array determining the type

	bool is_spot_light_;
	Vector3 spot_direction_; // the normailised directional vector the light is going
	float spot_cutoff_; //mustc be between 0 and 90
	float spot_exponent_; //default is 0

	float constant_attenuation_;
	float linear_attenuation_;
	float quadratic_attenuation_;

	bool on_;

};

#endif