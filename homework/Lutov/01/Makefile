CXXFLAGS = -O3 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wstrict-null-sentinel  -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++ -std=gnu++0x

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
EXECUTABLE = performance-benchmark

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $^ -o $@

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)
