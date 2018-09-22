//
// Created by 松田尚也 on 2018/09/19.
//

#ifndef EDU_SOFTWARE_CPP_EDUCONTENT_H
#define EDU_SOFTWARE_CPP_EDUCONTENT_H



/*
 ここに書かれた変数やメソッドやクラスはこのファイルをインクルードすることで共有できるようになる。
 その処理は通例、別のcppファイルで実装する。(一応ここにも書けるが推奨されない)
 その際、実装の二重定義をするとエラーになるので注意。
*/
class ContentMasterBase{
public:
    bool update_LOOP = true;

    virtual void update();
    void call();
};

class TitleContentMaster : public ContentMasterBase{
public:
    void update() override;
};

#endif //EDU_SOFTWARE_CPP_EDUCONTENT_H