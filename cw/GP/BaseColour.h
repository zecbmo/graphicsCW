#ifndef BASE_COLOUR_
#define BASE_COLOUR_

#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <string>
#include "ErrorSystem.h"

enum ColourModifier {NO_AMBIENT, NO_DIFFUSE, NO_SPECULAR, NONE};
enum DefaultTemplate { DEFAULT, AMBIENT, NATURAL, SHINY, PURE_WHITE }; //sets default colours for lights/Materials
enum Colour {	RED, BLUE, GREEN, PINK, ORANGE, YELLOW, PURPLE,			//Able to quickly set default colours for materials/lights
				BROWN, BLACK, WHITE, PROPERTIES_ONLY, MATERIAL_DEFAULT}; //Then can be ajusted to suit the property

																					
struct Colour_RGBA
{
	//Rather than passing array values and returning them, 
	//this helper struct will allow us to pass colour values to the Light Class
	Colour_RGBA() {};
	Colour_RGBA(float r1, float g1, float b1, float a1) { r = r1; g = g1, b = b1; a = a1; };
	
	float r, g, b, a;

	Colour_RGBA operator=(Colour_RGBA *rhs) 
	{
		this->r = rhs->r;
		this->g = rhs->g;
		this->b = rhs->b;
		this->a = rhs->a;
	}

};

class BaseColour //a parent class of the materials and light classes as the both share colours as a data memeber
{					//Shouldn't be used directly 
public:
	BaseColour() {};
	~BaseColour() {};

	void SetByTemplate(DefaultTemplate default_temp);

	
	void DisableValue(ColourModifier colour);
	void SetAllValues(Colour_RGBA ambient, Colour_RGBA diffuse, Colour_RGBA specular);
	void SetAllValues(Colour_RGBA defaults);
	void SetAllValues(float r, float g, float b, float a);
	void ResetAllValuesToZero(); 
	void SetAmbientColour(float r, float g, float b, float a);
	void SetAmbientColour(Colour_RGBA colour_values);
	void ResetAmbientToZero();
	Colour_RGBA GetAmbientColour();
	void SetDiffuseColour(float r, float g, float b, float a);
	void SetDiffuseColour(Colour_RGBA colour_values);
	void ResetDiffuseToZero();
	Colour_RGBA GetDiffuseColour();
	void SetSpecularColour(float r, float g, float b, float a);
	void SetSpecularColour(Colour_RGBA colour_values);
	void ResetSpecularToZero();
	Colour_RGBA GetSpecularColour();

protected:
	float ambient_[4]; //reminders:: comes from everywhere - minimum light value
	float diffuse_[4]; //from a particular direction - calculated using light and surface normal
	float specular_[4]; //Bounces off shape - shiny shiny
};

#endif