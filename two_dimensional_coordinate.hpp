#ifndef __common_two_dimensional_coordinate_hpp__
#define __common_two_dimensional_coordinate_hpp__

#include <cmath>

namespace Uccc
{
//#############################################################################
//template<class numeric_t>
//inline
//numeric_t Round( numeric_t & _value )
//{
//	return _value;
//}
////-----------------------------------------------------------------------------
//template<class numeric_t>
//inline
//numeric_t Round( numeric_t const & _value )
//{
//	return _value;
//}
////-----------------------------------------------------------------------------
//template<>
//inline
//double Round( double & _value )
//{
//	_value = std::round( _value * 100 ) / 100;
//	return _value;
//}
////-----------------------------------------------------------------------------
//template<>
//inline
//double Round( double const & _value )
//{
//	double result = std::round( _value * 100 ) / 100;
//	return result;
//}
//-----------------------------------------------------------------------------
template <class numeric_t>
struct two_dimensional_coordinate
{
public: //---------------------------------------------------------------------
typedef numeric_t Numeric;
numeric_t m_x;
numeric_t m_y;
//-----------------------------------------------------------------------------
two_dimensional_coordinate()
	:	m_x( 0 )
	,	m_y( 0 )
{}
//-----------------------------------------------------------------------------
two_dimensional_coordinate( numeric_t _x, numeric_t _y )
	:	m_x( _x )
	,	m_y( _y )
{}
//-----------------------------------------------------------------------------
two_dimensional_coordinate( two_dimensional_coordinate const & _src )
	:	m_x( _src.m_x )
	,	m_y( _src.m_y )
{}
//-----------------------------------------------------------------------------
void add( two_dimensional_coordinate const & _b )
{
    m_x += _b.m_x;
    m_y += _b.m_y;
}
//-----------------------------------------------------------------------------
void sub( two_dimensional_coordinate const & _b )
{
    m_x -= _b.m_x;
    m_y -= _b.m_y;
}
//-----------------------------------------------------------------------------
void mul( numeric_t _val )
{
	m_x *= _val;
	m_y *= _val;
}
//-----------------------------------------------------------------------------
void div( numeric_t _val )
{
	m_x /= _val;
	m_y /= _val;
}
//-----------------------------------------------------------------------------
double distance( const two_dimensional_coordinate& _b ) const
{
	double ret
		=	0.0
		+	pow( double( std::abs( m_x - _b.m_x ) ), 2.0 )
		+	pow( double( std::abs( m_y - _b.m_y ) ), 2.0 )
		;

	ret = pow( ret, 0.5 );

    return ret;
}
//-----------------------------------------------------------------------------
double length() const
{
	double ret
		=	0.0
		+	pow( double( m_x ), 2.0 )
		+	pow( double( m_y ), 2.0 )
		;

	ret = pow( ret, 0.5 );

    return ret;
}
//-----------------------------------------------------------------------------
two_dimensional_coordinate xy() const
{
	return two_dimensional_coordinate( m_x, m_y );
};
//-----------------------------------------------------------------------------
two_dimensional_coordinate yx() const
{
	return two_dimensional_coordinate( m_y, m_x );
};
//-----------------------------------------------------------------------------
};
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator%(
		two_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    two_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x % _b;
    ret.m_y = _a.m_y % _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator%(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    two_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x % _b.m_x;
    ret.m_y = _a.m_y % _b.m_y;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator%=(
		two_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x % _b;
    _a.m_y = _a.m_y % _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator%=(
		two_dimensional_coordinate< numeric_t > & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x % _b.m_x;
    _a.m_y = _a.m_y % _b.m_y;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator+(
		two_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    two_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x + _b;
    ret.m_y = _a.m_y + _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator+(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    two_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x + _b.m_x;
    ret.m_y = _a.m_y + _b.m_y;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator+=(
		two_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x + _b;
    _a.m_y = _a.m_y + _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator+=(
		two_dimensional_coordinate< numeric_t > & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x + _b.m_x;
    _a.m_y = _a.m_y + _b.m_y;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator-(
		two_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    two_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x - _b;
    ret.m_y = _a.m_y - _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator-(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    two_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x - _b.m_x;
    ret.m_y = _a.m_y - _b.m_y;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator-=(
		two_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x - _b;
    _a.m_y = _a.m_y - _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator-=(
		two_dimensional_coordinate< numeric_t > & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x - _b.m_x;
    _a.m_y = _a.m_y - _b.m_y;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator*(
		two_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    two_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x * _b;
    ret.m_y = _a.m_y * _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator*(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    two_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x * _b.m_x;
    ret.m_y = _a.m_y * _b.m_y;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator*=(
		two_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x * _b;
    _a.m_y = _a.m_y * _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator*=(
		two_dimensional_coordinate< numeric_t > & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x * _b.m_x;
    _a.m_y = _a.m_y * _b.m_y;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator/(
		two_dimensional_coordinate< numeric_t > const & _a
	,	numeric_t _b
	)
{
    two_dimensional_coordinate< numeric_t > ret( _a );
    ret.m_x = _a.m_x / _b;
    ret.m_y = _a.m_y / _b;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator/(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    two_dimensional_coordinate< numeric_t > ret;
    ret.m_x = _a.m_x / _b.m_x;
    ret.m_y = _a.m_y / _b.m_y;
    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator/=(
		two_dimensional_coordinate< numeric_t > & _a
	,	numeric_t _b
	)
{
    _a.m_x = _a.m_x / _b;
    _a.m_y = _a.m_y / _b;
    return _a;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
operator/=(
		two_dimensional_coordinate< numeric_t > & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    _a.m_x = _a.m_x / _b.m_x;
    _a.m_y = _a.m_y / _b.m_y;
    return _a;
}
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
switch_values( two_dimensional_coordinate< numeric_t > const & _a )
{
	two_dimensional_coordinate< numeric_t > ret;
	ret.m_x = _a.m_y;
	ret.m_y = _a.m_x;
	return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
switch_values( two_dimensional_coordinate< numeric_t > & _a )
{
	std::swap< numeric_t >( _a.m_x, _a.m_y );
}
//#############################################################################
template< class numeric_t >
inline
bool
operator==(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    return _a.m_x == _b.m_x && _a.m_y == _b.m_y;
}
//#############################################################################
template< class numeric_t >
inline
bool
operator!=(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    return _a.m_x != _b.m_x || _a.m_y != _b.m_y;
}
//#############################################################################
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
common_part(
		two_dimensional_coordinate< numeric_t > const & _a
	,	two_dimensional_coordinate< numeric_t > const & _b
	)
{
    two_dimensional_coordinate< numeric_t > first;
    two_dimensional_coordinate< numeric_t > second;

    if ( _a.m_x < _b.m_x )
    {
        first = _a;
        second = _b;
    } else {
        first = _b;
        second = _a;
    }

    two_dimensional_coordinate< numeric_t > ret(0,0);

    if (first.m_y < second.m_x) return ret;

    ret.m_x = second.m_x;

    ret.m_y
		=	first.m_y < second.m_y
		?	first.m_y
		:	second.m_y
		;

    return ret;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
floor( two_dimensional_coordinate< numeric_t > const & _source )
{
	two_dimensional_coordinate< numeric_t > return_value;

	return_value.m_x = std::floor( _source.m_x );
	return_value.m_y = std::floor( _source.m_y );

	return return_value;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
numeric_t
distance( numeric_t _longitunal, numeric_t _latitunal )
{
	numeric_t temporary_1 = _longitunal * _longitunal;
	numeric_t temporary_2 = _latitunal * _latitunal;

	return std::pow( temporary_1 + temporary_2, 0.5 );
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
numeric_t
operator<(
		two_dimensional_coordinate< numeric_t > const & _left
	,	two_dimensional_coordinate< numeric_t > const & _right
	)
{
	if ( _left.m_x < _right.m_x )
		return true;
	else if ( _left.m_x > _right.m_x )
		return false;
	return _left.m_y < _right.m_y;
}
//-----------------------------------------------------------------------------
template< typename numeric_1_t, typename numeric_2_t >
inline
two_dimensional_coordinate< numeric_2_t >
convert( two_dimensional_coordinate< numeric_1_t > const & src )
{
	return two_dimensional_coordinate< numeric_2_t >(
			numeric_2_t( src.m_x )
		,	numeric_2_t( src.m_y )
		);
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
bool
point_in_rectangle(
		two_dimensional_coordinate< numeric_t > const & _lower_left_corner
	,	two_dimensional_coordinate< numeric_t > const & _upper_right_corner
	,	two_dimensional_coordinate< numeric_t > const & _point
	)
{
	return
		_lower_left_corner.m_x <= _point.m_x
	&&	_upper_right_corner.m_x >= _point.m_x
	&&	_lower_left_corner.m_y <= _point.m_y
	&&	_upper_right_corner.m_y >= _point.m_y
	;
}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
rotate(
		two_dimensional_coordinate< numeric_t > const & _point
	,	two_dimensional_coordinate< numeric_t > const & _axis
	,	numeric_t _angle
	)
{
	const static double Pi = 3.14159265359;
	const static double DegreeToRadianRatio = 1.0 / 180.0 * Pi;

	two_dimensional_coordinate< numeric_t > translated = _point - _axis;
	two_dimensional_coordinate< numeric_t > rotated;

	double AngleInRadians = DegreeToRadianRatio * _angle;

	rotated.m_x
		=	translated.m_x * ( std::cos( AngleInRadians ) )
		-	translated.m_y * ( std::sin( AngleInRadians ) )
		;

	rotated.m_y
		=	translated.m_x * ( std::sin( AngleInRadians ) )
		+	translated.m_y * ( std::cos( AngleInRadians ) )
		;

	rotated.m_x;
	rotated.m_y;

	return rotated + _axis;

}
//-----------------------------------------------------------------------------
template< class numeric_t >
inline
two_dimensional_coordinate< numeric_t >
midpoint(
		two_dimensional_coordinate< numeric_t > const & _first
	,	two_dimensional_coordinate< numeric_t > const & _second
	)
{
	return two_dimensional_coordinate< numeric_t >(
			( _first.m_x + _second.m_x ) / numeric_t( 2.0 )
		,	( _first.m_y + _second.m_y ) / numeric_t( 2.0 )
		);
}

//#############################################################################
};
#endif