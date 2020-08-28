#ifndef __COMMON_SINGLETON_H__
#define __COMMON_SINGLETON_H__

#ifdef _WIN32

#ifndef _CPPRTTI
#error "Opaque Singleton Requires RTTI"
#endif

#endif

#include "dll_interface.hpp"

#include <map>
#include <memory>
#include <typeinfo>

#define DETAIL_COMMON_OPAQUE_SINGLETON_STRINGIFY( STRING ) #STRING

namespace Uccc
{
template<
		typename _singletonized_class
	,	template < typename > class _holder_type = std::shared_ptr
>
class opaque_singleton;



namespace Detail
{
//##################################################################################################
// typeid is guaranteed only for virtual type and with RTTI turned on.
// Thus inheritance from a virtual type is needed
// this dummy class does precisely that.
class UcccExport typeid_creation_enforcer
{
public:
	virtual ~typeid_creation_enforcer(){};
};
//##################################################################################################

class UcccExport instance_storage
{
	public:
		template< class _singletonized_class >
		static void add_instance( _singletonized_class * _instance )
		{
			std::size_t class_id = get_class_id< _singletonized_class >();

			auto element = get_storage_impl().find( class_id );

			if ( element != get_storage_impl().end() )
				throw std::exception( "ERROR: " __FILE__ ":" DETAIL_COMMON_OPAQUE_SINGLETON_STRINGIFY(__LINE__) " Double singleton instancing!" );

			get_storage_impl()[ class_id ] = reinterpret_cast< void * >( _instance );
		}

		template< class _singletonized_class >
		static _singletonized_class * get_instance()
		{
			std::size_t class_id = get_class_id< _singletonized_class >();

			auto element = get_storage_impl().find( class_id );

			if( element == get_storage_impl().end() )
				throw std::exception( "ERROR: " __FILE__ ":" DETAIL_COMMON_OPAQUE_SINGLETON_STRINGIFY(__LINE__) " No instance!" );

			return reinterpret_cast< _singletonized_class * >( element->second );
		}

		template< class _singletonized_class >
		static void delete_instance()
		{
			std::size_t class_id = get_class_id< _singletonized_class >();

			auto element = get_storage_impl().find( class_id );

			if ( element != get_storage_impl().end() )
			{
				_singletonized_class * instance
					=	reinterpret_cast< _singletonized_class * >( element->second );
				get_storage_impl().erase( element );
				delete instance;
				return;				
			}
		}

	private:
		template< class _singletonized_class >
		static std::size_t get_class_id()
		{
			return typeid( opaque_singleton< _singletonized_class > ).hash_code();
		}

	static std::map< std::size_t, void * > & get_storage_impl();
};
//--------------------------------------------------------------------------------------------------
struct instance_lifecycle_policy
{
	enum mnemonic
	{
			delete_instance
		,	keep_instance
	};
};

};
//##################################################################################################
template<
		typename _singletonized_class
	,	template < typename > class _holder_type
>
class opaque_singleton : public Detail::typeid_creation_enforcer
{
	typedef _holder_type< opaque_singleton< _singletonized_class, _holder_type > > holder_type;

	public:
	opaque_singleton()
	:	m_policy( Detail::instance_lifecycle_policy::keep_instance )
	{
	}
	//----------------------------------------------------------------------------------------------
	~opaque_singleton()
	{
		if( m_policy == Detail::instance_lifecycle_policy::delete_instance )
			Detail::instance_storage::delete_instance< _singletonized_class >();
	}

	//----------------------------------------------------------------------------------------------
	static
	holder_type
	manufacture()
	{
		Detail::instance_storage::add_instance< _singletonized_class >( new _singletonized_class );
		return holder_type(
				new opaque_singleton( Detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------
	template< typename _1 >
	static
	holder_type
	manufacture( _1 const & _a1 )
	{
		Detail::instance_storage::add_instance< _singletonized_class >(
				new _singletonized_class( _a1 )
			);

		return holder_type(
				new opaque_singleton( Detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------	
	template< typename _1 , typename _2 >
	static
	holder_type
	manufacture( _1 const & _a1, _2 const & _a2 )
	{
		Detail::instance_storage::add_instance< _singletonized_class >(
				new _singletonized_class( _a1, _a2 )
			);

		return holder_type(
				new opaque_singleton( detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------
	template< typename _1, typename _2, typename _3 >
	static
	holder_type
	manufacture( _1 const & _a1, _2 const & _a2, _3 const & _a3 )
	{
		Detail::instance_storage::add_instance< _singletonized_class >(
				new _singletonized_class( _a1, _a2, _a3 )
			);

		return holder_type(
				new opaque_singleton( Detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------
	template< typename _1, typename _2, typename _3, typename _4 >
	static
	holder_type
	manufacture( _1 const & _a1, _2 const & _a2, _3 const & _a3, _4 const & _a4 )
	{
		Detail::instance_storage::add_instance< _singletonized_class >(
				new _singletonized_class( _a1, _a2, _a3, _a4 )
			);

		return holder_type(
				new opaque_singleton( Detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------
	template< typename _1, typename _2, typename _3, typename _4, typename _5 >
	static
	holder_type
	manufacture( _1 const & _a1, _2 const & _a2, _3 const & _a3, _4 const & _a4, _5 const & _a5 )
	{
		Detail::instance_storage::add_instance< _singletonized_class >(
				new _singletonized_class( _a1, _a2, _a3, _a4, _a5 )
			);

		return holder_type(
				new opaque_singleton( Detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------
	template< typename _1, typename _2, typename _3, typename _4, typename _5, typename _6 >
	static
	holder_type
	manufacture(
			_1 const & _a1
		,	_2 const & _a2
		,	_3 const & _a3
		,	_4 const & _a4
		,	_5 const & _a5
		,	_6 const & _a6
		)
	{
		Detail::instance_storage::add_instance< _singletonized_class >(
				new _singletonized_class( _a1, _a2, _a3, _a4, _a5, _a6 )
			);

		return holder_type(
				new opaque_singleton( Detail::instance_lifecycle_policy::delete_instance )
			);
	}
	//----------------------------------------------------------------------------------------------
    _singletonized_class* operator->()
    {
        return Detail::instance_storage::get_instance< _singletonized_class >();
    }
//--------------------------------------------------------------------------------------------------
    _singletonized_class& operator*()
    {
        return *operator->();
    }
private: //-----------------------------------------------------------------------------------------
	opaque_singleton( Detail::instance_lifecycle_policy::mnemonic _lifecycle )
	:	m_policy( _lifecycle )
	{
	}

	Detail::instance_lifecycle_policy::mnemonic m_policy;
};
//##################################################################################################
};

#endif
