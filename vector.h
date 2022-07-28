#ifndef VECTOR_H
#define VECTOR_H

#include <memory> // not in git
using std::move;

namespace MC_Vec
{

template <typename T>
class Vector
{
  public:

    /* Default Constructor */
    Vector();

    /* Overloaded Constructor */
    Vector(int capacity);

    /* Overloaded Constructor */
    Vector(int capacity, const T& value);

    /* Copy Constructor */
    Vector(const Vector& source);

    /* Move Constructor */
    Vector(Vector&& source) noexcept;

    /* Destructor */
    ~Vector();

    /* Copy assignment operator*/
    const Vector& operator=(const Vector& rhs);

    /* Move assignment operator */
    Vector& operator=(Vector&& rhs) noexcept;

    /* Overloaded Subscript Opperator */
          T& operator[](int index)       { return elem[index]; }
    const T& operator[](int index) const { return elem[index]; }

    /*  Iterators  */
    using iterator = T*;
    using const_iterator = const T*;

    inline       iterator begin()       { return sizeV ? &elem[0]     : nullptr; }
    inline const_iterator begin() const { return sizeV ? &elem[0]     : nullptr; }
    inline       iterator end()         { return sizeV ? &elem[sizeV] : nullptr; }
    inline const_iterator end()   const { return sizeV ? &elem[sizeV] : nullptr; }

    /* Accessors */
    int size()     const { return sizeV; }
    int capacity() const { return space; }

    /* Mutators */
    void resize(int size, const T& value = 0);

    void reserve(int capacity);

    void push_back(T value);

    void clear(int capacity = 4);

    iterator insert(iterator ptr, const T& value);

    iterator erase(iterator ptr);


  private:
    int sizeV;    // Number of elements in vector
    int space;    // Total capacity
    T*  elem;     // Pointer to array of elements
};

}


/********************************************************************
 * Constructor:  class Vector
 *-------------------------------------------------------------------
 *  Initialize's all data memebers to a default value
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS: <none>
 *-------------------------------------------------------------------
 *   POST-CONDITIONS: All data members are set to a value of 0
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>::Vector()
    : sizeV { 0 }, space { 0 }, elem { nullptr } {}


/********************************************************************
 * Constructor:  class Vector
 *-------------------------------------------------------------------
 *  Initialize's all data memebers
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameter needs a defined argument
 *
 *        space (int) : The initial capacity of the vector
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The size of the vector is set to 0.
 *      The capacity of the vector will be set to the size of the arg.
 *      An array of the specified type will be allocated on the heap.
 *      All elements of the array will be set to 0.
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>::Vector(int space)
    : sizeV { 0 }, space { space }, elem { new T[space] {0} } {}


/********************************************************************
 * Constructor:  class Vector
 *-------------------------------------------------------------------
 *  Initialize's all data memebers
 *  All elements of the vector will contain the value of the argument
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameters needs a defined argument
 *
 *        space (int) : The initial size & capacity of the vector
 *        value (T&)  : A reference to a value of the specified type
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The size and capacity will be set to the size of the argumnet.
 *      An array of the specified type will be allocated on the heap.
 *      All elements of the array will contain the value passed as arg.
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>::Vector(int space, const T& value)
    : sizeV { space }, space { space }, elem { new T[space] }
{
    for (int index {0}; index < space; ++index)
    {
        elem[index] = value;
    }
}


/********************************************************************
 * Copy Constructor:  class Vector
 *-------------------------------------------------------------------
 *  Copy's all values from one vector to another
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      Another vector needs to have already been instantiated.
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      Performs a deep copy.
 *      The vector will contain the same values as the source vector.
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>::Vector(const Vector& source)
    : sizeV { source.sizeV }, space { source.space }, elem { new T[source.space] }
{
    for (int index {0}; index < sizeV; ++index)
    {
        elem[index] = source.elem[index];
    }
}


/********************************************************************
 * Move Constructor:  class Vector
 *-------------------------------------------------------------------
 *  Moves the resources from the source vector to the new vector
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS: A temp vector is needed for the source
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      Returns a vector pointing to the data of the source vector.
 *      The source vector will no longer be pointing to data.
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>::Vector(Vector&& source) noexcept
    : sizeV { move(source.sizeV) }, space { move(source.space) }, elem { move(source.elem) }
{
    source.elem = nullptr;
}


/********************************************************************
 * Destructor:  class Vector
 *-------------------------------------------------------------------
 *  Deallocates all memory associated with the vector
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS: <none>
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      All memory associated with the vector will be released.
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>::~Vector()
{
    delete[] elem;
}


/********************************************************************
 * Overloaded Operater = :  class Vector
 *-------------------------------------------------------------------
 *  Performes a deep copy of the vector on the right hand side
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      A instatiated vector needs to be on the right of the operator
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      RETURNS: A vector with same values as the vector on the right.
 ********************************************************************/
template <typename T>
const MC_Vec::Vector<T>& MC_Vec::Vector<T>::operator=(const Vector& rhs)
{
    if (this != &rhs)
    {
        if (sizeV)
        {
            delete[] elem;

            elem  = new T[rhs.space];

            for (int index {0}; index < rhs.sizeV; ++index)
            {
                elem[index] = rhs.elem[index];
            }
        }
        else
        {
            elem = nullptr;
        }

        sizeV = rhs.sizeV;
        space = rhs.space;
    }

    return *this;
}


/********************************************************************
 * Overloaded Operater = :  class Vector
 *-------------------------------------------------------------------
 *  Moves the resources from the vector on the right
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      A temp (RHV) vector needs to be on the right
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The temp vector on the right will no longer point to data.
 *
 *      RETURNS: A vector with same values as the vector on the right.
 ********************************************************************/
