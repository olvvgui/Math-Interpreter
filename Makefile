# ===== Configurações =====
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2
INCLUDES  := -Iincludes/DataStructures -Iincludes/Exceptions -Iincludes/Interpreter -Iincludes/Token -Iincludes/Utils 

TARGET    := Math_Interpreter
BUILD_DIR := build

# ===== Fontes =====
SRC := \
    src/Main.cpp \
    includes/DataStructures/DataStructures.cpp \
    includes/Exceptions/Exceptions.cpp \
    includes/Interpreter/Interpreter.cpp \
    includes/Token/Token.cpp \
    includes/Utils/Utils.cpp

OBJ := $(SRC:%.cpp=$(BUILD_DIR)/%.o)

# ===== Regra padrão =====
all: run

# ===== Executar =====
run: $(TARGET)
	@./$(TARGET)

# ===== Link =====
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@

# ===== Compilar .cpp -> .o =====
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ===== Limpar =====
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all
