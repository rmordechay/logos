generate_grammar:
	rm -rf gen
	java -jar grammar/antlr.jar -Dlanguage=Cpp -o gen Logos.g4
