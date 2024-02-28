if [ "$#" -eq 0 ]; then
  echo "Usage: format.sh <file/dir>"
  exit 1
fi

if [ "$1" = "-a" ]; then
  astyle --project src/**/*.cpp 
  astyle --project src/**/*.hpp
  exit 0
fi

astyle --project "$@"
