//===-- MICmdArgValListBase.h -----------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//++
// File:		MICmdArgValListBase.h
//
// Overview:	CMICmdArgValListBase interface.
//
// Environment:	Compilers:	Visual C++ 12.
//							gcc (Ubuntu/Linaro 4.8.1-10ubuntu9) 4.8.1
//				Libraries:	See MIReadmetxt. 
//
// Copyright:	None.
//--

#pragma once

// Third party headers:
#include <vector>

// In-house headers:
#include "MICmdArgValBase.h"

// Declarations:
class CMICmdArgContext;

//++ ============================================================================
// Details:	MI common code class. Command argument with addition options class. 
//			For example --recurse 1 2 4 [group ...]. Arguments object that
//			require a list of options associated with them derive from the 
//			CMICmdArgValListBase class. Additional options are also extracted from
//			the command arguments text string. 
//			An argument knows what type of argument it is and how it is to 
//			interpret the options (context) string to find and validate a matching 
//			options and so extract a values from it .
//			The CMICmdArgValBase objects are added to the derived argument class's
//			container. The option arguments belong to that derived class and will 
//			be deleted that object goes out of scope.
//			Based on the Interpreter pattern.
// Gotchas:	None.
// Authors:	Illya Rudkin 16/04/2014.
// Changes:	None.
//--
class CMICmdArgValListBase : public CMICmdArgValBaseTemplate< std::vector< CMICmdArgValBase * > >
{
// Typedef:
public:
	typedef std::vector< CMICmdArgValBase * >	VecArgObjPtr_t;

// Enums:
public:
	//++ ---------------------------------------------------------------------------------
	// Details:	CMICmdArgValListBase needs to know what type of argument to look for in
	//			the command options text. It also needs to create argument objects of
	//			a specific type.
	//--
	enum ArgValType_e
	{
		eArgValType_File	= 0,
		eArgValType_Consume,
		eArgValType_Number,
		eArgValType_OptionLong,
		eArgValType_OptionShort,
		eArgValType_String,
		eArgValType_StringQuoted,
		eArgValType_StringQuotedNumber,
		eArgValType_StringQuotedNumberPath,
		eArgValType_ThreadGrp,
		eArgValType_count,		// Always the last one
		eArgValType_invalid
	};

// Methods:
public:
	/* ctor */	CMICmdArgValListBase( void );
	/* ctor */	CMICmdArgValListBase( const CMIUtilString & vrArgName, const bool vbMandatory, const bool vbHandleByCmd );
	/* ctor */	CMICmdArgValListBase( const CMIUtilString & vrArgName, const bool vbMandatory, const bool vbHandleByCmd, const ArgValType_e veType );

// Overridden:
public:
	// From CMICmdArgValBase
	/* dtor */ virtual ~CMICmdArgValListBase( void );

// Methods:
protected:
	bool				IsExpectedCorrectType( const CMIUtilString & vrTxt, const ArgValType_e veType ) const;
	CMICmdArgValBase *	CreationObj( const CMIUtilString & vrTxt, const ArgValType_e veType ) const;
	
// Attributes:
protected:
	ArgValType_e	m_eArgType;

// Methods:
private:
	void	Destroy( void );
};
