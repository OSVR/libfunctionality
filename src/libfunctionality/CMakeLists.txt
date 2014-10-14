include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})
add_library(functionality
	Common.h
    Exceptions.h
	LoadModule.cpp
	LoadModule.h
	ModuleInterface.h)