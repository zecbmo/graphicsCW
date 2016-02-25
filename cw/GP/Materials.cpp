#include "Materials.h"


void Materials::Init()
{
	SetMaterialByTemplate(DEFAULT);
	shininess_ = 0;
	SetEmission(Colour_RGBA(0.0, 0.0, 0.0, 1.0));
	colour_ = Colour_RGBA(1, 1, 1, 1);
	direct_colour_control_ = false;
}
void Materials::Init(MaterialProperty material_template, Colour colour)
{
	SetMaterialByTemplate(material_template);
	SetColourByTemplate(colour);
	direct_colour_control_ = false;
}
void Materials::Init(MaterialProperty material_template, Colour_RGBA colour)
{
	SetMaterialByTemplate(material_template);
	colour_ = colour;
	direct_colour_control_ = false;
}
void Materials::SetMaterialByTemplate(MaterialProperty material)
{
	switch (material)
	{
	case GLASS: 
		SetAmbientColour(0.0, 0.0, 0.0, 1.0);
		SetDiffuseColour(0.588235, 0.670588, 0.729412, 1.0);
		SetSpecularColour(0.9, 0.9, 0.9, 1.0);
		SetEmission(0.0, 0.0, 0.0, 1.0);
		SetShininess(96.0);
		default_material_colour_ = Colour_RGBA(0.588235, 0.670588, 0.729412, 1.0);
		break;
	case BRASS:
		SetAmbientColour(0.329412, 0.223529, 0.027451, 1.0);
		SetDiffuseColour(0.780392, 0.568627, 0.113725, 1.0);
		SetSpecularColour(0.992157, 0.941176, 0.807843, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(27.8974);
		default_material_colour_ = Colour_RGBA(0.780392, 0.568627, 0.113725, 1.0);
		break;
	case BRONZE:
		SetAmbientColour(0.2125, 0.1275, 0.054, 1.0);
		SetDiffuseColour(0.714, 0.4284, 0.18144, 1.0);
		SetSpecularColour(0.393548, 0.271906, 0.166721, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(25.6);
		default_material_colour_ = Colour_RGBA(0.714, 0.4284, 0.18144, 1.0);
		break;
	case POLISHED_BRONZE:
		SetAmbientColour(0.25, 0.148, 0.06475, 1.0);
		SetDiffuseColour(0.4, 0.2368, 0.1036, 1.0);
		SetSpecularColour(0.774597, 0.458561, 0.200621, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(76.8);
		default_material_colour_ = Colour_RGBA(0.4, 0.2368, 0.1036, 1.0);
		break;
	case CHROME:
		SetAmbientColour(0.25, 0.25, 0.25, 1.0);
		SetDiffuseColour(0.4, 0.4, 0.4, 1.0);
		SetSpecularColour(0.774597, 0.774597, 0.774597, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(76.8);
		default_material_colour_ = Colour_RGBA(0.4, 0.4, 0.4, 1.0);
		break;
	case COPPER:
		SetAmbientColour(0.19125, 0.0735, 0.0225, 1.0);
		SetDiffuseColour(0.7038, 0.27048, 0.0828, 1.0);
		SetSpecularColour(0.256777, 0.137622, 0.086014, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(12.8);
		default_material_colour_ = Colour_RGBA(0.7038, 0.27048, 0.0828, 1.0);
		break;
	case POLISHED_COPPER:
		SetAmbientColour(0.2295, 0.08825, 0.0275, 1.0);
		SetDiffuseColour(0.5508, 0.2118, 0.066, 1.0);
		SetSpecularColour(0.580594, 0.223257, 0.0695701, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(51.2);
		default_material_colour_ = Colour_RGBA(0.5508, 0.2118, 0.066, 1.0);
		break;
	case GOLD:
		SetAmbientColour(0.24725, 0.1995, 0.0745, 1.0);
		SetDiffuseColour(0.75164, 0.60648, 0.22648, 1.0);
		SetSpecularColour(0.628281, 0.555802, 0.366065, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(51.2);
		default_material_colour_ = Colour_RGBA(0.75164, 0.60648, 0.22648, 1.0);
		break;
	case POLISHED_GOLD:
		SetAmbientColour(0.24725, 0.2245, 0.0645, 1.0);
		SetDiffuseColour(0.34615, 0.3143, 0.0903, 1.0);
		SetSpecularColour(0.797357, 0.723991, 0.208006, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(83.2);
		default_material_colour_ = Colour_RGBA(0.34615, 0.3143, 0.0903, 1.0);
		break;
	case PEWTER:
		SetAmbientColour(0.105882, 0.058824, 0.113725, 1.0);
		SetDiffuseColour(0.427451, 0.470588, 0.541176, 1.0);
		SetSpecularColour(0.333333, 0.333333, 0.521569, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(9.84615);
		default_material_colour_ = Colour_RGBA(0.427451, 0.470588, 0.541176, 1.0);
		break;
	case SILVER:
		SetAmbientColour(0.19225, 0.19225, 0.19225, 1.0);
		SetDiffuseColour(0.50754, 0.50754, 0.50754, 1.0);
		SetSpecularColour(0.508273, 0.508273, 0.508273, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(51.2);
		default_material_colour_ = Colour_RGBA(0.50754, 0.50754, 0.50754, 1.0);
		break;
	case POLISHED_SILVER:
		SetAmbientColour(0.23125, 0.23125, 0.23125, 1.0);
		SetDiffuseColour(0.2775, 0.2775, 0.2775, 1.0);
		SetSpecularColour(0.773911, 0.773911, 0.773911, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(89.6);
		default_material_colour_ = Colour_RGBA(0.2775, 0.2775, 0.2775, 1.0);
		break;
	case EMERALD:
		SetAmbientColour(0.0215, 0.1745, 0.0215, 0.55);
		SetDiffuseColour(0.07568, 0.61424, 0.07568, 0.55);
		SetSpecularColour(0.633, 0.727811, 0.633, 0.55);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(76.8);
		default_material_colour_ = Colour_RGBA(0.07568, 0.61424, 0.07568, 0.55);
		break;
	case JADE:
		SetAmbientColour(0.135, 0.2225, 0.1575, 0.95);
		SetDiffuseColour(0.54, 0.89, 0.63, 0.95);
		SetSpecularColour(0.316228, 0.316228, 0.316228, 0.95);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(12.8);
		default_material_colour_ = Colour_RGBA(0.54, 0.89, 0.63, 0.95);
		break;
	case OBSIDIAN:
		SetAmbientColour(0.05375, 0.05, 0.06625, 0.82);
		SetDiffuseColour(0.18275, 0.17, 0.22525, 0.82);
		SetSpecularColour(0.332741, 0.328634, 0.346435, 0.82);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(38.4);
		default_material_colour_ = Colour_RGBA(0.18275, 0.17, 0.22525, 0.82);
		break;
	case PEARL:
		SetAmbientColour(0.25, 0.20725, 0.20725, 0.922);
		SetDiffuseColour(1.0, 0.829, 0.829, 0.922);
		SetSpecularColour(0.296648, 0.296648, 0.296648, 0.922);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(11.264);
		default_material_colour_ = Colour_RGBA(1.0, 0.829, 0.829, 0.922);
		break;
	case RUBY:
		SetAmbientColour(0.1745, 0.01175, 0.01175, 0.55);
		SetDiffuseColour(0.61424, 0.04136, 0.04136, 0.55);
		SetSpecularColour(0.727811, 0.626959, 0.626959, 0.55);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(76.8);
		default_material_colour_ = Colour_RGBA(0.61424, 0.04136, 0.04136, 0.55);
		break;
	case TURQUOISE:
		SetAmbientColour(0.1, 0.18725, 0.1745, 0.8);
		SetDiffuseColour(0.396, 0.74151, 0.69102, 0.8);
		SetSpecularColour(0.297254, 0.30829, 0.306678, 0.8);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(12.8);
		default_material_colour_ = Colour_RGBA(0.396, 0.74151, 0.69102, 0.8);
		break;
	case PLASTIC:
		SetAmbientColour(0.0, 0.0, 0.0, 1.0);
		SetDiffuseColour(0.01, 0.01, 0.01, 1.0);
		SetSpecularColour(0.50, 0.50, 0.50, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(32.0);
		default_material_colour_ = Colour_RGBA(0.01, 0.01, 0.01, 1.0);
		break;
	case RUBBER:
		SetAmbientColour(0.02, 0.02, 0.02, 1.0);
		SetDiffuseColour(0.01, 0.01, 0.01, 1.0);
		SetSpecularColour(0.4, 0.4, 0.4, 1.0);
		SetEmission(0.0, 0.0, 0.0, 0.0);
		SetShininess(10.0);
		default_material_colour_ = Colour_RGBA();
		break;
	case DEFAULT:
		SetAmbientColour(0.2, 0.2, 0.2, 1.0);
		SetDiffuseColour(0.8, 0.8, 0.8, 1.0);
		SetSpecularColour(0.0, 0.0, 0.0, 1.0);
		SetEmission(0.0, 0.0, 0.0, 1.0);
		SetShininess(25);
		default_material_colour_ = Colour_RGBA(0.8, 0.8, 0.8, 1.0);
		break;
	}

}
void  Materials::SetMaterialByTemplate(MaterialProperty material, Colour colour)
{
	SetMaterialByTemplate(material);
	SetColourByTemplate(colour);
}
void  Materials::SetMaterialByTemplate(MaterialProperty material, Colour_RGBA colour)
{
	SetMaterialByTemplate(material);
	colour_ = colour;
}

void  Materials::SetColourByTemplate(Colour colour)
{
	switch (colour)
	{
	case RED:
		colour_ = Colour_RGBA();
		break;
	case BLUE:
		colour_ = Colour_RGBA();
		break;
	case GREEN:
		colour_ = Colour_RGBA();
		break;
	case PINK:
		colour_ = Colour_RGBA();
		break;
	case ORANGE:
		colour_ = Colour_RGBA();
		break;
	case YELLOW:
		colour_ = Colour_RGBA();
		break;
	case PURPLE:
		colour_ = Colour_RGBA();
		break;
	case BROWN:
		colour_ = Colour_RGBA();
		break;
	case BLACK:
		colour_ = Colour_RGBA();
		break;
	case WHITE:
		colour_ = Colour_RGBA(0.8f, 0.8f, 0.8f, 1);
		break;
	case PROPERTIES_ONLY:
		colour_ = Colour_RGBA(1,1,1,1);
		break;
	case MATERIAL_DEFAULT:
		colour_ = default_material_colour_;
		break;
	}
}

void Materials::SetEmission(Colour_RGBA colour_values)
{
	emission_[0] = colour_values.r;
	emission_[1] = colour_values.g;
	emission_[2] = colour_values.b;
	emission_[3] = colour_values.a;
}
void Materials::SetEmission(float r, float g, float b, float a)
{
	emission_[0] = r;
	emission_[1] = g;
	emission_[2] = b;
	emission_[3] = a;
}
Colour_RGBA  Materials::GetEmission()
{
	float r = emission_[0];
	float g = emission_[1];
	float b = emission_[2];
	float a = emission_[3];
	return Colour_RGBA(r, g, b, a);
}

void Materials::BindMaterial()
{
	if (!direct_colour_control_)
	{
		glColor4f(colour_.r, colour_.g, colour_.b, colour_.a);
	}
	else
	{
		glColor4f(1, 1, 1, 1);
	}

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shininess_);
	glMaterialfv(GL_FRONT, GL_EMISSION, emission_);
	
}


