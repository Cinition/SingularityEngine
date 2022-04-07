//
// Created by cornnieu on 3/15/2022.
//

#ifndef SINGULARITY_VECTOR3_H
#define SINGULARITY_VECTOR3_H

template <typename T> class Vector2;
template <typename T> class Vector4;

template <typename T>
class Vector3 {

public:

             Vector3( void )                      = default;
    explicit Vector3( T _x )                      { x = _x; y = _x; z = _x; }
             Vector3( T _x, T _y )                { x = _x; y = _y; z = T(0); }
             Vector3( T _x, T _y, T _z )          { x = _x; y = _y; z = _z; }
    explicit Vector3( Vector2<T> _v )             { x = _v.x; y = _v.y; z = T(0); }
    explicit Vector3( Vector2<T> _v, const T _z ) { x = _v.x; y = _v.y; z = _z; }
             Vector3( const Vector3<T>& _v )      { x = _v.x; y = _v.y; z = _v.z; }

////////////////////////////////////////////////////////////////

    template<typename T2> Vector3 operator + ( const T2 _o )          { return { x += _o, y += _o, z += _o }; }
    template<typename T2> Vector3 operator - ( const T2 _o )          { return { x -= _o, y -= _o, z -= _o }; }
    template<typename T2> Vector3 operator / ( const T2 _o )          { return { x /= _o, y /= _o, z /= _o }; }
    template<typename T2> Vector3 operator * ( const T2 _o )          { return { x *= _o, y *= _o, z *= _o }; }

    template<typename T2> Vector3 operator + ( const Vector2<T2> _v ) { return { x += _v.x, y += _v.y, z }; }
    template<typename T2> Vector3 operator - ( const Vector2<T2> _v ) { return { x -= _v.x, y -= _v.y, z }; }
    template<typename T2> Vector3 operator / ( const Vector2<T2> _v ) { return { x /= _v.x, y /= _v.y, z }; }
    template<typename T2> Vector3 operator * ( const Vector2<T2> _v ) { return { x *= _v.x, y *= _v.y, z }; }

    template<typename T2> Vector3 operator + ( const Vector3<T2> _v ) { return { x += _v.x, y += _v.y, z += _v.z }; }
    template<typename T2> Vector3 operator - ( const Vector3<T2> _v ) { return { x -= _v.x, y -= _v.y, z -= _v.z }; }
    template<typename T2> Vector3 operator / ( const Vector3<T2> _v ) { return { x /= _v.x, y /= _v.y, z /= _v.z }; }
    template<typename T2> Vector3 operator * ( const Vector3<T2> _v ) { return { x *= _v.x, y *= _v.y, z *= _v.z }; }

////////////////////////////////////////////////////////////////

    T x = T(0);
    T y = T(0);
    T z = T(0);
};

typedef Vector3 <int>    Vector3I;
typedef Vector3 <float>  Vector3F;
typedef Vector3 <double> Vector3D;

#endif //SINGULARITY_VECTOR3_H
