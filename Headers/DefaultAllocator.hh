/* Talisker
 * Foundation Toolkit
 */

/* Copyright 2012-2017 Mo McRoberts.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef TALISKER_DEFAULTALLOCATOR_HH_
# define TALISKER_DEFAULTALLOCATOR_HH_  1

# include "IAllocator.h"

# include "Object.hh"

namespace Talisker {

	class TALISKER_EXPORT_ DefaultAllocator: virtual public IAllocator, public Object
	{
	public:
		static IAllocator *defaultAllocator(void);
	public:
		DefaultAllocator();
		virtual ~DefaultAllocator();
		
		virtual void *alloc(size_t nbytes);
		virtual void *realloc(void *ptr, size_t nbytes);
		virtual void free(void *ptr);
		virtual size_t size(void *ptr);
		virtual int didAlloc(void *ptr);
		virtual void compact(void);
	};

};

#endif /*!TALISKER_DEFAULTALLOCATOR_HH_*/
