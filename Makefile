CXX			= g++
MINGW32_CXX		= i686-w64-mingw32-g++

CFLAGS			= -std=c++11 -static-libgcc -static-libstdc++ -static
LINK			= -lboost_system -lboost_thread

SRC			= src/*.cpp
TARGET			= server


linux:
	$(CXX) $(CFLAGS) $(SRC) -o $(TARGET) $(LINK) -lpthread

win32:
	$(CXX) $(CFLAGS) $(SRC) -D _WIN32_WINNT=0x0501 -o $(TARGET) -lwsock32 -lws2_32 $(LINK)

win32-cross-compile:
	$(MINGW32_CXX) $(CFLAGS) $(SRC) -D _WIN32_WINNT=0x0501 -o $(TARGET).exe -lwsock32 -lws2_32 $(LINK)

default:
ifeq ($(OS),Windows_NT)
	win32
else
	linux
endif

.PHONY: clean
clean:
	$(RM) $(TARGET)
	$(RM) $(TARGET).exe
