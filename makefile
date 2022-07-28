parser: parser.o transaction.o script.o bytes_helper.o
	g++ -o parser parser.o transaction.o script.o bytes_helper.o
