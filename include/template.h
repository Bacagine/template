/**
 * template.h
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com> in February 2025
 * 
 * Description: template project
 * 
 * Date: 20/02/2025
 */

#ifndef _TEMPLATE_H_
#define _TEMPLATE_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *                                                                            *
 *                                 Includes                                   *
 *                                                                            *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <libintl.h>
#include <stdbool.h>
#include <stdarg.h>
#include <getopt.h>
#include "build.h"

/******************************************************************************
 *                                                                            *
 *                             Defines and macros                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Program information defines
 */
#define VERSION        "1.0"
#define DESCRIPTION    "template is a template C source project"
#define COPYRIGHT      "Copyright (C) 2025"
#define DEV_NAME       "Gustavo Bacagine"
#define DEV_MAIL       "gustavo.bacagine@protonmail.com"
#define GITHUB_URL     "https://www.github.com/Bacagine/template"

/**
 * Program language defines
 */
#define _(STR) gettext(STR)
#define LOCALEDIR ""

/******************************************************************************
 *                                                                            *
 *                           Command Line Options                             *
 *                                                                            *
 ******************************************************************************/

/**
 * Command line structure and strings
 */
extern struct option astCmdOpt[];

/**
 * Arguments of command line options useds 
 * in usage message of program
 */
extern const char *kpszCmdArguments[];

/**
 * Help messages that showed in usage message
 * of program
 */
extern const char *kpszCmdMessages[];

/******************************************************************************
 *                                                                            *
 *                     Global variables and constants                         *
 *                                                                            *
 ******************************************************************************/

/**
 * Receive the name of program
 */
extern const char *gkpszProgramName;

/******************************************************************************
 *                                                                            *
 *                            Prototype functions                             *
 *                                                                            *
 ******************************************************************************/

/**
 * This function is based in the examples of the book 
 * "Aprenda em 24 horas Programacao para Linux"
 */
char *szGetProgramName(const char *szPathName);

/**
 * Show a help message in terminal
 */
void vPrintUsage(void);

/**
 * Show the version of program
 */
void vPrintVersion(void);

#ifdef __cplusplus
}
#endif

#endif
