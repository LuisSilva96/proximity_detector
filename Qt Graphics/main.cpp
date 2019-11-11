# include <QApplication>
# include <menu.h>

Menu * menu;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  menu = new Menu();
  menu->show();

  return app.exec();
}
