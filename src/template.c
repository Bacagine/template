/**
 * template.c
 * 
 * Written by Gustavo Bacagine <gustavo.bacagine@protonmail.com> in February 2025
 * 
 * Description: template project
 * 
 * Date: 20/02/2025
 */

#include "template.h"

int opterr = 0;
static const char *kszOptStr = "hvtg:";

struct option astCmdOpt[] = {
  { "help"         , no_argument      ,    0, 'h' },
  { "version"      , no_argument      ,    0, 'v' },
  { NULL           , 0                , NULL,  0  }
};

const char *kpszCmdArguments[] = {
  NULL,
  NULL,
  NULL
};

const char *kpszCmdMessages[] = {
  "Show this help and exit",
  "Show the version information and exit",
  NULL
};

const char *gkpszProgramName;

char *szGetProgramName(const char *szPathName) {
  char *pszProgramName = 0;
  
  if ( (pszProgramName = strrchr(szPathName, '/')) != 0 ) {
    ++pszProgramName; /* Skip '/' */
  }
  else {
    pszProgramName = (char *) szPathName; /* Nenhum dir. component */
  }

  return pszProgramName;
}

void vPrintUsage(void) {
  int ii = 0;
    
  printf(
    _("Usage: %s [OPTION]...\n\n"
    "%s\n\n"
    "Options:\n"),
    gkpszProgramName,
    DESCRIPTION
  );
  
  while ( astCmdOpt[ii].val != 0 ) {
    if ( astCmdOpt[ii].has_arg == required_argument ) {
      printf(
        _("  -%c <%s>\n"
        "    %s\n\n"),
        astCmdOpt[ii].val,
        kpszCmdArguments[ii],
        kpszCmdMessages[ii]
      );
    }
    else {
      printf(
        _("  -%c, --%s\n"
        "    %s\n\n"),
        astCmdOpt[ii].val,
        astCmdOpt[ii].name,
        kpszCmdMessages[ii]
      );
    }

    ii++;
  }
}

void vPrintVersion(void) {
  printf(
    _("%s %s\n"
    "Build in %s %s\n"
    "%s %s\n"
    "For reporting bugs, send a e-mail to <%s>\n"
    "Github: %s\n"),
    gkpszProgramName, 
    VERSION,
    __DATE__,
    __TIME__,
    COPYRIGHT,
    DEV_NAME,
    DEV_MAIL,
    GITHUB_URL
  );
}

bool bCommandLineIsOK(int argc, char **argv) {
  int iCmdLineOpt = 0;
  
  while ( (iCmdLineOpt = getopt_long(argc, argv, kszOptStr, astCmdOpt, NULL )) != -1 ) {
    switch ( iCmdLineOpt ) {
      case 'h': {
        printf("%s %s\n", gkpszProgramName, VERSION);
        vPrintUsage();
        exit(EXIT_SUCCESS);
      }
      case 'v': {
        vPrintVersion();
        exit(EXIT_SUCCESS);
      }
      case '?':
      default:
       return false; 
    }
  }

  return true;
}

int main(int argc, char **argv, char **envp) {
  int iRsl = 0;
  
  /* Setting the name of program */
  gkpszProgramName = szGetProgramName(argv[0]);
  
  setlocale(LC_ALL, "");
  
  bindtextdomain(gkpszProgramName, LOCALEDIR);
  textdomain(gkpszProgramName);

  /* Checking and validate the command line arguments */
  if ( !bCommandLineIsOK(argc, argv) ) {
    fprintf(stderr, _("Invalid use!\nPlease use %s -h to see help\n"), gkpszProgramName);
    exit(EXIT_FAILURE);
  }
  
  
  
  return iRsl;
}

