echo "number of connections"

read __connection_number

echo "Port number"

read __port_number
__exit_status = 0;
while [ $__connection_number -gt 0 ]
do
	nc localhost $__port_number
	__connection_number=$(( $__connection_number - 1))
done
