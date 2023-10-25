#!/bin/bash
# 
# install.sh: Script to install template
# 
# Written by DEV_NAME <email@example.com>
# 
# Date: dd/mm/aaaa

# Checking if user is root
if [[ $EUID -ne 0 ]]; then
  # Checking if the terminal suport colored text
  if test -n $(tput colors) && test $(tput colors) -ge 8; then
    printf "\033[1;31mE:\033[m This script must be run as root\n"
  else
    printf "E: This script must be run as root\n"
  fi

  exit 1
fi

printf "\n#######################\n"
printf "# Installing template #\n"
printf "#######################\n"

# Creating the documentation directory
mkdir -pv /usr/share/doc/template

# Install the binary of software and yout autocomplete script
cp -rvf ./bin/template /usr/bin
cp -rvf ./_template_complete.sh /usr/share/bash-completion/completions

# Installing the configuration file of the software
cp -rvf ./template.conf /etc

# Installing the documentation
cp -rvf ./man/template.1.gz /usr/share/man/man1
cp -rvf ./doc/* /usr/share/doc/template
cp -rvf ./LICENSE.gz /usr/share/doc/template
cp -rvf ./AUTHORS.gz /usr/share/doc/template
cp -rvf ./NEWS.gz /usr/share/doc/template
cp -rvf ./README.gz /usr/share/doc/template

printf "template was installed successfuly!\n"

