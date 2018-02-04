/*
 * Talisker
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

void *(*talisker_new_override_)(size_t nbytes) = NULL;
void (*talisker_delete_override_)(void *ptr) = NULL;

static pthread_key_t thread_key;
static pthread_key_t allocator_key;
static Thread *mainThread;

extern "C" void
talisker_init_thread_pre_(void)
{
	talisker_new_override_ = ::malloc;
	talisker_delete_override_ = ::free;
	pthread_key_create(&thread_key, NULL);
	pthread_key_create(&allocator_key, NULL);
}

extern "C" void
talisker_init_thread_(void)
{
	if(Thread::currentIsMainThread())
	{
		mainThread = Thread::currentThread();
	}
	talisker_new_override_ = NULL;
	talisker_delete_override_ = NULL;
}

extern "C" void
talisker_fini_thread_pre_(void)
{
	talisker_new_override_ = ::malloc;
	talisker_delete_override_ = ::free;
}

extern "C" void
talisker_fini_thread_(void)
{
	if(mainThread)
	{
		delete mainThread;
		mainThread = NULL;
	}
}

void *
operator new(size_t nbytes)
{
	IAllocator *allocator;

	if(talisker_new_override_)
	{
		return talisker_new_override_(nbytes);
	}
	allocator = Thread::allocator();
	return allocator->alloc(nbytes);
}

void
operator delete(void *ptr)
{
	IAllocator *allocator;

	if(talisker_delete_override_)
	{
		talisker_delete_override_(ptr);
		return;
	}
	allocator = Thread::allocator();
	allocator->free(ptr);
}

/* Obtain the Thread object for the current thread; the object must be
 * retained before it may be accessed by any other threads.
 */
Thread *
Thread::currentThread(void)
{
	pthread_t curthread;
	void *ptr;
	Thread *t;

	curthread = pthread_self();
	ptr = pthread_getspecific(thread_key);
	if(ptr)
	{
		return static_cast<Thread *>(ptr);
	}
	t = new Thread((unsigned long) curthread);
	pthread_setspecific(thread_key, (void *) t);
	return t;
}

/* Return a pointer to the main thread */
Thread *
Thread::mainThread(void)
{
	return ::mainThread;
}

/* Return true if the current thread is the main thread */
bool
Thread::currentIsMainThread(void)
{
#if defined(HAVE_PTHREAD_MAIN_NP)
	return pthread_main_np();
#elif defined(__linux__)
	if(syscall(SYS_gettid) == getpid())
	{
		return true;
	}
#else
# error Unable to determine API to use to detect main thread
#endif
	return false;
}

/* Terminate the current thread */
void
Thread::exit(void)
{
	pthread_exit(NULL);
}

/* Return the allocator for this thread */
IAllocator *
Thread::allocator(void)
{
	IAllocator *allocator;

	allocator = static_cast<IAllocator *>(pthread_getspecific(allocator_key));
	if(!allocator)
	{
		allocator = DefaultAllocator::defaultAllocator();
		pthread_setspecific(allocator_key, (void *) allocator);
	}
	return allocator;
}

/* Create a new, dormant, thread object */
Thread::Thread():
	Object::Object(),
	m_running(false),
	m_cancelled(false),
	m_finished(false),
	m_id(0),
	m_isMainThread(false),
	m_allocator(NULL),
	m_name(NULL)
{
}

/* Create a new dormant thread object with a different allocator */
Thread::Thread(IAllocator *threadAllocator):
	Object::Object(),
	m_running(false),
	m_cancelled(false),
	m_finished(false),
	m_id(0),
	m_isMainThread(false),
	m_allocator(threadAllocator),
	m_name(NULL)
{
	if(m_allocator)
	{
		m_allocator->retain();
	}
}

/* Internal: Create a new thread object for an existing thread */
Thread::Thread(unsigned long tid):
	Object::Object(),
	m_running(true),
	m_cancelled(false),
	m_finished(false),
	m_id(tid),
	m_allocator(NULL),
	m_name(NULL)
{
	m_isMainThread = currentIsMainThread();
}

/* Thread object destructor */
Thread::~Thread()
{
	if(m_allocator)
	{
		m_allocator->release();
	}
	delete m_name;
}

/* Start running a new thread */
void
Thread::start(void)
{
	if(m_running)
	{
		return;
	}
	/* TODO */
}

void
Thread::cancel(void)
{
	/* TODO: mutex */
	m_cancelled = true;
}

/* The implementation of a thread, invoked when the thread is started */
void
Thread::main(void)
{
	/* TODO */
}

/* Determine whether this is the main thread or not */
bool
Thread::isMainThread(void)
{
	return m_isMainThread;
}

/* Determine whether this is the same thread as the caller */
bool
Thread::isSelf(void)
{
	return ((pthread_t) m_id == pthread_self());
}

/* Determine whether this thread is running */
bool
Thread::executing(void)
{
	return m_running;
}

bool
Thread::finished(void)
{
	return m_finished;
}

bool
Thread::cancelled(void)
{
	return m_cancelled;
}

String *
Thread::name(void)
{
	if(!m_name)
	{		
		if(m_isMainThread)
		{
			m_name = new String("Main thread");
		}
		else if(m_id)
		{
			char buf[64];
			
			snprintf(buf, sizeof(buf) - 1, "%lu", m_id);
			m_name = new String(buf);
		}
		else
		{
			m_name = new String("(New thread)");
		}
	}
	return m_name;
}
