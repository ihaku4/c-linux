#! /bin/sh

echo "Is it morning? Please answer yes or no."
read YES_OR_NO
case "$YES_OR_NO" in
  yes|YES|Yes|y)
    echo "good morning!"
  ;;
  [Nn]*)
    echo "good afternoon!"
  ;;
  *)
    echo "Sorry, $YES_OR_NO not recognized. Enter yes or no."
    exit 1
  ;;
esac
exit 0
