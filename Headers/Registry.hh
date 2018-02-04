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

#ifndef TALISKER_REGISTRY_HH_
# define TALISKER_REGISTRY_HH_          1

# include "IRegistry.h"

# include "Object.hh"

namespace Talisker
{
	struct FactoryEntry;

	class TALISKER_EXPORT_ Registry: virtual public IRegistry, public Object
	{
	public:
		static IObject *constructor(void);
		static Registry *sharedRegistry(void);
	protected:
		static Registry *m_sharedRegistry;
	public:
		virtual ~Registry();   

		/* IObject */
		virtual int __stdcall queryInterface(const uuid_t riid, void **object);
		
		/* IRegistry */
		virtual int __stdcall registerFactory(const uuid_t clsid, IObject *factory);
		virtual int __stdcall unregisterFactory(const uuid_t clsid, IObject *factory);
		virtual int __stdcall classObject(const uuid_t clsid, const uuid_t iid, void **factory);
		virtual int __stdcall construct(const uuid_t clsid, const uuid_t iid, void **object);
		virtual IFactory *__stdcall factory(const uuid_t clsid);
		virtual int __stdcall registerConstructor(const uuid_t clsid, IRegistryConstructor constructor);
		virtual int __stdcall unregisterConstructor(const uuid_t clsid, IRegistryConstructor constructor);
	protected:
		FactoryEntry *m_factories;
		size_t m_fcount;
		size_t m_fsize;

		Registry();

		FactoryEntry *addCreateEntry(const uuid_t clsid);
		FactoryEntry *locateEntry(const uuid_t clsid);
		int removeEntry(FactoryEntry *p);
	};
};

#endif /*!TALISKER_REGISTRY_HH_*/
