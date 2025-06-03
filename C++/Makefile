# Пути
SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include

# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I$(INCLUDE_DIR)

# Файлы
OBJS = \
  $(BUILD_DIR)/main.o \
  $(BUILD_DIR)/math_utils.o \
  $(BUILD_DIR)/mod_inverse1.o \
  $(BUILD_DIR)/mod_inverse2.o \
  $(BUILD_DIR)/modexp.o \
  $(BUILD_DIR)/shamir.o \
  $(BUILD_DIR)/solveDiophantine.o

# Правила
program.out: $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD_DIR)/*.o program.out
