/**
 * cmdline.h
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *  
 * My cmdline file
 *
 * Date: 21/10/2023
 */

#ifndef _CMDLINE_H_
#define _CMDLINE_H_

/******************************************************************************
 *                                                                            *
 *                                 Includes                                   *
 *                                                                            *
 ******************************************************************************/
#include <stdio.h>
#include <getopt.h>
#include "template.h"
#include "log.h"
#include "cutils/cutils.h"

/******************************************************************************
 *                                                                            *
 *                           Command Line Options                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Structure that represnts
 * command line arguments
 */
typedef struct STRUCT_COMMAND_LINE
{
  char szTraceFile [_MAX_PATH];
  char szDebugLevel[_MAX_PATH];
  char szConfFile  [_MAX_PATH];
} STRUCT_COMMAND_LINE;

/**
 * Command line structure and strings
 */
extern struct option astCmdOpt[];

/**
 * Arguments of command line options useds 
 * in usage message of program
 */
extern const char *pszCmdArguments[];

/**
 * Help messages that showed in usage message
 * of program
 */
extern const char *pszCmdMessages[];

/******************************************************************************
 *                                                                            *
 *                     Global variables and constants                         *
 *                                                                            *
 ******************************************************************************/

/**
 * Command line arguments
 */
extern STRUCT_COMMAND_LINE gstCmdLine;

/******************************************************************************
 *                                                                            *
 *                            Prototype functions                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Print the help message for the user
 */
void vPrintUsage(void);

/**
 * Print the version of the software
 */
void vPrintVersion(void);

/**
 * Check if what wass passed on the command line is valid
 */
bool bCommandLineIsOK(int argc, char **argv);

/**
 * A detailed and excessive sample of what was passed on the command line
 */
void vTraceCommandLine(int argc, char **argv);

/**
 * \brief A detailed and excessive sampling of the system's environment variables
 */
void vTraceEnvp(char **envp);

/**
 * Save in the .log a information about the OS.
 */
void vTraceSystemInfo(void);

/**
 * Save in the .log the information about the software.
 */
void vTraceProgramInfo(void);

/**
 * This function is based in the examples of the book 
 * "Aprenda em 24 horas Programacao para Linux"
 *
 * This function return the name of argv[0] withouth the path,
 * for example, if argv[0] == "/usr/bin/program", the function returns
 * only the string "program".
 */
char *szGetProgramName(const char *szPathName);

#endif /* _CMDLINE_H_ */

