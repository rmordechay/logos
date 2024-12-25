generate_grammar:
	rm -rf logos/gen
	java -jar grammar/antlr.jar -Dlanguage=Cpp -o logos/gen Logos.g4
