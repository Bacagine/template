/**
 * template.c
 *
 * Written by DEV_NAME <email@example.com>
 *  
 * Description: My template file
 *
 * Date: dd/mm/aaaa
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "log/log.h"
#include "cutils/cutils.h"
#include "cutils/str.h"
#include "cutils/color.h"
#include "template.h"
#include "cmdline.h"

char gszConfFile[_MAX_PATH];
char gszTraceFile[_MAX_PATH];
DebugLevel giDebugLevel = 0;
bool gbColoredLogLevel = false;

const char *gkpszProgramName;
STRUCT_COMMAND_LINE gstCmdLine;

void vPrintErrorMessage(const char *kpszFmt, ...)
{
  va_list args;
  char szMsg[256];
  
  memset(szMsg, 0, sizeof(szMsg));
   
  va_start(args, kpszFmt);
  
  /**
   * Check if the terminal suport colors
   */
  if(bTerminalSupportColors() == false)
  {
    sprintf(szMsg, _("E: %s\n"), kpszFmt);

    vfprintf(stderr, szMsg, args);
    return;
  }
  
  sprintf(szMsg, _("\033[1;31mE:\033[m %s\n"), kpszFmt);
  
  vfprintf(stderr, szMsg, args);

  va_end(args);
}

/******************************************************************************
 *                                                                            *
 *                                   main                                     *
 *                                                                            *
 ******************************************************************************/
#ifdef __linux__
int main(int argc, char **argv, char **envp)
#else
int main(int argc, char **argv)
#endif /* __linux__ */
{
  int iRsl = 0;
  
  memset(&gstCmdLine, 0, sizeof(gstCmdLine));

  /* Setting the name of program */
  gkpszProgramName = szGetProgramName(argv[0]);
  
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevel);
  UNUSED(kszBoldColors);
  UNUSED(kszNormalColors);
  
  setlocale(LC_ALL, NULL);
  
  bindtextdomain(gkpszProgramName, LOCALE_DIR);
  textdomain(gkpszProgramName);
  
  /* Checking and validate the command line arguments */
  if(!bCommandLineIsOK(argc, argv))
  {
    vPrintUsage();
    exit(EXIT_FAILURE);
  }
  
  /* .conf file  */
  if(!bStrIsEmpty(gstCmdLine.szConfFile))
  {
    vSetConfFileName(gstCmdLine.szConfFile);
  }
  else
  {
    vSetConfFileName(CONF_FILE_NAME);
  }

  /* DebugLevel configurations */
  if(!bStrIsEmpty(gstCmdLine.szDebugLevel)) 
  {
    vSetLogLevel(atoi(gstCmdLine.szDebugLevel));
  }
  else 
  {
    vSetLogLevel(iGetLogLevel());
  }

  if(giDebugLevel < 0)
  {
    vPrintErrorMessage(_("Debug Level it's less than 0!"));

    exit(EXIT_FAILURE);
  }

  if(!bStrIsEmpty(gstCmdLine.szTraceFile))
  {
    vSetLogFileName(gstCmdLine.szTraceFile);
  }
  else
  {
    vSetLogFileName(LOG_FILE_NAME);
  }

  if(INFO_LOG_DETAILS)
  {
    vTraceBegin();
  }

  if(TRACE_LOG_DETAILS)
  {
    vTraceCommandLine(argc, argv);
    vTraceProgramInfo();
    vTraceSystemInfo();
    vTraceEnvp(envp);
  }
  
  /**
   * TODO: The rest of the code should go here.
   */

  if(INFO_LOG_DETAILS)
  {
    vTraceInfo(_("%s end iRsl == %d"), __func__, iRsl);
  }

  return iRsl;
}

