CXXFLAGS = -O3 -Wall -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wmissing-field-initializers -Wctor-dtor-privacy  -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++ --std=c++14

SOURCES = $(wildcard *.cpp)
OBJECTS = $(patsubst %.cpp,%.o,$(SOURCES))
EXECUTABLE = performance-benchmark

all : $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LOADLIBES) $(LDLIBS)

clean:
	$(RM) $(EXECUTABLE) $(OBJECTS)
