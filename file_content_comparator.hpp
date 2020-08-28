#ifndef __C1551493_8537_4033_A41B_B77F65D4A828__
#define __C1551493_8537_4033_A41B_B77F65D4A828__

#include "dll_interface.hpp"

#include <boost/filesystem/path.hpp>

#include <string>

namespace Uccc
{
//----------------------------------------------------------------------------------------------
class UcccExport FileContentComparator
{
public:
	FileContentComparator( boost::filesystem::path const & _path );

	bool Compare( FileContentComparator const & _other ) const;

	std::string GetResultString() const;

	void SetPath( boost::filesystem::path const & _path );

	boost::filesystem::path GetPath() const;

private:
	
	void OpenFile();

#pragma warning( disable : 4251 )
	boost::filesystem::path m_path;

	mutable std::string m_result;
};
//----------------------------------------------------------------------------------------------
}


#endif