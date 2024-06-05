//
// Created by twak on 11/11/2019.
//

#include "the_button.h"


void TheButton::init(TheButtonInfo* i) {
    setIcon( *(i->icon) );
    info =  i;
}

//added comment
void TheButton::clicked() {
    emit jumpTo(info);
}
