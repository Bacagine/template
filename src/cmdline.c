/**
 * cmdline.h
 *
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com>
 *  
 * My cmdline file
 *
 * Date: 21/10/2023
 */

#include "cmdline.h"

static const char *kszOptStr = "hvt:d:cC";

/**
 * Command line structure and strings
 */
struct option astCmdOpt[] = {
  { "help"         , no_argument      ,    0, 'h' },
  { "version"      , no_argument      ,    0, 'v' },
  { "trace"        , required_argument,    0, 't' },
  { "debug-level"  , required_argument,    0, 'd' },
  { "colored-log"  , no_argument      ,    0, 'c' },
  { "conf-file"    , required_argument,    0, 'C' },
  { NULL           , 0                , NULL,  0  }
};

/**
 * Arguments of command line options useds 
 * in usage message of program
 */
const char *pszCmdArguments[] = {
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
const char *pszCmdMessages[] = {
  "Show this message and exit",
  "Show the version and exit",
  "<file> is the path of the debug file",
  "<number> is the level of debug level",
  "Set a colored log",
  "<file> is the path of the configuration file",
  NULL
};

void vPrintUsage(void)
{
  int ii = 0;
  
  printf("Usage %s [options] <arguments>\n\n"
         "%s\n\n"
         "Options:\n", gkpszProgramName, DESCRIPTION);
  while(astCmdOpt[ii].name)
  {
    if(astCmdOpt[ii].has_arg == required_argument)
    {
      printf("  --%s=<%s>, -%c <%s>\n"
             "    %s\n\n", astCmdOpt[ii].name, pszCmdArguments[ii],
                           astCmdOpt[ii].val, pszCmdArguments[ii],
                           pszCmdMessages[ii]);
    }
    else
    {
      printf("  --%s, -%c\n"
             "    %s\n\n", astCmdOpt[ii].name, astCmdOpt[ii].val,
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
         "For reporting bugs, send a email to <%s>\n"), gkpszProgramName, 
                                                        VERSION,
                                                        __DATE__,
                                                        __TIME__,
                                                        COPYRIGHT,
                                                        DEVELOPER,
                                                        DEV_MAIL
  );
}
bool bCommandLineIsOK(int argc, char **argv)
{
  int iCmdLineOpt = 0;
  
  /**
   * Used to get the final of
   * conversion of strtol
   */
  char *pchEndPtr; 
  
  UNUSED(kszLogLevelColorInit);
  UNUSED(kszLogLevelColorEnd);
  UNUSED(kszLogLevel);

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
        sprintf(gstCmdLine.szTraceFile, "%s", optarg);
        break;
      case 'd':
        sprintf(gstCmdLine.szDebugLevel, "%s", optarg);

        strtol(gstCmdLine.szDebugLevel, &pchEndPtr, 10);

        if(*pchEndPtr != '\0')
        {
          return false;
        }

        break;
      case 'c':
        vSetColoredLogLevel(true);

        break;
      case 'C':
        sprintf(gstCmdLine.szConfFile, "%s", optarg);
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
  vTraceAll(_("Software..........: %s"),    gkpszProgramName);
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

char *szGetProgramName(const char *szPathName)
{
  char *pszProgramName = 0;
#ifdef __linux__
  if((pszProgramName = strrchr(szPathName, '/')) != 0)
  {
    ++pszProgramName; /* Skip '/' */
  }
#else
  if((pszProgramName = strrchr(szPathName, '\\')) != 0)
  {
    ++pszProgramName; /* Skip '\' */
  }
#endif /* __linux__ */
  else
  {
    pszProgramName = (char *) szPathName; /* Nenhum dir. component */
  }

  return pszProgramName;
}

