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

#ifndef TALISKER_THREAD_HH_
# define TALISKER_THREAD_HH_            1

# include "IAllocator.h"

# include "Object.hh"
# include "String.hh"

namespace Talisker {

	class TALISKER_EXPORT_ Thread: public Object
	{
	public:
		static Thread *currentThread(void);
		static Thread *mainThread(void);
		static bool currentIsMainThread(void);
		static void exit(void);
		static IAllocator *allocator(void);
	public:
		Thread();
		Thread(IAllocator *threadAllocator);
		virtual ~Thread();

		virtual void start(void);
		virtual void main(void);
		virtual void cancel(void);
		virtual bool isMainThread(void);
		virtual bool isSelf(void);
		virtual bool executing(void);
		virtual bool finished(void);
		virtual bool cancelled(void);
		virtual String *name(void);
	protected:
		Thread(unsigned long tid);

		bool m_running;
		bool m_cancelled;
		bool m_finished;
		unsigned long m_id;
		bool m_isMainThread;
		IAllocator *m_allocator;
		String *m_name;
	};

};

#endif /*!TALISKER_THREAD_HH_*/
