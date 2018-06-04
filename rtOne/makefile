CC = clang++
CONFIG = Debug
TARGET = ../x64/$(CONFIG)/rtOne
SOURCES = rtOne.cpp

.PHONY: $(TARGET)

$(TARGET): $(SOURCES)
	$(CC) $< -o $@ -D$(CONFIG)