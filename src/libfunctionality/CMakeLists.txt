include_directories(${LIBFUNCTIONALITY_INCLUDE_DIRS})

set(API
    Common.h
    Exceptions.h
    LoadModule.h
	ModuleInterface.h)

set(SOURCE LoadModule.cpp)
add_library(functionality ${API} ${SOURCE})