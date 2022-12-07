echo "number of connections"

read __connection_number

while [ $__connection_number -gt 0 ]
do
	( ./nc.sh &)
	__connection_number=$(( $__connection_number - 1))
done
