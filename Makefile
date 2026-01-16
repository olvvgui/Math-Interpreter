# ===== Configurações =====
CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra -O2
INCLUDES  := -Iincludes/DataStructures -Iincludes/Exceptions -Iincludes/Interpreter -Iincludes/Token -Iincludes/Utils 

TARGET    := Math_Interpreter
BUILD_DIR := build
LOG_FILE  := build.log

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
all: log_header run

# ===== Timestamp no log =====
log_header:
	@echo "==============================================" >> $(LOG_FILE)
	@echo "Build started at: $$(date '+%Y-%m-%d %H:%M:%S')" >> $(LOG_FILE)
	@echo "==============================================" >> $(LOG_FILE)

# ===== Executar =====
run: $(TARGET)
	@./$(TARGET)

# ===== Link =====
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $@ 2>> $(LOG_FILE)

# ===== Compilar .cpp -> .o =====
$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@ 2>> $(LOG_FILE)

# ===== Limpar =====
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

rebuild: clean all
