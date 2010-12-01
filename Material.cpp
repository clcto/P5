// ---------------------------------------------------------
// Material
//    represents a GL material, offering differnt 
//    values for different typ es of light
// ---------------------------------------------------------

#include "Material.h"

const Material Material::SHINY_RED(
                     0.5, 0.2, 0.2,
                     0.8, 0.1, 0.1,
                     0.6, 0.3, 0.3,
                     0,   0,   0,
                     20 );

const Material Material::SHINY_BLUE(
                     0.2, 0.2, 0.5,
                     0.1, 0.1, 0.8,
                     0.3, 0.3, 0.6,
                     0,   0,   0,
                     20 );

const Material Material::SHINY_GREEN(
                     0.2, 0.5, 0.2,
                     0.1, 0.8, 0.1,
                     0.3, 0.6, 0.3,
                     0,   0,   0,
                     20 );

const Material Material::PIANO_BLACK(
                     0.05, 0.05, 0.05,
                     0.05, 0.05, 0.05,
                     0.5, 0.5, 0.5,
                     0, 0, 0,
                     40 );
   // -----------------------------------------------------
   // creates the material with the properties given
Material::Material( float aR, float aG, float aB, 
                    float dR, float dG, float dB,
                    float srR, float srG, float srB,
                    float stR, float stG, float stB,
                    float exp )
{
   ambient.red = aR;
   ambient.green = aG;
   ambient.blue = aB;

   diffuse.red = dR;
   diffuse.green = dG;
   diffuse.blue = dB;

   specular_r.red = srR;
   specular_r.green = srG;
   specular_r.blue = srB;

   specular_t.red = stR;
   specular_t.green = stG;
   specular_t.blue = stB;

   exponent = exp;
}

Color Material::ka() const
{
   return ambient;
}

Color Material::kd() const
{
   return diffuse;
}

Color Material::ks() const
{
   return specular_r;
}

Color Material::kt() const
{
   return specular_t;
}

float Material::exp() const
{
   return exponent;
}
