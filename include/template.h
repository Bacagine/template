/**
 * template.h
 *
 * Written by DEV_NAME <email@example.com>
 *  
 * My template file
 *
 * Date: dd/mm/aaaa
 */

#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

/******************************************************************************
 *                                                                            *
 *                                 Includes                                   *
 *                                                                            *
 ******************************************************************************/
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <getopt.h>
#include <locale.h>
#include <libintl.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <pwd.h>
#include "log/log.h"

/******************************************************************************
 *                                                                            *
 *                             Defines and macros                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Program information defines
 */
#define VERSION        "1.0"
#define DESCRIPTION    "This software is a template"
#define COPYRIGHT      "Copyright (C) 2023"
#define DEVELOPER      "DEV_NAME"
#define DEV_MAIL       "email@example.com"
#define CONF_FILE_NAME "./template.conf"
#define LOG_FILE_NAME  "./template.log"
#define GITHUB_URL     "https://www.github.com/DEV_NAME/template"

/**
 * Program language defines
 */
#define _(STR) gettext(STR)
#define LOCALE_DIR ""

/**
 * This macro is used to remove
 * unused warnings during the
 * compilation.
 */
#define UNUSED(X) (void) X

/******************************************************************************
 *                                                                            *
 *                  Typedefs, structures, unions and enums                    *
 *                                                                            *
 ******************************************************************************/


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
  char szLogFileName  [LOG_FILE_NAME_LENGTH];
  char szDebugLevel   [256];
  char szConfFileName [256];
} STRUCT_COMMAND_LINE;

/**
 * Command line structure and strings
 */
static struct option astCmdOpt[] = {
  { "help"         , no_argument      ,    0, 'h' },
  { "version"      , no_argument      ,    0, 'v' },
  { "trace"        , required_argument,    0, 't' },
  { "debug-level"  , required_argument,    0, 'd' },
  { "colored-log"  , no_argument      ,    0, 'c' },
  { "conf-filename", required_argument,    0, 'C' },
  { NULL           , 0                , NULL,  0  }
};

/**
 * Arguments of command line options useds 
 * in usage message of program
 */
static const char *pszCmdArguments[] = {
  NULL,
  NULL,
  "file",
  "number",
  NULL,
  "file",
  NULL
};

/**
 * Help messages that showed in usage message
 * of program
 */
static const char *pszCmdMessages[] = {
  "Show this message and exit",
  "Show the version and exit",
  "<file> is the path of the debug file",
  "<number> is the level of debug level",
  "Set a colored log",
  "<file> is the path of the .conf file of software",
  NULL
};


/******************************************************************************
 *                                                                            *
 *                     Global variables and constants                         *
 *                                                                            *
 ******************************************************************************/

/* Receive the name of program */
extern const char *kpszProgramName;

/**
 * Command line arguments
 */
extern STRUCT_COMMAND_LINE stCmdLine;

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
 * Print a formatted error message
 */
void vPrintErrorMessage(const char *kpszFmt, ...);

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
 * This function is based in the examples of the book 
 * "Aprenda em 24 horas Programacao para Linux"
 *
 * This function return the name of argv[0] withouth the path,
 * for example, if argv[0] == "/usr/bin/program", the function returns
 * only the string "program".
 */
char *szGetBaseName(const char *szPathName);

#endif /* _TEMPLATE_H_ */

