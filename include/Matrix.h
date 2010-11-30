// 3D Matrix

#ifndef _Matrix_H_
#define _Matrix_H_

#include "Point.h"
#include "Vector.h"

#include <assert.h>
#include <iostream>
#include <math.h>

using namespace std;

// A basic implementation of a 3D Homogeneous Matrix class,
// which does not contain inverse, determinant, and other 
// functions normally contained in such a class.
class Matrix
{
public:
    // Default constructor
    Matrix()
    {
        Set();
    }
    
    // Explicit constructor
    Matrix( double xx, double xy, double xz, double xw,
            double yx, double yy, double yz, double yw,
            double zx, double zy, double zz, double zw,
            double wx, double wy, double wz, double ww )
    {
        Set( xx, xy, xz, xw,
             yx, yy, yz, yw,
             zx, zy, zz, zw,
             wx, wy, wz, ww );
    }
    
    // Explicit constructor using array of 16 doubles in column-major order
    Matrix( double* v )
    {
        Set( v[0], v[4], v[ 8], v[12],
             v[1], v[5], v[ 9], v[13],
             v[2], v[6], v[10], v[14],
             v[3], v[7], v[11], v[15] );
    }
    
    // Copy constructor
    Matrix( const Matrix& matrix )
    {    
        Set( matrix );
    }
    
    // Initialize to Identity
    void Set()
    {
        Set( 1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1 );
    }
    
    // Intialize with doubles
    void Set( double xx, double xy, double xz, double xw,
              double yx, double yy, double yz, double yw,
              double zx, double zy, double zz, double zw,
              double wx, double wy, double wz, double ww )
    {
        m[X].Set( xx, xy, xz, xw );
        m[Y].Set( yx, yy, yz, yw );
        m[Z].Set( zx, zy, zz, zw );
        m[W].Set( wx, wy, wz, ww );
    }
    
    // Initialize with a Matrix
    void Set( const Matrix& matrix )
    {
        m[X] = matrix.m[X];
        m[Y] = matrix.m[Y];
        m[Z] = matrix.m[Z];
        m[W] = matrix.m[W];
    }
    
    void Set( int row, int col, double value )
    {
        assert( X <= row && row <= W && X <= col && col <= W );
        m[row][col] = value;
    }
    
    // Access components
    Point& operator[]( int index )
    {
        assert( X <= index && index <= W );
        return m[index];
    }
    
    // Access components
    const Point& operator[]( int index ) const
    {
        assert( X <= index && index <= W );
        return m[index];
    }
    
    // Assign other matrix's values to this matrix
    Matrix& operator=( const Matrix& matrix )
    {
        Set( matrix );
        return *this;
    }
    
    // Create new Matrix that is this * other
    Matrix operator*( const Matrix& other ) const
    {
        Matrix result;
        
        for ( int ii = X; ii <= W; ii++ )
        {
            for ( int jj = X; jj <= W; jj++ )
            {
                double sum = 0.0;
                for ( int kk = X; kk <= W; kk++ )
                {
                    sum += m[ii][kk] * other.m[kk][jj];
                }
                
                result[ii][jj] = sum;
            }
        }
        
        return result;
    }
    
    // Create new Point that is this * point
    Point operator*( const Point& point ) const
    {
        Point result;
        
        for ( int ii = X; ii <= W; ii++ )
        {
            Point temp = m[ii];
            result[ii] = temp * point;
        }
        
        return result;
    }
    
    // Create new Vector that is this * vector
    Vector operator*( const Vector& vector ) const
    {
        Vector result;
        
        for ( int ii = X; ii <= W; ii++ )
        {
            result[ii] = (Vector) m[ii] * vector;
        }
        
        return result;
    }
    
    // Equality operator
    bool operator==( const Matrix& other ) const
    {
        return    m[X] == other[X]
               && m[Y] == other[Y]
               && m[Z] == other[Z]
               && m[W] == other[W];
    }
    
    // Output to stream
    friend ostream& operator<<( ostream& os, const Matrix& matrix )
    {
        os.precision( 3 );
        os << matrix.m[X];
        os << matrix.m[Y];
        os << matrix.m[Z];
        os << matrix.m[W];
        os.precision( 6 );
        return os;
    }
    
private:
    Point m[4];
};

#endif
