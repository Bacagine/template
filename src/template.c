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

char gszConfFileName[LOG_FILE_NAME_LENGTH];
char gszLogFileName[LOG_FILE_NAME_LENGTH];
DebugLevel giDebugLevel = 0;
bool gbColoredLogLevel = false;

const char *kpszProgramName;
STRUCT_COMMAND_LINE stCmdLine;

static const char *kszOptStr = "hvt:d:cC:";

void vPrintUsage(void)
{
  int ii = 0;
  
  printf(_("Usage %s [options] <arguments>\n\n"
         "%s\n\n"
         "Options:\n"), kpszProgramName, DESCRIPTION);
  while(astCmdOpt[ii].name)
  {
    if(astCmdOpt[ii].has_arg == required_argument)
    {
      printf(_("  --%s=<%s>, -%c <%s>\n"
             "    %s\n\n"), astCmdOpt[ii].name, pszCmdArguments[ii],
                            astCmdOpt[ii].val, pszCmdArguments[ii],
                            pszCmdMessages[ii]);
    }
    else
    {
      printf(_("  --%s, -%c\n"
             "    %s\n\n"), astCmdOpt[ii].name, astCmdOpt[ii].val,
                            pszCmdMessages[ii]);
    }

    ii++;
  }
}

void vPrintVersion(void)
{
  printf(_("%s %s\n"
         "Build in %s %s\n"
         "%s %s\n"
         "For reporting bugs, send a email to <%s>\n"), kpszProgramName, 
                                                        VERSION,
                                                        __DATE__,
                                                        __TIME__,
                                                        COPYRIGHT,
                                                        DEVELOPER,
                                                        DEV_MAIL
  );
}

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

bool bCommandLineIsOK(int argc, char **argv)
{
  int iCmdLineOpt = 0;
  
  /**
   * Used to get the final of
   * conversion of strtol
   */
  char *pchEndPtr; 

  while((iCmdLineOpt = getopt_long(argc, argv, kszOptStr, astCmdOpt, NULL )) != -1)
  {
    switch(iCmdLineOpt)
    {
      case 'h':
        vPrintUsage();
        exit(EXIT_SUCCESS);
      case 'v':
        vPrintVersion();
        exit(EXIT_SUCCESS);
      case 't':
        sprintf(stCmdLine.szLogFileName, "%s", optarg);
        break;
      case 'd':
        sprintf(stCmdLine.szDebugLevel, "%s", optarg);

        strtol(stCmdLine.szDebugLevel, &pchEndPtr, 10);

        if(*pchEndPtr != '\0')
        {
          return false;
        }

        break;
      case 'c':
        vSetColoredLogLevel(true);

        break;
      case 'C':
        sprintf(stCmdLine.szConfFileName, "%s", optarg);
        break;
      case '?':
      default:
        return false;
    }
  }

  return true;
}

void vTraceCommandLine(int argc, char **argv)
{
  int ii;

  vTraceBegin();

  vTraceAll("argc == %d", argc);

  for(ii = 0; ii < argc; ii++)
  {
    vTraceAll("0x%08lX argv[%d] == %s", (long) &argv[ii], ii, argv[ii]);
  }

  vTraceEnd();
}

void vTraceEnvp(char **envp)
{
  int ii;

  vTraceBegin();

  if(envp != NULL)
  {
    for(ii = 0; envp[ii] != 0; ii++)
    {
      vTraceAll("0x%08lX envp[%d] == %s", (long) &envp[ii], ii, envp[ii]);
    }
  }

  vTraceEnd();
}

char *szGetProgramName(const char *szPathName)
{
  char *pszProgramName = 0;
  
  if((pszProgramName = strrchr(szPathName, '/')) != 0)
  {
    ++pszProgramName; /* Skip '/' */
  }
  else
  {
    pszProgramName = (char *) szPathName; /* Nenhum dir. component */
  }

  return pszProgramName;
}

