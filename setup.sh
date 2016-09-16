#!/usr/bin/env bash
pushd "$(dirname "$0")"

# Install premake
[[ -d .premake ]] || mkdir .premake
pushd "./.premake"

# Remove existing premake archive
if [ -e premake.tar.gz ]; then
  rm premake.tar.gz
fi

# Download premake
if [ "$(uname)" == "Darwin" ]; then
  curl -L -o premake.tar.gz https://github.com/premake/premake-core/releases/download/v5.0.0-alpha9/premake-5.0.0-alpha9-macosx.tar.gz
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
  curl -L -o premake.tar.gz https://github.com/premake/premake-core/releases/download/v5.0.0-alpha9/premake-5.0.0-alpha9-linux.tar.gz
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ]; then
  echo ERROR
fi

# Extract premake
if [ -s premake.tar.gz ]; then
  tar -xvzf premake.tar.gz
  rm premake.tar.gz
else
  echo ERROR
fi

# Run premake to generate our project
if [ "$(uname)" == "Darwin" ]; then
    ./premake5 --file=../premake.lua xcode4
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    ./premake5 --file=../premake.lua gmake
fi

popd

popd
