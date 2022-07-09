add_executable(lobby lobby.cpp game_handler.cpp player_handler.cpp game_request_supervisor.cpp)
target_link_libraries(lobby PRIVATE Boost::program_options TBB::tbb networking turn_based)