void vTraceSystemInfo(void)
{
  /**
   * Date and time information
   */
  time_t tCurrentDateTime;
  struct tm *pstDateTime;
  
  /**
   * Operating System information
   */
  struct utsname stSysInfo;
  
  /**
   * User system info
   */
  struct passwd *pstUserInfo = getpwuid(getuid());

  time(&tCurrentDateTime);
  pstDateTime = localtime(&tCurrentDateTime);

  vTraceBegin();
 
  if(uname(&stSysInfo) != 0)
  {
    vTraceWarning(_("E: uname(&stSysInfo) != 0"));
  }

  if(pstUserInfo == NULL)
  {
    vTraceWarning(_("pstUserInfo == NULL"));
  }
  
  vTraceAll(_(" GETTING SYSTEM INFORMATION"));
  vTraceAll(_("----------------------------"));
  
  vTraceAll("Current date and time:"
      " %02d/%02d/%04d %02d:%02d:%02d", pstDateTime->tm_mday,
                                        pstDateTime->tm_mon + 1,
                                        pstDateTime->tm_year + 1900,
                                        pstDateTime->tm_hour,
                                        pstDateTime->tm_min,
                                        pstDateTime->tm_sec
  );
  
  vTraceAll(_(" OPERATING SYSTEM INFORMATION"));
  vTraceAll(_("------------------------------"));
  vTraceAll(_("Operating Systen........: %s"), stSysInfo.sysname);
  vTraceAll(_("Host Name...............: %s"), stSysInfo.nodename);
  vTraceAll(_("Kernel Version..........: %s"), stSysInfo.release);
  vTraceAll(_("Operation System Version: %s"), stSysInfo.version);
  vTraceAll(_("Architecture............: %s"), stSysInfo.machine);
  vTraceAll(_("------------------------------"));

  vTraceAll(_(" USER SYSTEM INFORMATION"));
  vTraceAll(_("-------------------------"));
  vTraceAll(_("UID.....................: %u"), pstUserInfo->pw_uid);
  vTraceAll(_("GID.....................: %u"), pstUserInfo->pw_gid);
  vTraceAll(_("User Name...............: %s"), pstUserInfo->pw_name);
  vTraceAll(_("Full Name...............: %s"), pstUserInfo->pw_gecos);
  vTraceAll(_("Home Directory..........: %s"), pstUserInfo->pw_dir);
  vTraceAll(_("Default Shell...........: %s"), pstUserInfo->pw_shell);
  vTraceAll(_("-------------------------"));
  
  vTraceEnd();
}

void vTraceProgramInfo(void)
{
  vTraceAll(_("%s - begin"), __func__);
  
  vTraceAll(_(" PROGRAM INFORMATION"));
  vTraceAll(_("---------------------"));
  vTraceAll(_("Software..........: %s"),    kpszProgramName);
  vTraceAll(_("Version...........: %s"),    VERSION);
  vTraceAll(_("Copyright.........: %s"),    COPYRIGHT);
  vTraceAll(_("Configuration file: %s"),    CONF_FILE_NAME);
  vTraceAll(_("Log file..........: %s"),    LOG_FILE_NAME);
  vTraceAll(_("Build in..........: %s %s"), __DATE__, __TIME__);
  vTraceAll(_("Report bugs to....: <%s>"),  DEV_MAIL);
  vTraceAll(_("Github............: %s"),    GITHUB_URL);
  vTraceAll(_("---------------------"));

  vTraceAll(_("%s - end"), __func__);
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
  
  memset(&stCmdLine, 0, sizeof(stCmdLine));

  /* Setting the name of program */
  kpszProgramName = szGetProgramName(argv[0]);
  
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevel);
  UNUSED(kszBoldColors);
  UNUSED(kszNormalColors);
  
  setlocale(LC_ALL, NULL);
  
  bindtextdomain(kpszProgramName, LOCALE_DIR);
  textdomain(kpszProgramName);
  
  /* Checking and validate the command line arguments */
  if(!bCommandLineIsOK(argc, argv))
  {
    vPrintUsage();
    exit(EXIT_FAILURE);
  }
  
  /* .conf file  */
  if(!bStrIsEmpty(stCmdLine.szConfFileName))
  {
    vSetConfFileName(stCmdLine.szConfFileName);
  }
  else
  {
    vSetConfFileName(CONF_FILE_NAME);
  }

  /* DebugLevel configurations */
  if(!bStrIsEmpty(stCmdLine.szDebugLevel)) 
  {
    vSetLogLevel(atoi(stCmdLine.szDebugLevel));
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

  if(!bStrIsEmpty(stCmdLine.szLogFileName))
  {
    vSetLogFileName(stCmdLine.szLogFileName);
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

