//===-- MICmnResources.h ----------------------------------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//++
// File:		MICmnResources.h
//
// Overview:	CMICmnResources interface.
//
// Environment:	Compilers:	Visual C++ 12.
//							gcc (Ubuntu/Linaro 4.8.1-10ubuntu9) 4.8.1
//				Libraries:	See MIReadmetxt. 
//
// Copyright:	None.
//--

#pragma once

// Third party headers
#include <map>

// In-house headers:
#include "MIUtilSingletonBase.h"
#include "MIUtilString.h"  
#include "MICmnBase.h"

//++ ============================================================================
// Details: MI string test data resource definitions. These IDs match up with
//			actual string data in a map internal to CMICmnResources.
//			*** Be sure to update ms_ppResourceId2TextData[] array ****
enum
{
    IDS_PROJNAME							= 1,
    IDS_MI_VERSION_DESCRIPTION_DEBUG		,
    IDS_MI_VERSION_DESCRIPTION				,
    IDS_MI_APPNAME_SHORT					,
    IDS_MI_APPNAME_LONG						,
    IDS_MI_APP_FILEPATHNAME					,
    IDS_MI_APP_ARGS							,
    IDE_MI_VERSION_GDB						,

    IDS_UTIL_FILE_ERR_INVALID_PATHNAME		= 10,
    IDS_UTIL_FILE_ERR_OPENING_FILE			,
    IDS_UTIL_FILE_ERR_OPENING_FILE_UNKNOWN	,
    IDE_UTIL_FILE_ERR_WRITING_FILE			,
    IDE_UTIL_FILE_ERR_WRITING_NOTOPEN		,
	
    IDS_RESOURCES_ERR_STRING_NOT_FOUND		= 20,
    IDS_RESOURCES_ERR_STRING_TABLE_INVALID	,

    IDS_MI_CLIENT_MSG						= 50,

    IDS_LOG_MSG_CREATION_DATE				= 60,
    IDS_LOG_MSG_FILE_LOGGER_PATH			,
    IDS_LOG_MSG_VERSION						,
    IDS_LOG_ERR_FILE_LOGGER_DISABLED		,
    IDS_LOG_MEDIUM_ERR_INIT					,
    IDS_LOG_MEDIUM_ERR_WRITE_ANY			,
    IDS_LOG_MEDIUM_ERR_WRITE_MEDIUMFAIL		,
	IDE_MEDIUMFILE_ERR_GET_FILE_PATHNAME_SYS,

    IDS_MEDIUMFILE_NAME						= 70,
    IDS_MEDIUMFILE_ERR_INVALID_PATH			,
    IDS_MEDIUMFILE_ERR_FILE_HEADER			,
    IDS_MEDIUMFILE_NAME_LOG					,

    IDE_OS_ERR_UNKNOWN						= 80,
    IDE_OS_ERR_RETRIEVING					,

    IDS_DRIVERMGR_DRIVER_ERR_INIT			= 90,

    IDE_MEDIUMSTDERR_NAME					= 110,
    IDE_MEDIUMSTDOUT_NAME					,

    IDE_MI_APP_EXIT_OK						= 120,
    IDE_MI_APP_EXIT_WITH_PROBLEM			,

    IDE_MI_APP_ARG_USAGE					= 130,
    IDE_MI_APP_ARG_HELP						,
    IDE_MI_APP_ARG_VERSION					,
    IDE_MI_APP_ARG_VERSION_LONG				,
    IDE_MI_APP_ARG_INTERPRETER				,

    IDS_STDIN_ERR_INVALID_PROMPT			= 140,
    IDS_STDIN_ERR_THREAD_CREATION_FAILED	,
    IDS_STDIN_ERR_THREAD_DELETE				,
    IDS_STDIN_ERR_CHKING_BYTE_AVAILABLE		,

    IDS_CMD_QUIT_HELP						= 150,

    IDS_THREADMGR_ERR_THREAD_ID_INVALID		= 160,
    IDS_THREADMGR_ERR_THREAD_FAIL_CREATE	,
    IDS_THREADMGR_ERR_THREAD_ID_NOT_FOUND	,
    IDS_THREADMGR_ERR_THREAD_STILL_ALIVE	,

    IDS_FALLTHRU_DRIVER_CMD_RECEIVED		= 170,

    IDS_CMDFACTORY_ERR_INVALID_CMD_NAME		= 180,
    IDS_CMDFACTORY_ERR_INVALID_CMD_CR8FN	,
    IDS_CMDFACTORY_ERR_CMD_NOT_REGISTERED	,
    IDS_CMDFACTORY_ERR_CMD_ALREADY_REGED	,

    IDS_CMDMGR_ERR_CMD_FAILED_CREATE		= 190,
    IDS_CMDMGR_ERR_CMD_INVOKER				,

    IDS_PROCESS_SIGNAL_RECEIVED				= 210,