template <typename T>
MC_Vec::Vector<T>& MC_Vec::Vector<T>::operator=(Vector&& rhs) noexcept
{
    delete[] elem;

    elem  = move(rhs.elem);
    sizeV = move(rhs.sizeV);
    space = move(rhs.space);

    rhs.elem = nullptr;
}


/********************************************************************
 * Method resize :  class Vector
 *-------------------------------------------------------------------
 *  Mutator; Resizes the vector to a given size.
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *     The following parameter needs a defined argument
 *          size (int) : The newsize of the vector
 *
 *      The following parameter is optional - default = 0
 *          value (T&) : Reference to a value of the specified type
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The vector will be resized to the value of size passed as arg.
 *      If size is smaller, the capacity will not shrink.
 *      If size is larger,  the capacity will increase if needed.
 *      When size is larger, each element will be set to the given value.
 ********************************************************************/
template <typename T>
void MC_Vec::Vector<T>::resize(int size, const T& value)
{
    if (size < sizeV)
    {
        for (int index {size-1}; index < sizeV; ++index)
        {
            elem[index] = 0;
        }
    }
    else
    {
        if (size > space)
        {
            reserve(size);
        }

        for (int index {sizeV}; index < size; ++index)
        {
            elem[index] = value;
        }
    }

    sizeV = size;
}


/********************************************************************
 * Method reserve:  class Vector
 *-------------------------------------------------------------------
 *  Mutator; Increases the capacity of the vector,
 *           If the argument is larger then the current capacity.
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameter needs a defined value
 *          capacity (int) : size to set the new capacity to.
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The capacity of the vector will be resized to the given size.
 ********************************************************************/
template <typename T>
void MC_Vec::Vector<T>::reserve(int capacity)
{
    T* array;  // CALC & CALC - new array for elements

    if (capacity > space)
    {
        array = new T[capacity];

        for (int index {0}; index < sizeV; ++index)
        {
            array[index] = move(elem[index]);
        }

        delete[] elem;

        elem  = array;
        space = capacity;
    }
}


/********************************************************************
 * Method push_back :  class Vector
 *-------------------------------------------------------------------
 *  Mutator: Adds an element to the end of the vector
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameter needs a defined value
 *          value (T) : A value of the specified type
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The vector will contain the added element at the very end.
 *      Size of the vector will increase by 1.
 *      Capacity of the vector will increase if needed.
 ********************************************************************/
template <typename T>
void MC_Vec::Vector<T>::push_back(T value)
{
    if (!sizeV)
    {
        reserve(4);
    }
    else if (sizeV == space)
    {
        reserve(2 * sizeV);
    }

    elem[sizeV] = value;

    ++sizeV;
}


/********************************************************************
 * Method clear :  class Vector
 *-------------------------------------------------------------------
 *  Mutator: clears the vector and instatiates a new vector.
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameter is optional
 *          capacity (int) : capacity of the new vector.
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *     All elements in the vector prior to calling this method will
 *     be cleared. A new vector will be established with a capcity of
 *     the size passed as an argument, or a default value of 4. The
 *     size of the vector will be 0.
 ********************************************************************/
template <typename T>
void MC_Vec::Vector<T>::clear(int capacity)
{
    delete[] elem;

    elem = new T[capacity];

    sizeV = 0;
    space = capacity;
}


/********************************************************************
 * Method insert :  class Vector
 *-------------------------------------------------------------------
 *  Mutator;  Inserts a element at a specified location
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameters needs a defined value
 *
 *          ptr   (T*) : pointer to location to add the new element
 *          value (T&) : reference to the value to be inserted
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The value argument will be added to location of argument ptr.
 *      All proceeding elements will be moved to the right by 1.
 *      Size of the vector will increase by 1.
 *      Capacity of the vector will increase if needed.
 *
 *     NOTE: This method verifies that ptr is a valid position.
 *           Nothing changes if the ptr points to invalid position.
 *
 *     RETURNS: Pointer to location where element was added or null.
 ********************************************************************/
template <typename T>
T* MC_Vec::Vector<T>::insert(iterator ptr, const T& value)
{
    iterator ptr2;  // CALC & CALC - ptr that decrements from end()
    int      dif;   // CALC & CALC - offset from begin()

    if (ptr >= begin() && ptr < end())
    {
        if (sizeV == space)
        {
            dif = ptr - begin();

            reserve(space + 4);

            ptr = begin() + dif;
        }

        ptr2 = end();

        while (ptr2 > ptr)
        {
            *ptr2 = *(ptr2 - 1);
            --ptr2;
        }

        *ptr = value;

        ++sizeV;

        return ptr;
    }
    else
    {
        return nullptr;
    }

}


/********************************************************************
 * Method erase :  class Vector
 *-------------------------------------------------------------------
 *  Mutator;  Removes an element at a specified location
 *-------------------------------------------------------------------
 *   PRE-CONDITIONS:
 *      The following parameter needs a defined value
 *          ptr   (T*) : pointer to location to remove element
 *-------------------------------------------------------------------
 *   POST-CONDITIONS:
 *      The following parameter needs a defined argument
 *          ptr (T*) : pointer to location to remove element.
 *
 *     NOTE: This method verifies that ptr is a valid position.
 *           Nothing changes if the ptr points to invalid position.
 *
 *     RETURNS: ptr to location where element was removed, or null.
 ********************************************************************/
template <typename T>
T* MC_Vec::Vector<T>::erase(iterator ptr)
{
    if (ptr >= begin() && ptr < end())
    {
        for (iterator p = ptr; p < end()-1; ++p)
        {
            *p = *(p+1);
        }

        --sizeV;

        *(end()) = 0;
    }
    else
    {
        ptr = nullptr;
    }

    return ptr;
}

#endif
