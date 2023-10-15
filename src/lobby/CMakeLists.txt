add_executable(lobby lobby_main.cpp game_handler.cpp player_handler.cpp game_request_supervisor.cpp)
target_link_libraries(lobby PRIVATE Boost::program_options TBB::tbb networking turn_based)

add_executable(lobby_tester lobby_tester.cpp)
target_link_libraries(lobby_tester PRIVATE networking)

add_executable(game_mock game_mock.cpp)
target_link_libraries(game_mock PRIVATE networking)
