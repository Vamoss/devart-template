var shapes = [];
var currentColorElement;

function setup() {
	createCanvas(400, 400);

	currentColorElement = document.querySelector("#colors li:first-child");
	currentColorElement.className = "selected";

	document.querySelector("#colors").onclick = onClickColor;
	document.querySelector("#clean").onclick = onClickClean;

	clean();
  	strokeWeight(2);
}

function draw() {
	background(0);
	noFill();
	shapes.forEach(s => {
		stroke(s.color.r, s.color.g, s.color.b);
		beginShape();
		s.coords.forEach(p => {
			vertex(p.x, p.y);
		});
		endShape();
	});
}

function mousePressed(){
	if(mouseX < 0 || mouseX > width || mouseY < 0 || mouseY > height) return;
	newShape(mouseX, mouseY);
}

function mouseDragged(){
	if(mouseX < 0 || mouseX > width || mouseY < 0 || mouseY > height) return;
	addPoint(mouseX, mouseY);
}


//-----------------------------------
class Point {
  constructor(x ,y) {
    this.x = x;
    this.y = y;
  }
}

//-----------------------------------
class Color {
  constructor(r, g, b) {
    this.r = r;
    this.g = g;
    this.b = b;
    this.stringFormat = r.toString()+","+g.toString()+","+b.toString();
  }
}

//-----------------------------------
class Shape {
  constructor(color, x, y) {
  	this.coords = [];
    this.color = color;
    this.stringFormat = color.stringFormat;
    this.add(x,y);
  }
  
  add(x, y) {
    this.coords.push(new Point(x ,y));
    this.stringFormat += ","+(x/width).toString()+","+(y/height).toString();
  }
}

function clean() {
  shapes = [];
  send();
}

function newShape(x, y) {
  if (shapes.length > 0) {
	var lastShape = shapes[shapes.length-1];
	var lastPoint = lastShape.coords[lastShape.coords.length-1];
    shapes.push(new Shape(new Color(0,0,0), lastPoint.x, lastPoint.y));
  }
  
  var data = currentColorElement.dataset;
  var color = new Color(parseInt(data["r"]), parseInt(data["g"]), parseInt(data["b"]));
  shapes.push(new Shape(color, x, y));
}

function addPoint(x, y) {
  shapes[shapes.length-1].add(x,y);
  send();
}

function onClickColor(e) {
  var elem = e.target;
  if (elem.tagName == "LI") {
    currentColorElement.className = "";
    currentColorElement = elem;
    currentColorElement.className = "selected";
  }
}

function onClickClean(e) {
  clean();
}

// protocol
// r,g,b,x,y,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y_r,g,b,x,y,x,y,x,y;
function send() {
	var s = "";
	for (var i = 0, total = shapes.length; i < total; i++) {
		if (i > 0) {
			s += "_";
		}
		s += shapes[i].stringFormat;
	}
	if (shapes.length > 0) {
		var first = shapes[0].coords[0];
		var lastShape = shapes[shapes.length-1];
		var last = lastShape.coords[lastShape.coords.length-1];
		s += "_0,0,0,"+(last.x/width).toString()+","+(last.y/height).toString()+","+(first.x/width).toString()+","+(first.y/width).toString();
	}

	var url = "http://localhost:8910/actions";
	httpPost(url, "text", s);
}

