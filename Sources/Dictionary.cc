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

Dictionary::Dictionary():
	Object::Object(),
	m_dict(NULL)
{
}

Dictionary::~Dictionary()
{
	DictionaryPrivate *cur, *tmp;

	HASH_ITER(hh, m_dict, cur, tmp)
	{
		HASH_DEL(m_dict, cur);
		free(cur->key);
		cur->value->release();
	}
}

IObject *
Dictionary::valueForKey(const char *key)
{
	DictionaryPrivate *item;
	
	HASH_FIND_STR(m_dict, key, item);
	if(!item)
	{
		return NULL;
	}
	item->value->retain();
	return item->value;
}

IObject *
Dictionary::valueForKey(const String &str)
{
	return valueForKey(str.c_str());
}

void
Dictionary::setObject(const char *key, IObject *value)
{
	DictionaryPrivate *item;

	HASH_FIND_STR(m_dict, key, item);
	if(item)
	{
		if(item->value == value)
		{
			return;
		}
		item->value->release();
		item->value = value;
		value->retain();
		return;
	}
	item = new DictionaryPrivate;
	item->key = strdup(key);
	item->value = value;
	HASH_ADD_KEYPTR(hh, m_dict, item->key, strlen(item->key), item);
	value->retain();
}

void
Dictionary::setObject(const String &str, IObject *value)
{
	setObject(str.c_str(), value);
}

/* IDictionary */

size_t
Dictionary::count(void)
{
	return HASH_COUNT(m_dict);
}

/*
IObject *
Dictionary::valueForKey(IString *key)
{
	return valueForKey(key->c_str());
}
*/

/*
void
Dictionary::setObject(IString *key, IObject *value)
{
	setObject(str->c_str(), value);
}
*/
