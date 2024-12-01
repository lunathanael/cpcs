CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
DEBUG_FLAGS = -DTESTING -Wconversion -Werror -pedantic -g -g3 -DDEBUG -D_GLIBCXX_DEBUG
RELEASE_FLAGS = -Ofast -DNDEBUG

SRC = $(filter-out %_submit.cpp,$(wildcard *.cpp))
NAME = $(basename $(SRC)).exe
DEBUG_NAME = $(basename $(SRC))_debug.exe

# Check for multiple source files
ifneq ($(words $(SRC)),1)
    $(warning "Warning: Multiple .cpp files found (excluding submission*.cpp). Please ensure only one main source file exists.")
    $(error "Build stopped")
endif

.PHONY: all debug release submit clean

all: release

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
	@python lib/utils/submit.py $(SRC) $(SRC_SUBMIT)
	@echo Submission file created: $(SRC_SUBMIT)

clean:
	@del /F /Q *.exe *_submit.cpp 2>nul
	@echo Cleaned up.

