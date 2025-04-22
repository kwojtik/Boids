add_library(predator predator.cpp)

target_include_directories(predator PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(predator
    PUBLIC boid
    PUBLIC SFML::Graphics
)