	IDS_MI_INIT_ERR_LOG						= 230,
    IDS_MI_INIT_ERR_RESOURCES				,
    IDS_MI_INIT_ERR_INIT					,
    IDS_MI_INIT_ERR_STREAMSTDIN				,
    IDS_MI_INIT_ERR_STREAMSTDOUT			,
    IDS_MI_INIT_ERR_STREAMSTDERR			,
    IDS_MI_INIT_ERR_FALLTHRUDRIVER			,
    IDS_MI_INIT_ERR_THREADMGR				,
    IDS_MI_INIT_ERR_CMDINTERPRETER			,
    IDS_MI_INIT_ERR_CMDMGR					,
    IDS_MI_INIT_ERR_CMDFACTORY				,
    IDS_MI_INIT_ERR_CMDINVOKER				,
    IDS_MI_INIT_ERR_CMDMONITOR				,
    IDS_MI_INIT_ERR_LLDBDEBUGGER			,
    IDS_MI_INIT_ERR_DRIVERMGR				,
    IDS_MI_INIT_ERR_DRIVER					,
    IDS_MI_INIT_ERR_OUTOFBANDHANDLER		,
    IDS_MI_INIT_ERR_DEBUGSESSIONINFO		,
    IDS_MI_INIT_ERR_THREADMANAGER			,

    IDS_CODE_ERR_INVALID_PARAMETER_VALUE	= 250,
    IDS_CODE_ERR_INVALID_PARAM_NULL_POINTER	,

    IDS_LLDBDEBUGGER_ERR_INVALIDLISTENER	= 260,
    IDS_LLDBDEBUGGER_ERR_INVALIDDEBUGGER	,
    IDS_LLDBDEBUGGER_ERR_CLIENTDRIVER		,
    IDS_LLDBDEBUGGER_ERR_STARTLISTENER		,
    IDS_LLDBDEBUGGER_ERR_THREADCREATIONFAIL	,
    IDS_LLDBDEBUGGER_ERR_THREAD_DELETE		,
    IDS_LLDBDEBUGGER_ERR_INVALIDBROADCASTER	,
    IDS_LLDBDEBUGGER_ERR_INVALIDCLIENTNAME	,
    IDS_LLDBDEBUGGER_ERR_CLIENTNOTREGISTERD ,
    IDS_LLDBDEBUGGER_ERR_STOPLISTENER		,
    IDS_LLDBDEBUGGER_ERR_BROARDCASTER_NAME	,
    IDS_LLDBDEBUGGER_WRN_UNKNOWN_EVENT		,

    IDS_LLDBOUTOFBAND_ERR_UNKNOWN_EVENT		= 280,
	IDS_LLDBOUTOFBAND_ERR_PROCESS_INVALID	,

    IDS_DBGSESSION_ERR_SHARED_DATA_RELEASE	= 290,
	IDS_DBGSESSION_ERR_SHARED_DATA_ADD		,
    
    IDS_MI_SHTDWN_ERR_LOG					= 340,
    IDS_MI_SHUTDOWN_ERR						,
    IDE_MI_SHTDWN_ERR_RESOURCES				,
    IDE_MI_SHTDWN_ERR_STREAMSTDIN			,
    IDS_MI_SHTDWN_ERR_STREAMSTDOUT			,
    IDS_MI_SHTDWN_ERR_STREAMSTDERR			,
    IDS_MI_SHTDWN_ERR_THREADMGR				,
    IDS_MI_SHTDWN_ERR_CMDINTERPRETER		,
    IDS_MI_SHTDWN_ERR_CMDMGR				,
    IDS_MI_SHTDWN_ERR_CMDFACTORY			,
    IDS_MI_SHTDWN_ERR_CMDINVOKER			,
    IDS_MI_SHTDWN_ERR_CMDMONITOR			,
    IDS_MI_SHTDWN_ERR_LLDBDEBUGGER			,
    IDS_MI_SHTDWN_ERR_DRIVERMGR				,
    IDS_MI_SHTDWN_ERR_DRIVER				,
    IDS_MI_SHTDWN_ERR_OUTOFBANDHANDLER		,
    IDS_MI_SHTDWN_ERR_DEBUGSESSIONINFO		,
    IDE_MI_SHTDWN_ERR_THREADMANAGER			,

    IDS_DRIVER_ERR_PARSE_ARGS				= 400,
    IDS_DRIVER_ERR_PARSE_ARGS_UNKNOWN		,
    IDS_DRIVER_ERR_CURRENT_NOT_SET			,
    IDS_DRIVER_ERR_NON_REGISTERED			,
    IDS_DRIVER_SAY_DRIVER_USING				,
    IDS_DRIVER_ERR_ID_INVALID				,
    IDS_DRIVER_ERR_FALLTHRU_DRIVER_ERR		,
    IDS_DRIVER_CMD_RECEIVED					,
    IDS_DRIVER_CMD_NOT_IN_FACTORY			,

    IDS_DRIVER_WAITING_STDIN_DATA			= 410,

    IDS_STDOUT_ERR_NOT_ALL_DATA_WRITTEN		= 420,
	IDS_STDERR_ERR_NOT_ALL_DATA_WRITTEN		= 430,

