import 'dart:html';


// protocol
// x,y,x,y,x,y,x,y_x,y,x,y,x,y_x,y,x,y,x,y;

var shapes = new List<Shape>();
var dragging = false;

var currentColor = new Color(255, 255, 255);
 
var canvasRect;
final CanvasRenderingContext2D context = (querySelector("#canvas") as CanvasElement).context2D;

//-----------------------------------
class Point {
  
  var x,y;
  
  Point(x ,y) {
    this.x = x;
    this.y = y;
  }
}

//-----------------------------------
class Color {
  
  var r,g,b;
  var stringFormat;
  
  Color(r, g, b) {
    this.r = r;
    this.g = g;
    this.b = b;
    stringFormat = r.toString()+","+g.toString()+","+b.toString();
  }
}

//-----------------------------------
class Shape {
  
  var color;
  var coords = new List<Point>();
  var stringFormat;
  
  Shape(color, x, y) {
    this.color = color;
    stringFormat = color.stringFormat;
    add(x,y);
  }
  
  void add(x, y) {
    coords.add(new Point(x ,y));
    stringFormat += ","+(x/canvasRect.width).toString()+","+(y/canvasRect.height).toString();
  }
}

//-----------------------------------
void main() {

  canvasRect = context.canvas.getBoundingClientRect();

  context.canvas..onMouseDown.listen(onMouseDown)
      ..onMouseMove.listen(onMouseMove)
      ..onMouseUp.listen(onMouseUp)
      ..onMouseOut.listen(onMouseUp);
  querySelector("body").onMouseUp.listen(onMouseUp);

  querySelector("#colors").onClick.listen(onClickColor);
  querySelector("#clean").onClick.listen(onClickClean);

  clean();
}

void clean() {
  shapes = [];
  draw();
  send();
}

void draw() {
  context.clearRect(0, 0, canvasRect.width, canvasRect.height);
  for (var i = 0; i < shapes.length; i++) {
    drawShape(shapes[i]);
  }
}

void drawShape(Shape s) {
  if (s.color.r == 0 && s.color.g == 0 && s.color.b == 0) return;
  
  context..beginPath()
         ..lineWidth = 2
         ..strokeStyle = "rgb("+s.color.stringFormat+")"
         ..moveTo(s.coords[0].x, s.coords[0].y);
         
  for (var i = 1, total = s.coords.length; i < total; i++) {
    context.lineTo(s.coords[i].x, s.coords[i].y);
  }
  
  context.stroke();
}

void newShape(x, y) {
  if (shapes.length > 0) {
    var lastPoint = shapes.last.coords.last;
    shapes.add(new Shape(new Color(0,0,0), lastPoint.x, lastPoint.y));
    shapes.last.add(x, y);
  }
  shapes.add(new Shape(currentColor, x, y));
}

void addPoint(x, y) {
  shapes.last.add(x,y);
  draw();
  send();
}

void onMouseDown(MouseEvent e) {
  dragging = true;
  newShape(e.client.x-canvasRect.left, e.client.y-canvasRect.top);
}

void onMouseMove(MouseEvent e) {  
  if (dragging) {
    addPoint(e.client.x-canvasRect.left, e.client.y-canvasRect.top);
  }
}

void onMouseUp(MouseEvent e) {
  dragging = false;
}

void onClickColor(MouseEvent e) {
  var data = (e.target as Element).dataset;
  currentColor = new Color(data["r"], data["g"], data["b"]);
}

void onClickClean(MouseEvent e) {
  clean();
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
  for (var i = 0, total = shapes.length; i < total; i++) {
    if (i > 0) {
      s += "_";
    }
    s += shapes[i].stringFormat;
  }
  if (shapes.length > 0) {
    var first = shapes.first.coords.first;
    var last = shapes.last.coords.last;
    s += "_0,0,0,"+(last.x/canvasRect.width).toString()+","+(last.y/canvasRect.height).toString()+","+(first.x/canvasRect.width).toString()+","+(first.y/canvasRect.width).toString();
  }
  
  try {
    //var url = "http://1.1.1.4:8910/actions";
    var url = "http://localhost:8910/actions";
    request.open("POST", url, async: false);
    request.send(s);
  } catch (e) {
    //print(e);
  }
}

