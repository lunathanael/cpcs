CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
DEBUG_FLAGS = -DTESTING -Wconversion -Werror -pedantic -g -g3 -DDEBUG -D_GLIBCXX_DEBUG
RELEASE_FLAGS = -Ofast -DNDEBUG

SRC = $(filter-out %_submit.cpp,$(wildcard *.cpp))
NAME = $(basename $(SRC)).exe
DEBUG_NAME = $(basename $(SRC))_debug.exe

.PHONY: all debug release submit clean new

ifneq ($(MAKECMDGOALS),new)
    ifneq ($(words $(SRC)),1)
        $(warning "Warning: Multiple (or None) .cpp files found (excluding submission*.cpp). Please ensure only one main source file exists.")
        $(error "Build stopped")
    endif
endif

all: release

new: lib/utils/template.cpp
	@copy "lib\utils\template.cpp" "main.cpp"
	@echo Created new source file: main.cpp

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(DEBUG_NAME)

release: CXXFLAGS += $(RELEASE_FLAGS) 
release: $(NAME)

$(NAME): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

$(DEBUG_NAME): $(SRC)
	$(CXX) $(CXXFLAGS) $< -o $@

SRC_SUBMIT = $(basename $(SRC))_submit.cpp
submit: $(SRC) lib/utils/submit.py
	@python3 lib/utils/submit.py $(SRC) $(SRC_SUBMIT)
	@echo Submission file created: $(SRC_SUBMIT)

clean:
	@del /F /Q *.exe *_submit.cpp 2>nul
	@echo Cleaned up.

