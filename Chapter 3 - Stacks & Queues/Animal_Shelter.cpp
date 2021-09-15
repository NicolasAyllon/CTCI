/*
Animal Shelter:
An animal shelter, which holds only dogs and cats, operates on a strictly 
"first in, first out" basis. People must adopt either the "oldest" 
(based on arrival time) of all animals at the shelter, or they can select
 whether they would prefer a dog or cat (and will receive the oldest animal of
that type). 

They cannot select which specific animal they would like. 
Create the data structures to maintain this system and implement operations
such as enqueue, dequeueAny, dequeueDog, and dequeueCat.
*/

#include <ctime>
#include <sstream>
#include <queue>

enum AnimalType { 
  Dog, Cat
};

std::string getAnimalName(enum AnimalType type) {
  switch(type) {
    case Dog: return "Dog";
    case Cat: return "Cat";
  }
}


struct Animal {
  AnimalType animal_type;
  std::time_t arrival_time; // [?] or struct tm arrival_time;
  std::string name;
  
  Animal(
    AnimalType animal_type_in, 
    time_t arrival_time_in = std::time(nullptr), 
    std::string name_in = "") 
    : animal_type(animal_type_in),
      arrival_time(arrival_time_in),
      name(name_in) 
      {};
  
  std::string toString(bool includeAnimalType = true) {
    std::stringstream ss;
    ss << name << ", ";
    if(includeAnimalType) {
      ss << getAnimalName(animal_type) << ", ";
    }
    ss << "arrived " << arrival_time;
    return ss.str();
  }
  
  friend std::ostream& operator<<(std::ostream& out, const Animal& animal) {
    out << animal.name << ", " 
        << getAnimalName(animal.animal_type) << ", "
        << "arrived " << animal.arrival_time;
    return out;
  }
};


class AnimalShelter {
 private:
  std::queue<Animal> dog_queue;
  std::queue<Animal> cat_queue;

 public:
  // Precondition: Animal animal is has its animal_type initialized to a valid
  // option of the enum AnimalType: either 'dog' or 'cat'.
  void enqueue(Animal animal) {
    if(animal.animal_type == Dog) {
      dog_queue.push(animal);
      return;
    }
    if(animal.animal_type == Cat) {
      cat_queue.push(animal);
      return;
    }
  }

  void dequeueAny() {
    // If both queues are empty, do nothing.
    if(dog_queue.empty() && cat_queue.empty()) {
      return;
    }
    // If the cat queue is empty (dog queue is not), dequeue dog.
    if(cat_queue.empty()) {
      dog_queue.pop();
      return;
    }
    // If the dog queue is empty (cat queue is not), dequeue cat.
    if(dog_queue.empty()) {
      cat_queue.pop();
      return;
    }
    // If both dog and cat queues are not empty, dequeue the oldest.
    // (If both have the same arrival time, arbitrarily dequeue the dog.)
    if(dog_queue.front().arrival_time <= cat_queue.front().arrival_time) {
      dog_queue.pop();
    } else {
      cat_queue.pop();
    }
  }

  std::string getFrontDogAsString() {
    if(dog_queue.empty()) {
      return "(none)";
    }
    return dog_queue.front().toString(false);
  }

  std::string getFrontCatAsString() {
    if(cat_queue.empty()) { 
      return "(none)"; 
    }
    return cat_queue.front().toString(false);
  }

  void dequeueDog() {
    if(dog_queue.empty()) { return; }
    dog_queue.pop();
  }

  void dequeueCat() {
    if(cat_queue.empty()) { return; }
    cat_queue.pop();
  }

  int totalAnimals() {
    return dog_queue.size() + cat_queue.size();
  }

  int totalDogs() {
    return dog_queue.size();
  }

  int totalCats() {
    return cat_queue.size();
  }
  
  bool empty() {
    return dog_queue.empty() && cat_queue.empty();
  }

  std::string dogsToString() {
    std::stringstream ss;
    for(int i = 0; i < dog_queue.size(); ++i) {
      ss << dog_queue.front() << '\n';
      dog_queue.push(dog_queue.front());
      dog_queue.pop();
    }
  }

  std::string catsToString() {
    //[+] implement
  }
};