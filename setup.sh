#!/usr/bin/env bash
pushd "$(dirname "$0")"

# Parse Arguments
while [[ $# -gt 0 ]]
do
key="$1"

case $key in
    --with-tests)
    WITH_TESTS="--with-tests"
    shift # past argument
    ;;
    --force)
    CLEAN="true"
    shift # past argument
    ;;
    *)
          # unknown option
    ;;
esac
shift # past argument or value
done

# Install dependencies
if ! [ -z "$WITH_TESTS" ]; then
  echo "Update test dependencies..."
  git submodule update --init -- vendor/googletest
fi

# Create preamke working directory
[[ -d .premake ]] || mkdir .premake
pushd "./.premake"

# Remove existing premake archive
if [ -e premake.tar.gz ] && ! [ -z "$CLEAN"]; then
  rm premake.tar.gz
fi

# Install premake
if ! [ -e premake.tar.gz ]; then
  echo "Downloading premake binaries..."
  if [ "$(uname)" == "Darwin" ]; then
    curl -L -o premake.tar.gz https://github.com/premake/premake-core/releases/download/v5.0.0-alpha9/premake-5.0.0-alpha9-macosx.tar.gz
  elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    curl -L -o premake.tar.gz https://github.com/premake/premake-core/releases/download/v5.0.0-alpha9/premake-5.0.0-alpha9-linux.tar.gz
  elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] || [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    curl -L -o premake.zip https://github.com/premake/premake-core/releases/download/v5.0.0-alpha9/premake-5.0.0-alpha9-windows.zip
  fi

  echo "Extracting premake binaries..."
  if [ -s premake.tar.gz ]; then
    tar -xvzf premake.tar.gz
  elif [ -s premake.zip ]; then
    unzip premake.zip
  else
    echo "ERROR: premake archive does not exist"
  fi
fi

# Run premake to generate our project
if [ "$(uname)" == "Darwin" ]; then
    ./premake5 --file=../premake.lua xcode4 $WITH_TESTS
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    ./premake5 --file=../premake.lua gmake $WITH_TESTS
elif [ "$(expr substr $(uname -s) 1 10)" == "MINGW32_NT" ] || [ "$(expr substr $(uname -s) 1 10)" == "MINGW64_NT" ]; then
    ./premake5.exe --file=../premake.lua gmake $WITH_TESTS
fi

popd

popd
