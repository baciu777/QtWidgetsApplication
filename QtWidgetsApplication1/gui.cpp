#include "gui.h"
#include <QtWidgets/qboxlayout.h>
#include <QString>
#include <QtWidgets/qtablewidget.h>
#include "basketgui.h"
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <chrono>

void GUI::initGUI()
{   

    QHBoxLayout* layout_main = new QHBoxLayout{};

    setLayout(layout_main);

    QVBoxLayout* ly11 = new QVBoxLayout{};
    ly11->addWidget(lst);
    QHBoxLayout* ly12 = new QHBoxLayout{};

    // colors
    btnDelete->setStyleSheet(" background-color: red ");
    btnAdd->setStyleSheet(" background-color: green ");
    btnUpdate ->setStyleSheet(" background-color: yellow ");

    ly12->addWidget(btnDelete);
    ly12->addWidget(btnFilterDesc);
    ly12->addWidget(btnFilterType);
    ly11->addLayout(ly12);

    QVBoxLayout* ly = new QVBoxLayout{};
    auto* ly1 = new QFormLayout;
    ly1->addRow("Nume", txtname);
    ly1->addRow("Description", txtdescription);
    ly1->addRow("Type", txttype);
    txtduration->setSuffix("seconds");
    ly1->addRow("Duration", txtduration);
    ly->addLayout(ly1);
    ly->addWidget(btnPrint);

    auto* lundo_bucket_raport = new QHBoxLayout{};
    lundo_bucket_raport->addWidget(btnUndo);
    lundo_bucket_raport->addWidget(btnBucket);
    
    ly->addItem(lundo_bucket_raport);
    auto* bucketcrud = new QHBoxLayout{};
    bucketcrud->addWidget(btnbasketcrud);
    bucketcrud->addWidget(btncrudadd);
    bucketcrud->addWidget(btncruddel);
    bucketcrud->addWidget(btnreadbucket);

    ly->addItem(bucketcrud);
    QVBoxLayout* ly2 = new QVBoxLayout{};
    ly2->addWidget(this->btnAdd);
    ly2->addWidget(btnUpdate);

    auto* ly3 = new QHBoxLayout{};
    ly3->addWidget(btnSortName);
    ly3->addWidget(btnSortDesc);
    ly3->addWidget(btnSortTypeDesc);
    ly3->addWidget(btnExit);
    ly->addLayout(ly2);
    ly->addLayout(ly3);

    layout_main->addLayout(ly11);
    layout_main->addLayout(ly);

    /*QTableWidgetItem* header0 = new QTableWidgetItem();
    header0->setText("Name");
    table->setHorizontalHeaderItem(0, header0);
    QTableWidgetItem* header1 = new QTableWidgetItem();
    header1->setText("Description");
    table->setHorizontalHeaderItem(1, header1);
    QTableWidgetItem* header2 = new QTableWidgetItem();
    header2->setText("Type");
    table->setHorizontalHeaderItem(2, header2);
    QTableWidgetItem* header3 = new QTableWidgetItem();
    header3->setText("Duration");
    table->setHorizontalHeaderItem(3, header3);
   */
    layout_main->addWidget(table);
    //layout_main->addStretch();
}
void GUI::initConnect()
{
    QObject::connect(this->btnExit, &QPushButton::clicked, [&]() {
        qDebug() << "GOODBYE";
        QMessageBox::information(nullptr, "info", "GOODBYE");
        close();
        });
    QObject::connect(this->btnAdd, &QPushButton::clicked, this, &GUI::addGUI);
    QObject::connect(this->btnUpdate, &QPushButton::clicked, this, &GUI::updGUI);
    QObject::connect(this->btnDelete, &QPushButton::clicked, this, &GUI::delGUI);
    QObject::connect(this->btnRaport, &QPushButton::clicked, this, &GUI::raportGUI);

    QObject::connect(this->btnBucket, &QPushButton::clicked, this, [&](){
        btnBucket->setEnabled(false);
                auto smallgui =new  SmallGUI{this,serv,servbucket};//facem pointeri sa nu fie doar local si sa ramana si dupa terminarea functie
                smallgui->show();
                qDebug()<<"gata";
                
            
        });
    QObject::connect(this->btnbasketcrud, &QPushButton::clicked, this, [&]() {
        //btnBucket->setEnabled(false);
         
        auto crudgui = new CosGUICuLista{ cos };
        crudgui->show();
        qDebug() << "gata";


        });
    QObject::connect(this->btnreadbucket, &QPushButton::clicked, this, [&]() {
        //btnBucket->setEnabled(false);

        auto readgui =new HistogramGUI { cos };
        readgui->show();
        qDebug() << "gata";


        });

    QObject::connect(this->btnPrint, &QPushButton::clicked, this, [&]()
        {loadData(serv.getAll());
        });
    QObject::connect(this->btnUndo, &QPushButton::clicked, this, &GUI::undoGUI);
    QObject::connect(this->btnSortDesc, &QPushButton::clicked, [&]()
        {loadData(serv.sortdesc());
        });
    QObject::connect(this->btnSortName, &QPushButton::clicked, [&]()
        {loadData(serv.sortname());
        });
    QObject::connect(this->btnSortTypeDesc, &QPushButton::clicked, [&]()
        {loadData(serv.sortTypeDescription());
        });
    QObject::connect(this->btnFilterDesc, &QPushButton::clicked, [&]()
        {auto desc = txtdescription->text();
    loadData(serv.filter1(desc.toStdString()));
        });
    QObject::connect(this->btnFilterType, &QPushButton::clicked, [&]()
        {auto type = txttype->text();
    loadData(serv.filter2(type.toStdString()));
        });


    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]()
        {auto sel = lst->selectedItems();
        if (sel.isEmpty()) 
        {

        txtname->setText("");
        txtdescription->setText("");
        txttype->setText("");
        //txtduration->setText(""); 
        txtduration->setSuffix("seconds");
        }
        else
        {
            auto selItem = sel.at(0);
            auto name=selItem->text();
            auto type = selItem->data(Qt::UserRole).toString();
            txtname->setText(name);
            txttype->setText(type);
            auto ac = serv.find(name.toStdString(), "a", type.toStdString(), 1);
            txtdescription->setText(QString::fromStdString(ac.getdescription()));
            //txtduration->setText(QString::number(ac.getduration()));
            txtduration->setValue((ac.getduration()));
            txtduration->setSuffix("seconds");
        }

        });



    QObject::connect(this->btncrudadd, &QPushButton::clicked, this, &GUI::addGUIcrud);
    QObject::connect(this->btncruddel, &QPushButton::clicked, this, &GUI::delGUIcrud);
}
void GUI::loadData(const vector<Activity>& activities)
{
    lst->clear();
    qDebug() << activities.size();
    int i = 0;
    //int nrl = int(serv.getAll().size()) + 1;
    //table->setRowCount(nrl);

    for (const auto& ac : activities)
    {
       
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(ac.getname()));
        item->setData(Qt::UserRole, QString::fromStdString(ac.gettype()));
        lst->addItem(item);

        //table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(ac.getname())));
        //table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(ac.getdescription())));
        //table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(ac.gettype())));
       // table->setItem(i, 3, new QTableWidgetItem(QString::number(ac.getduration())));
        i++;
    }
    table->setModel(model);
   
}
void GUI::addGUI()
{
    auto name = txtname->text().toStdString();
    auto description = txtdescription->text().toStdString();
    auto type = txttype->text().toStdString();
    auto duration = txtduration->text().toInt();
    try {
        serv.add(name, description, type, duration);
        loadData(serv.getAll());

    }
    catch ( ValidatorException& ex)
    {
        QLineEdit noc;
        for (const auto& el : ex.getMessage())
        {
            QString arc;
            arc = tr("%1\n").arg(QString::fromStdString(el));//susta
            noc.setText(noc.text() + arc);
        }
        QMessageBox::warning(this, "Warning", noc.text());
    }
    catch (RepoException& ex)
    {
        
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}
void GUI::addGUIcrud()
{
    auto name = txtname->text().toStdString();
    auto description = txtdescription->text().toStdString();
    auto type = txttype->text().toStdString();
    auto duration = txtduration->text().toInt();
    try {
        auto ceva = serv.find(name, description, type, duration);
        auto ac=Activity(name, description, type, duration);
        cos.adauga(ac);
        //loadData(serv.getAll());

    }
    catch (ValidatorException& ex)
    {
        QLineEdit noc;
        for (const auto& el : ex.getMessage())
        {
            QString arc;
            arc = tr("%1\n").arg(QString::fromStdString(el));//susta
            noc.setText(noc.text() + arc);
        }
        QMessageBox::warning(this, "Warning", noc.text());
    }
    catch (RepoException& ex)
    {

        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}
void GUI::updGUI()
{
    auto name = txtname->text().toStdString();
    auto description = txtdescription->text().toStdString();
    auto type = txttype->text().toStdString();
    auto duration = txtduration->text().toInt();
    try {
        serv.update(name, description, type, duration);
        loadData(serv.getAll());
    }
    catch (ValidatorException& ex)
    {
        QLineEdit noc;
        for (const auto& el : ex.getMessage())
        {
            QString arc;
            arc = tr("%1\n").arg(QString::fromStdString(el));//susta
            noc.setText(noc.text() + arc);
        }
        QMessageBox::warning(this, "Warning", noc.text());
    }
    catch (RepoException& ex)
    {

        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}
void GUI::delGUI()
{
    auto name = txtname->text().toStdString();
    auto type = txttype->text().toStdString();
    try {
        serv.delete_a(name, "a", type,1);
        loadData(serv.getAll());
    }
    catch (ValidatorException& ex)
    {
        QLineEdit noc;
        for (const auto& el : ex.getMessage())
        {
            QString arc;
            arc = tr("%1\n").arg(QString::fromStdString(el));//susta
            noc.setText(noc.text() + arc);
        }
        QMessageBox::warning(this, "Warning", noc.text());
    }
    catch (RepoException& ex)
    {

        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}
void GUI::delGUIcrud()
{
    auto name = txtname->text().toStdString();
    auto type = txttype->text().toStdString();
    try {
        auto ceva = serv.find(name, "1", type, 1);
  
        //serv.delete_a(name, "a", type, 1);
        cos.del(ceva);
        loadData(serv.getAll());
    }
    catch (ValidatorException& ex)
    {
        QLineEdit noc;
        for (const auto& el : ex.getMessage())
        {
            QString arc;
            arc = tr("%1\n").arg(QString::fromStdString(el));//susta
            noc.setText(noc.text() + arc);
        }
        QMessageBox::warning(this, "Warning", noc.text());
    }
    catch (RepoException& ex)
    {

        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}
void GUI::undoGUI()
{
    try {
        serv.UNDO();
        loadData(serv.getAll());
    }
    catch (RepoException& ex)
    {
        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }

}

void GUI::raportGUI()
{
    auto w = serv.raport_duration();
    std::unordered_map<int, Dto_duration>::iterator it = w.begin();
    lst->clear();
    while (it != w.end())
    {
        const int y = it->first;
        Dto_duration ob = it->second;
        string full = "Duration: " + std::to_string(y) +" " + "activities: " + std::to_string(ob.getNumber());
        it++;
        
        lst->addItem(QString::fromStdString(full));
    }
}

void GUI::setbucket()
{
    btnBucket->setEnabled(true);
}




void SmallGUI::initSmall()
{
    QHBoxLayout* lymain = new  QHBoxLayout;
    setLayout(lymain);
    auto* lyfirst = new QFormLayout;
    lyfirst->addWidget(lbl);
    lyfirst->addRow("random number", txtr);
    lyfirst->addRow("fisier .csv", txtf);
    lymain->addLayout(lyfirst);
    auto* ly1 = new QFormLayout;
    ly1->addRow("Nume", txtname);
    ly1->addRow("Description", txtdescription);
    ly1->addRow("Type", txttype);
    txtduration->setRange(0, 10);
    
    
    ly1->addRow("Duration", txtduration);
    lbdurmin->setText("0");
    ly1->addRow("Min", lbdurmin);
    lbdurmax->setText("10");
    ly1->addRow("Min", lbdurmax);
    lbdurcurent->setText("0");
    ly1->addRow("Min", lbdurcurent);
    lymain->addLayout(ly1);
    QVBoxLayout* ly2 = new  QVBoxLayout;
    ly2->addWidget(btnadd);
    ly2->addWidget(btnaddrandom);
    ly2->addWidget(btnclear);
    ly2->addWidget(btnexport);
    ly2->addWidget(btnexit);
    
    lymain->addLayout(ly2);
    
}
void SmallGUI::initConnect()
{
    QObject::connect(this->btnexit, &QPushButton::clicked, [&]() {
        qDebug() << "GOODBYE";
        QMessageBox::information(nullptr, "info", "GOODBYE");
        this->gui->setbucket();//facem asta doar pentru a debloca butonu de bucket

        close();
        });
    QObject::connect(this->btnadd, &QPushButton::clicked, this, &SmallGUI::add);
    QObject::connect(this->btnaddrandom, &QPushButton::clicked, this, &SmallGUI::addrandom);
    QObject::connect(this->btnclear, &QPushButton::clicked, this, &SmallGUI::clear);
    QObject::connect(this->btnexport, &QPushButton::clicked, this, &SmallGUI::bexport);
    QObject::connect(lst, &QListWidget::itemSelectionChanged, [&]()
        {auto sel = lst->selectedItems();
    if (sel.isEmpty())
    {

        txtname->setText("");
        txtdescription->setText("");
        txttype->setText("");
        //txtduration->setText("");
        txtduration->setValue(0);
        
    }
    else
    {
        auto selItem = sel.at(0);
        auto name = selItem->text();
        auto type = selItem->data(Qt::UserRole).toString();
        txtname->setText(name);
        txttype->setText(type);
        auto ac = serv.find(name.toStdString(), "a", type.toStdString(), 1);
        txtdescription->setText(QString::fromStdString(ac.getdescription()));
        //txtduration->setText(QString::number(ac.getduration()));
        txtduration->setValue(ac.getduration());
    }

        });


    QObject::connect(txtduration, &QSlider::valueChanged, this, [=]() {
        lbdurcurent->setText(QString::number(txtduration->value())); });
    

}
void SmallGUI::reloaddata()
{
    auto a = servbucket.getAll().size();
    lbl->setText(QString::number(a));
}
void SmallGUI::add()
{
    auto name = txtname->text().toStdString();
    auto description = txtdescription->text().toStdString();
    auto type = txttype->text().toStdString();
    //auto duration = txtduration->text().toInt();
    auto duration = txtduration->value();
    try {

        //Activity newe = serv.find(name, description, type, duration);
        Activity newe = serv.find(name, description, type, duration);
        servbucket.add(newe.getname(), newe.getdescription(), newe.gettype(), newe.getduration());
        reloaddata();
    }
    catch (ValidatorException& ex)
    {
        QLineEdit noc;
        for (const auto& el : ex.getMessage())
        {
            QString arc;
            arc = tr("%1\n").arg(QString::fromStdString(el));//susta
            noc.setText(noc.text() + arc);
        }
        QMessageBox::warning(this, "Warning", noc.text());
    }
    catch (RepoException& ex)
    {

        QMessageBox::warning(this, "Warning", QString::fromStdString(ex.getMessage()));
    }
}

void SmallGUI::addrandom()
{
    unsigned int nr = txtr->text().toInt();
    vector < Activity > v = serv.getAll();
    std::mt19937 const mt{ std::random_device{}() };
    std::uniform_int_distribution<> const dist(0, int(v.size()) - 1);

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    unsigned const int ss = unsigned int(seed);
    std::shuffle(v.begin(), v.end(), std::default_random_engine(ss));
    if (servbucket.getAll().size() + nr <= v.size())
    {
        int start = int(v.size()) - 1;
        while (nr)
        {
            Activity found = v.at(start);
            try {
                servbucket.add(found.getname(), found.getdescription(), found.gettype(), found.getduration());
                reloaddata();
                nr--;

            }
            catch (RepoException& ex)
            {
                cout << ex.getMessage() << endl;
            }
            start--;

        }
    }
    else QMessageBox::warning(this, "Warning", "the number given is to big");

}

void SmallGUI::clear()
{
    servbucket.clear_all();
    reloaddata();
}

void SmallGUI::bexport()
{
    string fName=txtf->text().toStdString();
    
    std::ofstream out;
    out.open(fName);
    if (fName.empty())
        QMessageBox::warning(this, "Warning", "Wrong excel file name!");
    out << "Name" << ";" << "Description" << ";" << "Type" << ";" << "Duration" << endl;
    for (auto& ac : servbucket.getAll())
    {
        out << ac.getname() << ";";
        out << ac.getdescription() << ";";
        out << ac.gettype() << ";";
        out << ac.getduration() << ";";
        out << std::endl;
    }

    out.close();
}
