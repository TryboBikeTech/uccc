#ifndef __common_ensure_range_hpp__
#define __common_ensure_range_hpp__

namespace common
{
//-----------------------------------------------------------------------------
    /**
        @remark
            ensure that a value is between a and b including those two
        @return
            value modfied between a and b
    */
    template < class numeric_t >
    void ensure_range( numeric_t _lower, numeric_t _upper, numeric_t& _value )
    {
        if ( _upper < _lower )
            std::swap( _upper, _lower );

        if ( _value < _lower )
			_value = _lower;

        if ( _value > _upper )
			_value = _upper;
    }
//-----------------------------------------------------------------------------
};
#endif