#include <iostream>
#include <cstdlib>
#include "Animal_Shelter.cpp"


// Note: This works only on Windows.
void clearScreen() {
  std::system("cls");
}

void printBanner() {
  std::cout << "===========================" << '\n';
  std::cout << "Commonwealth Animal Shelter" << '\n';
  std::cout << "===========================" << '\n';
}

void printBlankLines(int n) {
  while(n--) { std::cout << '\n'; }
}

void printMenu() {
  printBanner();
  printBlankLines(1);
  std::cout << "(V)iew animals"              << '\n';
  std::cout << "(N)ew animal"                << '\n';
  std::cout << "(A)dopt"                     << '\n';
  std::cout                                  << '\n';
  std::cout << "(X) to exit"                 << '\n';
}

void printGoodbye() {
  std::cout << "~~*~~*~~*~~*~~*~~*~~*~~*~~*~" << '\n';
  std::cout << " Thank you for visiting! :D"  << '\n';
  std::cout << "~*~~*~~*~~*~~*~~*~~*~~*~~*~~" << '\n';
}

void printAnimals(AnimalShelter& shelter) {
  printBanner();
  std::cout << "Dogs" << '\n';
  std::cout << shelter.dogsToString();
  std::cout << "Cats" << '\n';
  std::cout << shelter.catsToString();
}

void createNewAnimal(AnimalShelter& shelter) {
  std::cout << "Which animal would you like to adopt?" << '\n';
  printBlankLines(1);
  std::cout << "(D)og: " << shelter.getFrontDogAsString() << '\n';
  std::cout << "(C)at: " << shelter.getFrontCatAsString() << '\n';
  std::cout << "(L)ongest at shelter: " << '\n';
}

void processAdopt(AnimalShelter& shelter) {

}



int main() {
  // std::time_t current_time = std::time(nullptr);
  // struct tm* timeinfo = localtime(&current_time);
  // std::cout << "time_t: " << ctime(&current_time) << '\n';
  // std::cout << "struct tm: " << asctime(timeinfo) << '\n';
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
