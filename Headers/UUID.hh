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

#ifndef TALISKER_UUID_HH_
# define TALISKER_UUID_HH_              1

# include "Object.hh"
# include "String.hh"

namespace Talisker
{
	class TALISKER_EXPORT_ UUID: public Object
	{
	public:
		static const int lower = 0;
		static const int upper = (1<<0);
		static const int compact = (1<<1);

		/* Generate a new UUID */
		UUID();
		/* Duplicate a UUID object */
		UUID(const UUID &uuid);
		UUID(const UUID *uuid);
		/* Represent a UUID structure */
		UUID(const uuid_t uuid);
		/* Parse a UUID string */
		UUID(const char *uuidstr);
		UUID(const String &uuidstr);
		UUID(const String *uuidstr);
		
		virtual ~UUID();

		virtual String *string(int format = UUID::lower);
	protected:
		uuid_t m_uuid;
	};
};

#endif /*!TALISKER_UUID_HH_*/
