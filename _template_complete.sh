##
# _template_complete.sh
#
# Written by DEV_NAME <email@example.com>
#  
# Description: My template file
# 
# Date: dd/mm/aaaa
# 

_template_complete()
{
  local cur_word
  local prev_word
  local long_type_list
  local short_type_list

  cur_word="${COMP_WORDS[COMP_CWORD]}"
  prev_word="${COMP_WORDS[COMP_CWORD-1]}"

  long_type_list=`template --help --version --trace \
    --debug-level --colored-log --conf-filename`
  short_type_list=`template -h -v -t -l -c -C`
  
  case "$cur_word" in
    --*) COMPREPLY=( $(compgen -W "${long_type_list}" -- ${cur_word}) );;
    -*) COMPREPLY=( $(compgen -W "${short_type_list}" -- ${cur_word}) );;
  esac

  return 0
}

complete -F _template_complete -o default template

