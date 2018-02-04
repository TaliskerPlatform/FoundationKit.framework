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

#ifndef TALISKER_DICTIONARY_HH_
# define TALISKER_DICTIONARY_HH_        1

# include "IDictionary.h"

# include "Object.hh"

namespace Talisker
{
#ifndef TALISKER_INTERNAL_FOUNDATION_
	struct DictionaryPrivate;
#endif

	class TALISKER_EXPORT_ Dictionary: public Object
	{
	public:
		Dictionary();
		virtual ~Dictionary();

		virtual IObject *valueForKey(const String &key);
		virtual IObject *valueForKey(const char *key);
		virtual void setObject(const char *key, IObject *object);
		virtual void setObject(const String &key, IObject *object);

		virtual size_t count(void);
/*		virtual IObject *valueForKey(IString *key); */

/*		virtual void setObject(IString *key, IObject *object); */
	protected:
		DictionaryPrivate *m_dict;
	};
};

#endif /*!TALISKER_DICTIONARY_HH_*/
