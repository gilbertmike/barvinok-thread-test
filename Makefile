build:
	g++ -o forking forking.cpp -lbarvinok -lisl -lntl -lpolylibgmp -lgmp
	g++ -o threading threading.cpp -lbarvinok -lisl -lntl -lpolylibgmp -lgmp