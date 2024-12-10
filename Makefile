CXX = g++ -g -std=c++20

FILES = build/main.o build/Utaste.o build/User.o build/Restaurant.o build/Reservation.o
EXE = UTaste

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@

build/main.o: src/main.cpp src/Utaste.hpp src/constants.hpp src/libraries.hpp
	$(CXX) -c $< -o $@

build/Utaste.o: src/Utaste.cpp src/Utaste.hpp
	$(CXX) -c $< -o $@

build/User.o: src/User.cpp src/User.hpp
	$(CXX) -c $< -o $@

build/Restaurant.o: src/Restaurant.cpp src/Restaurant.hpp
	$(CXX) -c $< -o $@

build/Reservation.o: src/Reservation.cpp src/Reservation.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)
