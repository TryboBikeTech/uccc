#ifndef __73F03241_713C_4B14_94B0_C83509464534__
#define __73F03241_713C_4B14_94B0_C83509464534__

#include "file_content_comparator.hpp"
#include "dll_interface.hpp"
#include "two_dimensional_coordinate.hpp"
#include <boost/intrusive_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>

#include <string>

namespace Uccc
{

void UcccExport PrintResult(
		std::string const & _initial
	,	std::string const & _expected
	,	std::string const & _result
	,	std::string const & _expectationName
	);

void UcccExport PrintResult(
		std::string const & _expected
	,	std::string const & _result
	,	std::string const & _expectationName
	);

void UcccExport Success( std::string const & _expectationName );

void UcccExport Failed( std::string const & _expectationName );

void UcccExport Info( std::string const & _info );
//-------------------------------------------------------------------------------------------------
template< typename _Type >
std::string Stringify( _Type const & _type );

//-------------------------------------------------------------------------------------------------
template< typename _Floating, typename _Dummy >
inline
std::string Stringify( _Floating const & _floating )
{
	std::string result;

	if( _floating < _Floating( 0.0001 ) )
	{
		result = "Unconvertable.";
	}
	if( std::abs( _floating ) < _Floating( 10000.0 ) && std::abs( ( _floating ) - std::round( _floating ) ) > _Floating( 0.0001 ) )
	{
		result = boost::lexical_cast< std::string >( _floating );
		if( result.length() > 8 )
			result = result.substr( 0, 8 );
	}
	else
	{
		result = boost::lexical_cast< std::string >( std::round( _floating ) );
	}

	if( result == "-0" )
		result = "0";

	while( result.length() < 9 )
		result = " " + result;

	return result;
}
//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify< float >( float const & _float )
{
	return Stringify< float, int >( _float );
}

//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify< double >( double const & _double )
{
	return Stringify< double, int >( _double );
}
//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify( two_dimensional_coordinate< double > const & _point )
{
	return  "( " + Stringify( _point.m_x ) + " : " + Stringify( _point.m_y ) + " )";
}

//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify( std::string const & _string )
{
	return _string;
}
//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify( int const & _int )
{
	return boost::lexical_cast< std::string >( _int );
}
//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify( bool const & _bool )
{
	return _bool ? "True" : "False";
}
//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify( std::size_t const & _point )
{
	return  "( " + boost::lexical_cast< std::string >( _point ) + " )";
}
//-------------------------------------------------------------------------------------------------
template<>
inline
std::string Stringify( FileContentComparator const & _comparator )
{
	return _comparator.GetResultString();
}
//-------------------------------------------------------------------------------------------------
template< typename _Type >
class Expectation
{
public:
	Expectation(
			_Type const & _initial
		,	_Type const & _expectation
		,	std::string const & _expectationName
		,	bool _failUninitialized = true
		)
	:	m_initial( _initial )
	,	m_expected( _expectation )
	,	m_expectationName( _expectationName )
	,	m_failUninitialized( _failUninitialized )
	,	m_emptyInitial( false )
	{
	}

	Expectation(
			_Type const & _expectation
		,	std::string const & _expectationName
		,	bool _failUninitialized = true
		)
	:	m_expected( _expectation )
	,	m_expectationName( _expectationName )
	,	m_failUninitialized( _failUninitialized )
	,	m_emptyInitial( true )
	{
	}

	void Check( _Type const & _result ) const
	{
		if( m_emptyInitial )
		{
			PrintResult(
					Stringify( m_expected )
				,	Stringify( _result )
				,	m_expectationName
				);
		}
		else
		{
			PrintResult(
					Stringify( m_initial )
				,	Stringify( m_expected )
				,	Stringify( _result )
				,	m_expectationName
				);
		}

	}

	void Check( boost::optional< _Type > const & _result ) const
	{
		if( _result.is_initialized() )
			Check( *_result );
		else if( m_failUninitialized )
			Failed( m_expectationName );
		else
			Success( m_expectationName );
	}

	void Check( boost::intrusive_ptr< _Type > const & _result ) const
	{
		if( _result.is_initialized() )
			Check( *_result );
		else if( m_failUninitialized )
			Failed( m_expectationName );
		else
			Success( m_expectationName );
	}

	_Type Initial() const
	{
		return m_initial;
	}

	_Type Expected() const
	{
		return m_expected;
	}

private:

	bool m_emptyInitial;
	_Type m_initial;
	_Type m_expected;
	std::string m_expectationName;
	bool m_failUninitialized;
};
//-------------------------------------------------------------------------------------------------
template< typename _Type >
class Comparison
{
public:
	Comparison( std::string const & _name )
	:	m_name( _name )
	{
	}

	void
	Equal( _Type const & _left, _Type const & _right ) const
	{
		if( _left == _right )
		{
			Success( m_name );
			return;
		}
		else
		{
			Failed(
					m_name
				+	": Equality comparison. Result:\n"
				+	Stringify( _left )
				+	"\n"
				+	Stringify( _right )	
				);
		}
	}

	void
	Different( _Type const & _left, _Type const & _right ) const
	{
		if( !( _left == _right ) )
		{
			Success( m_name );
			return;
		}
		else
		{
			Failed(
					m_name
				+	": Difference comparison. Result: "
				+	Stringify( _left )
				+	" "
				+	Stringify( _right )	
				);
		}
	}

private:

	std::string m_name;
};
}


#endif