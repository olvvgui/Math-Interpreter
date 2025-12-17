# ==============================
# CONFIGURAÇÕES FÁCEIS DE ALTERAR
# ==============================

TARGET   = Math_Interpreter
CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17
INCLUDES = -Iincludes

# ==============================
# ARQUIVOS DO PROJETO
# ==============================

SRC = Main.cpp \
      includes/Expression.cpp \
      includes/Token.cpp \
      includes/Utils.cpp

OBJ = $(SRC:.cpp=.o)

# ==============================
# REGRAS
# ==============================

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

run: all
	./$(TARGET)

.PHONY: all clean run
