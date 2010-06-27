PDF		= pdflatex
DOCBASE	= dpsmanual

.PHONY: clean

all:
	@$(PDF) $(DOCBASE).tex
	@rm -rf $(DOCBASE).aux $(DOCBASE).log

clean:
	@rm -rf $(DOCBASE).pdf
