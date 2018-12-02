file(GLOB SRC_FILES "./include/*/*.h" "./src/*.cpp")
# message("-- Modules files: " ${SRC_FILES})

add_library(${LIBRARY_NAME} SHARED
  ${SRC_FILES}
)

target_link_libraries(${LIBRARY_NAME}
  "-lX11"
)
