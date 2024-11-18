for file in ./*; do
  if [ -f "$file" ] && [ -x "$file" ] && [ "$file" != "./run.sh" ]; then
    echo "$file"
    "$file"
  fi
done