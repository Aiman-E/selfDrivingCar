add_executable(${PROJECT_NAME} main.c context.c world.c simulation.c)

target_link_libraries(${PROJECT_NAME}
  csfml-graphics
  csfml-window
  csfml-system
  csfml-network
  csfml-audio
)