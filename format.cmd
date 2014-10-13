cd /d "%~dp0"
clang-format -style=file -i src/libfunctionality/*.h src/libfunctionality/*.cpp tests/cplusplus/*.cpp tests/cplusplus/*.h