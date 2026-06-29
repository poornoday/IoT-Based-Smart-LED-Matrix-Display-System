#ifndef GAMES_H
#define GAMES_H

#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>

// --- SNAKE SYSTEM CORE ---
struct Point { int x, y; };
Point snake[64];
int snakeLength = 3;
Point snakeDir = {1, 0};
Point food = {4, 4};
bool gameOverSnake = false;

void initSnake() {
  snakeLength = 3;
  snake[0] = {3, 3};
  snake[1] = {2, 3};
  snake[2] = {1, 3};
  snakeDir = {1, 0};
  food = {random(0, 8), random(0, 8)};
  gameOverSnake = false;
}

void runSnakeAI() {
  // Simplistic AI: Turn toward food to keep the matrix active in demo mode
  if (snake[0].x < food.x) snakeDir = {1, 0};
  else if (snake[0].x > food.x) snakeDir = {-1, 0};
  else if (snake[0].y < food.y) snakeDir = {0, 1};
  else if (snake[0].y > food.y) snakeDir = {0, -1};
}

void updateSnake(Adafruit_NeoMatrix &m) {
  m.fillScreen(0);
  if (gameOverSnake) {
    m.setTextColor(m.Color(255, 0, 0));
    m.setCursor(1, 0);
    m.print("X");
    m.show();
    return;
  }

  // Calculate new head position
  Point newHead = {snake[0].x + snakeDir.x, snake[0].y + snakeDir.y};

  // Wall collisions (wrapping)
  if (newHead.x < 0) newHead.x = 7;
  if (newHead.x > 7) newHead.x = 0;
  if (newHead.y < 0) newHead.y = 7;
  if (newHead.y > 7) newHead.y = 0;

  // Move snake body body segments backward
  for (int i = snakeLength - 1; i > 0; i--) {
    snake[i] = snake[i - 1];
  }
  snake[0] = newHead;

  // Check if food was eaten
  if (snake[0].x == food.x && snake[0].y == food.y) {
    if (snakeLength < 64) snakeLength++;
    food = {random(0, 8), random(0, 8)};
  }

  // Draw Food (Red)
  m.drawPixel(food.x, food.y, m.Color(255, 0, 0));
  // Draw Snake (Green)
  for (int i = 0; i < snakeLength; i++) {
    m.drawPixel(snake[i].x, snake[i].y, m.Color(0, 255, 0));
  }
  m.show();
}

// --- PONG SYSTEM CORE ---
int ballX = 3, ballY = 3;
int ballDX = 1, ballDY = 1;
int paddleX = 3;
int paddleWidth = 3;

void initPong() {
  ballX = 3; ballY = 3;
  ballDX = 1; ballDY = 1;
  paddleX = 3;
}

void updatePong(Adafruit_NeoMatrix &m) {
  m.fillScreen(0);

  // Ball physics & tracking mechanics
  ballX += ballDX;
  ballY += ballDY;

  // Horizontal wall bounces
  if (ballX <= 0 || ballX >= 7) ballDX = -ballDX;
  
  // Top wall bounce
  if (ballY <= 0) ballDY = -ballDY;

  // Bottom paddle check or reset
  if (ballY == 6) {
    if (ballX >= paddleX && ballX < paddleX + paddleWidth) {
      ballDY = -ballDY;
    }
  }

  if (ballY >= 7) { // Ball dropped out, reset position
    initPong();
  }

  // Basic Paddle Tracking AI
  if (ballX > paddleX + 1 && paddleX < 8 - paddleWidth) paddleX++;
  if (ballX < paddleX && paddleX > 0) paddleX--;

  // Draw Elements: Ball (White), Paddle (Blue)
  m.drawPixel(ballX, ballY, m.Color(255, 255, 255));
  m.drawFastHLine(paddleX, 7, paddleWidth, m.Color(0, 0, 255));
  m.show();
}

#endif