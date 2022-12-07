from threading import Thread
import os
def func():
	os.system("nc localhost 3000 &")
	return ;

for i in range (0,300) :
	t1 = Thread(target = func, args = ())
	t1.start()
	x = []
	x.append(t1)

for i in x :
	i.join()
