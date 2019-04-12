'use strict';
var lineColor = "#ddd";

var canvas = document.getElementById('board');
console.log(canvas);
var context = canvas.getContext('2d');

var canvasSize = 500;
var sectionSize = canvasSize / 8;

canvas.width = canvasSize;
canvas.height = canvasSize;

context.translate(0.5, 0.5);

function initBoard(){
	let b = [];

	for(let i=0;i<8;i++){
		b.push([]);
		for(let j=0;j<8;j++) b[i].push(0);
	}

	return b;
}

function drawSquare(i,j,color){
	context.beginPath();
	context.rect(i,j,sectionSize,sectionSize);
	context.fillStyle = color;
	context.fill();
}

function drawLines (lineWidth, strokeStyle) {
	for(let i=0;i<8;i++){
		for(let j=0;j<8;j++){
			if((i+j)%2 != 0) drawSquare(i*sectionSize,j*sectionSize,"lightgray");
			else drawSquare(i*sectionSize,j*sectionSize,"white");
		}
	}
	/*
  var lineStart = 4;
  var lineLenght = canvasSize - 5;
  context.lineWidth = lineWidth;
  context.lineCap = 'round';
  context.strokeStyle = strokeStyle;
  context.beginPath();


  for (var y = 1;y <= 7;y++) {
    context.moveTo(lineStart, y * sectionSize);
    context.lineTo(lineLenght, y * sectionSize);
  }

  for (var x = 1;x <= 7;x++) {
    context.moveTo(x * sectionSize, lineStart);
    context.lineTo(x * sectionSize, lineLenght);
  }

  context.stroke();
*/

}

drawLines(10, lineColor);

let board = initBoard();
/*
get board
*/

/*
init board
*/
