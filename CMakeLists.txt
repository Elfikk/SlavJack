cmake_minimum_required(VERSION 3.14)
project(slavjack)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723 #v1.17.0
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	hello_test
	tests/hello_test.cpp
)

target_link_libraries(
	hello_test
	GTest::gtest_main
)

include_directories(
	src/
)

add_executable(
	card_test
	tests/card_test.cpp
)

target_link_libraries(
	card_test
	GTest::gtest_main
)

add_executable(
	card_deck_test
	src/card_deck.cpp
	tests/card_deck_test.cpp
)

target_link_libraries(
	card_deck_test
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(hello_test card_test card_deck)

