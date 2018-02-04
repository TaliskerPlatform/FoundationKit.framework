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

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include "p_foundation.hh"

using namespace Talisker;

UUID::UUID():
	Object::Object()
{
	uuid_generate(m_uuid);
}

UUID::UUID(const UUID &uuid):
	Object::Object()
{
	memcpy(m_uuid, uuid.m_uuid, sizeof(m_uuid));
}

UUID::UUID(const UUID *uuid):
	Object::Object()
{
	memcpy(m_uuid, uuid->m_uuid, sizeof(m_uuid));
}

UUID::UUID(const uuid_t uuid):
	Object::Object()
{
	memcpy(m_uuid, uuid, sizeof(m_uuid));
}

UUID::~UUID()
{
}

String *
UUID::string(int format)
{
	char buf[37], *s, *d;

	if(format & UUID::upper)
	{
		uuid_unparse_upper(m_uuid, buf);
	}
	else
	{
		uuid_unparse_lower(m_uuid, buf);
	}
	if(format & UUID::compact)
	{
		for(s = d = buf; *s; s++)
		{
			if(*s == '-')
			{
				continue;
			}
			*d = *s;
			d++;
		}
		*d = 0;
	}
	return new String(buf);
}
