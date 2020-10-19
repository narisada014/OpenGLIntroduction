TARGET	= output
SOURCES	= $(wildcard *.cpp)
HEADERS	= $(wildcard *.h)
OBJECTS	= $(patsubst %.cpp,%.o,$(SOURCES))
CXXFLAGS = -g -Wall -std=c++11 -I/usr/local/include
LDLIBS	= -L/usr/local/lib -lglfw -lGLEW -framework OpenGL -framework CoreVideo -framework IOKit -framework Cocoa

.PHONY: clean

$(TARGET): $(OBJECTS)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

$(TARGET).dep: $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -MM $(SOURCES) > $(TARGET).dep

clean:
	-$(RM) $(TARGET) *.o *~ .*~ a.out core

-include $(TARGET).dep
