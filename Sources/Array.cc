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

static void talisker_array_copy_(void *dst, const void *src);
static void talisker_array_dtor_(void *el);

static UT_icd talisker_array_icd = {
	sizeof(IObject *),
	NULL,
	talisker_array_copy_,
	talisker_array_dtor_
};

Array::Array():
	Object::Object(),
	m_data(NULL)
{
	utarray_new(m_data, &talisker_array_icd);
}

Array::~Array()
{
	utarray_free(m_data);
}

bool
Array::containsObject(IObject *obj)
{
	ssize_t idx;

	idx = utarray_eltidx(m_data, &obj);
	if(idx == -1)
	{
		return -1;
	}
	return 0;
}

size_t
Array::count(void)
{
	return utarray_len(m_data);
}

IObject *
Array::firstObject(void)
{
	IObject *o;

	o = static_cast<IObject *>(*((void **) utarray_front(m_data)));
	if(o)
	{
		o->retain();
	}
	return o;
}

IObject *
Array::lastObject(void)
{
	IObject *o;

	o = static_cast<IObject *>(*((void **) utarray_back(m_data)));
	if(o)
	{
		o->retain();
	}
	return o;
}

IObject *
Array::objectAtIndex(size_t index)
{
	IObject *o;
	
	o = static_cast<IObject *>(*((void **) utarray_eltptr(m_data, index)));
	if(o)
	{
		o->retain();
	}
	return o;
}

ssize_t
Array::indexOfObject(IObject *obj)
{
	return utarray_eltidx(m_data, &obj);
}

void
Array::addObject(IObject *obj)
{
	utarray_push_back(m_data, (void **) &obj);
}

void
Array::insertObject(IObject *obj, size_t index)
{
	utarray_insert(m_data, (void **) &obj, index);
}

void
Array::removeObject(IObject *obj)
{
	ssize_t idx;

	idx = utarray_eltidx(m_data, &obj);
	if(idx == -1)
	{
		return;
	}
	utarray_erase(m_data, idx, 1);
}

void
Array::removeObjectAtIndex(size_t idx)
{
	utarray_erase(m_data, idx, 1);
}

void
Array::removeLastObject(void)
{
	utarray_pop_back(m_data);
}

void
Array::removeAllObjects(void)
{
	utarray_clear(m_data);
}

static void
talisker_array_copy_(void *dst, const void *src)
{
	IObject **dest = static_cast<IObject **>(dst);
	IObject *const *source = static_cast<IObject *const *>(src);

	*dest = *source;
	(*dest)->retain();
}

static void
talisker_array_dtor_(void *el)
{
	IObject **obj = static_cast<IObject **>(el);

	(*obj)->release();
}



