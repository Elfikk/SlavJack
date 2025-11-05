# The Premise

Writing a small card video game, served via a websocket web server, self-hosted
and exposed on a purchased domain like slavjack.uk.

Going to start with Uno BlackJack.

## Components

Video Game Logic - Knows the state of the current game, possible moves from 
this point, win conditions etc. Shouldn't need to handle HTTP requests 
directly, with some kind of adapter in the middle. 
-> Crafts Responses to Incoming Moves. The aim is to write this in a way that
   does not require a server at all. I'd like to unit test this.
-> This needs to be written with a common API that could be extended to handle
   other games.

WebSocket Web Server - Written with uWebSockets. Want to provide live updates
for multiple players, rather than serving a static HTTP(S) webpage, so want to
use websockets. Will simply forward the requests to the GameState, though it 
will need to handle more things i.e player joining and leaving.

Nginx Proxy - Exposing my webserver would be a pretty silly idea. Better to
have the nginx point in the middle for some security. nginx does allow for 
elevating a HTTP connection to a WebSocket one, so can go ahead with that.

Front End Dynamic Web Page - Probably more React? Though not necessarilly.
Feel like writing repeatable card objects would be useful. Gives interface
to actually send through updates to the game logic (via many layers).

Will need a domain and to setup the DNS appropriately. And then there's 
probably more layers that I simply not aware of - one can only find out...

I'll want to make the game logic and websocket web servers Buildroot packages
which are started up by the init scripts (more Busybox!). This is gonna be 
fun :) 

A large part of this is getting an embedded-ish platform running this kind of 
application out of the box. This way, down the line, I have an application to
get working once I am doing a BSP bring-up. Gonna be great. 

