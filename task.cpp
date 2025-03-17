#include "../headers/headers.hpp"
#include <vector> // Ensure vector is included
#include <queue>  // Ensure queue is included
#include <stack>  // Ensure stack is included
#include <string> // Ensure string is included

// Player Class Implementation
// Constructor to initialize player
Player::Player(string n) : name(n), health(100), moves(10), coins(0), enemiesDefeated(0) {}

// Reduce player's health by specified damage
void Player::takeDamage(int damage) {
    health -= damage;
    if (health < 0) health = 0;
}

// Increase player's health by specified amount
void Player::heal(int amount) {
    health += amount;
    if (health > 100) health = 100;
}

// Add an item to the player's inventory
void Player::addToInventory(string item) {
    inventory.push_back(item);
}

// Add coins to the player's collection
void Player::addCoins(int amount) {
    coins += amount;
}

// Decrease the number of remaining moves by 1
void Player::useMove() {
    moves--;
}

// Increment the number of enemies defeated
void Player::incrementEnemiesDefeated() {
    enemiesDefeated++;
}

// Get the player's current health
int Player::getHealth() const { return health; }

// Get the number of remaining moves
int Player::getMoves() const { return moves; }

// Get the player's name
string Player::getName() const { return name; }

// Get the number of coins collected
int Player::getCoins() const { return coins; }

// Get the number of enemies defeated
int Player::getEnemiesDefeated() const { return enemiesDefeated; }

// Get the player's inventory
vector<string> Player::getInventory() const { return inventory; }

// Enemy Class Implementation

// Constructor to initialize enemy
Enemy::Enemy(string n, string desc, int hr) : name(n), description(desc), healthRequired(hr) {}

// Get the enemy's name
string Enemy::getName() const { return name; }

// Get the enemy's description
string Enemy::getDescription() const { return description; }

// Get the health required to defeat the enemy
int Enemy::getHealthRequired() const { return healthRequired; }

// Treasure Class Implementation

// Constructor to initialize treasure
Treasure::Treasure(string i1, string i2, string k) : item1(i1), item2(i2), key(k) {}

// Get the first treasure item
string Treasure::getItem1() const { return item1; }

// Get the second treasure item
string Treasure::getItem2() const { return item2; }

// Get the key to the next room
string Treasure::getKey() const { return key; }

// Room Class Implementation

// Constructor to initialize room
Room::Room(string n, Enemy e, Treasure t, string c) : name(n), enemy(e), treasure(t), challenge(c) {}

// Dungeon Class Implementation

// Constructor to initialize the dungeon
Dungeon::Dungeon() {
    // Initialize rooms (Linked List)
    rooms.push_back(new Room("Base", Enemy("Shadow Stalker", "A stealthy, dark creature that lurks in the shadows.", 15), Treasure("5 Coins", "Armour", "Key1"), "Collect 5 coins"));
    rooms.push_back(new Room("Bronze", Enemy("Viper", "A venomous menace that ambushes foes with poison.", 25), Treasure("5 Coins", "Health Booster Potion", "Key2"), "Exit the room within 5 seconds")); 
    rooms.push_back(new Room("Platinum", Enemy("Crawler", "A fast, wall-climbing creature that swarms its prey.", 35), Treasure("Health Booster Potion", "Armour", "Key3"), "Defeat the enemy without armour"));
    rooms.push_back(new Room("Silver", Enemy("Hunter", "A swift and deadly assassin that strikes from the shadows.", 50), Treasure("5 Coins", "Armour", "Key4"), "Solve the riddle: I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?"));
    rooms.push_back(new Room("Gold", Enemy("Boss", "The ultimate challenge of the dungeon.", 70), Treasure("5 Coins", "Health Booster Potion", "Key5"), "Defeat the boss"));

    // Add enemies to the queue
    for (size_t i = 0; i < rooms.size(); i++) {
        enemyQueue.push(rooms[i]->enemy);
    }
}

