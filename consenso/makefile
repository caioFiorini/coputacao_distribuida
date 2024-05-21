# Nome do compilador
CXX = g++

# Flags do compilador
CXXFLAGS = -Wall -Wextra -Werror -std=c++11 -I.

# Arquivos fonte
SOURCES = main.cpp processos.cpp sistema.cpp

# Arquivos objeto
OBJECTS = $(SOURCES:.cpp=.o)

# Nome do executável
TARGET = meu_programa

# Regras padrão
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para criar arquivos objeto
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Limpar os arquivos gerados
clean:
	rm -f $(OBJECTS) $(TARGET)

# Limpar todos os arquivos gerados e extras
distclean: clean

# Phony targets
.PHONY: all clean distclean
