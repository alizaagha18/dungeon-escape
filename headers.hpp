#pragma once

#include <iostream>
#include <string>
#include <vector> 
#include <queue> 
#include <stack> 
#include <chrono> // For timing functionality
#include <thread> // For sleep functionality
using namespace std;

// Class for Player
class Player {
private:
    string name;           // Player's name
    int health;           // Player's health
    vector<string> inventory; // Player's inventory (dynamic array)
    int moves;            // Remaining moves
    int coins;            // Coins collected
    int enemiesDefeated;  // Number of enemies defeated

public:
    Player(string n); // Constructor to initialize player
    void takeDamage(int damage); // Reduce player's health by specified damage
    void heal(int amount); // Increase player's health by specified amount
    void addToInventory(string item); // Add an item to the player's inventory
    void addCoins(int amount); // Add coins to the player's collection
    void useMove(); // Decrease the number of remaining moves by 1
    void incrementEnemiesDefeated(); // Increment the number of enemies defeated
    int getHealth() const; // Get the player's current health
    int getMoves() const; // Get the number of remaining moves
    string getName() const; // Get the player's name
    int getCoins() const; // Get the number of coins collected
    int getEnemiesDefeated() const; // Get the number of enemies defeated
    vector<string> getInventory() const; // Get the player's inventory
};

// Class for Enemy
class Enemy {
private:
    string name;           // Enemy's name
    string description;    // Enemy's description
    int healthRequired;    // Health required to defeat the enemy

public:
    Enemy(string n, string desc, int hr); // Constructor to initialize enemy
    string getName() const; // method to get the enemy's name
    string getDescription() const; // method to get the enemy's description
    int getHealthRequired() const; // method to get the health required to defeat the enemy
};

// Class for Treasure
class Treasure {
private:
    string item1; // First treasure item
    string item2; // Second treasure item
    string key;   // Key to the next room

public:
    Treasure(string i1, string i2, string k); // Constructor to initialize treasure
    string getItem1() const; //method to get the first treasure item
    string getItem2() const; // method to get the second treasure item
    string getKey() const; // method to get the key to the next room
};

// Class for Room
class Room {
public:
    string name;     // Room's name
    Enemy enemy;     // Enemy in the room
    Treasure treasure; // Treasure in the room
    string challenge; // Challenge in the room

    Room(string n, Enemy e, Treasure t, string c); // Constructor to initialize room
};

// Class for Dungeon
class Dungeon {
private:
    queue<Enemy> enemyQueue; // Queue to manage enemies in order
    stack<Room*> roomStack;  // Stack to track the player's path
    vector<Room*> rooms;     // Linked list to manage rooms

public:
    Dungeon(); // Constructor to initialize the dungeon
    ~Dungeon(); // Destructor to clean up dynamically allocated memory
    void displayRules() const; // Display the game rules at the start
    Room* getNextRoom(); // Go to  the next room in the dungeon
    void enterRoom(Player& player); // Enter a room and handle player choices
    void backtrack(Player& player); // go bavk to the previous room
    void displayRanking(const Player& player) const; // Display the player's ranking at the end of the game
};

