PROJECT(turglem_russian)

SET(CMAKE_INSTALL_PREFIX /usr/local)

SET(CMAKE_C_FLAGS "-O3 -Wall -fomit-frame-pointer -funroll-loops -pedantic -Wno-long-long -fPIC")
SET(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

INCLUDE_DIRECTORIES(include)

FIND_PATH(MAFSA_INCLUDE MAFSA/automaton.h PATHS /opt/include /usr/include /usr/local/include)
INCLUDE_DIRECTORIES(${MAFSA_INCLUDE})

FIND_PATH(TURGLEM_INCLUDE turglem/lemmatizer.h PATHS /opt/include /usr/include /usr/local/include)
INCLUDE_DIRECTORIES(${TURGLEM_INCLUDE})

FIND_LIBRARY(MAFSA_LIBRARY NAMES MAFSA PATHS /opt/lib /usr/lib /usr/local/lib)
FIND_LIBRARY(TURGLEM_LIBRARY NAMES turglem PATHS /opt/lib /usr/lib /usr/local/lib)
FIND_LIBRARY(TXML_LIBRARY NAMES txml PATHS /opt/lib /usr/lib /usr/local/lib)

ADD_LIBRARY(turglem-russian STATIC charset_adapters.c)
SET_TARGET_PROPERTIES(turglem-russian PROPERTIES VERSION 0.1 SOVERSION 1)

ADD_EXECUTABLE(morph_compiler_russian morph_compiler_russian.cpp)
TARGET_LINK_LIBRARIES(morph_compiler_russian turglem-russian ${TXML_LIBRARY} expat)

ADD_CUSTOM_COMMAND(TARGET morph_compiler_russian POST_BUILD COMMAND echo "Please wait, compiling dictionaries!")
ADD_CUSTOM_COMMAND(TARGET morph_compiler_russian POST_BUILD COMMAND ./morph_compiler_russian ${turglem_russian_SOURCE_DIR}/paradigms.xml ${turglem_russian_SOURCE_DIR}/lemmas.xml dict_russian.auto paradigms_russian.bin prediction_russian.auto)

INSTALL(FILES include/turglem/russian/charset_adapters.h
	      include/turglem/russian/charset_adapters.hpp
	      include/turglem/russian/gram_const.h
	DESTINATION include/turglem/russian)

INSTALL(FILES paradigms.xml 
	      lemmas.xml 
	      ${turglem_russian_BINARY_DIR}/dict_russian.auto 
	      ${turglem_russian_BINARY_DIR}/paradigms_russian.bin 
	      ${turglem_russian_BINARY_DIR}/prediction_russian.auto 
	DESTINATION share/turglem/russian)

IF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
INSTALL(TARGETS turglem-russian DESTINATION lib64)
ELSE(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
INSTALL(TARGETS turglem-russian DESTINATION lib)
ENDIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")

INSTALL(TARGETS morph_compiler_russian DESTINATION bin)

