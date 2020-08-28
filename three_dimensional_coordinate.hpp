#ifndef __common_three_dimensional_coordinate_hpp__
#define __common_three_dimensional_coordinate_hpp__

#include <cmath>

#include "two_dimensional_coordinate.hpp"

namespace Uccc
{
//#############################################################################
template < class numeric_t >
struct three_dimensional_coordinate
{
public: //---------------------------------------------------------------------
typedef numeric_t coord_type;

numeric_t m_x;
numeric_t m_y;
numeric_t m_z;
//-----------------------------------------------------------------------------
three_dimensional_coordinate()
	:	m_x( 0 )
	,	m_y( 0 )
	,	m_z( 0 )
{}
//-----------------------------------------------------------------------------
three_dimensional_coordinate( numeric_t _x, numeric_t _y, numeric_t _z )
	:	m_x( _x )
	,	m_y( _y )
	,	m_z( _z )
{}
//-----------------------------------------------------------------------------
three_dimensional_coordinate( three_dimensional_coordinate const & _src )
	:	m_x( _src.m_x )
	,	m_y( _src.m_y )
	,	m_z( _src.m_z )
{}
//-----------------------------------------------------------------------------
void add( three_dimensional_coordinate const & _b )
{
    m_x += _b.m_x;
    m_y += _b.m_y;
	m_z += _b.m_z;
}
//-----------------------------------------------------------------------------
void sub( three_dimensional_coordinate const & _b )
{
    m_x -= _b.m_x;
    m_y -= _b.m_y;
	m_z -= _b.m_z;
}
//-----------------------------------------------------------------------------
void mul( numeric_t _val )
{
	m_x *= _val;
	m_y *= _val;
	m_z *= _val;
}
//-----------------------------------------------------------------------------
double length( const three_dimensional_coordinate& _b ) const
{
	double ret
		=	0.0
		+	pow( std::abs( m_x - _b.m_x ) , 2)
		+	pow( std::abs( m_y - _b.m_y ) , 2)
		+	pow( std::abs( m_z - _b.m_z ) , 2)
		;

	ret = pow( ret, 0.5 );

    return ret;
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate< numeric_t > xy() const
{
	return two_dimensional_coordinate< numeric_t >( m_x, m_y );
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate< numeric_t > xz() const
{
	return two_dimensional_coordinate< numeric_t >( m_x, m_z );
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate< numeric_t > yz() const
{
	return two_dimensional_coordinate< numeric_t >( m_y, m_z );
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate< numeric_t > yx() const
{
	return two_dimensional_coordinate< numeric_t >( m_y, m_x );
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate< numeric_t > zx() const
{
	return two_dimensional_coordinate< numeric_t >( m_z, m_x );
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate< numeric_t > zy() const
{
	return two_dimensional_coordinate< numeric_t >( m_z, m_y );
}
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void xy( two_dimensional_coordinate< numeric_t > const & _other )
{
	m_x = _other,m_x;
	m_y = _other.m_y;
}
//-----------------------------------------------------------------------------
void xz( two_dimensional_coordinate< numeric_t > const & _other )
{
	m_x = _other.m_x;
	m_z = _other.m_y;
}
//-----------------------------------------------------------------------------
void yz( two_dimensional_coordinate< numeric_t > const & _other )
{
	m_y = _other.m_x;
	m_z = _other.m_y;
}
//-----------------------------------------------------------------------------
void yx( two_dimensional_coordinate< numeric_t > const & _other )
{
	m_y = _other.m_x;
	m_x = _other.m_y;
}
//-----------------------------------------------------------------------------
void zx( two_dimensional_coordinate< numeric_t > const & _other )
{
	m_z = _other.m_x;
	m_x = _other.m_y;
}
//-----------------------------------------------------------------------------
void zy( two_dimensional_coordinate< numeric_t > const & _other )
{
	m_z = _other.m_x;
	m_y = _other.m_y;
}
//-----------------------------------------------------------------------------
three_dimensional_coordinate xyz()
{
	return three_dimensional_coordinate( m_x, m_y, m_z );
}
//-----------------------------------------------------------------------------
three_dimensional_coordinate xzy()
{
	return three_dimensional_coordinate( m_x, m_z, m_y );
}
//-----------------------------------------------------------------------------
three_dimensional_coordinate yzx()
{
	return three_dimensional_coordinate( m_y, m_z, m_z );
}
//-----------------------------------------------------------------------------
three_dimensional_coordinate yxz()
{
	return three_dimensional_coordinate( m_y, m_x, m_z );
}
//-----------------------------------------------------------------------------
three_dimensional_coordinate zxy()
{
	return three_dimensional_coordinate( m_x, m_y, m_z );
}
//-----------------------------------------------------------------------------
three_dimensional_coordinate zyx()
{
	return three_dimensional_coordinate( m_z, m_y, m_x );
}

};
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator%(
		three_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    three_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x % _b;
    ret.m_y = _a.m_y % _b;
	ret.m_z = _a.m_z % _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator%(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    three_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x % _b.m_x;
    ret.m_y = _a.m_y % _b.m_y;
	ret.m_z = _a.m_z % _b.m_z;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator%=(
		three_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x % _b;
    _a.m_y = _a.m_y % _b;
	_a.m_z = _a.m_z % _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator%=(
		three_dimensional_coordinate< numeric_t > & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x % _b.m_x;
    _a.m_y = _a.m_y % _b.m_y;
	_a.m_z = _a.m_z % _b.m_z;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator+(
		three_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    three_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x + _b;
    ret.m_y = _a.m_y + _b;
	ret.m_z = _a.m_z + _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator+(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    three_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x + _b.m_x;
    ret.m_y = _a.m_y + _b.m_y;
	ret.m_z = _a.m_z + _b.m_z;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator+=(
		three_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x + _b;
    _a.m_y = _a.m_y + _b;
	_a.m_z = _a.m_z + _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator+=(
		three_dimensional_coordinate< numeric_t > & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x + _b.m_x;
    _a.m_y = _a.m_y + _b.m_y;
	_a.m_z = _a.m_z + _b.m_z;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator-(
		three_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    three_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x - _b;
    ret.m_y = _a.m_y - _b;
	ret.m_z = _a.m_z - _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator-(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    three_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x - _b.m_x;
    ret.m_y = _a.m_y - _b.m_y;
	ret.m_z = _a.m_z - _b.m_z;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator-=(
		three_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x - _b;
    _a.m_y = _a.m_y - _b;
	_a.m_z = _a.m_z - _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator-=(
		three_dimensional_coordinate< numeric_t > & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x - _b.m_x;
    _a.m_y = _a.m_y - _b.m_y;
	_a.m_z = _a.m_z - _b.m_z;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator*(
		three_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    three_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x * _b;
    ret.m_y = _a.m_y * _b;
	ret.m_z = _a.m_z * _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator*(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    three_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x * _b.m_x;
    ret.m_y = _a.m_y * _b.m_y;
	ret.m_z = _a.m_z * _b.m_z;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator*=(
		three_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x * _b;
    _a.m_y = _a.m_y * _b;
	_a.m_z = _a.m_z * _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator*=(
		three_dimensional_coordinate< numeric_t > & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x * _b.m_x;
    _a.m_y = _a.m_y * _b.m_y;
	_a.m_z = _a.m_z * _b.m_z;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator/(
		three_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    three_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x / _b;
    ret.m_y = _a.m_y / _b;
	ret.m_z = _a.m_z / _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator/(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    three_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x / _b.m_x;
    ret.m_y = _a.m_y / _b.m_y;
	ret.m_z = _a.m_z / _b.m_z;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator/=(
		three_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x / _b;
    _a.m_y = _a.m_y / _b;
	_a.m_z = _a.m_z / _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
operator/=(
		three_dimensional_coordinate< numeric_t > & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x / _b.m_x;
    _a.m_y = _a.m_y / _b.m_y;
	_a.m_z = _a.m_z / _b.m_z;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
switch_values( three_dimensional_coordinate< numeric_t > const & _a )
{
	three_dimensional_coordinate< numeric_t > ret;
	ret.m_x = _a.m_y;
	ret.m_y = _a.m_x;
	ret.m_z = _a.m_z;
	return ret;
}
//#############################################################################
template< class numeric_t >
inline
bool
operator==(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    return _a.m_x == _b.m_x && _a.m_y == _b.m_y && _a.m_z == _b.m_z;
}
//#############################################################################
template< class numeric_t >
inline
bool
operator!=(
		three_dimensional_coordinate< numeric_t > const & _a
	,	three_dimensional_coordinate< numeric_t > const & _b
	)
{
    return _a.m_x != _b.m_x || _a.m_y != _b.m_y || _a.m_z != _b.m_z;
}
//#############################################################################
template< class numeric_t >
inline
three_dimensional_coordinate< numeric_t >
floor( three_dimensional_coordinate< numeric_t > _source )
{
	three_dimensional_coordinate< numeric_t > return_value;

	return_value.m_x = std::floor( _source.m_x );
	return_value.m_y = std::floor( _source.m_y );
	return_value.m_z = std::floor( _source.m_z );

	return return_value;
}
//-----------------------------------------------------------------------------
template< typename numeric_1_t, typename numeric_2_t >
inline
three_dimensional_coordinate< numeric_2_t >
convert( three_dimensional_coordinate< numeric_1_t > const & src )
{
	return three_dimensional_coordinate< numeric_2_t >(
			numeric_2_t( src.m_x )
		,	numeric_2_t( src.m_y )
		,	numeric_2_t( src.m_z )
		);
}

//-----------------------------------------------------------------------------
template< typename numeric_1_t>
inline
numeric_1_t dot(
		three_dimensional_coordinate< numeric_1_t > const & _left
	,	three_dimensional_coordinate< numeric_1_t > const & _right
	)
{
	return	_left.m_x * _right.m_x
		+	_left.m_y * _right.m_y
		+	_left.m_z * _right.m_z
		;
}
//-----------------------------------------------------------------------------
template< typename numeric_1_t>
inline
three_dimensional_coordinate< numeric_1_t > cross(
		three_dimensional_coordinate< numeric_1_t >const & _left
	,	three_dimensional_coordinate< numeric_1_t >const & _right
	)
{
	return three_dimensional_coordinate< numeric_1_t >(
			_left.m_y * _right.m_z - _left.m_z * _right.m_y
		,	_left.m_z * _right.m_x - _left.m_x * _right.m_z
		,	_left.m_x * _right.m_y - _left.m_y * _right.m_x
		);
}

//#############################################################################
};
#endif