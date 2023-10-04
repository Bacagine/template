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

  vLogInfo(_("%s - begin"), __func__);

  vLogTrace("argc == %d", argc);

  for(ii = 0; ii < argc; ii++)
  {
    vLogTrace("0x%08lX argv[%d] == %s", (long) &argv[ii], ii, argv[ii]);
  }

  vLogInfo(_("%s - end"), __func__);
}

void vTraceEnvp(char **envp)
{
  int ii;

  vLogInfo(_("%s - begin"), __func__);

  if(envp != NULL)
  {
    for(ii = 0; envp[ii] != 0; ii++)
    {
      vLogTrace("0x%08lX envp[%d] == %s", (long) &envp[ii], ii, envp[ii]);
    }
  }

  vLogInfo(_("%s - end"), __func__);
}

/**
 * This function is based in the examples of the book 
 * "Aprenda em 24 horas Programacao para Linux"
 */
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

  vLogInfo(_("%s - begin"), __func__);
 
  if(uname(&stSysInfo) != 0)
  {
    vLogWarning(_("E: uname(&stSysInfo) != 0"));
  }

  if(pstUserInfo == NULL)
  {
    vLogWarning(_("pstUserInfo == NULL"));
  }
  
  vLogTrace(_(" GETTING SYSTEM INFORMATION"));
  vLogTrace(_("----------------------------"));
  
  vLogTrace("Current date and time:"
      " %02d/%02d/%04d %02d:%02d:%02d", pstDateTime->tm_mday,
                                        pstDateTime->tm_mon + 1,
                                        pstDateTime->tm_year + 1900,
                                        pstDateTime->tm_hour,
                                        pstDateTime->tm_min,
                                        pstDateTime->tm_sec
  );
  
  vLogTrace(_(" OPERATING SYSTEM INFORMATION"));
  vLogTrace(_("------------------------------"));
  vLogTrace(_("Operating Systen........: %s"), stSysInfo.sysname);
  vLogTrace(_("Host Name...............: %s"), stSysInfo.nodename);
  vLogTrace(_("Kernel Version..........: %s"), stSysInfo.release);
  vLogTrace(_("Operation System Version: %s"), stSysInfo.version);
  vLogTrace(_("Architecture............: %s"), stSysInfo.machine);
  vLogTrace(_("------------------------------"));

  vLogTrace(_(" USER SYSTEM INFORMATION"));
  vLogTrace(_("-------------------------"));
  vLogTrace(_("UID.....................: %u"), pstUserInfo->pw_uid);
  vLogTrace(_("GID.....................: %u"), pstUserInfo->pw_gid);
  vLogTrace(_("User Name...............: %s"), pstUserInfo->pw_name);
  vLogTrace(_("Full Name...............: %s"), pstUserInfo->pw_gecos);
  vLogTrace(_("Home Directory..........: %s"), pstUserInfo->pw_dir);
  vLogTrace(_("Default Shell...........: %s"), pstUserInfo->pw_shell);
  vLogTrace(_("-------------------------"));
  
  vLogInfo(_("%s - end"), __func__);
}

void vTraceProgramInfo(void)
{
  vLogTrace(_("%s - begin"), __func__);
  
  vLogTrace(_(" PROGRAM INFORMATION"));
  vLogTrace(_("---------------------"));
  vLogTrace(_("Software..........: %s"),    kpszProgramName);
  vLogTrace(_("Version...........: %s"),    VERSION);
  vLogTrace(_("Copyright.........: %s"),    COPYRIGHT);
  vLogTrace(_("Configuration file: %s"),    CONF_FILE_NAME);
  vLogTrace(_("Log file..........: %s"),    LOG_FILE_NAME);
  vLogTrace(_("Build in..........: %s %s"), __DATE__, __TIME__);
  vLogTrace(_("Report bugs to....: <%s>"),  DEV_MAIL);
  vLogTrace(_("Github............: %s"),    GITHUB_URL);
  vLogTrace(_("---------------------"));

  vLogTrace(_("%s - end"), __func__);
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

  if(INFO_LEVEL)
  {
    vLogInfo(_("%s - begin"), __func__);
  }

  if(TRACE_LEVEL)
  {
    vTraceCommandLine(argc, argv);
    vTraceProgramInfo();
    vTraceSystemInfo();
    vTraceEnvp(envp);
  }
  
  /**
   * TODO: The rest of the code should go here.
   */

  if(INFO_LEVEL)
  {
    vLogInfo(_("%s end iRsl == %d"), __func__, iRsl);
  }

  return iRsl;
}

