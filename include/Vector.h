// 3D Vector

#ifndef _Vector_H_
#define _Vector_H_

#include <assert.h>
#include <iostream>
#include <math.h>

using namespace std;

enum { X, Y, Z, W };

// A 3D Homogeneous Vector
class Vector
{
public:
    // Default constructor
    Vector()
    {
        Set();
    }
    
    // Explicit constructor
    Vector( double x, double y, double z )
    {
        Set( x, y, z );
    }
    
    // Explicit constructor
    Vector( double x, double y, double z, double w )
    {
        Set( x, y, z, w );
    }
    
    // Copy constructor
    Vector( const Vector& vector )
    {    
        Set( vector );
    }
    
    // Initialize to default ( 0, 0, 0, 1 )
    void Set()
    {
        Set( 0.0, 0.0, 0.0, 0.0 );
    }
    
    // Intialize with doubles
    void Set( double x, double y, double z )
    {
        Set( x, y, z, 0.0 );
    }
    
    void Set( double x, double y, double z, double w )
    {
        v[X] = x;
        v[Y] = y;
        v[Z] = z;
        v[W] = w;
    }
    
    // Initialize with a Vector
    void Set( const Vector& vector )
    {
        Set( vector.v[X], vector.v[Y], vector.v[Z], vector.v[W] );
    }
    
    // Access components   
    double& operator[]( int index )
    {
        assert( X <= index && index <= W );
        return v[index];
    }
    
    // Access components   
    double operator[]( int index ) const
    {
        assert( X <= index && index <= W );
        return v[index];
    }
    
    // Assign other vector's values to this vector
    Vector& operator=( const Vector& vector )
    {
        Set( vector );
        return *this;
    }
    
    // Add other vector to this vector
    Vector& operator+=( const Vector& vector )
    {
        v[X] += vector.v[X];
        v[Y] += vector.v[Y];
        v[Z] += vector.v[Z];
        //v[W] += vector.v[W];
        return *this;
    }
    
    // Subtract other vector from this vector
    Vector& operator-=( const Vector& vector )
    {
        v[X] -= vector.v[X];
        v[Y] -= vector.v[Y];
        v[Z] -= vector.v[Z];
        //v[W] -= vector.v[W];
        return *this;
    }
    
    // Scale this vector
    Vector& operator*=( double scale )
    {
        v[X] *= scale;
        v[Y] *= scale;
        v[Z] *= scale;
        //v[W] *= scale;
        return *this;
    }
    
    // Divide this vector
    Vector& operator/=( double factor )
    {
        if ( factor == 0.0 )
        {
            return *this;
        }
        *this *= 1.0 / factor;
        return *this;
    }
        
    // Set length of this vector to 1.0, if original length is not zero
    Vector& Normalize()
    {
        double length = Length();
        if ( length != 0.0 )
        {
            *this *= 1.0 / length;
        }
        return *this;
    }
    
    // Get length of this vector
    double Length() const
    {
        return sqrt( *this * *this );
    }
    
    // Create new Vector that is the negation of this vector
    Vector operator-() const
    {
        Vector result( *this );
        result *= -1.0;
        return result;
    }
    
    // Create new Vector that is this + other
    Vector operator+( const Vector& other ) const
    {
        Vector result( *this );
        result += other;
        return result;
    }
    
    // Create new Vector that is this - other
    Vector operator-( const Vector& other ) const
    {
        Vector result( *this );
        result -= other;
        return result;
    }
    
    // Dot product of this and other vector
    double operator*( const Vector& other ) const
    {
        return v[X] * other.v[X] +
               v[Y] * other.v[Y] +
               v[Z] * other.v[Z] +
               v[W] * other.v[W];
    }
    
    // Create new Vector that is the cross product of two vectors
    Vector operator%( const Vector& other ) const
    {
        Vector result( v[Y] * other.v[Z] - v[Z] * other.v[Y],
                       v[Z] * other.v[X] - v[X] * other.v[Z],
                       v[X] * other.v[Y] - v[Y] * other.v[X],
                       0 );
        return result;
    }
    
    // Create new Vector that is this * scale
    Vector operator*( double scale ) const
    {
        Vector result( *this );
        result *= scale;
        return result;
    }
    
    // Create new Vector that is scale * other
    friend Vector operator*( double scale, const Vector& other )
    {
        return other * scale;
    }
    
    // Create new Vector that is this / factor
    Vector operator/( double factor ) const
    {
        assert( factor != 0 );
        Vector result( *this );
        result *= 1.0 / factor;
        return result;
    }
    
    // Equality operator
    bool operator==( const Vector& other ) const
    {
        return    v[X] == other[X]
               && v[Y] == other[Y]
               && v[Z] == other[Z]
               && v[W] == other[W];
    }
    
    // Output to stream
    friend ostream& operator<<( ostream& os, const Vector& vector )
    {
        os.precision( 3 );
        os << "["; os.width( 7 ); os << vector.v[X];
        os << " "; os.width( 7 ); os << vector.v[Y];
        os << " "; os.width( 7 ); os << vector.v[Z];
        os << " "; os.width( 7 ); os << vector.v[W] << "]";
        os.precision( 6 );
        return os;
    }
    
    // Input from stream
    friend istream& operator>>( istream& is, Vector& vector )
    {
        for ( int ii = 0; ii < 4; ii++ )
        {
            is >> vector[ii];
        }
        return is;
    }
    
private:
    double v[4];
};

#endif
