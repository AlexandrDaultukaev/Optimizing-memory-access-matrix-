echo "compiling..."
g++ -Wall -o main main.c

for ((i=1000; i<=6000; i+=1000)) do
	echo "bench -n $i"
	./main -n $i	
done

echo "Done"