// Destructor to clean up dynamically allocated memory
Dungeon::~Dungeon() {
    for (size_t i = 0; i < rooms.size(); i++) {
        delete rooms[i];
    }
}

// Display the game rules
void Dungeon::displayRules() const {
    cout << "Welcome to Dungeon Escape!\n";
    cout << "Rules:\n";
    cout << "1. You have 10 moves to escape the dungeon.\n"; // Updated moves
    cout << "2. Each room has an enemy, a treasure, and a challenge.\n";
    cout << "3. Defeat enemies to collect treasures and keys.\n";
    cout << "4. If your health drops below 20, you lose.\n";
    cout << "5. Complete challenges to progress.\n";
    cout << "Good luck!\n";
}

// Get the next room in the dungeon
Room* Dungeon::getNextRoom() {
    if (!rooms.empty()) {
        Room* nextRoom = rooms.front();
        rooms.erase(rooms.begin()); // Remove room from linked list
        return nextRoom;
    }
    return nullptr;
}

// Enter a room and handle player choices
void Dungeon::enterRoom(Player& player) {
    Room* currentRoom = getNextRoom();
    if (currentRoom) {
        roomStack.push(currentRoom); // Add room to stack for backtracking
        cout << "\nEntering Room: " << currentRoom->name << endl;
        cout << "Enemy: " << currentRoom->enemy.getName() << " - " << currentRoom->enemy.getDescription() << endl;
        cout << "Challenge: " << currentRoom->challenge << endl;

        // Player choices
        cout << "1. Take key and go to next room\n";
        cout << "2. Fight enemy and collect treasure\n";
        cout << "3. Take the challenge and fight the enemy\n";
        int choice;
        cin >> choice;

        if (choice == 2 || choice == 3) {
            if (player.getHealth() >= currentRoom->enemy.getHealthRequired()) {
                cout << "You defeated the enemy and collected the treasure!\n";
                player.addToInventory(currentRoom->treasure.getItem1());
                player.addToInventory(currentRoom->treasure.getItem2());
                player.addCoins(10); // Gain 10 coins for defeating the enemy
                player.incrementEnemiesDefeated();
                player.takeDamage(currentRoom->enemy.getHealthRequired()); // Lose health
            } else {
                cout << "You failed to defeat the enemy. Health decreased by 10.\n";
                player.takeDamage(10);
            }
        }

        // Handle Room 2 challenge (exit within 5 seconds)
        if (currentRoom->name == "Bronze" && (choice == 2 || choice == 3)) {
            cout << "You have 5 seconds to exit the room. Type 'exit' quickly!\n";
            auto start = chrono::steady_clock::now();
            string input;
            cin >> input;
            auto end = chrono::steady_clock::now();
            chrono::duration<double> elapsed = end - start;

            if (input == "exit" && elapsed.count() <= 5) {
                cout << "You exited the room in time!\n";
            } else {
                cout << "You failed to exit the room in time. Health decreased by 10.\n";
                player.takeDamage(10);
            }
        }

        player.useMove(); // Decrease move count
    }
}

// Backtrack to the previous room
void Dungeon::backtrack(Player& player) {
    if (!roomStack.empty()) {
        Room* previousRoom = roomStack.top();
        roomStack.pop(); // Remove room from stack
        cout << "\nBacktracking to Room: " << previousRoom->name << endl;
        player.useMove(); // Decrease move count
    } else {
        cout << "No rooms to backtrack to.\n";
    }
}

// Display the player's ranking at the end of the game
void Dungeon::displayRanking(const Player& player) const {
    cout << "\nRanking:\n";
    cout << "Name: " << player.getName() << endl;
    cout << "Enemies Defeated: " << player.getEnemiesDefeated() << endl;
    cout << "Coins Collected: " << player.getCoins() << endl;
    cout << "Health Remaining: " << player.getHealth() << endl;
    cout << "Inventory: ";
    for (size_t i = 0; i < player.getInventory().size(); i++) {
        cout << player.getInventory()[i] << " ";
    }
    cout << endl;
}