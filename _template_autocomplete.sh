#!/bin/bash

_template_autocomplete() {
  local cur prev opts

  cur="${COMP_WORDS[COMP_CWORD]}"
  
  prev="${COMP_WORDS[COMP_CWORD-1]}"

  opts="--help -h --version -v --trace= --debug-level="

  if [[ ${cur} == -* ]]; then
    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
    return 0
  fi

  case "${prev}" in
    --trace=)
      COMPREPLY=( $(compgen -f -- "${cur}") )
      return 0
      ;;
    --debug-level=)
      COMPREPLY=( $(compgen -W "0 1 2 3 4 5 6 7 8 9" -- "${cur}") )
      return 0
      ;;
  esac
}

complete -F _template_autocomplete template
