/* Talisker
 * Foundation Toolkit
 */

/* Copyright 2015-2017 Mo McRoberts.
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

#ifndef P_FOUNDATION_HH_
# define P_FOUNDATION_HH_              1

# define TALISKER_INTERNAL_            1
# define TALISKER_INTERNAL_FOUNDATION_ 1
# define _BSD_SOURCE

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <syslog.h>
# if defined(__linux__)
#  include <sys/syscall.h>
# endif
# include <dlfcn.h>
# include <uuid/uuid.h>

namespace Talisker {

# define UT_array ArrayPrivate
# include <utarray.h>

# define UriUriStructA URIPrivate
# include <Uri.h>

struct DictionaryPrivate;

};

# include <uthash.h>

# include <FoundationKit/FoundationKit.h>

# define BLOCK_SIGNATURE                0xFEEF11F0UL

struct Talisker::FactoryEntry
{
	uuid_t clsid;
	int type;
	union
	{
		IObject *object;
		IFactory *factory;
		IRegistryConstructor constructor;
	};
};

struct block_head_struct
{
	uint32_t signature;
	size_t size;
};

struct Talisker::DictionaryPrivate
{
	char *key;
	IObject *value;
	UT_hash_handle hh;
};


#endif /*!P_FOUNDATION_HH_*/
