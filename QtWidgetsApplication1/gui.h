#pragma once
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>
#include <QtWidgets/qspinbox.h>
#include <string>
#include <qdebug.h>
#include "basketactivity.h"
#include "histogramgui.h"
#include "modelview.h"
using std::string;
#include "service.h"
class GUI :public QWidget
{
public:
    GUI(Service& serv, Service& servbucket, CosActivity& cos) :serv{ serv }, servbucket{ servbucket }, cos{ cos }
	{
        
        initGUI();
        model = new MyTableModel{ serv.getAll() };
        loadData(serv.getAll());
        initConnect();
	}
    void setbucket();
private:
    Service& serv;
    Service& servbucket;
    CosActivity& cos;
    MyTableModel* model;
    QListWidget* lst = new QListWidget;

    QPushButton* btnExit = new QPushButton{ "&Exit" };
    QPushButton* btnAdd = new QPushButton{ "&Add" };
    QLineEdit* txtname = new QLineEdit;
    QLineEdit* txtdescription = new QLineEdit;
    QLineEdit* txttype = new QLineEdit;
    //QLineEdit* txtduration = new QLineEdit;
    QSpinBox* txtduration = new QSpinBox;
    QPushButton* btnDelete = new QPushButton{ "delete" };
    QPushButton* btnUpdate = new QPushButton{ "Update" };
    QPushButton* btnSortName = new QPushButton{ "sort name" };
    QPushButton* btnSortDesc = new QPushButton{ "sort descripition" };
    QPushButton* btnSortTypeDesc = new QPushButton{ "sort type+desc" };
    QPushButton* btnFilterDesc = new QPushButton{ "filter desc" };
    QPushButton* btnFilterType = new QPushButton{ "filter type" };
    QPushButton* btnPrint = new QPushButton{ "PRINT" };
    QPushButton* btnUndo = new QPushButton{ "Undo" };
    QPushButton* btnRaport = new QPushButton{ "Raport" };
    QPushButton* btnBucket = new QPushButton{ "Bucket" };
    QPushButton* btnbasketcrud = new QPushButton{ "BucketCRUD" };
    QPushButton* btncrudadd = new QPushButton{ "add basket crud" };
    QPushButton* btncruddel = new QPushButton{ "del basket crud" };
    QPushButton* btnreadbucket = new QPushButton{ "Bucket read" };
    //QPushButton* btncrud = new QPushButton{ "BucketCRUD" };
    
    //QTableWidget* table = new QTableWidget{ 0,4 };
    QTableView* table = new QTableView;
    void initGUI();
    void loadData(const vector<Activity>& activities);
    void initConnect();
    void addGUI();
    void addGUIcrud();
    void updGUI();
    void delGUI();
    void delGUIcrud();
    void undoGUI();
    void raportGUI();


};

class SmallGUI :public QDialog
{
private:
    GUI* gui;//dam pointer doar pentru a face susta cu butonu de bucket sa nu se reapeleze cand vrea el
    Service& serv;
    Service& servbucket;
    QListWidget* lst = new QListWidget;
    QLabel* lbl = new QLabel{ "nothing" };
    QPushButton* btnadd = new QPushButton{ "add" };
    QPushButton* btnaddrandom = new QPushButton{ "add random" };
    QPushButton* btnclear = new QPushButton{ "clear" };
    QPushButton* btnexport = new QPushButton{ "export" };  
    QPushButton* btnexit = new QPushButton{ "&Exit" };


    QLineEdit* txtname = new QLineEdit;
    QLineEdit* txtdescription = new QLineEdit;
    QLineEdit* txttype = new QLineEdit;
    //QLineEdit* txtduration = new QLineEdit;
    QSlider* txtduration = new QSlider;
    QLabel* lbdurmin = new QLabel;
    QLabel* lbdurmax = new QLabel;
    QLabel* lbdurcurent = new QLabel;

    QLineEdit* txtr = new QLineEdit;
    QLineEdit* txtf = new QLineEdit;

public:
    SmallGUI(GUI* gui, Service& serv, Service& servbucket) :gui{ gui },serv { serv }, servbucket{ servbucket }
    {
        initSmall();
        
        initConnect();
        
    }

    void initSmall();
    void initConnect();
    void reloaddata();
    void add();
    void addrandom();
    void clear();
    void bexport();

};
