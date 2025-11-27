PDF_DIR := pdf
PREAMBLE := $(PDF_DIR)/preambule.tex
MAIN := $(PDF_DIR)/projet.tex

.PHONY: all clean projet help parts

help:
	@echo "  make projet   # compile pdf/projet.pdf (fichier principal)"
	@echo "  make clean    # supprime fichiers parasites et (conserve projet.pdf)"

projet:
	@if command -v latexmk >/dev/null 2>&1; then \
		echo "Compilation du projet principal avec latexmk..."; \
		latexmk -pdf -silent -output-directory=$(PDF_DIR) $(MAIN); \
	else \
		echo "latexmk non trouvé, utilisation de pdflatex (2 passes)"; \
		pdflatex -halt-on-error -interaction=nonstopmode -output-directory=$(PDF_DIR) $(MAIN); \
		pdflatex -halt-on-error -interaction=nonstopmode -output-directory=$(PDF_DIR) $(MAIN); \
	fi

clean:
	@echo "Supprimer les fichiers parasites (conserver $(PDF_DIR)/projet.pdf)..."
	@find $(PDF_DIR) -maxdepth 1 -type f \( -name '*.aux' -o -name '*.log' -o -name '*.out' -o -name '*.toc' -o -name '*.fdb_latexmk' -o -name '*.fls' \) -delete || true
	@find $(PDF_DIR) -maxdepth 1 -type f -name 'part*.pdf' -not -name 'projet.pdf' -delete || true
	@echo "Clean ok."
