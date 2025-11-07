MAKE_DIR = $(PWD)

run_tests:
	cmake --build build/ && cd build/ && ./card_test
	cd $(MAKE_DIR)

.PHONY: run_tests
