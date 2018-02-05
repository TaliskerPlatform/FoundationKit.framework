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

#ifndef TALISKER_DECLARATIONS_H_
# define TALISKER_DECLARATIONS_H_      1

#ifndef __cplusplus
# include <stdbool.h>
#endif
#include <stdarg.h>
#include <stdint.h>
#include <sys/types.h>
#include <uuid/uuid.h>

# if !defined(_WIN32) && !defined(__CYGWIN__)
#  define __stdcall /* */
# endif

# if defined(__GNUC__)
#  define ALIAS(name__) \
	__asm__(#name__)
# else
#  define ALIAS(name__) /* */
# endif

# if defined(__cplusplus)

/* COM interface declarations for C++ */

#  define DECLARE_INTERFACE(name__) \
	struct name__
#  define DECLARE_INTERFACE_(name__, parent__) \
	struct name__: virtual public parent__
#  define BEGIN_INTERFACE /* */
#  define END_INTERFACE /* */
#  define THIS /* */
#  define THIS_ /* */
#  define PURE = 0
#  define STDMETHOD_(type__, name__) \
	virtual type__ __stdcall name__
#  define STDMETHOD(name__) \
	STDMETHOD(int, name__)

# else /*__cplusplus*/

/* COM interface declarations for C */
		
#  define DECLARE_INTERFACE(name__) \
	struct name__ { \
		struct name__##_vtable_ *lpVtbl; \
	}; \
	struct name__##_vtable_
#  define DECLARE_INTERFACE_(name__, parent__) \
	DECLARE_INTERFACE(name__)
#  define BEGIN_INTERFACE /* */
#  define END_INTERFACE /* */
#  define THIS \
	struct INTERFACE *self
#  define THIS_ \
	struct INTERFACE *self,
#  define PURE /* */
#  define STDMETHOD_(type__, name__) \
	type__ __stdcall (*name__)
#  define STDMETHOD(name__) \
	STDMETHOD_(int, name__)

# endif /*__cplusplus*/

# undef TALISKER_EXPORT_
# if defined(_WIN32) || defined(__CYGWIN__)

/* On Windows, use dllimport/dllexport */

#  ifdef TALISKER_INTERNAL_
#   define TALISKER_EXPORT_             __declspec(dllexport)
#  else
#   define TALISKER_EXPORT_             __declspec(dllimport)
#  endif

# else /*_WIN32 || __CYGWIN*/

/* On other platforms, use __attribute__((visibility...)) if available */

#  if defined(TALISKER_INTERNAL_) && __GNUC__ >= 4
#   define TALISKER_EXPORT_             __attribute__((visibility("default")))
#  else
#   define TALISKER_EXPORT_
#  endif

# endif

#endif /*!TALKISKER_DECLARATIONS_H_*/

#undef UUID_DEFINE
#ifdef INITGUID
# define UUID_DEFINE(name, a1, a2, a3, a4, b1, b2, c1, c2, d1, d2, e1, e2, e3, e4, e5, e6) \
  const uuid_t name TALISKER_EXPORT_ = { a1, a2, a3, a4, b1, b2, c1, c2, d1, d2, e1, e2, e3, e4, e5, e6}
#else
# define UUID_DEFINE(name, a1, a2, a3, a4, b1, b2, c1, c2, d1, d2, e1, e2, e3, e4, e5, e6) \
	extern const uuid_t name TALISKER_EXPORT_
# endif
