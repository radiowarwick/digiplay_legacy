ROOT	=	../..
TEDIA	=	tedia2sql
FLAGS	=	-t postgres -c
TARGET	=	$(ROOT)/share/dps/db/digiplay.sql

FILES	=	usersgroupsdir.dia cartsets.dia audio.dia scripts.dia \
	        showplans.dia sustainer.dia website.dia digiplay.dia

$(TARGET): $(FILES)
	rm -f $(TARGET) $(TARGET).bak
	$(TEDIA) $(FLAGS) -o $(TARGET) $(FILES)

all: db
default: all

clean:
	@rm -f .*.tmpfile $(TARGET)
