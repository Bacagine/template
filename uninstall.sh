#!/bin/bash
# 
# uninstall.sh: Script to uninstall template
# 
# Written by DEV_NAME <email@example.com>
# 
# Date: dd/mm/aaaa

# Checking if user is root
if [[ $EUID -ne 0 ]]; then
  # Checking if the terminal suport colored text
  if test -n $(tput colors) && test $(tput colors) -ge 8; then
    printf "\033[1;31mE:\033[m This script must be run as root\n"
  fi
  
  print "E: This script must be run as root\n"

  exit 1
fi

if test -f /usr/bin/template; then
  printf "#########################\n"
  printf "# Uninstalling template #\n"
  printf "#########################\n"

  # Creating the documentation directory
  rm -rv /usr/share/doc/template

  # Install the binary of software and yout autocomplete script
  rm -rvf /usr/bin/template
  rm -rvf /usr/share/bash-completion/completions/_template_complete.sh 

  # Installing the configuration file of the software
  rm -rvf /etc/template.conf

  # Installing the documentation
  cp -rvf /usr/share/man/man1/template.1.gz
  cp -rvf /usr/share/doc/template

  printf "\ntemplate was uninstalled successfuly!\n"
else
  # Checking if the terminal suport colored text
  if test -n $(tput colors) && test $(tput colors) -ge 8; then
    printf "\033[1;31mE:\033[m template is not installed!\n"
  else
    printf "E: template is not installed!\n"
  fi

  printf "Nothing to do\n"

  exit 1
fi

