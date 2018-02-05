/* Talisker
 * Foundation Toolkit
 */

/* Copyright 2017 Mo McRoberts.
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

class DebugObject : public Object
{
public:
	
	DebugObject():
		Object::Object()
	{
		Talisker::debug("[DebugObject::DebugObject] creating a new debugging Object 0x%08x\n", (unsigned long)  static_cast<void *>(this));
	}

	virtual ~DebugObject()
	{
		Talisker::debug("[DebugObject::~DebugObject] Object 0x%08x has reached end-of-life\n", (unsigned long)  static_cast<void *>(this));
	}
};

IObject *
Object::createObject()
{
	return new DebugObject();
}

Object::Object():
	m_refcount(1)
{
}

Object::~Object()
{
	if(m_refcount > 1 && m_refcount != (uint32_t) -1)
	{
		Talisker::notice("[Object::~Object]: destroying object 0x%08x while dangling or corrupted references exist\n", (unsigned long)  static_cast<void *>(this));
	}
}

int __stdcall
Object::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IObject))
	{
		IObject *obj = static_cast<IObject *>(this);

		obj->retain();
		*object = obj;
		return 0;
	}
	return -1;
}

/* XXX These methods are lacking barriers at present */

uint32_t __stdcall
Object::retain(void)
{
	if(m_refcount == (uint32_t) -1)
	{
		/* This is a singleton; pretend that we just increased from 1 to 2 */
		return 2;
	}
	m_refcount++;
	return m_refcount;
}

uint32_t __stdcall
Object::release(void)
{
	if(m_refcount == (uint32_t) -1)
	{
		/* This is a singleton; pretend that we just decreased from 2 to 1 */
		return 1;
	}
	if(m_refcount == 1)
	{
		delete this;
		return 0;
	}
	m_refcount--;
	return m_refcount;
}
