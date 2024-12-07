for file in ./*; do
  if [ -f "$file" ] && [ -x "$file" ] && [ "$file" != "./run.sh" ]; then
    echo "\033[32m$file\033[0m"
    "$file"
    echo
  fi
done