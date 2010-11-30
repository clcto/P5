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
                float = 0 );

      void GLInit() const;

         // constant materials that can be used whenever
      static const Material BRASS,
                            MATTE_RED,
                            CHROME,
                            BLACK_PLASTIC;
      
   private:
      Color ambient, diffuse, specular, exponent;
      float shine;
};
