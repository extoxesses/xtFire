file(GLOB SRC_FILES "./src/*.cpp")

add_executable(${SAMPLE_NAME}
  ${SRC_FILES}
)

target_link_libraries(${SAMPLE_NAME}
  ${LIBRARY_NAME}
)
