cd /d "%~dp0"
cd ..
clang-format -style=file -i src/libfunctionality/*.h src/libfunctionality/*.cpp tests/cplusplus/*.cpp tests/cplusplus/*.h