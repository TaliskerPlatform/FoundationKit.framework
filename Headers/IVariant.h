/* DO NOT EDIT: Automatically generated from IVariant.idl by idl */

#ifndef IVariant_FWD_DEFINED
# define IVariant_FWD_DEFINED
typedef struct IVariant IVariant;
#endif

#ifndef IVARIANT_H_IDL_
# define IVARIANT_H_IDL_

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
# include <FoundationKit/IObject.h>

/* IVariant version 0.0 */

# ifndef __IVariant_INTERFACE_DEFINED__
#  define __IVariant_INTERFACE_DEFINED__
#  undef INTEFACE
#  define INTERFACE IVariant


DECLARE_INTERFACE_(IVariant, IObject)
{
	BEGIN_INTERFACE

#  ifdef (__cplusplus)
	static const int16_t T_UNDEFINED = 0;
	static const int16_t T_VOID = 1;
	static const int16_t T_STRING = 2;
	static const int16_t T_BOOLEAN = 3;
	static const int16_t T_INT = 4;
	static const int16_t T_DECIMAL = 5;
	static const int16_t T_ARRAY = 6;
	static const int16_t T_OBJECT = 7;
	static const int16_t T_UUID = 8;
	static const int16_t T_DATETIME = 9;

#  else /*__cplusplus*/

#  define T_UNDEFINED 0
#  define T_VOID 1
#  define T_STRING 2
#  define T_BOOLEAN 3
#  define T_INT 4
#  define T_DECIMAL 5
#  define T_ARRAY 6
#  define T_OBJECT 7
#  define T_UUID 8
#  define T_DATETIME 9
#  endif /*__cplusplus*/

# if !defined(__cplusplus)
	/* IObject */
	STDMETHOD_(int, queryInterface)(THIS_ const uuid_t riid, void **object) PURE;
	STDMETHOD_(int32_t, retain)(THIS) PURE;
	STDMETHOD_(int32_t, release)(THIS) PURE;
# endif /*!__cplusplus*/

	/* IVariant */
	STDMETHOD_(int, typeCode)(THIS) PURE;

	END_INTERFACE
};

#  if !defined(__cplusplus)
#   define IVariant_queryInterface(__this, riid, object) __this->lpVtbl->queryInterface(__this, riid, object)
#   define IVariant_retain(__this) __this->lpVtbl->retain(__this)
#   define IVariant_release(__this) __this->lpVtbl->release(__this)
#   define IVariant_typeCode(__this) __this->lpVtbl->typeCode(__this)
#  endif /*!__cplusplus*/
#  undef INTERFACE
# endif /*!__IVariant_INTERFACE_DEFINED__*/


/* IID_IVariant = {ca20ee39-4290-4c3e-a02f-c83ccccb57ff} */
UUID_DEFINE(IID_IVariant, 0xca, 0x20, 0xee, 0x39,  0x42, 0x90, 0x4c, 0x3e, 0xa0, 0x2f, 0xc8, 0x3c, 0xcc, 0xcb, 0x57, 0xff);

#endif /*!IVARIANT_H_IDL_*/
