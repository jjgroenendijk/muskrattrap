# Makefile for the payloadCoder project
# This Makefile compiles the project, manages dependencies, and tracks build numbers.
# Note: The code should be cleaned to remove all warnings for production use.

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -Wextra -Weffc++ -Wpedantic \
           -Wold-style-cast -Winit-self -Wno-unused -Wshadow \
           -Wno-parentheses -Wlogical-op -Wredundant-decls \
           -Wcast-align -Wsign-promo -Wmissing-include-dirs \
           -Woverloaded-virtual -Wctor-dtor-privacy

EXECUTABLE = payloadCoder
SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean clean-depend depend

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) buildnumber.num
	$(CXX) $(CXXFLAGS) $(OBJECTS) $(LDXXFLAGS) -o $@
	@echo "-- Build: " $$(cat buildnumber.num)

# Create dependency file
depend: $(SOURCES)
	$(CXX) $(CXXFLAGS) -MM $^ > depend

-include depend

# Build number management
buildnumber.num: $(OBJECTS)
	@if ! test -f buildnumber.num; then echo 0 > buildnumber.num; fi
	@echo $$(($$(cat buildnumber.num) + 1)) > buildnumber.num

# Clean up build artifacts
clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)

# Clean up build artifacts and dependency file
clean-depend: clean
	$(RM) depend

# Show warnings during compilation
warnings:
	$(CXX) $(CXXFLAGS) -fsyntax-only $(SOURCES)

# Display build number
show-build:
	@cat buildnumber.num

# Launch the executable
launch: $(EXECUTABLE)
	./$(EXECUTABLE)