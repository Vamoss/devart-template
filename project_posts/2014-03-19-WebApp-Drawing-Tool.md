This video shows a WebApp made with Dart(https://www.dartlang.org/), that contain a drawing tool communication with a Openframeworks WebServer(https://github.com/mazbox/ofxWebServer).

The velocity through wifi connection is really fast!

https://www.youtube.com/watch?v=hQJ7xbYbNFU

We developed a simple HTTPPost data structure to send the line color and coordinates:

	 r,g,b,x,y,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y

The RGB values go from 0 to 255, and the XY values from 0.0f to 1.0f.


### Communication Diagram

![Communication Diagram](../project_images/9-communication-diagram.png?raw=true "Communication Diagram")