BUILDDIR=bin
TARGETS=$(BUILDDIR)/seq-merge $(BUILDDIR)/par-merge

.phony: all
all: $(TARGETS)

$(BUILDDIR)/seq-merge: src/mergesort-seq.cpp
	mkdir -p $(BUILDDIR)
	g++ -fopenmp src/mergesort-seq.cpp -o bin/seq-merge

$(BUILDDIR)/par-merge: src/mergesort-par.cpp
	mkdir -p $(BUILDDIR)
	g++ -fopenmp src/mergesort-par.cpp -o bin/par-merge

$(BUILDDIR)/jc: src/JC_mergesort-par.cpp
	mkdir -p $(BUILDDIR)
	g++ -fopenmp src/mergesort-par.cpp -o bin/jc

