#ifndef LIGHTING_H_
#define LIGHTING_H_


#include "BaseColour.h"

//Questions to ask paul
	//Spot lights direction - should it be normalised??

//Light.h Created by Gary McCartan 1402860
//Lecture materials and http://archive.gamedev.net/archive/reference/programming/features/superquadric/page2.html used as reference


enum LightType {DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT};


class Light : public BaseColour
{
	//from this light class, you will be able to create and manage different light sources
	//on initialisation the type can be defined alongside some templates that will set up the light
	//all lights will be init with some default values ie poision, colours, attenuation etc
public:
	Light() {};
	~Light() {};

	//init functions
	void Init(int glLightDefine = GL_LIGHT0); //the defualt int will set up the default lights 
	void Init(int glLightDefine, LightType type, MatTemplate default_light = DEFAULT); //passing an enum type I will have templates for different types of lights
	

	//colour templates
	void SetColourByTemplate(Colour colour, ColourModifier modifier);

	//position
	void SetPosition(Vector3 position);
	void SetPosition(float x, float y, float z);
	Vector3 GetPosition();

	//defining type
	void SetType(LightType type);
	LightType GetType();

	//Spotlight values
	void SetSpotDirection(Vector3 direction);
	void SetSpotDirection(float x, float y, float z);
	Vector3 GetSpotDirection();
	inline void SetSpotCutoff(float cutoff) { spot_cutoff_ = cutoff; };
	inline float GetSpotCutoff() { return spot_cutoff_; };
	inline void SetSpotExponent(float exponent) { spot_exponent_ = exponent; };
	inline float GetSpotExponent() { return spot_exponent_; };	

	//Attenuation values
	inline void SetAllAttenuations(float con, float lin, float quad) { constant_attenuation_ = con; linear_attenuation_ = lin; quadratic_attenuation_ = quad; };
	inline void SetConstantAttenuation(float con) { constant_attenuation_ = con; };
	inline float GetConstantAttenuation() { return constant_attenuation_; };
	inline void SetLinearAttenuation(float lin) { linear_attenuation_ = lin; };
	inline float GetLinearAttenuation() { return linear_attenuation_; };
	inline void SetQuadraticAttenuation(float quad) { quadratic_attenuation_ = quad; };	

	//ID
	inline std::string GetID() { return id_; };

	//on or off?
	inline void SetOn(bool on) { on_ = on; }; //for if the light is on or off
	inline bool GetOn() { return on_; };
	inline void toggleOn() { on_ = !on_; };

	void Render(); //might better being called update values

private:
	//helper functions

	void InitHelperFunction(float glLightDefine);
	void SetID(); //private and called at the end of init. set by opengl

	//member variables
	int gl_light_num_; //Stores GL_LIGHT0 etc
	std::string id_; //Stores a string literal of the gl_light_num (For Error reporting and Identifiying problems)
						
	//rather than manipulating the position array 
	Vector3 vec_pos_; //a vector 3 position will be stored and the values passed in when updating the light
	LightType light_type_; //contains the last info for the position array determining the type

	Vector3 spot_direction_; // the normailised directional vector the light is going
	float spot_cutoff_; //mustc be between 0 and 90
	float spot_exponent_; //default is 0

	float constant_attenuation_; 
	float linear_attenuation_;
	float quadratic_attenuation_;

	bool on_;

};

#endif