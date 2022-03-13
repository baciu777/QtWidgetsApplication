#pragma once
#include "domain.h"

class CosGUICuLista : public QWidget, public Observer {
private:
    CosActivity& cos;
    QListWidget* lst;
    QPushButton* btn;
    QPushButton* btnRandom;

    void loadList(const std::vector<Activity>& activities) {
        lst->clear();
        for (auto& p : activities) {
            lst->addItem(QString::fromStdString(p.getname()));
        }
    }
    void initGUI() {
        QHBoxLayout* ly = new QHBoxLayout;
        lst = new QListWidget;
        ly->addWidget(lst);
        btn = new QPushButton("Clear cos");
        ly->addWidget(btn);

        btnRandom = new QPushButton("Add random 3");
        ly->addWidget(btnRandom);
        
       
        setLayout(ly);
    }
    void connectSignals() {
        cos.addObserver(this);
        QObject::connect(btn, &QPushButton::clicked, [&]() {
            cos.goleste();
            
            loadList(cos.lista());
            });
        QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
            cos.umple(3);
            loadList(cos.lista());
            });

    }
public:
    CosGUICuLista(CosActivity& cos) :cos{ cos } {
        initGUI();
        connectSignals();
        loadList(cos.lista());
    }

    void update() override {
        loadList(cos.lista());
    }

    ~CosGUICuLista() {
        cos.removeObserver(this);
    }

};
