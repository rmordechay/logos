generate_grammar:
	rm -rf logos/parser
	java -jar grammar/antlr.jar -no-listener -Dlanguage=Cpp -o logos/parser Logos.g4
