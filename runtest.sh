#!/bin/bash

# Run tagger test on files in data/

./tagcorpus --entities=data/test_entities.tsv --names=data/test_names.tsv \
	    --types=data/test_types.tsv < data/test_documents.tsv
