# Nome do executável
TARGET = programa

# Compilador
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Arquivos
SRCS = main.cpp expression.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

# Regra para o executável
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regra genérica para gerar .o
%.o: %.cpp expression.h
	$(CXX) $(CXXFLAGS) -c $<

# Executar o programa
run: $(TARGET)
	./$(TARGET)

# Limpar arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)
