#ifndef __common_intrudable_hpp__
#define __common_intrudable_hpp__

#include "boost/intrusive_ptr.hpp"

namespace Uccc
{

//#################################################################################################
template< class _intrudable >
inline
void
intrusive_ptr_add_ref( _intrudable* _referee )
{
	++_referee->m_reference_counter;
}
//-------------------------------------------------------------------------------------------------
template< class _intrudable >
inline
void
intrusive_ptr_release( _intrudable* _referee )
{
	--_referee->m_reference_counter;
	if ( _referee->m_reference_counter == 0 )
	{
		delete _referee;
		_referee = 0;
	}
}
//-------------------------------------------------------------------------------------------------
namespace detail
{
	struct intrudable
	{
		intrudable()
		:	m_reference_counter( 0 )
		{}

		virtual ~intrudable(){};

		long long m_reference_counter;
	};
}
//-------------------------------------------------------------------------------------------------
struct intrudable : virtual public detail::intrudable
{
};
//#################################################################################################

}

#endif