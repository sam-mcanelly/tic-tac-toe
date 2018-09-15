#include "UTGraph.h"

void UTGraph::create() {
    display->drawFastVLine(1, 1, 50, WHITE);
    display->drawFastHLine(1, 50, 125, WHITE);
    display->display();
}