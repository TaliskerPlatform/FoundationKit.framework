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

static struct block_head_struct *block_head(void *ptr);

static DefaultAllocator *def_allocator = NULL;

extern "C" void
talisker_init_allocator_(void)
{
	def_allocator = new DefaultAllocator();
}

extern "C" void
talisker_fini_allocator_(void)
{
	delete def_allocator;
	def_allocator = NULL;
}

/* Return the shared default allocator instance */
IAllocator *
DefaultAllocator::defaultAllocator(void)
{
	def_allocator->m_refcount = -1;
	return def_allocator;
}

DefaultAllocator::DefaultAllocator():
	Object::Object()
{
}

DefaultAllocator::~DefaultAllocator()
{
}

void *
DefaultAllocator::alloc(size_t nbytes)
{
	unsigned char *ptr;
	struct block_head_struct *head;

	ptr = (unsigned char *) ::malloc(sizeof(struct block_head_struct) + nbytes);
	if(!ptr)
	{
		return NULL;
	}
	head = (struct block_head_struct *) ((void *) ptr);
	head->signature = BLOCK_SIGNATURE;
	head->size = nbytes;
	ptr += sizeof(struct block_head_struct);
	return ptr;
}

void *
DefaultAllocator::realloc(void *ptr, size_t newsize)
{
	struct block_head_struct *head;
	unsigned char *nptr;

	if(!ptr)
	{
		return alloc(newsize);
	}
	head = block_head(ptr);
	if(!head || head->signature != BLOCK_SIGNATURE)
	{
		Talisker::notice("heap corruption: block 0x%08x (head 0x%08x) has an invalid signature (0x%08x)\n", (unsigned long) ptr, (unsigned long) (void *) head, head->signature);
		return NULL;
	}
	nptr = (unsigned char *) ::realloc(head, sizeof(struct block_head_struct) + newsize);
	if(!nptr)
	{
		return NULL;
	}
	head = (struct block_head_struct *) ((void *) nptr);
	head->size = newsize;
	return (void *) &(nptr[sizeof(struct block_head_struct)]);
}

void
DefaultAllocator::free(void *ptr)
{
	struct block_head_struct *head;

	if(!ptr)
	{
		return;
	}
	head = block_head(ptr);
	if(!head || head->signature != BLOCK_SIGNATURE)
	{
		Talisker::notice("heap corruption: block 0x%08x (head 0x%08x) has an invalid signature (0x%08x)\n", (unsigned long) ptr, (unsigned long) (void *) head, head->signature);
		return;
	}
	::free(head);
}

int
DefaultAllocator::didAlloc(void *ptr)
{
	struct block_head_struct *head;

	if(!ptr)
	{
		return 0;
	}
	head = block_head(ptr);
	if(!head || head->signature != BLOCK_SIGNATURE)
	{
		return 0;
	}
	return 1;
}

size_t
DefaultAllocator::size(void *ptr)
{
	struct block_head_struct *head;

	if(!ptr)
	{
		return 0;
	}
	head = block_head(ptr);
	if(!head || head->signature != BLOCK_SIGNATURE)
	{
		return (size_t) -1;
	}
	return head->size;
}

void
DefaultAllocator::compact(void)
{
	/* No-op */
}

static struct block_head_struct *
block_head(void *ptr)
{
	unsigned char *cptr;

	cptr = ((unsigned char *) ptr) - sizeof(struct block_head_struct);
	return (struct block_head_struct *) ((void *) cptr);
}
