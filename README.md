# Template

This repository contains my personal template project for my C/C++ projects

To better understand my codes, read the README.md at [this link](https://github.com/Bacagine/Bacagine)

# How to use?

## Dependecies

You ned two libraries to compile and use this template:

1) libtrace [https://github.com/Bacagine/trace/](https://github.com/Bacagine/trace/)
2) libcutils [https://github.com/Bacagine/cutils/](https://github.com/Bacagine/cutils/)

Compile the libraries above and follow the steps bellow:

1) Put the .so file in the lib file of this repository
2) Copy the include/trace directory to the include directory of this repository
3) Copy the include/cutils directory to the include directory of this repository

## Desciption of the files
```c
template
├── AUTHORS
├── ChangeLog
├── INSTALL
├── LICENSE
├── Makefile
├── NEWS
├── README
├── README.md
├── TODO
├── _template_complete.sh
├── doc
├── include
│   └── template.h
├── install.sh
├── lib
├── man
│   └── template.1
├── mk
├── mkall
├── mkclean
├── mkd
├── mkdall
├── mkdistclean
├── mkinstall
├── mkstrip
├── mkuninstall
├── src
│   └── template.c
├── template.conf
└── uninstall.sh

5 directories, 25 files

AUTHORS...........: The name and email of project author
ChangeLog.........: Changelog of project
INSTALL...........: Installation guide
LICENSE...........: License of software
Makefile..........: Makefile of the project
NEWS..............: File content the news about the project
README............: This file containing a explanation about the files of project
README.md.........: The README of github
TODO..............: File containing the TODO of the software
_template_complete: Autocomplete script of the software
doc...............: Documentation directory
template.h........: Header file of the library
install.sh........: Installation script
lib...............: Library directory (.so and .a files)
template.1........: A man page of the library and your functions
mk................: A make script
mkall.............: make all script
mkclean...........: make clean script
mkd...............: make debug script
mkdall............: make debug all script
mkdistclean.......: make distclean script
mkinstall.........: make install script
mktest............: make test script
mkuninstall.......: make uninstall script
template.c........: C source file of the library
template.conf.....: A .conf example file to use the log library in your C programs
uninstall.sh......: Uninstall script of the software
```

## Configuring the files for create a new C project

1) Replace all "template" and "TEMPLATE" strings for your software name
2) Replace all DEV_NAME to your name
3) Repalce all email@example.com to your e-mail
4) Change the license if you don't like of the default LICENSE (I use GPLv2)
5) Change the DESCRIPTION define in template.h
6) Change the GITHUB_URL define in template.h
7) Change COPYRIGHT define in template.h
8) Change the string "dd/mm/aaaa" to the creation date of your program
9) Change the string "My template file" in .h and .c files to your software description

