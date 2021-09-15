#include <iostream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include "Animal_Shelter.cpp"


// Note: This works only on Windows.
void clearScreen() {
  std::system("cls");
}

void printGoodbye() {
  std::cout << "~~*~~*~~*~~*~~*~~*~~*~~*~~*~"    << '\n';
  std::cout << " Thank you for visiting! :D"     << '\n';
  std::cout << "~*~~*~~*~~*~~*~~*~~*~~*~~*~~"    << '\n';
  std::cout << "         ___                   " << '\n';
  std::cout << "    __/_  `.  .-\"\"\"-.       " << '\n'; 
  std::cout << "    \\_,` | \\-'  /   )`-')    " << '\n';  
  std::cout << "     \"\") `\"`    \\  ((`\"`  " << '\n'; 
  std::cout << "    ___Y  ,    .'7 /|          " << '\n';
  std::cout << "   (_,___/...-` (_/_/          " << '\n';
  std::cout <<                                      '\n';
  std::cout << "(artwork from asciiart.eu)"      << '\n';
  std::cout <<                                      '\n';
}

void printAsciiDog() {
  std::cout << "           __        "      << '\n';
  std::cout << "      (___()'`;      "      << '\n';
  std::cout << "      /,    /`       "      << '\n';
  std::cout << "      \\\\\"--\\\\   "      << '\n';
  std::cout << '\n';
  std::cout << "(artwork from asciiart.eu)" << '\n';
}


void printAsciiCat() {
  std::cout << "   _._     _,-'\"\"`-._  "  << '\n';
  std::cout << "(,-.`._,'(       |\\`-/| "  << '\n';
  std::cout << "    `-.-' \\ )-`( , o o) "  << '\n';
  std::cout << "          `-    \\`_`\"'-"  << '\n';
  std::cout << '\n';
  std::cout << "(artwork from asciiart.eu)" << '\n';
}

void printBanner(std::string title) {
  std::string separator_bar (title.size(),'-');
  std::cout << separator_bar << '\n';
  std::cout << title << '\n';
  std::cout << separator_bar << '\n';
}

// Main Menu
void printMenu() {
  clearScreen();
  printBanner("Commonwealth Animal Shelter");
  std::cout <<                                  '\n';
  std::cout << "(V)iew animals"              << '\n';
  std::cout << "(N)ew animal"                << '\n';
  std::cout << "(A)dopt"                     << '\n';
  std::cout << "-----------"                 << '\n';
  std::cout << "(X) to exit"                 << '\n';
  std::cout <<                                  '\n';
  std::cout << "Choice: ";
}

// View animals
void printAnimals(AnimalShelter& shelter) {
  printBanner("Animals");
  std::cout << "Dogs:" << '\n';
  std::cout << shelter.dogsToString();
  std::cout << '\n';
  std::cout << '\n';
  std::cout << "Cats:" << '\n';
  std::cout << shelter.catsToString();
  std::cout << '\n';
  std::cout << '\n';
  std::cout << "Press [enter] to return to menu";
  std::cin.ignore();
  std::cin.get();
}

// Add new animal to shelter
void createNewAnimal(AnimalShelter& shelter) {
  std::cin.ignore();
  printBanner("New Animal");
  std::string name;
  AnimalType type;

  std::string s_choice;
  bool waitingForChoice = true;
  char choice;

  std::cout << "(D)og or (C)at?: ";
  
  while(waitingForChoice) {
    std::getline(std::cin, s_choice);

    // [Enter] quits this menu
    if(s_choice.empty()) {
      return;
    } 
    else {
      choice = toupper(s_choice[0]);
    }
  
    switch(choice) {
      case 'D': {
        waitingForChoice = false;
        type = Dog;
        break;
      }
      case 'C': {
        waitingForChoice = false;
        type = Cat;
        break;
      }
      default: {
        
        break;
      }
    }
  }

  std::cout << "Name: ";
  std::cin >> name;

  Animal newAnimal(type, name);
  shelter.enqueue(newAnimal);
}


// used in processAdopt
void printCongratulations(Animal animal) {
  clearScreen();
  std::cout << "~*~~*~~*~~*~~*~~*~" << '\n';
  std::cout << " Congratulations! " << '\n';
  std::cout << "~*~~*~~*~~*~~*~~*~" << '\n';
  std::cout << '\n';
  std::cout << " You adopted " << animal.name << "!" << '\n';
  std::cout << '\n';
  
  if(animal.animal_type == Dog) {
    printAsciiDog();
  }
  else {
    printAsciiCat();
  }

  std::cout << "Press [enter] to return to menu";
  std::cin.get();
}

// Adopt an animal
void processAdopt(AnimalShelter& shelter) {
  std::cin.ignore(); // ignore 1 newline '\n'

  std::cout << "Which animal would you like to adopt?" << '\n';
  std::cout << '\n';
  std::cout << "(D)og: " << shelter.getFrontDogAsString() << '\n';
  std::cout << "(C)at: " << shelter.getFrontCatAsString() << '\n';
  std::cout << "(O)ldest: " 
            << shelter.getFrontAnimalAsString() << '\n';
  std::cout << '\n';

  bool waitingForChoice = true;
  char choice;
  std::string s_choice;

  while(waitingForChoice) {
    // if(std::cin.get() == '\n') {
    //   break;
    // }
    std::cout << "Choice: ";
    std::getline(std::cin, s_choice);

    // [Enter] quits this menu
    if(s_choice.empty()) {
      return;
    }
    else {
      choice = toupper(s_choice[0]);
    }

    switch(choice) {
      case 'D': {
        if(shelter.totalDogs() > 0) {
          waitingForChoice = false;
          printCongratulations(shelter.getFrontDog());
          shelter.dequeueDog();
        }
        else {
          std::cout << "No dogs available, sorry!" << '\n';
        }
        break;
      }
      case 'C': {
        if(shelter.totalCats() > 0) {
          waitingForChoice = false;
          printCongratulations(shelter.getFrontCat());
          shelter.dequeueCat();
        }
        else {
          std::cout << "No cats available, sorry!" << '\n';
        }
        break;
      }
      case 'O': {
        if(shelter.totalAnimals() > 0) {
          waitingForChoice = false;
          printCongratulations(shelter.getFrontAnimal());
          shelter.dequeueAny();
        }
        else {
          std::cout << "No animals available, sorry!" << '\n';
        }
        break;
      }
      default: {
        waitingForChoice = false;
        break;
      }
    }
  }
}



int main() {
  AnimalShelter shelter;
  bool userWishesToContinue = true;

  while(userWishesToContinue) {
    printMenu();
    char choice;
    std::cin >> choice;
    choice = toupper(choice);
    // Redraw screen
    clearScreen();
    switch(choice) {
      case 'V': {
        printAnimals(shelter);
        break;
      }
      case 'N': {
        createNewAnimal(shelter);
        break;
      }
      case 'A': {
        processAdopt(shelter);
        break;
      }
      case 'X': {
        userWishesToContinue = false;
        printGoodbye();
        break;
      }
      default: break;
    }
  }
  return 0;
}
