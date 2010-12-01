// ---------------------------------------------------------
// Material
//    represents a GL material, offering differnt 
//    values for different typ es of light
// ---------------------------------------------------------

#include "Color.h"
#include "GL/gl.h"

class Material
{
   public:
      Material( float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0, float = 0, float = 0,
                float = 0 );

      Color ka() const;
      Color kd() const;
      Color ks() const;
      Color kt() const;
      float exp() const;

      static const Material SHINY_RED;
      static const Material SHINY_BLUE;
      static const Material SHINY_GREEN;

   private:
      Color ambient, diffuse, 
            specular_r, specular_t;

      float exponent;
};
