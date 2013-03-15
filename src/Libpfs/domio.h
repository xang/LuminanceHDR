/**
 * @brief PFS library - DOM I/O
 *
 * This file is a part of Luminance HDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2003,2004 Rafal Mantiuk and Grzegorz Krawczyk
 * Copyright (C) 2011 Davide Anastasia
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Rafal Mantiuk, <mantiuk@mpi-sb.mpg.de>
 * @author Davide Anastasia <davideanastasia@users.sourceforge.net>
 */

#ifndef PFS_DOMIO_H
#define PFS_DOMIO_H

#include <cstdio>

namespace pfs
{
// forward declaration
class Frame;

/// @brief Reading and writing frames in PFS format from/to streams.
namespace DOMIO
{

/// @brief Creates a frame that can be latter written to the stream
/// using writeFrame method. This method and readFrame are the
/// only way to create Frame objects.
///
/// @note Frame object must be released with freeFrame methods
/// as soon as it is no longer needed. Otherwise the
/// application will run out of memory.
///
/// @param width width of the frame to create
/// @param height height of the frame to create
/// @return Frame object that can be modified and written back to PFS
/// stream using writeFrame method
Frame *createFrame( size_t width, size_t height );

/// @brief Deallocated memory allocated with createFrame or readFrame. Must
/// be called as soon as frame is not needed. Pointer to a frame is
/// invalid after this method call.
///
/// @param frame Frame object to be freed
void freeFrame( Frame *frame );


} // namespace DOMIO
} // namespace pfs

#endif // PFS_DOMIO_H




