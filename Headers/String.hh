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

#ifndef TALISKER_STRING_HH_
# define TALISKER_STRING_HH_           1

# include "IString.h"

# include "Object.hh"

namespace Talisker
{
	class TALISKER_EXPORT_ String: public Object
	{
	public:
		static const size_t endpos = (size_t) -1;
		
		String();
		String(const char *cstr);
		String(const String *str);
		String(const String &str);
		virtual ~String();

		virtual String &operator=(const char *str);
		virtual String &operator=(const String *str);
		virtual String &operator=(const String &str);

		virtual void assign(const unsigned char *bytes, size_t nbytes);
		virtual void assign(const char *str, size_t maxlen = String::endpos);
		virtual void assign(const String &str, size_t maxlen = String::endpos);

		virtual void append(const unsigned char *bytes, size_t nbytes);	   
		virtual void append(const char *str, size_t maxlen = String::endpos);
		virtual void append(const String &str, size_t maxlen = String::endpos);
		
		virtual void insert(const unsigned char *bytes, size_t pos, size_t nbytes);
		virtual void insert(const char *str, size_t pos = 0, size_t maxlen = String::endpos);
		virtual void insert(const String &str, size_t pos = 0, size_t maxlen = String::endpos);
		
		/* IObject */

		/* IString */
		virtual String *dup(void) const;
		virtual const char *c_str(void) const;
		virtual const unsigned char *bytes(void) const;
		virtual size_t length(void) const;
		virtual void assign(const String *str, size_t maxlen = String::endpos);
		virtual void append(const String *str, size_t maxlen = String::endpos);
		virtual void remove(size_t start = 0, size_t end = String::endpos);
		virtual void insert(const String *str, size_t pos = 0, size_t maxlen = String::endpos);
	protected:
		size_t m_len;
		size_t m_size;
		unsigned char *m_buf;

		void resizeToHold(size_t newlen);
	};
};

#endif /*!TALISKER_STRING_HH_*/
