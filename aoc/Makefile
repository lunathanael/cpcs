CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -march=native
DEBUG_FLAGS = -DTESTING -Wconversion -Werror -pedantic -g -g3 -DDEBUG -D_GLIBCXX_DEBUG -fsanitize=address,undefined
RELEASE_FLAGS = -Ofast -DNDEBUG

SRC = $(filter-out %_submit.cpp,$(wildcard *.cpp))
NAME = $(basename $(SRC)).out
DEBUG_NAME = $(basename $(SRC))_debug.out

.PHONY: all debug release submit clean new

ifneq ($(MAKECMDGOALS),new)
    ifneq ($(words $(SRC)),1)
        $(warning "Warning: Multiple (or None) .cpp files found (excluding submission*.cpp). Please ensure only one main source file exists.")
        $(error "Build stopped")
    endif
endif

all: release

new: lib/utils/template.cpp
	@cp "./lib/utils/template.cpp" "main.cpp"
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
	@rm -f *.out *_submit.cpp
	@echo Cleaned up.

