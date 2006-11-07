FIND_PROGRAM(RASQALCONFIG_EXECUTABLE NAMES rasqal-config PATHS
   /usr/bin
   /usr/local/bin
)
#reset vars
set(RASQAL_LIBRARIES)
set(RASQAL_CFLAGS)

# if rasqual-config has been found
IF(RASQALCONFIG_EXECUTABLE)

  EXEC_PROGRAM(${RASQALCONFIG_EXECUTABLE} ARGS --libs RETURN_VALUE _return_VALUE OUTPUT_VARIABLE RASQAL_LIBRARIES)

  EXEC_PROGRAM(${RASQALCONFIG_EXECUTABLE} ARGS --cflags RETURN_VALUE _return_VALUE OUTPUT_VARIABLE RASQAL_CFLAGS)

  IF(RASQAL_LIBRARIES AND RASQAL_CFLAGS)
    SET(Rasqal_FOUND TRUE)
    message(STATUS "Found rasqal: ${RASQAL_LIBRARIES}")
  ENDIF(RASQAL_LIBRARIES AND RASQAL_CFLAGS)

  MARK_AS_ADVANCED(RASQAL_CFLAGS RASQAL_LIBRARIES)

ELSE(RASQALCONFIG_EXECUTABLE)
   SET(Rasqual_FOUND FALSE)
   message(FATAL_ERROR "rasqual library not found") 
ENDIF(RASQALCONFIG_EXECUTABLE)
