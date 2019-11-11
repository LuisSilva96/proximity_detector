# include "auto_panel.h"

Auto_panel::Auto_panel(QWidget * parent)
  : QWidget(parent)
{
  setWindowFlags(Qt::CustomizeWindowHint);

  this->resize(WIDTH, HEIGHT);

  move(QApplication::desktop()->screen()->rect().center() - rect().center());
}

Auto_panel::~Auto_panel()
{
	//empty
}

void Auto_panel::paintEvent(QPaintEvent *)
{
}

void Auto_panel::closeEvent(QCloseEvent *)
{
  this->~Auto_panel();
}

void Auto_panel::keyPressEvent(QKeyEvent * evt)
{
  switch (evt->key())
  {
    case Qt::Key_Escape:
    {  
    	menu->show();
      setVisible(false);
    }
    break;
  }
}
