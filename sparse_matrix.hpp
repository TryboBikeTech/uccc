#ifndef __sparse_matrix_h__
#define __sparse_matrix_h__

#include "two_dimensional_coordinate.hpp"
#include "dll_interface.hpp"

#include <vector>
#include <list>
#include <boost/random.hpp>

namespace Uccc
{
//#############################################################################
class UcccExport SparseMatrix
{
	typedef two_dimensional_coordinate< int > index_range;
    typedef std::list< index_range > strip_list;
    typedef std::vector< strip_list > data_matrix;
    typedef strip_list::iterator data_iter;
public: //---------------------------------------------------------------------
    SparseMatrix( index_range size );
//-----------------------------------------------------------------------------
    /** add an element into the array
    * @param, coords.m_x - longitunal coordinate of the element
    * @param, coords.m_y - latitunal coordinate of the element
    */
    void AddAt(index_range coords);
//-----------------------------------------------------------------------------
    /** obtain an iformation if there is an element at coordinate
    * @param, coords.m_x - longitunal coordinate of the element
    * @param, coords.m_y - latitunal coordinate of the element
    * @return, true if there is an element, false otherwise
    */
    bool IsAt(index_range coords);
//-----------------------------------------------------------------------------
    /** obtain an element at a given set of vertices,
    * and then remove it from the matrix
    * @param, coords.m_x - longitunal coordinate of the element
    * @param, coords.m_y - latitunal coordinate of the element
    * @return, true if there is an element, false otherwise
    */
    bool RemoveAt(index_range coords);
//-----------------------------------------------------------------------------
    /** print contents of a given row
    */
    void Print(int row);
//-----------------------------------------------------------------------------
    void PrintAll();
//-----------------------------------------------------------------------------
    /** get a random element index that is guaranteed to be adjacent to
    * the area of array elements
    */
    index_range GetRandomAdjacentElement();
//-----------------------------------------------------------------------------
    index_range GetRandomElement();
//-----------------------------------------------------------------------------
    /** Returns next valid 'true' element in an array. If (-1,-1) is passed,
        then it will return the "first" element, ie the one that is closest to (0,0).

        if invalid element is passed, then the array will err

        The array is traversed row by row. Return of (-1,-1) means that no element
        exists that is bigger.
    */
    index_range Next(index_range& current);
//-----------------------------------------------------------------------------
    /** Return the first element of the array
    */
    index_range First();
//-----------------------------------------------------------------------------
    /** return the array 'last' marker, ie an element that is 1 position after the array
    */
    index_range Last();
//-----------------------------------------------------------------------------
    /** clear all data from matrix (set to false);
    */
    void Clear();
private: //--------------------------------------------------------------------
    bool Validate(index_range coords);
//-----------------------------------------------------------------------------
    /** will return an element which is adjacent to the current matirx in a latitunal way
    * or is and edge if adjacency is not possible
    */
    int GetRandomRowAdjacentElement(int row);
//-----------------------------------------------------------------------------
    /** add a single strip to the array
    * @param begin - starting element
    * @param end - last element
    * @param index - to which row to add the strip
    */
    void AddStrip(int begin, int end, int index);
//-----------------------------------------------------------------------------
    /** get next element to the given position, traversing the matrix row by row.
    * @param index - row where the 'current' element is located
    * @param positon - column of the element
    */
    int NextInRow(int index, int position);
//-----------------------------------------------------------------------------
	int RandomValueInRange( int _lower, int _upper );
//-----------------------------------------------------------------------------
#pragma warning( disable : 4251 )
    data_matrix m_elements; ///< pointer to the data
    int m_latitude;
	int m_longitude;

	boost::random::mt19937 m_random_number_generator;
};
//#############################################################################
};

#endif
