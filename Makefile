CXX = g++ -g -std=c++20

FILES = build/main.o build/Utaste.o build/User.o build/Restaurant.o build/Reservation.o build/Terminal.o
EXE = UTaste

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@

build/main.o: src/main.cpp src/Terminal.hpp
	$(CXX) -c $< -o $@

build/Utaste.o: src/Utaste.cpp src/Utaste.hpp src/User.hpp src/Restaurant.hpp src/Exceptions.hpp
	$(CXX) -c $< -o $@

build/User.o: src/User.cpp src/User.hpp src/district.hpp src/Reservation.hpp 
	$(CXX) -c $< -o $@

build/Restaurant.o: src/Restaurant.cpp src/Restaurant.hpp src/district.hpp src/Reservation.hpp
	$(CXX) -c $< -o $@

build/Reservation.o: src/Reservation.cpp src/Reservation.hpp src/User.hpp src/Exceptions.hpp
	$(CXX) -c $< -o $@

build/Terminal.o: src/Terminal.cpp src/Terminal.hpp src/constants.hpp src/libraries.hpp src/Utaste.hpp src/Exceptions.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)
