add_library(boid boid.cpp)

target_include_directories(boid PUBLIC "${PROJECT_SOURCE_DIR}/src/includes")

target_link_libraries(boid
    PUBLIC predator
    PUBLIC SFML::Graphics
)