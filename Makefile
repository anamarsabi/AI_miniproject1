# Directives
vpath %.h include/
vpath %.cpp src/
vpath %.o $(OBJ)

# Compiler
CXX = g++
CXXFLAGS = -g

# File variables
LOCATION := location
EXEC_LOCATION = $(BIN)$(LOCATION)
LOCATION_SRC := location.cpp
LOCATION_OBJ := $(LOCATION_SRC:.cpp=.o)

# Directory variables
OBJ := obj/
BIN := bin/

# Other variables
BOLD = `tput bold`
GREEN = `tput setaf 2`
RESET = `tput sgr0`

# Define variables
define compile =
@echo "Compilando $@ ..."
$(CXX) $(CXXFLAGS) -o $@ $<
@echo "${GREEN}HECHO${RESET}"
endef
define makedir =
@echo "Creando carpeta $@ ..."
mkdir -p $@
@echo "${GREEN}HECHO${RESET}"
endef
define makeexec =
@echo "Generando el ejecutable $@ ..."
$(CXX) $(CXXFLAGS) -o $@ $^
@-mv $? $(OBJ)
@echo "${GREEN}HECHO${RESET}"
endef

# Pattern-specific variables
%.o: CXXFLAGS += -I./include -c

# Recipeless rules
all: $(EXEC_LOCATION) $(EXEC_CERCANIA) $(EXEC_INSERCION) $(EXEC_INVENT) $(EXEC_COMPARISON) $(EXEC_TAREAS)
.PHONY: $(EXEC_LOCATION) $(EXEC_CERCANIA) $(EXEC_INSERCION) $(EXEC_TAREAS) $(EXEC_COMPARISON) $(EXEC_INVENT)
$(EXEC_LOCATION) : | $(BIN)
$(LOCATION_OBJ) : location.h |$(OBJ)

# File ruleS
$(EXEC_LOCATION): $(LOCATION_OBJ)
	$(makeexec)

$(LOCATION_OBJ): $(LOCATION_SRC)
	$(compile)

# Directory rules
$(OBJ):
	$(makedir)

$(BIN):
	$(makedir)

# Other rules
clean:
	@rm -rf $(BIN)
	@echo "Los ejecutables han sido borrados"
	@rm -rf $(OBJ)
	@echo "La carpeta $(OBJ) ha sido borrada con todos sus archivos"*
