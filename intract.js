const net = require('net');

const socket = new net.Socket();

const host = 'localhost';
const port = 3;
const pass = 'local';
const nick = 'Aissam';
const user = 'Abarchil';

socket.connect(port, host, () => {
    socket.write(`PASS ${pass}\r\n`);
    socket.write(`NICK ${nick}\r\n`);
    socket.write(`USER ${user} 0 * :${user}\r\n`);
});
