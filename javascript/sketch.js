let dist = 10
function setup() {
  createCanvas(1024, 1024);
  noStroke();
  for(let i = 0; i < 64; i++)
    for(let j = 0; j < 64; j++)
    {
      fill(red_colors[i*64+j], green_colors[i*64+j], blue_colors[i*64+j])
      rect(i*dist, j*dist, dist)
    }  
}

function draw() {
  
}
