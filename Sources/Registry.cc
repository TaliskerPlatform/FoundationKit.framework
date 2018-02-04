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

#define FT_NONE                         0
#define FT_OBJECT                       1
#define FT_FACTORY                      2
#define FT_CONSTRUCTOR                  3

using namespace Talisker;

static Registry *registry;

/* TODO: thread safety; allocator */

extern "C" void
talisker_fini_registry_(void)
{
	delete registry;
}

IObject *
Registry::constructor(void)
{
	Registry *inst;
   
	inst = Registry::sharedRegistry();
	return static_cast<IObject *>(inst);
}

Registry *
Registry::sharedRegistry(void)
{
	if(!registry)
	{
		registry = new Registry();
	}
	return registry;
}

Registry::Registry():
	Object::Object(),
	m_factories(NULL),
	m_fcount(0),
	m_fsize(0)
{
	m_refcount = -1;
}

Registry::~Registry()
{
	size_t c;

	if(this == registry)
	{
		registry = NULL;
	}
	for(c = 0; c < m_fcount; c++)
	{
		if(m_factories[c].type == FT_OBJECT)
		{
			m_factories[c].object->release();
		}
		else if(m_factories[c].type == FT_FACTORY)
		{
			m_factories[c].factory->release();
		}
	}
	free(m_factories);
}

int __stdcall
Registry::queryInterface(const uuid_t riid, void **object)
{
	if(!uuid_compare(riid, IID_IRegistry))
	{
		IRegistry *obj = static_cast<IRegistry *>(this);
		
		obj->retain();
		*object = obj;
		return 0;
	}
	return Object::queryInterface(riid, object);
}

int __stdcall
Registry::registerFactory(const uuid_t clsid, IObject *object)
{
	UUID uu(clsid);
	String *s;
	FactoryEntry *p;
	IFactory *factory;

	if(!(p = addCreateEntry(clsid)))
	{
		return -1;
	}
	if(p->type != FT_NONE)
	{
		s = uu.string();
		Talisker::notice("Registry: ignored attempt to register a factory for {%s} more than once\n", s->c_str());
		s->release();
		return -1;
	}
	if(object->queryInterface(IID_IFactory, (void **) &factory))
	{
		Talisker::debug("Registry: new factory doesn't support IFactory\n");
		/* The factory doesn't support IFactory */
		p->type = FT_OBJECT;
		p->object = object;
		object->retain();
		return 0;
	}
	Talisker::debug("Registry: registered an IFactory factory\n");
	p->type = FT_FACTORY;
	p->factory = factory;
	/* No need to explicitly retain, as queryInterface does it for us */
	return 0;
}

int __stdcall
Registry::unregisterFactory(const uuid_t clsid, IObject *object)
{
	FactoryEntry *p;

	p = locateEntry(clsid);
	if(!p)
	{
		Talisker::notice("Registry: ignored attempt to unregister a factory for a class which is not registered\n");
		return -1;
	}
	if(p->type != FT_OBJECT && p->type != FT_FACTORY)
	{
		Talisker::notice("Registry: ignored attempt to unregister a factory for a class with a different kind of factory\n");
		return -1;
	}
	if(p->type == FT_FACTORY)
	{
		if(p->object != object)
		{
			IFactory *factory;

			if(object->queryInterface(IID_IFactory, (void **) &factory))
			{
				Talisker::notice("Registry: ignored attempt to unregister a factory for a class registered with a different factory\n");
				return -1;
			}
			if(factory != p->factory)
			{
				Talisker::notice("Registry: ignored attempt to unregister a factory for a class registered with a different factory\n");
				factory->release();
				return -1;
			}
			factory->release();
			p->factory->release();
		}
	}
	else
	{
		if(p->object != object)
		{
			Talisker::notice("Registry: ignored attempt to unregister a factory for a class registered with a different factory\n");
			return -1;
		}
		p->object->release();
	}
	return removeEntry(p);
}

IFactory *__stdcall
Registry::factory(const uuid_t clsid)
{
	size_t c;

	for(c = 0; c < m_fcount; c++)
	{
		if(!uuid_compare(m_factories[c].clsid, clsid))
		{
			if(m_factories[c].type != FT_FACTORY)
			{
				return NULL;
			}
			m_factories[c].factory->retain();
			return m_factories[c].factory;
		}
	}
	return NULL;
}

int __stdcall
Registry::classObject(const uuid_t clsid, const uuid_t iid, void **factory)
{
	FactoryEntry *p;

	p = locateEntry(clsid);
	if(!p)
	{
		return -1;
	}
	if(p->type == FT_NONE || p->type == FT_CONSTRUCTOR)
	{
		return -1;
	}
	if(!uuid_compare(iid, IID_IObject) ||
	   (p->type == FT_FACTORY && !uuid_compare(iid, IID_IFactory)))
	{
		p->object->retain();
		*factory = p->object;
		return 0;
	}
	return p->object->queryInterface(iid, factory);
}