	IDS_CMD_ARGS_ERR_N_OPTIONS_REQUIRED		= 440,
    IDS_CMD_ARGS_ERR_OPTION_NOT_FOUND		,			
    IDS_CMD_ARGS_ERR_VALIDATION_MANDATORY	,
	IDS_CMD_ARGS_ERR_VALIDATION_INVALID		,
	IDS_CMD_ARGS_ERR_VALIDATION_MAN_INVALID	,
	IDS_CMD_ARGS_ERR_VALIDATION_MISSING_INF	,
	IDS_CMD_ARGS_ERR_CONTEXT_NOT_ALL_EATTEN	,
	
    IDS_WORD_INVALIDBRKTS					= 1000,
    IDS_WORD_NONE							,
    IDS_WORD_NOT							,
    IDS_WORD_INVALIDEMPTY					,
    IDS_WORD_INVALIDNULLPTR					,
    IDS_WORD_UNKNOWNBRKTS					,
	IDS_WORD_NOT_IMPLEMENTED				,
	IDS_WORD_NOT_IMPLEMENTED_BRKTS			,
	IDS_WORD_UNKNOWNTYPE_BRKTS				,

    IDS_CMD_ERR_N_OPTIONS_REQUIRED			= 2000,
    IDS_CMD_ERR_OPTION_NOT_FOUND			,			
	IDS_CMD_ERR_ARGS						,	
	IDS_CMD_WRN_ARGS_NOT_HANDLED			,
	IDS_CMD_ERR_FNFAILED					,
    IDS_CMD_ERR_SHARED_DATA_NOT_FOUND		,
    IDS_CMD_ERR_LLDBPROCESS_DETACH			,
    IDS_CMD_ERR_SETWKDIR					,
    IDS_CMD_ERR_INVALID_TARGET				,
    IDS_CMD_ERR_INVALID_TARGET_CURRENT		,
    IDS_CMD_ERR_INVALID_TARGET_TYPE			,
    IDS_CMD_ERR_INVALID_TARGET_PLUGIN		,
    IDS_CMD_ERR_CONNECT_TO_TARGET			,
    IDS_CMD_ERR_INVALID_TARGETPLUGINCURRENT	,
    IDS_CMD_ERR_NOT_IMPLEMENTED				,
    IDS_CMD_ERR_CREATE_TARGET				,
    IDS_CMD_ERR_BRKPT_LOCATION_FORMAT		,
    IDS_CMD_ERR_BRKPT_INVALID				,
    IDS_CMD_ERR_BRKPT_CNT_EXCEEDED			,
    IDS_CMD_ERR_SOME_ERROR					,
	IDS_CMD_ERR_THREAD_INVALID				,
	IDS_CMD_ERR_THREAD_FRAME_RANGE_INVALID	,				
	IDS_CMD_ERR_FRAME_INVALID				,
	IDS_CMD_ERR_VARIABLE_DOESNOTEXIST		,
	IDS_CMD_ERR_VARIABLE_ENUM_INVALID		,
	IDS_CMD_ERR_VARIABLE_EXPRESSIONPATH		,
	IDS_CMD_ERR_VARIABLE_CREATION_FAILED	
};

//++ ============================================================================
// Details:	MI common code implementation class. Handle application resources
//			and locality. 
//			Singleton class.
// Gotchas:	None.
// Authors:	Illya Rudkin 29/01/2014.
// Changes:	None.
//--
class CMICmnResources
:	public CMICmnBase
,	public MI::ISingleton< CMICmnResources >
{
	friend class MI::ISingleton< CMICmnResources >;
	
// Methods:
public:
	bool	Initialize( void );
	bool	Shutdown( void );
	
	CMIUtilString	GetString( const MIuint vResourceId ) const;
	bool			HasString( const MIuint vResourceId ) const;
		
// Typedef:
private:
	typedef std::map< MIuint, const MIchar * >	MapRscrIdToTextData_t;
	typedef std::pair< MIuint, const MIchar * >	MapPairRscrIdToTextData_t;

// Enumerations:
private:
	enum Buffer_e
	{
		eBufferSize = 2048
	};

// Structs:
private:
	struct SRsrcTextData
	{
			  MIuint	id;
		const MIchar *	pTextData;		
	};

// Methods:
private:
	/* ctor */	CMICmnResources( void );
	/* ctor */	CMICmnResources( const CMICmnResources & );
	void		operator=( const CMICmnResources & );
	
	bool	GetStringFromResource( const MIuint vResourceId, CMIUtilString & vrwResourceString ) const;
	bool	ReadResourceStringData( void );

// Overridden:
private:
	// From CMICmnBase
	/* dtor */ virtual ~CMICmnResources( void );

// Attributes:
private:
	static const SRsrcTextData	ms_pResourceId2TextData[];
	//
	MIuint						m_nResourceId2TextDataSize;
	MapRscrIdToTextData_t		m_mapRscrIdToTextData;
};

//++ =========================================================================
// Details: Macro short cut for retrieving a text data resource
//--
#define MIRSRC( x ) CMICmnResources::Instance().GetString( x ).c_str()