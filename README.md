# What is an IRC protocol ?

<aside>
🚨 IRC (Internet Relay Chat) is a protocol for real-time text communication over the Internet. It allows users to communicate with each other in real-time through chat rooms (also known as channels) or through private messages.

</aside>

# What is an IRC server ?

<aside>
🚨 An IRC server is a computer that runs software that implements the IRC protocol and allows users to connect to it and communicate with each other. An IRC server typically listens for incoming connections on a specific port (usually 6667) and allows users to connect to it using an IRC client.

</aside>

<aside>
⚠️ In summary, the IRC protocol is the set of rules and guidelines that define how IRC servers and clients communicate with each other, while an IRC server is a computer that runs software that implements the IRC protocol and allows users to connect to it and communicate with each other.

</aside>

# How does IRC server work ?

1. The IRC server listens for incoming connections on a specific port (usually 6667).
2. When a user connects to the IRC server using an IRC client, the server authenticates the user and assigns them a unique nickname.
3. The user can then join one or more chat rooms (also known as channels) on the server, or send private messages to other users.
4. When a user sends a message, the server receives the message and broadcasts it to all other users in the same chat room or private conversation.
5. The server maintains a list of users and channels and keeps track of who is in which chat room or private conversation. It also stores messages and other data related to the chat sessions.
6. The server may also implement additional features, such as user lists, topic management, and moderation tools.

# What is IRC client ?

<aside>
🚨 A client is anything connecting to a server that is not another server.  Each client is distinguished from other clients by a unique nickname having a maximum length of nine (9) characters.

</aside>

# list of IRC commands

## for regular users :

- JOIN: This command allows a user to join a channel on the server.
- PART: This command allows a user to leave a channel on the server.
- PRIVMSG: This command allows a user to send a message to another user or a channel.
- NICK: This command allows a user to change their nickname.
- PASS: This command allows a user to enter the password.
- USER: This command allows a user to enter username.
- WHOIS: This command allows a user to request information about another user, such as their real name, hostname, and so on.
- SENDFILE: This command allows a user to send files to another user.

## for operator users :

- KICK: This command allows an operator to forcibly remove a user from a channel.
- BAN: This command allows an operator to ban a user from a channel, preventing them from re-joining.
- MODE: This command allows an operator to set or modify the modes of a channel or user. Operators can use modes to set permissions or change the behavior of the server or channel.
- KILL: This command allows an operator to disconnect a user from the server.
- OP: This command allows an operator to grant operator privileges to another user.
