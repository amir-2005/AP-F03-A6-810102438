CXX = g++
CXXFLAGS = -std=c++11

BUILD_DIR = build
TEMPLATE_DIR = .template
OUT_EXE = UTaste

ifeq ($(OS),Windows_NT)
	LDLIBS += -l Ws2_32
endif

all: $(BUILD_DIR) $(OUT_EXE)

$(OUT_EXE): $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o \
             $(BUILD_DIR)/strutils.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o \
             $(BUILD_DIR)/Utaste.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Restaurant.o $(BUILD_DIR)/Reservation.o $(BUILD_DIR)/Discount.o  
			$(CXX) $(CXXFLAGS) $^ $(LDLIBS) -o $@  

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp utils/strutils.hpp utils/strutils.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/strutils.o: utils/strutils.cpp utils/strutils.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/strutils.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/handlers.o: src/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: src/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Utaste.o: src/Utaste.cpp src/Utaste.hpp src/User.hpp src/Restaurant.hpp src/Exceptions.hpp src/libraries.hpp src/constants.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/User.o: src/User.cpp src/User.hpp src/district.hpp src/Reservation.hpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Restaurant.o: src/Restaurant.cpp src/Restaurant.hpp src/district.hpp src/Reservation.hpp src/Discount.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Reservation.o: src/Reservation.cpp src/Reservation.hpp src/User.hpp src/Exceptions.hpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/Discount.o: src/Discount.cpp src/Discount.hpp src/Reservation.hpp src/Exceptions.hpp src/libraries.hpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@


.PHONY: all clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
