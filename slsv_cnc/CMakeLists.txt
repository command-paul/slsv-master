cmake_minimum_required(VERSION 2.6)

project(SLSV)
add_subdirectory(src/State)
add_subdirectory(src/Interface)
add_subdirectory(src/Interface/Telnet)
add_subdirectory(src/Coverage)
add_subdirectory(src)
add_subdirectory(tests-cpp)

SET(CMAKE_BINARY_DIR "./")
SET(CMAKE_BINARY_DIR "./")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/SLSV)
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

message(WARNING,"RUN THIS THROUGH THE INTEL PS FOR MEM LEAKS !!!")
message(WARNING,"Use the supp and Python3.6 malloc env variable when using valgrind !!!")
message(WARNING,"Please re work the paths for the include files -  a little messy right now !")
message(WARNING,"SWIG Template variable naming is poor please Rework !!!")

find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_BINARY_DIR}/../docs/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating documentation with Doxygen"
        VERBATIM )
else (DOXYGEN_FOUND)
  message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)

# Install Options
set(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/build)
add_custom_command(OUTPUT ${OUTPUT} COMMAND ${PYTHON} ARGS setup.py)
install(CODE "execute_process(COMMAND python3 setup.py install)")