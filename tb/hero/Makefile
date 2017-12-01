target:
	mkdir -p ./classes/main
	javac -encoding utf8 ./Room.java -d ./classes
	javac -encoding utf8 ./Warehouse.java -d ./classes
	javac -encoding utf8 ./Item.java -d ./classes
	javac -encoding utf8 ./Hero.java -d ./classes
	javac -encoding utf8 ./Graph.java  -d ./classes/main/ -classpath ./classes
run:
	cp -f item_name.txt  ./classes/main
	java -classpath ./classes/main:./classes Graph

test: 
	mkdir -p ./classes/test
	javac -encoding utf8 ./Test.java -d ./classes/test
	java -ea -classpath ./classes/test:./classes Test
clean:
	rm -rf classes
