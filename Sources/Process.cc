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

static int process_argc;
static char **process_argv;
static char **process_envp;
static Process *process;

extern "C" void talisker_init_(void) __attribute__((constructor(100)));
extern "C" void talisker_fini_(void) __attribute__((destructor(100)));

#if defined(HAVE_NXARGC) && defined(HAVE_NXARGV)
extern "C" int NXArgc;
extern "C" char **NXArgv;
#endif
#if defined(HAVE__DL_ARGV)
extern "C" char **_dl_argv;
#endif
#if defined(HAVE_ENVIRON)
extern char **environ;
#endif

extern "C" void
talisker_init_(void)
{
	int argc = 1;
	static const char *def_argv[] = { "(null)", NULL };
	static const char *def_envp[] = { NULL, NULL };
	char **argv, **envp;
	
	argv = (char **) (const char **) def_argv;
	envp = (char **) (const char **) def_envp;
#if defined(HAVE_NXARGC) && defined(HAVE_NXARGV)
	argc = NXArgc;
	argv = NXArgv;
#endif
#if defined(HAVE__DL_ARGV)
	argv = _dl_argv;
	for(argc = 0; argv && argv[argc]; argc++) { }
#endif
#if defined(HAVE_ENVIRON)
	envp = environ;
#endif
	talisker_init_process_(argc, argv, envp);
	talisker_init_thread_pre_();
	talisker_init_thread_();
}

extern "C" void
talisker_fini_(void)
{
	talisker_fini_thread_pre_();
}

extern "C" void
talisker_init_process_(int argc, char **argv, char **envp)
{
	process_argc = argc;
	process_argv = argv;
	process_envp = envp;
}

extern "C" void
talisker_fini_process_(void)
{
	if(process)
	{
		delete process;
	}
}

void
Talisker::debug(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::currentProcess()->vdebug(format, ap);
}

void
Talisker::log(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::currentProcess()->vlog(format, ap);
}

void
Talisker::notice(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::currentProcess()->vnotice(format, ap);
}

void
Talisker::warn(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::currentProcess()->vwarn(format, ap);
}

void
Talisker::err(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	Process::currentProcess()->verr(format, ap);
}

Process *
Process::currentProcess(void)
{
	const char *t;
	int mask;

	if(!process)
	{
		process = new Process();
		process->m_refcount = (uint32_t) -1; /* This is a singleton */
		process->m_id = (long) getpid();
		t = strrchr(process_argv[0], '/');
		if(t)
		{
			t++;
		}
		else
		{
			t = process_argv[0];
		}
		openlog(t, LOG_NDELAY|LOG_NOWAIT|LOG_PERROR|LOG_PID, LOG_USER);
		t = getenv("TALISKER_LOGLEVEL");
		mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
			LOG_MASK(LOG_CRIT) | LOG_MASK(LOG_ERR) |
			LOG_MASK(LOG_WARNING);
		if(t)
		{
			if(!strcmp(t, "emerg"))
			{
				mask = LOG_MASK(LOG_EMERG);
			}
			else if(!strcmp(t, "alert"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT);
			}
			else if(!strcmp(t, "crit"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
					LOG_MASK(LOG_CRIT);
			}
			else if(!strcmp(t, "err") || !strcmp(t, "error"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
					LOG_MASK(LOG_CRIT) | LOG_MASK(LOG_ERR);
			}
			else if(!strcmp(t, "warn") || !strcmp(t, "warning"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
					LOG_MASK(LOG_CRIT) | LOG_MASK(LOG_ERR) |
					LOG_MASK(LOG_WARNING);
			}
			else if(!strcmp(t, "notice"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
					LOG_MASK(LOG_CRIT) | LOG_MASK(LOG_ERR) |
					LOG_MASK(LOG_WARNING) | LOG_MASK(LOG_NOTICE);
			}
			else if(!strcmp(t, "info"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
					LOG_MASK(LOG_CRIT) | LOG_MASK(LOG_ERR) |
					LOG_MASK(LOG_WARNING) | LOG_MASK(LOG_NOTICE) |
					LOG_MASK(LOG_INFO);
			}
			else if(!strcmp(t, "debug"))
			{
				mask = LOG_MASK(LOG_EMERG) | LOG_MASK(LOG_ALERT) |
					LOG_MASK(LOG_CRIT) | LOG_MASK(LOG_ERR) |
					LOG_MASK(LOG_WARNING) | LOG_MASK(LOG_NOTICE) |
					LOG_MASK(LOG_INFO) | LOG_MASK(LOG_DEBUG);
			}
			else
			{
				Talisker::notice("unknown TALIKSER_LOGLEVEL value '%s'\n", t);
			}
		}
		setlogmask(mask);
		process->m_argc = process_argc;
		process->m_argv = process_argv;
		process->m_envp = process_envp;
	}
	return process;
}

Process::Process():
	Object::Object(),
	m_id(0),
	m_argc(0),
	m_argv(NULL),
	m_envp(NULL)
{
}

Process::~Process()
{
	if(process == this)
	{
		process = NULL;
	}
}

void
Process::debug(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_DEBUG, format, ap);
}

void
Process::vdebug(const char *format, va_list ap)
{
	vsyslog(LOG_DEBUG, format, ap);
}

void
Process::log(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_INFO, format, ap);
}

void
Process::vlog(const char *format, va_list ap)
{
	vsyslog(LOG_INFO, format, ap);
}

void
Process::notice(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_NOTICE, format, ap);
}

void
Process::vnotice(const char *format, va_list ap)
{
	vsyslog(LOG_NOTICE, format, ap);
}

void
Process::warn(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_WARNING, format, ap);
}

void
Process::vwarn(const char *format, va_list ap)
{
	vsyslog(LOG_WARNING, format, ap);
}

void
Process::err(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vsyslog(LOG_ERR, format, ap);
}

void
Process::verr(const char *format, va_list ap)
{
	vsyslog(LOG_ERR, format, ap);
}

