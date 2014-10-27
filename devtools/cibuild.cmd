cd /d "%~dp0"
cd ..
rmdir /s /q install
rmdir /s /q build
mkdir build
cd build
cmake .. -G "Visual Studio 12" "-DCMAKE_INSTALL_PREFIX=%WORKSPACE%\install"
cmake --build . --config Debug
cmake --build . --config RelWithDebInfo
cmake --build . --config RelWithDebInfo --target INSTALL

bin\Debug\LoadTest.exe --gtest_output=xml:test_details.Debug.xml
bin\RelWithDebInfo\LoadTest.exe --gtest_output=xml:test_details.RelWithDebInfo.xml

pause