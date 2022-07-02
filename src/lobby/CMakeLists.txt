add_executable(lobby lobby.cpp game_handler.cpp player_handler.cpp)
target_link_libraries(lobby Boost::program_options networking turn_based)
