cd /d "%~dp0"
cd ..
forfiles /s /m *.cpp /C "clang-format -style=file -i @relpath"
forfiles /s /m *.h /C "clang-format -style=file -i @relpath"
rem src\libfunctionality\*.h src\libfunctionality\*.cpp tests\cplusplus\*.cpp tests\cplusplus\*.h
pause
