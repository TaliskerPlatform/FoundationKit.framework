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

Factory::Factory():
	Object::Object()
{
}

Factory::~Factory()
{
}

int __stdcall
Factory::queryInterface(const uuid_t iid, void **object)
{
	if(!uuid_compare(iid, IID_IFactory))
	{
		IFactory *obj = static_cast<IFactory *>(this);

		obj->retain();
		*object = obj;
		return 0;
	}
	return Object::queryInterface(iid, object);
}

int __stdcall
Factory::createInstance(IObject *outer, const uuid_t iid, void **object)
{
	(void) outer;
	(void) iid;
	(void) object;

	return -1;
}

int __stdcall
Factory::lock(bool lock)
{
	if(lock)
	{
		this->retain();
	}
	else
	{
		this->release();
	}
	return 0;
}


