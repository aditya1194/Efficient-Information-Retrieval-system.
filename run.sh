g++  -std=c++0x src/main.cpp 
touch parsedFile
path="$1"
python src/parser.py "$1"
./a.out
