all:
	g++ -pthread main.cpp myMonitor.cpp -oproject

clean:
	rm project