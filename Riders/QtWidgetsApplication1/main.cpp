#include "QtWidgetsApplication1.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "Repo.h"
#include "GUI.h"
#include "Tests.h"

int main(int argc, char *argv[])
{
   // Tests t;
   // t.testAll();
    QApplication a(argc, argv);
    //QtWidgetsApplication1 w;
   //Tests t;
   // t.testAll();
    AstronomerRepo astronomers;
    StarRepo stars;
    AstroService a_service{ astronomers };
    StarService s_service{ stars };
    for (auto& item : astronomers.getRepo())
    {
        GUI* g = new GUI{item,s_service,a_service};
        g->show();
    }
    //w.show();
    return a.exec();
}
