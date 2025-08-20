VELT_PATH="/c/Users/olekb/projects/VELT/bin"
PROFILE="$HOME/.bashrc"

if ! grep -q "$VELT_PATH" "$PROFILE"; then
  echo "export PATH=\"\$PATH:$VELT_PATH\"" >> "$PROFILE"
  echo "VELT path added to \$PROFILE"
else
  echo "VELT path already exists in \$PROFILE"
fi

source "$PROFILE"