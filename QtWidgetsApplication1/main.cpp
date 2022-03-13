#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qpushbutton.h>

#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets\qformlayout.h>
#include <QtWidgets\qgridlayout.h>
#include "QtWidgetsApplication1.h"


#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "domain.h"
#include "tests.h"
#include "service.h"
#include "ui.h"
#include "validator.h"
#include "repolab.h"
#include "gui.h"
#include "basketgui.h"
#include "histogramgui.h"
#include "LocatarRepoFile.h"
int main(int argc, char *argv[])
{


    all_tests();
_CrtDumpMemoryLeaks();


    printf("Baciu\n");
    printf("\n");
    Repository repo;
    ActivityValidator val;
    RepoFile repofile("merge.txt");
    //Repositorylab repo((float)0.5);
    Service serv{ repofile ,val };
    Repository repobucket;
    ActivityValidator valbucket;
    Service servbucket{ repobucket ,valbucket };

    QApplication a(argc, argv);
    CosActivity cos{ serv };
    GUI gui{ serv ,servbucket,cos};
    gui.show();
   
        std::cout << "\nEND\n";
  
      
     a.exec();
      
        return 0;
}
