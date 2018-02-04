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

#ifndef TALISKER_ARRAY_HH_
# define TALISKER_ARRAY_HH_             1

# include "IArray.h"

# include "Object.hh"

namespace Talisker
{
#ifndef TALISKER_INTERNAL_FOUNDATION_
	struct ArrayPrivate;
#endif

	class TALISKER_EXPORT_ Array: public Object
	{
	public:
		Array();
		virtual ~Array();
		
		virtual bool containsObject(IObject *obj);
		virtual size_t count(void);
		virtual IObject *firstObject(void);
		virtual IObject *lastObject(void);
		virtual IObject *objectAtIndex(size_t index);
		virtual ssize_t indexOfObject(IObject *obj);
		
		virtual void addObject(IObject *obj);
		virtual void insertObject(IObject *obj, size_t index);
		virtual void removeObject(IObject *obj);
		virtual void removeObjectAtIndex(size_t index);
		virtual void removeLastObject(void);
		virtual void removeAllObjects(void);

	protected:
		ArrayPrivate *m_data;
	};
};

#endif /*!TALISKER_ARRAY_HH_*/
