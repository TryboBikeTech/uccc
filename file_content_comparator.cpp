#include "file_content_comparator.hpp"

#include <boost/filesystem/operations.hpp>
#include <boost/lexical_cast.hpp>

#include <fstream>

namespace Uccc
{
//----------------------------------------------------------------------------------------------
FileContentComparator::FileContentComparator( boost::filesystem::path const & _path )
:	m_path( _path )
,	m_result( "files are equal" )
{
}
//----------------------------------------------------------------------------------------------
std::string
FileContentComparator::GetResultString() const
{
	return m_result;
}
//----------------------------------------------------------------------------------------------
bool
FileContentComparator::Compare( FileContentComparator const & _other ) const
{
	if( boost::filesystem::equivalent( m_path, _other.m_path ) )
		return true;

	if( !boost::filesystem::exists( m_path ) && !boost::filesystem::exists( _other.m_path ) )
		return true;

	if( !boost::filesystem::exists( m_path ) )
	{
		m_result = "File is missing";
		_other.m_result = "Compared to is missing";
		return false;
	}

	if( !boost::filesystem::exists( _other.m_path ) )
	{
		_other.m_result = "File is missing";
		m_result = "Compared to is missing";
		return false;
	}

	std::string path = m_path.string();
	std::string otherPath = _other.m_path.string();

	std::ifstream stream( path.c_str(), std::ios::in );
	
	if( !stream.good() )
	{
		m_result = "File could not be opened";
		_other.m_result = "Other could not be opened";
		return false;
	}

	std::ifstream otherStream( otherPath.c_str(), std::ios::in );

	if( !otherStream.good() )
	{
		_other.m_result = "File could not be opened";
		m_result = "Other could not be opened";
		return false;
	}

	int lineNumber = 0;

	while( stream.good() && otherStream.good() )
	{
		std::string line;
		std::getline( stream, line );
		
		std::string otherLine;
		std::getline( otherStream, otherLine );

		++lineNumber;

		if( line != otherLine )
		{
			static std::string quot = "\"";

			m_result
				=	"Difference in line: "
				+	boost::lexical_cast< std::string >( lineNumber )
				+	"."
				+	quot + line + quot
				;

			_other.m_result
				=	"Difference in line: "
				+	boost::lexical_cast< std::string >( lineNumber )
				+	"."
				+	quot + otherLine + quot
				;
				
			return false;
		}
		++lineNumber;
	}

	return true;
}
//----------------------------------------------------------------------------------------------
void
FileContentComparator::SetPath( boost::filesystem::path const & _path )
{
	m_path = _path;
}
//----------------------------------------------------------------------------------------------
boost::filesystem::path
FileContentComparator::GetPath() const
{
	return m_path;
}
//----------------------------------------------------------------------------------------------
}