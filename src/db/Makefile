ROOT	=	../..
TEDIA	=	tedia2sql
FLAGS	=	-t postgres -c
TARGET	=	$(ROOT)/share/dps/db/digiplay.sql

FILES	=	usersgroupsdir.dia audiosets.dia audio.dia scripts.dia \
	        showplans.dia sustainer.dia website.dia digiplay.dia

$(TARGET): $(FILES)
	rm -f $(TARGET) $(TARGET).bak
	$(TEDIA) $(FLAGS) -o $(TARGET).tmp $(FILES)
	cat $(TARGET).tmp | grep -v "drop index" \
					| grep -v "drop table" \
					| grep -v "drop constraint" \
					> $(TARGET)
	rm $(TARGET).tmp

all: db
default: all

clean:
	@rm -f .*.tmpfile $(TARGET)
