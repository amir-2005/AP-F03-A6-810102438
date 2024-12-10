CXX = g++ -g -std=c++20

FILES = build/main.o build/Utaste.o build/User.o build/Restaurant.o build/Reservation.o build/Terminal.o
EXE = UTaste

all: $(EXE)

$(EXE): $(FILES)
	$(CXX) $^ -o $@

build/main.o: src/main.cpp src/Utaste.hpp src/Terminal.hpp
	$(CXX) -c $< -o $@

build/Utaste.o: src/Utaste.cpp src/Utaste.hpp src/constants.hpp src/libraries.hpp src/district.hpp
	$(CXX) -c $< -o $@

build/User.o: src/User.cpp src/User.hpp src/constants.hpp src/libraries.hpp src/district.hpp
	$(CXX) -c $< -o $@

build/Restaurant.o: src/Restaurant.cpp src/Restaurant.hpp src/constants.hpp src/libraries.hpp src/district.hpp
	$(CXX) -c $< -o $@

build/Reservation.o: src/Reservation.cpp src/Reservation.hpp src/constants.hpp src/libraries.hpp src/district.hpp
	$(CXX) -c $< -o $@

build/Terminal.o: src/Terminal.cpp src/Terminal.hpp src/constants.hpp src/libraries.hpp src/district.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean

clean:
	rm -f $(FILES) $(EXE)
