#ifndef MATERIALS_H_
#define MATERIALS_H_

#include "BaseColour.h"

//This material class will allow you to add materials to objects effiecently
//A material can be created in the Object Class and stored relative to that object
//the function BindMaterial() must be called before any drawing takes place

//class created using lecture slides as reference (even though they told me emission was a single float)
//Material properties borrowed from http://globe3d.sourceforge.net/g3d_html/gl-materials__ads.htm

enum MaterialProperty {	GLASS, BRASS, BRONZE, POLISHED_BRONZE, CHROME, COPPER, 
					POLISHED_COPPER, GOLD, POLISHED_GOLD, PEWTER, SILVER, 
					POLISHED_SILVER, EMERALD, JADE, OBSIDIAN, PEARL,
					RUBY, TURQUOISE, PLASTIC, RUBBER, DEFAULT};

class Materials :public BaseColour
{
public:
	Materials() {};
	~Materials() {};

	//initialisers
	void Init();		 //by default only the properties will be supplied (no colour/white)
	void Init(MaterialProperty material_template, Colour colour = WHITE); //similar to SetByMaterialTemplate can set a colour
	void Init(MaterialProperty material_template, Colour_RGBA colour);

	//binding material must be called before creating the object
	void BindMaterial(); 
	
	//Sets a material based on default values
	void SetMaterialByTemplate(MaterialProperty material); //will not affect the base colour only change the material properties

	// this allows for a specific colour to be set to a material based on default material types or a Colour_RGBA
	//PROPERTIES_ONLY will only apply the properties ie. white/no colour (1,1,1,1,)
	//MATERIAL_DEFAULT will pass in the colour based on the material eg Gold would be yellow and bronze would be brown
	void SetMaterialByTemplate(MaterialProperty material, Colour colour);
	void SetMaterialByTemplate(MaterialProperty material, Colour_RGBA colour);

	void SetColourByTemplate(Colour colour); //Set colour based on enum template

	//colour stuff
	inline void SetColor(Colour_RGBA colour) { colour_ = colour; };
	inline Colour_RGBA GetColour() { return colour_; };

	inline void SetShininess(float shiny) { shininess_ = shiny; };
	inline float GetShininess() {return shininess_;};
	void SetEmission(Colour_RGBA colour_values);
	void SetEmission(float r, float g, float b, float a);
	Colour_RGBA GetEmission();


	//direct control over colour will set the default value of the glColour4f to (1,1,1,1), white, 
	//allowing for more direct manipulation over ambient diffuse etc
	inline void SetDirectColourControl(bool control) { direct_colour_control_ = control; };
	inline bool GetDirectColourControl() { return direct_colour_control_; };
	
private:
	Colour_RGBA colour_;
	Colour_RGBA default_material_colour_; // set if a material is crated using templates. used to control setting colour by material 
	float shininess_;
	float emission_[4];
	bool direct_colour_control_; //direct colour control 
};

#endif