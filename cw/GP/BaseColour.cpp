#include "BaseColour.h"





void BaseColour::SetAllValues(Colour_RGBA ambient, Colour_RGBA diffuse, Colour_RGBA specular)
{
	SetAmbientColour(ambient);
	SetDiffuseColour(diffuse);
	SetSpecularColour(specular);
}
void BaseColour::SetAllValues(Colour_RGBA defaults)
{
	SetAmbientColour(defaults);
	SetDiffuseColour(defaults);
	SetSpecularColour(defaults);
}
void BaseColour::SetAllValues(float r, float g, float b, float a)
{
	SetAmbientColour(Colour_RGBA(r,g,b,a));
	SetDiffuseColour(Colour_RGBA(r, g, b, a));
	SetSpecularColour(Colour_RGBA(r, g, b, a));
}
void BaseColour::ResetAllValuesToZero()
{
	SetAmbientColour(0, 0, 0, 0);
	SetDiffuseColour(0, 0, 0, 0);
	SetSpecularColour(0, 0, 0, 0);


}
void BaseColour::SetAmbientColour(float r, float g, float b, float a)
{
	ambient_[0] = r;
	ambient_[1] = g;
	ambient_[2] = b;
	ambient_[3] = a;
}
void BaseColour::SetAmbientColour(Colour_RGBA colour_values)
{
	ambient_[0] = colour_values.r;
	ambient_[1] = colour_values.g;
	ambient_[2] = colour_values.b;
	ambient_[3] = colour_values.a;
}
void BaseColour::ResetAmbientToZero()
{
	SetAmbientColour(0, 0, 0, 0);
}
Colour_RGBA BaseColour::GetAmbientColour()
{
	float r = ambient_[0];
	float g = ambient_[1];
	float b = ambient_[2];
	float a = ambient_[3];
	return Colour_RGBA(r, g, b, a);
}

void BaseColour::SetDiffuseColour(float r, float g, float b, float a)
{
	diffuse_[0] = r;
	diffuse_[1] = g;
	diffuse_[2] = b;
	diffuse_[3] = a;
}
void BaseColour::SetDiffuseColour(Colour_RGBA colour_values)
{
	diffuse_[0] = colour_values.r;
	diffuse_[1] = colour_values.g;
	diffuse_[2] = colour_values.b;
	diffuse_[3] = colour_values.a;
}
void BaseColour::ResetDiffuseToZero()
{
	SetDiffuseColour(0, 0, 0, 0);
}
Colour_RGBA BaseColour::GetDiffuseColour()
{
	float r = diffuse_[0];
	float g = diffuse_[1];
	float b = diffuse_[2];
	float a = diffuse_[3];
	return Colour_RGBA(r, g, b, a);
}

void BaseColour::SetSpecularColour(float r, float g, float b, float a)
{
	specular_[0] = r;
	specular_[1] = g;
	specular_[2] = b;
	specular_[3] = a;
}
void BaseColour::SetSpecularColour(Colour_RGBA colour_values)
{
	specular_[0] = colour_values.r;
	specular_[1] = colour_values.g;
	specular_[2] = colour_values.b;
	specular_[3] = colour_values.a;
}
void BaseColour::ResetSpecularToZero()
{
	SetSpecularColour(0, 0, 0, 0);
}
Colour_RGBA BaseColour::GetSpecularColour()
{
	float r = specular_[0];
	float g = specular_[1];
	float b = specular_[2];
	float a = specular_[3];
	return Colour_RGBA(r, g, b, a);
}

void BaseColour::DisableValue(ColourModifier modifier)
{
	switch (modifier)
	{
	case NO_AMBIENT:	SetAmbientColour(0, 0, 0, 0);
						break;
	case NO_DIFFUSE:	SetDiffuseColour(0, 0, 0, 0);
						break;
	case NO_SPECULAR:	SetSpecularColour(0, 0, 0, 0);
						break;
	case NONE:			//bing nothing happens
						break;
	}

}