int __stdcall
Registry::construct(const uuid_t clsid, const uuid_t iid, void **object)
{
	FactoryEntry *p;

	p = locateEntry(clsid);
	if(!p)
	{
		Talisker::debug("Registry: cannot construct an instance for a class with no registered factory or constructor\n");
		return -1;
	}
	if(p->type == FT_NONE)
	{
		Talisker::debug("Registry: ignoring attempt to construct an instance of a class with no factory type\n");
		return -1;
	}
	if(p->type == FT_OBJECT)
	{
		/* Can't construct using a factory which doesn't support IFactory */
		Talisker::debug("Registry: cannot construct an instance for a class whose factory doesn't support IFactory\n");
		return -1;
	}
	if(p->type == FT_FACTORY)
	{
		Talisker::debug("Registry: invoking IFactory::createInstance()\n");
		return p->factory->createInstance(NULL, iid, object);
	}
	if(p->type == FT_CONSTRUCTOR)
	{
		IObject *inst;
		int r;

		Talisker::debug("Registry: invoking constructor for class\n");
		inst = p->constructor();
		if(!inst)
		{
			return -1;
		}
		if(uuid_compare(iid, IID_IObject))
		{
			r = inst->queryInterface(iid, object);
			inst->release();
		}
		else
		{
			*object = inst;
			r = 0;
		}
		return r;
	}
	/* Unsupported construction method */
	return -1;
}

int __stdcall
Registry::registerConstructor(const uuid_t clsid, IRegistryConstructor constructor)
{
	UUID uu(clsid);
	String *s;
	FactoryEntry *p;

	if(!(p = addCreateEntry(clsid)))
	{
		return -1;
	}
	if(p->type != FT_NONE)
	{
		s = uu.string();
		Talisker::notice("Registry: ignored attempt to register a constructor for {%s} which already has a registration\n", s->c_str());
		s->release();
		return -1;
	}
	p->type = FT_CONSTRUCTOR;
	p->constructor = constructor;
	return 0;
}

int __stdcall
Registry::unregisterConstructor(const uuid_t clsid, IRegistryConstructor constructor)
{
	FactoryEntry *p;

	p = locateEntry(clsid);
	if(!p)
	{
		Talisker::notice("Registry: ignored attempt to unregister a constructor for a class which is not registered\n");
		return -1;
	}
	if(p->type != FT_CONSTRUCTOR)
	{
		Talisker::notice("Registry: ignored attempt to unregister a constructor for a class with a different kind of factory\n");
		return -1;
	}
	if(p->constructor != constructor)
	{
		Talisker::notice("Registry: ignored attempt to unregister a constructor for a class with a different registered constructor\n");
		return -1;
	}
	return removeEntry(p);
}

FactoryEntry *
Registry::addCreateEntry(const uuid_t clsid)
{
	size_t c;
	FactoryEntry *p;

	for(c = 0; c < m_fcount; c++)
	{
		if(!uuid_compare(m_factories[c].clsid, clsid))
		{
			return &(m_factories[c]);
		}
	}
	if(m_fcount + 1 > m_fsize)
	{
		p = (FactoryEntry *) realloc(m_factories, sizeof(FactoryEntry) * (m_fsize + 8));
		if(!p)
		{
			return NULL;
		}
		m_factories = p;
		m_fsize += 8;
	}
	p = &(m_factories[m_fcount]);
	m_fcount++;
	memset(p, 0, sizeof(FactoryEntry));
	memcpy(p->clsid, clsid, sizeof(uuid_t));
	return p;
}

FactoryEntry *
Registry::locateEntry(const uuid_t clsid)
{
	size_t c;

	for(c = 0; c < m_fcount; c++)
	{
		if(!uuid_compare(m_factories[c].clsid, clsid))
		{
			return &(m_factories[c]);
		}
	}
	return NULL;
}

int
Registry::removeEntry(FactoryEntry *p)
{
	size_t c;
	
	for(c = 0; c < m_fcount; c++)
	{
		if(p == &(m_factories[c]))
		{
			if(c + 1 < m_fcount)
			{
				memmove(&(m_factories[c]), &(m_factories[c + 1]), sizeof(FactoryEntry) * (m_fcount - c - 1));
			}			
			m_fcount--;
			return 0;
		}
	}
	Talisker::err("Registry: Internal: failed to remove registry entry because the pointer was out of range\n");
	return -1;
}
