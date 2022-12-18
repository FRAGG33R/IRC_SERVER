#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_WIDTH = 50;
const int MAX_HEIGHT = 50;

// Structure to represent a single tile on the map
struct Tile {
  int scrapAmount;
  int owner;
  int numRobots;
  bool hasRecycler;
};

// Structure to represent the game state
struct GameState {
  int myMatter;
  int oppMatter;
  Tile map[MAX_WIDTH][MAX_HEIGHT];
};

// Function to initialize the game state from input
void initialize(GameState& state) {
  cin >> state.myMatter >> state.oppMatter;
  for (int y = 0; y < MAX_HEIGHT; y++) {
    for (int x = 0; x < MAX_WIDTH; x++) {
      cin >> state.map[x][y].scrapAmount >> state.map[x][y].owner >> state.map[x][y].numRobots >> state.map[x][y].hasRecycler;
    }
  }
}

// Function to output a MOVE action
void outputMove(int fromX, int fromY, int toX, int toY, int numRobots) {
  cout << "MOVE " << fromX << " " << fromY << " " << toX << " " << toY << " " << numRobots << endl;
}

// Function to output a BUILD action
void outputBuild(int x, int y, string type) {
  cout << "BUILD " << x << " " << y << " " << type << endl;
}

// Function to output a SPAWN action
void outputSpawn(int x, int y, int numRobots) {
  cout << "SPAWN " << x << " " << y << " " << numRobots << endl;
}

// Function to find the best move for a group of robots to take
void findBestMove(const GameState& state, int fromX, int fromY, int& toX, int& toY) {
  // Initialize best score to negative infinity
  int bestScore = -1e9;
  
  // Check all adjacent tiles
  for (int dx = -1; dx <= 1; dx++) {
    for (int dy = -1; dy <= 1; dy++) {
      int x = fromX + dx;
      int y = fromY + dy;
      
      // Skip invalid tiles
      if (x < 0 || x >= MAX_WIDTH || y < 0 || y >= MAX_HEIGHT) continue;
      
      // Calculate the score for moving to this tile
      int score = 0;
      if (state.map[x][y].owner != 1) score += state.map[x][y].scrapAmount;
      if (state.map[x][y].owner == 0) score -= state.map[x][y].scrapAmount;
      
      // Update the best score and target coordinates if necessary
 if (score > bestScore) {
        bestScore = score;
        toX = x;
        toY = y;
      }
    }
  }
}

int main() {
  // Initialize the game state
  GameState state;
  initialize(state);
  
  // Vector to store the coordinates of tiles with robots
  vector<pair<int, int>> robotTiles;
  
  // Find all tiles with robots
  for (int y = 0; y < MAX_HEIGHT; y++) {
    for (int x = 0; x < MAX_WIDTH; x++) {
      if (state.map[x][y].numRobots > 0 && state.map[x][y].owner == 1) {
        robotTiles.emplace_back(x, y);
      }
    }
  }
  
  // Check if we have enough matter to build a recycler
  if (state.myMatter >= 10) {
    // Check if we already have a recycler
    bool hasRecycler = false;
    for (int y = 0; y < MAX_HEIGHT; y++) {
      for (int x = 0; x < MAX_WIDTH; x++) {
        if (state.map[x][y].hasRecycler) {
          hasRecycler = true;
          break;
        }
      }
    }
    
    // Build a recycler if we don't already have one
    if (!hasRecycler) {
      outputBuild(0, 0, "RECYCLER");
      state.myMatter -= 10;
    }
  }
  
  // Check if we have enough matter
// Check if we have enough matter to spawn a new robot
  if (state.myMatter >= 10) {
    // Find the tile with the most scrap
    int bestTileIndex = -1;
    int mostScrap = -1;
    for (int i = 0; i < robotTiles.size(); i++) {
      int x = robotTiles[i].first;
      int y = robotTiles[i].second;
      if (state.map[x][y].scrapAmount > mostScrap) {
        mostScrap = state.map[x][y].scrapAmount;
        bestTileIndex = i;
      }
    }
    
    // Spawn a new robot on the tile with the most scrap
    if (bestTileIndex != -1) {
      int x = robotTiles[bestTileIndex].first;
      int y = robotTiles[bestTileIndex].second;
      outputSpawn(x, y, 1);
      state.myMatter -= 10;
    }
  }
  
  // Move all robots towards the best adjacent tile
  for (int i = 0; i < robotTiles.size(); i++) {
    int fromX = robotTiles[i].first;
    int fromY = robotTiles[i].second;
    int toX, toY;
    findBestMove(state, fromX, fromY, toX, toY);
    outputMove(fromX, fromY, toX, toY, state.map[fromX][fromY].numRobots);
  }
  
  return 0;
}
