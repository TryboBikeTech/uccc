#include "unit_tests_framework.hpp"

#include <iostream>
#include <string>


#ifdef WIN32
#include <Windows.h>
#endif

namespace Uccc
{

//-------------------------------------------------------------------------------------------------
namespace ColorBits
{
	const short Blue = 0x01;
	const short Green = 0x02;
	const short Red = 0x04;
	const short Intensity = 0x8;
	const short BackBlue = 0x10;
	const short BackGreen = 0x20;
	const short BackRed = 0x40;
	const short BackIntensity = 0x80;
};


struct ConsoleTextColor
{
	enum Mnemonic
	{
			Red = ColorBits::Red | ColorBits::Intensity
		,	Green = ColorBits::Green | ColorBits::Intensity
		,	Blue = ColorBits::Blue | ColorBits::Intensity
	};
};

//-------------------------------------------------------------------------------------------------
void ConsoleColouredOutput(
		std::string const & _text
	,	ConsoleTextColor::Mnemonic _color
	)
{
#ifdef WIN32
	HANDLE stdOut = GetStdHandle( STD_OUTPUT_HANDLE );

	CONSOLE_SCREEN_BUFFER_INFO bufferInfo;

	memset( &bufferInfo, 0, sizeof( bufferInfo ) );

	GetConsoleScreenBufferInfo( stdOut, &bufferInfo );

	WORD screenBitmask = bufferInfo.wAttributes;
	screenBitmask &= 0x00;
	screenBitmask |= _color;

	SetConsoleTextAttribute( stdOut, screenBitmask );
#endif
	std::cout << _text;
#ifdef WIN32
	SetConsoleTextAttribute( stdOut, bufferInfo.wAttributes );
#endif

	std::cout << ": ";

}
//-------------------------------------------------------------------------------------------------
void PrintResult(
		std::string const & _initial
	,	std::string const & _expected
	,	std::string const & _result
	,	std::string const & _expectationName
	)
{
	if( _expected != _result )
	{
		ConsoleColouredOutput( "ERROR", ConsoleTextColor::Red );

		std::cout
			<<	"Expectation: "
			<<	"\"" <<_expectationName << "\"" << " "
			<<	"failed.\n"
			<<	"\tInitial value: "
			<<	_initial << ". "
			<<	"Expected: "
			<<	_expected << " "
			<<	"got: "
			<<	_result << "\n"
			;
	}
	else
	{
		Success( _expectationName );
	}
}
//-------------------------------------------------------------------------------------------------
void PrintResult(
		std::string const & _expected
	,	std::string const & _result
	,	std::string const & _expectationName
	)
{
	if( _expected != _result )
	{
		ConsoleColouredOutput( "ERROR", ConsoleTextColor::Red );

		std::cout
			<<	"Expectation: "
			<<	"\"" <<_expectationName << "\"" << " "
			<<	"failed.\n"
			<<	"Expected: "
			<<	_expected << " "
			<<	"got: "
			<<	_result << "\n"
			;
	}
	else
	{
		Success( _expectationName );
	}
}

//-------------------------------------------------------------------------------------------------
void
Success( std::string const & _expectationName )
{
	ConsoleColouredOutput( "SUCCESS", ConsoleTextColor::Green );

	std::cout
		<<	"Expectation: "
		<<	"\"" <<_expectationName << "\"" << " "
		<<	"passed.\n"
		;
}
//-------------------------------------------------------------------------------------------------
void
Failed( std::string const & _expectationName )
{
	ConsoleColouredOutput( "ERROR", ConsoleTextColor::Red );

	std::cout
		<<	"Expectation: "
		<<	"\"" << _expectationName << "\"" << " "
		<<	"failed.\n"
		;
}
//-------------------------------------------------------------------------------------------------
void Info( std::string const & _info )
{
	ConsoleColouredOutput( "INFO", ConsoleTextColor::Blue );

	std::cout << _info << "\n";
}

}