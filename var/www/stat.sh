#! /bin/bash
set -e

cd `pwd`

file_pattern=$1

function main {
  for rev in `revisions`; do
    echo "`commit_description` `diff_to_pre`"
    pre_rev=$rev
  done
}

function revisions {
  git rev-list HEAD --reverse
}

function commit_description {
  echo
  git log --oneline -1 $rev
}

function diff_to_pre {
  echo
  test "$pre_rev" == '' && (git ls-tree $rev -r)
  test "$pre_rev" != '' && (git diff-tree $pre_rev $rev -r | awk '{print $4" "$5" "$6}')
  #test "$pre_rev" != '' && (git diff $pre_rev $rev --name-status)
  #test "$pre_rev" != '' && (git diff $pre_rev $rev --full-index)
  #echo $pre_rev $rev
}

function number_of_lines {
  git ls-tree -r $rev |
  grep "$file_pattern" |
  awk '{print $3}' |
  xargs git show |
  wc -l;
}

main
