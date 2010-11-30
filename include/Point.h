// 3D Point

#ifndef _Point_H_
#define _Point_H_

#include "Vector.h"

#include <assert.h>
#include <iostream>
#include <math.h>

using namespace std;

// A 3D Homogeneous Point
class Point
{
public:
    // Default constructor
    Point()
    {
        Set();
    }
    
    // Explicit constructor
    Point( double x, double y, double z )
    {
        Set( x, y, z );
    }
    
    // Explicit constructor
    Point( double x, double y, double z, double w )
    {
        Set( x, y, z, w );
    }
    
    // Copy constructor
    Point( const Point& point )
    {    
        Set( point );
    }
    
    // Cast Point to Vector
    operator Vector() const
    {
        return Vector( v[X], v[Y], v[Z], v[W] );
    }
    
    // Initialize to default ( 0, 0, 0, 1 )
    void Set()
    {
        Set( 0.0, 0.0, 0.0, 1.0 );
    }
    
    // Intialize with doubles
    void Set( double x, double y, double z )
    {
        Set( x, y, z, 1.0 );
    }
    
    void Set( double x, double y, double z, double w )
    {
        v[X] = x;
        v[Y] = y;
        v[Z] = z;
        v[W] = w;
    }
    
    // Initialize with a Point
    void Set( const Point& point )
    {
        Set( point.v[X], point.v[Y], point.v[Z], point.v[W] );
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
    
    // Assign other point's values to this point
    Point& operator=( const Point& point )
    {
        Set( point );
        return *this;
    }
    
    // Add other point to this point
    Point& operator+=( const Point& point )
    {
        v[X] += point.v[X];
        v[Y] += point.v[Y];
        v[Z] += point.v[Z];
        //v[W] += point.v[W];
        return *this;
    }
    
    // Subtract other point from this point
    Point& operator-=( const Point& point )
    {
        v[X] -= point.v[X];
        v[Y] -= point.v[Y];
        v[Z] -= point.v[Z];
        //v[W] -= point.v[W];
        return *this;
    }
    
    // Scale this point
    Point& operator*=( double scale )
    {
        v[X] *= scale;
        v[Y] *= scale;
        v[Z] *= scale;
        //v[W] *= scale;
        return *this;
    }
    
    // Divide this point
    Point& operator/=( double factor )
    {
        if ( factor == 0.0 )
        {
            return *this;
        }
        *this *= 1.0 / factor;
        return *this;
    }
    
    // Divide this point by w, if not zero
    Point& Homogenize()
    {
        if ( v[W] != 0.0 )
        {
            *this *= 1.0 / v[W];
            v[W] = 1.0;
        }
        return *this;
    }
    
    // Create new Point that is the negation of this point
    Point operator-() const
    {
        Point result( *this );
        result *= -1.0;
        return result;
    }
    
    // Create new Point that is this + other
    Point operator+( const Point& other ) const
    {
        Point result( *this );
        result += other;
        return result;
    }
    
    // Create new Point that is this - other
    Point operator-( const Point& other ) const
    {
        Point result( *this );
        result -= other;
        return result;
    }
            
    // Inner product of this and other point. Not Dot product!
    double operator*( const Point& other ) const
    {
        return v[X] * other.v[X] +
               v[Y] * other.v[Y] +
               v[Z] * other.v[Z] +
               v[W] * other.v[W];
    }
        
    // Create new Point that is this * scale
    Point operator*( double scale ) const
    {
        Point result( *this );
        result *= scale;
        return result;
    }
    
    // Create new Point that is scale * other
    friend Point operator*( double scale, const Point& other )
    {
        return other * scale;
    }
    
    // Create new Point that is this / factor
    Point operator/( double factor ) const
    {
        assert( factor != 0 );
        Point result( *this );
        result *= 1.0 / factor;
        return result;
    }
    
    // Equality operator
    bool operator==( const Point& other ) const
    {
        return    v[X] == other[X]
               && v[Y] == other[Y]
               && v[Z] == other[Z]
               && v[W] == other[W];
    }
    
    // Output to stream
    friend ostream& operator<<( ostream& os, const Point& point )
    {
        os.precision( 3 );
        os << "["; os.width( 7 ); os << point.v[X];
        os << " "; os.width( 7 ); os << point.v[Y];
        os << " "; os.width( 7 ); os << point.v[Z];
        os << " "; os.width( 7 ); os << point.v[W] << "]";
        os.precision( 6 );
        return os;
    }
    
    // Input from stream
    friend istream& operator>>( istream& is, Point& point )
    {
        for ( int ii = 0; ii < 4; ii++ )
        {
            is >> point[ii];
        }
        return is;
    }
    
private:
    double v[4];
};

#endif
