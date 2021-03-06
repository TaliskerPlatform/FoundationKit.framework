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

#ifndef TALISKER_OBJECT_HH_
# define TALISKER_OBJECT_HH_           1

# include "IObject.h"

# if defined(__cplusplus)

/* C++ interface to Talisker::Object */

namespace Talisker {

	class TALISKER_EXPORT_ Object: virtual public IObject
	{
	public:
		static IObject *createObject(void) ALIAS(Talisker.Object.createObject);
	public:
		Object();
		virtual ~Object();
	public:
		virtual __stdcall int queryInterface(const uuid_t riid, void **object);
		virtual __stdcall uint32_t retain();
		virtual __stdcall uint32_t release();
	protected:
		uint32_t m_refcount;
	};

};

# else

/* C interface to Talisker::Object */

IObject *Talisker_Object_createObject(void) ALIAS(Talisker.Object.createObject);

# endif

#endif /*!TALISKER_OBJECT_HH_*/
