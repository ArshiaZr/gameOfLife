#include <iostream>
#include "p5.hpp"
#include <vector>

P5& p5 = P5::getInstance();

std::vector<bool> grid;
int w = 20;
int cols, rows;

std::vector<bool> neighbours(int x, int y){
    std::vector<bool> n;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            int col = (x + i + cols) % cols;
            int row = (y + j + rows) % rows;
            n.push_back(grid[col + row * cols]);
        }
    }
    return n;
}


void setup(){
    p5.createCanvas(400, 400);
    cols = p5.width / w;
    rows = p5.height / w;
    p5.frameRate(10);
    grid.resize(cols * rows);
    for(int i = 0; i < cols * rows; i++){
        grid[i] = p5.random(1) < 0.2;
    }
}

void draw(){
    p5.background(220);

    // Draw the grid
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            int x = i * w;
            int y = j * w;
            if(grid[i + j * cols]){
                p5.fill(0);
                p5.stroke(255);
                p5.rect(x, y, w-1, w-1);
            }
        }
    }

    // Compute next generation
    std::vector<bool> next;
    next.resize(cols * rows);
    for(int i = 0; i < cols; i++){
        for(int j = 0; j < rows; j++){
            int state = grid[i + j * cols];
            std::vector<bool> n = neighbours(i, j);
            int sum = 0;
            for(int k = 0; k < n.size(); k++){
                sum += n[k];
            }
            int index = i + j * cols;
            if(state == 0 && sum == 3){
                next[index] = 1;
            } else if(state == 1 && (sum < 2 || sum > 3)){
                next[index] = 0;
            } else {
                next[index] = state;
            }
        }
    }
    // Update grid
    grid = next;
}

void mousePressed(){
    int x = p5.mouseX / w;
    int y = p5.mouseY / w;
    int index = x + y * cols;
    grid[index] = !grid[index];
}

int main(){
    p5.registerMethod("setup", setup);
    p5.registerMethod("draw", draw);
    p5.registerMethod("mousePressed", mousePressed);

    p5.run();
    return 0;
}