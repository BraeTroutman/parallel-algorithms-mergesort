BUILDDIR=bin
TARGETS=$(BUILDDIR)/seq-merge

.phony: all
all: $(TARGETS)

$(BUILDDIR)/seq-merge: src/mergesort-seq.cpp
	mkdir -p $(BUILDDIR)
	g++ -fopenmp src/mergesort-seq.cpp -o bin/seq-merge
