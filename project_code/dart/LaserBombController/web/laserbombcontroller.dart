import 'dart:html';
import 'dart:convert';


//protocol
// x,y,x,y,x,y,x,y_x,y,x,y,x,y_x,y,x,y,x,y;

var shapes = [];
var dragging = false;

var canvasRect;
final CanvasRenderingContext2D context = (querySelector("#canvas") as CanvasElement).context2D;


class Shape {
  
  var r,g,b;
  var coords;
  
  void begin(r,g,b,x,y) {
    this.r = r;
    this.g = g;
    this.b = b;
    coords = [x,y];
  }
  
  void add(x,y) {
    coords..add(x)..add(y);
  }
  
  String toString() {
    var s = r.toString()+","+g.toString()+","+b.toString();
    for (var i = 0, total = coords.length; i < total; i++) {
      s += ","+(coords[i]/canvasRect.width).toString();
    }
    return s;
  }
  
  String getColor() {
    var s = r.toString()+","+g.toString()+","+b.toString();
    return s;
  }
  
}

void main() {

  canvasRect = context.canvas.getBoundingClientRect();

  context.canvas.onMouseDown.listen(onMouseDown);
  context.canvas.onMouseUp.listen(onMouseUp);
  context.canvas.onMouseMove.listen(onMouseMove);

  draw();  
}

void draw() {
  context.clearRect(0, 0, 300, 300);
  for (var i = 0; i < shapes.length; i++) {
    drawShape(shapes[i]);
  }
}

void drawShape(coords) {
  context..beginPath()
         ..lineWidth = 2
         ..strokeStyle = "#3333ff"
         ..moveTo(coords[0], coords[1]);
         
  for (var i = 1, total = coords.length/2; i < total; i++) {
    context.lineTo(coords[i*2], coords[i*2+1]);
  }
  
  context.stroke();
}

void drawShape2(Shape s) {
  context..beginPath()
         ..lineWidth = 2
         ..strokeStyle = "#3333ff"
         ..moveTo(coords[0], coords[1]);
         
  for (var i = 1, total = coords.length/2; i < total; i++) {
    context.lineTo(coords[i*2], coords[i*2+1]);
  }
  
  context.stroke();
}

void beginShape(x, y) {
  shapes.add([x,y]);
}

void addPoint(x,y) {
  shapes.last..add(x)..add(y);
  draw();
  send();
}

void onMouseDown(e) {
  dragging = true;
  beginShape(e.clientX-canvasRect.left, e.clientY-canvasRect.top);
}

void onMouseUp(e) {
  dragging = false;
  //send();
}

void onMouseMove(e) {  
  if (dragging) {
    addPoint(e.clientX-canvasRect.left, e.clientY-canvasRect.top);
  }
}

void send() {
  HttpRequest request = new HttpRequest(); // create a new XHR
  /*
  // add an event handler that is called when the request finishes
  request.onReadyStateChange.listen((_) {
    if (request.readyState == HttpRequest.DONE &&
        (request.status == 200 || request.status == 0)) {
      // data saved OK.
      print(request.responseText); // output the response from the server
    }
  });
  */
  
  var s = "";
  var value;
  for (var i = 0, total = shapes.length; i < total; i++) {
    if (i > 0) {
      s += "_";
    }
    s += "255,0,0";
    for (var j = 0, total2 = shapes[i].length; j < total2; j++) {
      value = shapes[i][j]/canvasRect.width;
      s += ","+value.toString();
    }
  }
  
  print(s);
  
  try {
    var url = "http://1.1.1.4:8910/actions";
    request.open("POST", url, async: false);
    request.send(s);
  } catch (e) {
    print(e);
  }
}
