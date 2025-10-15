.PHONY: all clean run

GTESTSFLAGS = -lgtest -lgmock -pthread

all: build

run: all
	cd build && ./MazeCPP

style:
	clang-format -n -style=Google $(wildcard *.h) $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*.h)

style-format:
	clang-format -i -style=Google $(wildcard *.h) $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*.h)


build:
	mkdir -p ../build
	cmake -S ../src -B ../build
	cmake --build ../build/

gcov:
	g++ -std=c++20 --coverage model/Model.cpp model/Matrix.cpp model/WallMap.cpp model/file_worker/FileWorker.cpp model/path_finder/PathFinder.cpp model/generation_strategy/IGenerationStrategy.cpp model/generation_strategy/MazeGenerationStrategy.cpp model/generation_strategy/CaveGenerationStrategy.cpp unit_test/tests.cpp unit_test/cave_test.cpp unit_test/maze_test.cpp -Imodel/ -Imodel/path_finder/ -Imodel/generation_strategy/ -Imodel/generation_strategy/generation_config/ -Imodel/error_handler/ -Imodel/file_worker -Imodel/randomizer -Icommon $(GTESTSFLAGS) -o coverage_executable
	./coverage_executable
	lcov -t "gcov_report" -o coverage.info -c -d . --ignore-errors mismatch
	lcov --extract coverage.info "*/model/path_finder/*" "*/model/generation_strategy" -o coverage_filtered.info
	genhtml -o report coverage_filtered.info
	open report/index.html
SOURCES = $(shell find ./ -type f -name "*.cpp" -not \( -path './model/ModelAdapter.cpp' -o -path './controller/*.cpp' -o -path './view/*.cpp' -o -path './main.cpp' \) -print)

test: 
	g++ -std=c++17 $(SOURCES) -Icommon -Imodel/ -Imodel/generation_strategy -Imodel/generation_strategy/generation_config -Imatrix/ -Imodel/error_handler -Imodel/file_worker -Imodel/path_finder -Imodel/randomizer -o exec_unit_test $(GTESTSFLAGS)
	./exec_unit_test

clean:
	@rm -rf ../build
	@rm -rf report
	@rm -rf exec_unit_test
	@rm -rf unit_testt
	@rm -rf coverage_executable
	@rm -rf coverage.info
	@rm -rf coverage_filtered.info
	@rm -rf ../doxygen
	@find . -name '*.gcov' -delete
	@find . -name '*.gcda' -delete
	@find . -name '*.gcno' -delete


install: all
	cp ../build/MazeCPP $(PATH_TO_APP)

uninstall:
	rm -rf $(PATH_TO_APP)/MazeCPP


dvi: clean

ARCHIVE_NAME = MazeCPP.tar.gz

dist: clean
	tar -czf ${ARCHIVE_NAME} $$(ls -I "tests")

distclean:
	@rm -rf ${ARCHIVE_NAME}