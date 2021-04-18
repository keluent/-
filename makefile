wM : worker.o workManager.o employee.o  manager.o boss.o main.o
	g++ -o wM  main.o workManager.o worker.o employee.o boss.o manager.o


worker.0 : worker.cpp worker.h
	g++ -c worker.cpp

workManager.o : workManager.cpp workManager.h
	g++ -c workManager.cpp

employee.o : employee.cpp employee.h
	g++ -c employee.cpp

manager.o	: manager.cpp manager.h
	g++ -c manager.cpp

boss.o : boss.cpp boss.h
	g++ -c boss.cpp

main.o : main.cpp
	g++ -c main.cpp


clean:
	rm  -f *.o
