/*======================================================================

  This file is part of the elastix software.

  Copyright (c) University Medical Center Utrecht. All rights reserved.
  See src/CopyrightElastix.txt or http://elastix.isi.uu.nl/legal.php for
  details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE. See the above copyright notices for more information.

======================================================================*/

/** This class is a modification of an ITK class.
 * The original copyright message is pasted here, which includes also
 * the version information: */
/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date: 2008-04-15 19:54:41 +0200 (Tue, 15 Apr 2008) $
  Version:   $Revision: 1573 $

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef _itkVectorDataContainer_txx
#define _itkVectorDataContainer_txx
#include "itkVectorDataContainer.h"

#include "itkNumericTraits.h"

namespace itk
{

/**
 * Get a reference to the element at the given index.
 * It is assumed that the index exists, and it will not automatically
 * be created.
 *
 * It is assumed that the value of the element is modified through the
 * reference.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::Element&
VectorDataContainer< TElementIdentifier , TElement >
::ElementAt(ElementIdentifier id)
{
  this->Modified();
  return this->VectorType::operator[](id);
}

/**
 * Get a reference to the element at the given index.
 * It is assumed that the index exists, and it will not automatically
 * be created.
 *
 */
template <typename TElementIdentifier, typename TElement>
const typename VectorDataContainer< TElementIdentifier , TElement >::Element&
VectorDataContainer< TElementIdentifier , TElement >
::ElementAt(ElementIdentifier id) const
{
  return this->VectorType::operator[](id);
}



/**
 * Get a reference to the element at the given index.
 * If the element location does not exist, it will be created with a
 * default element value.
 *
 * It is assumed that the value of the element is modified through the
 * reference.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::Element&
VectorDataContainer< TElementIdentifier , TElement >
::CreateElementAt(ElementIdentifier id)
{
  if(id >= this->VectorType::size())
    {
    this->CreateIndex(id);
    }
  this->Modified();
  return this->VectorType::operator[](id);
}


/**
 * Read the element from the given index.
 * It is assumed that the index exists.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::Element
VectorDataContainer< TElementIdentifier , TElement >
::GetElement(ElementIdentifier id) const
{
  return this->VectorType::operator[](id);
}


/**
 * Set the element value at the given index.
 * It is assumed that the index exists.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::SetElement(ElementIdentifier id, Element element)
{
  this->VectorType::operator[](id) = element;
  this->Modified();
}


/**
 * Set the element value at the given index.
 * If the element location does not exist, it will be created with a
 * default element value.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::InsertElement(ElementIdentifier id, Element element)
{
  if(id >= static_cast<ElementIdentifier>(this->VectorType::size()))
    {
    this->CreateIndex(id);
    }
  this->VectorType::operator[](id) = element;
  this->Modified();
}


/**
 * Check if the index range of the STL vector is large enough to allow the
 * given index without expansion.
 */
template <typename TElementIdentifier, typename TElement>
bool
VectorDataContainer< TElementIdentifier , TElement >
::IndexExists(ElementIdentifier id) const
{
  return (NumericTraits<ElementIdentifier>::IsNonnegative(id)
          && (id < this->VectorType::size()));
}



/**
 * Check if the given index is in range of the STL vector.  If it is not,
 * return false.  Otherwise, set the element through the pointer (if it isn't
 * NULL), and return true.
 */
template <typename TElementIdentifier, typename TElement>
bool
VectorDataContainer< TElementIdentifier , TElement >
::GetElementIfIndexExists(ElementIdentifier id, Element* element) const
{
  if (NumericTraits<ElementIdentifier>::IsNonnegative(id)
      && (id < this->VectorType::size()))
    {
    if(element)
      {
      *element = this->VectorType::operator[](id);
      }
    return true;
    }
  return false;
}


/**
 * Make sure that the index range of the STL vector is large enough to allow
 * the given index, expanding it if necessary.  The index will contain
 * the default element regardless of whether expansion occurred.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::CreateIndex(ElementIdentifier id)
{
  if(id >= static_cast<ElementIdentifier>(this->VectorType::size()))
    {
    /**
     * The vector must be expanded to fit the
     * new id.
     */
    this->VectorType::resize(id+1);
    this->Modified();
    }
  else if(id > 0)
    {
    /**
     * No expansion was necessary.  Just overwrite the index's entry with
     * the default element.
     */
    this->VectorType::operator[](id) = Element();
    this->Modified();
    }
}


/**
 * It doesn't make sense to delete a vector index.
 * Instead, just overwrite the index with the default element.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::DeleteIndex(ElementIdentifier id)
{
  this->VectorType::operator[](id) = Element();
  this->Modified();
}


/**
 * Get a begin const iterator for the vector.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::ConstIterator
VectorDataContainer< TElementIdentifier , TElement >
::Begin(void) const
{
  return ConstIterator(0, this->VectorType::begin());
}


/**
 * Get an end const iterator for the vector.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::ConstIterator
VectorDataContainer< TElementIdentifier , TElement >
::End(void) const
{
  return ConstIterator(this->VectorType::size()-1, this->VectorType::end());
}


/**
 * Get a begin iterator for the vector.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::Iterator
VectorDataContainer< TElementIdentifier , TElement >
::Begin(void)
{
  return Iterator(0, this->VectorType::begin());
}


/**
 * Get an end iterator for the vector.
 */
template <typename TElementIdentifier, typename TElement>
typename VectorDataContainer< TElementIdentifier , TElement >::Iterator
VectorDataContainer< TElementIdentifier , TElement >
::End(void)
{
  return Iterator(this->VectorType::size()-1, this->VectorType::end());
}


/**
 * Get the number of elements currently stored in the vector.
 */
template <typename TElementIdentifier, typename TElement>
unsigned long
VectorDataContainer< TElementIdentifier , TElement >
::Size(void) const
{
  return static_cast<unsigned long>( this->VectorType::size() );
}


/**
 * Clear the elements. The final size will be zero.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::Initialize(void)
{
  this->VectorType::clear();
}



/**
 *    Allocate memory for at the requested number of elements.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::Reserve(ElementIdentifier size)
{
  this->CreateIndex(size-1);
}


/**
 *   Try to compact the internal representation of the memory.
 */
template <typename TElementIdentifier, typename TElement>
void
VectorDataContainer< TElementIdentifier , TElement >
::Squeeze(void)
{
}

} // end namespace itk

#endif
