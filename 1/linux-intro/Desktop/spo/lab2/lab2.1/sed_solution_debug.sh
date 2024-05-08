#!/bin/sh
echo "Sentence   one.Sentence two.   Sentence   three.     Sentence four . . . " | sed --debug -Ee 's/\b[ ]+/ /g; s/\b\.[ ]*/.  /g'

