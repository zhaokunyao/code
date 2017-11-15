target:
	mkdir -p ./classes/main
	javac -encoding utf8 ./Room.java -d ./classes
	javac -encoding utf8 ./Graph.java  -d ./classes/main/ -classpath ./classes
run:
	java -classpath ./classes/main:./classes Graph
clean:
	rm -rf classes
