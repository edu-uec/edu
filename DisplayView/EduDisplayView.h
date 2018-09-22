//
// Created by 松田尚也 on 2018/09/20.
//

#ifndef EDU_SOFTWARE_CPP_EDUDISPLAYVIEW_H
#define EDU_SOFTWARE_CPP_EDUDISPLAYVIEW_H


class DisplayViewBase{
public:
    bool update_LOOP = true;
    //virtual void update(){};
};

class TitleDisplayView : public DisplayViewBase{
public:
    void update();
};

#endif //EDU_SOFTWARE_CPP_EDUDISPLAYVIEW_H