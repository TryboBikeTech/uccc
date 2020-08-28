#include "sparse_matrix.hpp"
#include "ensure_range.hpp"

#include <iostream>

namespace Uccc
{
//-----------------------------------------------------------------------
const static int OccupiedRow = 1;

SparseMatrix::SparseMatrix( index_range _size )
{
    m_latitude = _size.m_y;
	m_longitude = _size.m_y;
    m_elements.resize( _size.m_x + OccupiedRow );
}
//-----------------------------------------------------------------------------
void SparseMatrix::AddAt(index_range coords)
{
#ifdef DEBUG
    if (!validate(coords)) throw 0;
#endif
    // check the size of a given longitunal column
    int column_size = m_elements[coords.m_x].size();

    if (IsAt(coords)) return;

    if (column_size == 0)
    {
        AddStrip(coords.m_y, coords.m_y + 1, coords.m_x);
        if (coords.m_x != m_longitude)
        {
            AddAt(index_range(m_longitude, coords.m_x));
        }
        return;
    }

    data_iter indice = m_elements[coords.m_x].begin();
    data_iter bumper = m_elements[coords.m_x].end();
    for (int x = 0; x < column_size;++x)
    {
        if (indice->m_x <= coords.m_y && indice->m_y > coords.m_y)
        {
            return;
        }
        // element is smaller then first strip in the array
        if (indice->m_x > coords.m_y)
        {
            if (indice->m_x > coords.m_y + 1)
            {
                // at least two element difference
                // check if it
                AddStrip(coords.m_y, coords.m_y + 1, coords.m_x);
            } else {
                // 1 element difference, increase x
                --indice->m_x;
            }
            return;
        }
        // add one element to the back
        if (indice->m_y == coords.m_y)
        {
            ++indice->m_y;
            // increasing x might have joined this strip to another, let's check if
            // that is true
            ++indice;
            // exploiting partial condition estimation!
            if ( indice != bumper && indice->m_x == coords.m_y + 1)
            {
                // there is a join
                // remove old and increase previous
                int y = indice->m_y;
                --indice;
                indice->m_y = y;
                ++indice;
                m_elements[coords.m_x].erase(indice);
            }
            return;
        } else {
            ++indice;
        }
    }
    AddStrip(coords.m_y, coords.m_y + 1, coords.m_x);
}
//-----------------------------------------------------------------------------
/** obtain an iformation if there is an element at coordinate
* @param, coords.m_x - longitunal coordinate of the element
* @param, coords.m_y - latitunal coordinate of the element
* @return, true if there is an element, false otherwise
*/
bool SparseMatrix::IsAt(index_range coords)
{
#ifdef DEBUG
    if (!validate(coords)) throw 0;
#endif
    data_iter indice = m_elements[coords.m_x].begin();
    data_iter bumper = m_elements[coords.m_x].end();

    for (;indice != bumper; ++indice)
    {
        if (indice->m_x <= coords.m_y && indice->m_y > coords.m_y)
        {
            return true;
        }
    }
    return false;
}
//-----------------------------------------------------------------------------
/** obtain an element at a given set of vertices,
* and then remove it from the matrix
* @param, coords.m_x - longitunal coordinate of the element
* @param, coords.m_y - latitunal coordinate of the element
* @return, true if there is an element, false otherwise
*/
bool SparseMatrix::RemoveAt(index_range coords)
{
#ifdef DEBUG
    if (!validate(coords)) throw 0;
#endif
    if (!IsAt(coords))
    {
        return false;
    } else {
        data_iter indice = m_elements[coords.m_x].begin();
        data_iter bumper = m_elements[coords.m_x].end();

        for (; indice != bumper; ++indice)
        {
            if (indice->m_x == coords.m_y)
            {
                ++indice->m_x;
                if (indice->m_x == indice->m_y)
                {
                    m_elements[coords.m_x].erase(indice);
                    if (m_elements[coords.m_x].size() == 0 && coords.m_x != m_longitude)
                    {
                        RemoveAt(index_range(m_longitude, coords.m_x));
                    }
                }
                return true;
            }

            if (indice->m_y == coords.m_y + 1)
            {
                --indice->m_y;
                return true;
            }

            if (indice->m_x <= coords.m_y && indice->m_y > coords.m_y)
            {
                int tmp = indice->m_y;
                indice->m_y = coords.m_y;
                index_range newElement(coords.m_y + 1, tmp);
                ++indice;
                m_elements[coords.m_x].insert(indice,newElement);
                return true;
            }

        }
    }
    return false;
}
//-----------------------------------------------------------------------------
/** print contents of a given row
*/
void SparseMatrix::Print(int row)
{
    data_iter indice = m_elements[row].begin();
    data_iter bumper = m_elements[row].end();

    if (indice == bumper) return;

    std::cout << "row :" <<  row << ": ";
    for (; indice != bumper;++indice)
    {
        std::cout << indice->m_x << " " << indice->m_y << "|";
    }
    std::cout << "\n";
}
//-----------------------------------------------------------------------------
void SparseMatrix::PrintAll()
{
    for (int x = 0; x != m_longitude + 1 ; ++x)
    {
        Print(x);
    }
    std::cout << "\n";
}
//-----------------------------------------------------------------------------
/** get a random element index that is guaranteed to be adjacent to
* the area of array elements
*/
SparseMatrix::index_range
SparseMatrix::GetRandomAdjacentElement()
{
    index_range ret;
    ret.m_x = GetRandomRowAdjacentElement(m_longitude);

    if (ret.m_x < 0)
    {
        return index_range(-1,-1);
    }

    ret.m_y = GetRandomRowAdjacentElement(ret.m_x);

    if (ret.m_y < 0)
    {
        return index_range(-1,-1);
    }
    // returned row is empty, which means we need to improvise;

    return ret;
}
//-----------------------------------------------------------------------------
/** Returns a random element of the matrix
*
*/
SparseMatrix::index_range
SparseMatrix::GetRandomElement()
{
    index_range result(-1,-1);
    // choose the strip to use the value from
    int rowSize = m_elements[m_longitude].size();
    if (rowSize == 0) return result;

    // strip extracted, now get the row of strip
    data_iter dat = m_elements[m_longitude].begin();
    std::advance(dat , RandomValueInRange( 0, rowSize - 1 ) );
    index_range strip = *dat ;
    result.m_x = RandomValueInRange(strip.m_x, strip.m_y - 1);

    rowSize = m_elements[result.m_x].size();
    if (rowSize == 0) return index_range(-1,-1);

    dat = m_elements[result.m_x].begin();
    std::advance(dat , RandomValueInRange(0, rowSize - 1));
    strip = *dat ;
    result.m_y = RandomValueInRange(strip.m_x, strip.m_y -1 );

    return result;
}
//-----------------------------------------------------------------------------
/** Returns next valid 'true' element in an array. If (-1,-1) is passed,
    then it will return the "first" element, ie the one that is closest to (0,0).

    if invalid element is passed, then the array will err

    The array is traversed row by row. Return of (-1,-1) means that no element
    exists that is bigger.
*/
SparseMatrix::index_range
SparseMatrix::Next( index_range& current)
{
#ifdef DEBUG
    if (!Validate(current)) throw 0;
#endif
    // check if a row indexed by current.m_x exists

    if (current.m_x == current.m_y && current.m_x == -1)
    {
        // no rows exist
        if (m_elements[m_longitude].size() == 0)
        {
            return current;
        }

        // some rows exist
        current.m_x = m_elements[m_longitude].begin()->m_x;
        current.m_y = m_elements[current.m_x].begin()->m_x;
        return current;
    }

#ifdef DEBUG
    if (!IsAt(current)) throw 1;
#endif

    // first, check if there is next element in a row
    current.m_y += 1;
    if (IsAt(current)) return current;
    current.m_y -= 1;

    // nope, next strip might provide more luck, search for next strip in a row
    current.m_y = NextInRow(current.m_x, current.m_y);
    if (current.m_y != -1) return current;
        
    // well, not found, so we need to find a next row and return first item
    current.m_x = NextInRow(m_longitude, current.m_x);
    if (current.m_x == -1) return current; // return -1,-1

    current.m_y = m_elements[current.m_x].begin()->m_x;
    return current;
}
//-----------------------------------------------------------------------------
SparseMatrix::index_range SparseMatrix::First()
{
    return Next(index_range(-1,-1));
}
//-----------------------------------------------------------------------------
SparseMatrix::index_range SparseMatrix::Last()
{
    return index_range(-1,-1);
}
//-----------------------------------------------------------------------------
bool SparseMatrix::Validate(index_range coords)
{
    return coords.m_x <= m_longitude || coords.m_x >= 0 || coords.m_y >= 0;
}
//-----------------------------------------------------------------------------
/** will return an element which is adjacent to the current matirx in a latitunal way
* or is and edge if adjacency is not possible
*/
int SparseMatrix::GetRandomRowAdjacentElement(int row)
{
    // two cases, if the ROW is equal to longitude, then
    // return random number in longitude
    // otherwise return a random adjacent in latitude

    // get size of the row
    int rowSize = m_elements[row].size();

    if (rowSize == 0) return -1;

    // get beginning of the row
    data_iter indice = m_elements[row].begin();

    int choice =RandomValueInRange( 0, rowSize ); // choose which strip to take an element
    for (int x = 0; x < choice;++x, ++indice); // increase indice to the element

    if (row == m_longitude)
    {
        int diff = indice->m_y - indice->m_x; // retrieve the row contents and calculate diff
        choice = RandomValueInRange( 0, diff - 1 ); // get random number from 0 to diff
        return indice->m_x + choice; // result -> begining of the row + diff, giving a random element which is true in a given row
    } else {
        choice = RandomValueInRange( 0, 99 );
        int ret;
        choice <= 49 ? ret = indice->m_x - 1 : ret = indice->m_y;
        common::ensure_range< int >( 0 , m_latitude - 1 , ret );
        return ret;
    }
}
//-----------------------------------------------------------------------------
void SparseMatrix::AddStrip(int begin, int end, int index)
{
    // search for the strip which will fit
    data_iter indice = m_elements[index].begin();
    data_iter bumper = m_elements[index].end();

    index_range strip(begin, end);

    if (indice == bumper)
    {
        m_elements[index].push_back(strip);
    } else {
        if (indice->m_x > strip.m_y)
        {
            m_elements[index].insert(indice, strip);
        } else {
            ++indice;
            if (indice == bumper)
            {
                m_elements[index].push_back(strip);
            }
        }
    }
}
//-----------------------------------------------------------------------------
int SparseMatrix::NextInRow(int index, int position)
{
    data_iter indice = m_elements[index].begin();
    data_iter bumper = m_elements[index].end();

    position += 1; // create candidate
    for (; indice != bumper ; ++indice)
    {
        // case 1, index is after current strip, might be before next, continue loop
        if (indice->m_y <= position)
        {
            continue;
        }

        // case 2, index in in a strip
        if (indice->m_x <= position && indice->m_y > position)
        {
            return position;
        }

        // case 3, index is before current strip
        if (indice->m_x > position)
        {
            return indice->m_x;
        }
    }

    return -1;
}
//-----------------------------------------------------------------------------
void SparseMatrix::Clear()
{
    data_matrix::iterator indice = m_elements.begin();
    data_matrix::iterator bumper = m_elements.end();

    for (; indice != bumper; ++indice)
    {
        indice->clear();
    }
}
//-----------------------------------------------------------------------------
int
SparseMatrix::RandomValueInRange(
		int _lower
	,	int _upper
	)
{
	if ( _lower > _upper )
		std::swap( _lower, _upper );
	int return_value
		=	int(
					m_random_number_generator()
				*	std::abs( _upper - _lower )
				-	_lower
				);

	return return_value;
}
//#############################################################################
}
