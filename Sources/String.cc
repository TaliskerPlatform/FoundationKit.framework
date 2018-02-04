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

#define SIZE(l)                         (((l/16) + 1) * 16)

/* TODO: use allocator */

String::String():
	Object::Object(),
	m_len(0)
{
	m_size = SIZE(m_len);
	m_buf = (unsigned char *) malloc(m_size);
	m_buf[m_len] = 0;
}

String::String(const char *cstr):
	Object::Object()
{
	if(!cstr)
	{
		cstr = "";
	}
	m_len = strlen(cstr);
	m_size = SIZE(m_len);
	m_buf = (unsigned char *) malloc(m_size);
	memcpy(m_buf, cstr, m_len);
	m_buf[m_len] = 0;
}

String::String(const String *str):
	Object::Object()
{
	m_len = str->m_len;
	m_size = SIZE(m_len);
	m_buf = (unsigned char *) malloc(m_size);
	memcpy(m_buf, str->m_buf, m_len);
	m_buf[m_len] = 0;
}

String::~String()
{
	free(m_buf);
}

String *
String::dup(void) const
{
	return new String(this);
}

const char *
String::c_str(void) const
{
	return (const char *) m_buf;
}

const unsigned char *
String::bytes(void) const
{
	return m_buf;
}

size_t
String::length(void) const
{
	return m_len;
}

String &
String::operator=(const char *str)
{
	assign((const unsigned char *) str, strlen(str));
	return *this;
}

String &
String::operator=(const String *str)
{
	assign(str->m_buf, str->m_len);
	return *this;
}

String &
String::operator=(const String &str)
{
	assign(str.m_buf, str.m_len);
	return *this;
}

void
String::assign(const unsigned char *bytes, size_t nbytes)
{
	resizeToHold(nbytes);
	memcpy(m_buf, bytes, nbytes);
	m_len = nbytes;
	m_buf[m_len] = 0;
}

void
String::assign(const char *str, size_t maxlen)
{
	size_t l;

	l = strlen(str);
	assign((const unsigned char *) str, (l < maxlen ? l : maxlen));
}

void
String::assign(const String &str, size_t maxlen)
{
	assign(str.m_buf, (str.m_len < maxlen ? str.m_len : maxlen));
}

void
String::assign(const String *str, size_t maxlen)
{
	assign(str->m_buf, (str->m_len < maxlen ? str->m_len : maxlen));
}

void
String::append(const unsigned char *bytes, size_t nbytes)
{
	if(!nbytes)
	{
		return;
	}
	resizeToHold(nbytes + m_len);
	memcpy(&m_buf[m_len], bytes, nbytes);
	m_len += nbytes;
	m_buf[m_len] = 0;
}

void
String::append(const char *str, size_t maxlen)
{
	size_t l;

	l = strlen(str);
	append((const unsigned char *) str, (l < maxlen ? l : maxlen));
}

void
String::append(const String *str, size_t maxlen)
{
	append(str->m_buf, (str->m_len < maxlen ? str->m_len : maxlen));
}


void
String::append(const String &str, size_t maxlen)
{
	append(str.m_buf, (str.m_len < maxlen ? str.m_len : maxlen));
}

void
String::remove(unsigned long start, unsigned long len)
{
	size_t l;

	if(start > m_len)
	{
		return;
	}
	l = m_len - start;
	if(len < l)
	{
		l -= len;
		memmove(&m_buf[start], &m_buf[start + len], l);
		m_len -= len;
	}
	else
	{
		m_len -= l;
	}
	m_buf[m_len] = 0;
}

void
String::insert(const unsigned char *bytes, size_t pos, size_t nbytes)
{
	if(pos >= m_len)
	{
		append(bytes, nbytes);
		return;
	}
	resizeToHold(m_len + nbytes);
	memmove(&(m_buf[pos + nbytes]), &(m_buf[pos]), m_len - pos);
	memcpy(&(m_buf[pos]), bytes, nbytes);
	m_len += nbytes;
	m_buf[m_len] = 0;
}

void
String::insert(const char *str, size_t pos, size_t maxlen)
{
	size_t l;
	
	l = strlen(str);
	insert((const unsigned char *) str, pos, (l < maxlen ? l : maxlen));
}

void
String::insert(const String &str, size_t pos, size_t maxlen)
{
	insert(str.m_buf, pos, (str.m_len < maxlen ? str.m_len : maxlen));
}

void
String::insert(const String *str, size_t pos, size_t maxlen)
{
	insert(str->m_buf, pos, (str->m_len < maxlen ? str->m_len : maxlen));
}


void
String::resizeToHold(size_t newlen)
{
	size_t s;
	unsigned char *p;

	s = SIZE(newlen);
	if(s > m_size)
	{
		p = (unsigned char *) realloc(m_buf, s);
		m_buf = p;
		m_size = s;
	}	
}
