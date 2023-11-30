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
#include "trace/trace.h"

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
 *                     Global variables and constants                         *
 *                                                                            *
 ******************************************************************************/

/* Receive the name of program */
extern const char *gkpszProgramName;

/******************************************************************************
 *                                                                            *
 *                            Prototype functions                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Print a formatted error message
 */
void vPrintErrorMessage(const char *kpszFmt, ...);

#endif /* _TEMPLATE_H_ */

