#include "singleton.hpp"

#include <map>

namespace Uccc
{
namespace Detail
{

static std::map< std::size_t, void * > s_instances;

std::map< std::size_t, void * > & instance_storage::get_storage_impl()
{
	return s_instances;
}

}
}