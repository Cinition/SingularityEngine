//
// Created by cornnieu on 3/15/2022.
//

#ifndef SINGULARITY_VECTOR2_H
#define SINGULARITY_VECTOR2_H

template <typename T> class Vector3;
template <typename T> class Vector4;

template <typename T>
class Vector2 {

public:

             Vector2( void )          = default;
    explicit Vector2( T _x )          { x = _x; y = _x; }
             Vector2( T _x, T _y )    { x = _x; y = _y; }
             Vector2( const Vector2<T>& _v ) { x = _v.x; y = _v.y; }

////////////////////////////////////////////////////////////////

    template<typename T2> Vector2 operator + ( const T2 _o )          { return { x += _o, y += _o }; }
    template<typename T2> Vector2 operator - ( const T2 _o )          { return { x -= _o, y -= _o }; }
    template<typename T2> Vector2 operator / ( const T2 _o )          { return { x /= _o, y /= _o }; }
    template<typename T2> Vector2 operator * ( const T2 _o )          { return { x *= _o, y *= _o }; }

    template<typename T2> Vector2 operator + ( const Vector2<T2> _v ) { return { x += _v.x, y += _v.y }; }
    template<typename T2> Vector2 operator - ( const Vector2<T2> _v ) { return { x -= _v.x, y -= _v.y }; }
    template<typename T2> Vector2 operator / ( const Vector2<T2> _v ) { return { x / _v.x, y /= _v.y }; }
    template<typename T2> Vector2 operator * ( const Vector2<T2> _v ) { return { x *= _v.x, y *= _v.y }; }

////////////////////////////////////////////////////////////////

    T x = T(0);
    T y = T(0);
};

typedef Vector2 <int>    Vector2I;
typedef Vector2 <float>  Vector2F;
typedef Vector2 <double> Vector2D;

#endif //SINGULARITY_VECTOR2_H
