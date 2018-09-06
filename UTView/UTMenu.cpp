#include "UTView.h"
#include "UTMenu.h"

void UTMenu::create() {
     //create border for menu
    display->fillRect(0, 10, 70, 42, BLACK);
    display->drawRect(0, 10, 70, 42, WHITE);

    drawMenuViewButtons();

    display->display();
}