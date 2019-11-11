# include "menu.h"

Menu::Menu(QWidget * parent)
  : QWidget(parent)
{
  setWindowFlags(Qt::CustomizeWindowHint);

  background.load(":/menu/sprites/background.jpg");
  background1.load(":/menu/sprites/background1.jpg");
  arrows[0] = new QPixmap(":/menu/sprites/1.jpg");
  arrows[1] = new QPixmap(":/menu/sprites/5.jpg");
  arrows[2] = new QPixmap(":/menu/sprites/4.jpg");
  arrows[3] = new QPixmap(":/menu/sprites/3.jpg");
  arrows[4] = new QPixmap(":/menu/sprites/2.jpg");

  options[0] = new QPixmap(":/menu/sprites/manual.png");
  options[1] = new QPixmap(":/menu/sprites/auto.png");
  options[2] = new QPixmap(":/menu/sprites/exit.png");
  options[3] = new QPixmap(":/menu/sprites/continue.png");
  options[4] = new QPixmap(":/menu/sprites/menu.png");

  this->resize(WIDTH, HEIGHT);

  move(QApplication::desktop()->screen()->rect().center() - rect().center());

  position = 0;

  connect(&timer, SIGNAL(timeout()), this, SLOT(slot_update()));

  timer.setInterval(60);
  timer.start();

}

Menu::~Menu()
{
	//empty
}

void Menu::slot_update()
{

  arrow_animation();

  repaint();
}

void Menu::paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  setWindowState(Qt::WindowActive);

  //std::cout << finished << std::endl;

  if(not (manual_panel->get_finished()))
  {
    painter.drawPixmap(0, 0, background);

    painter.drawPixmap(385, 356 + 85*(position), *arrows[animation_position]);

    if(not is_paused)
    {
      painter.drawPixmap(430, 353 + 85*(0), *options[0]);
      painter.drawPixmap(455, 353 + 85*(1), *options[1]);
    }
    else
    {
      painter.drawPixmap(415, 353 + 85*(0), *options[3]);
      painter.drawPixmap(440, 353 + 85*(1), *options[4]);
    }

    painter.drawPixmap(465, 353 + 85*(2), *options[2]);
  }
  else
    painter.drawPixmap(0, 0, background1);

}

void Menu::closeEvent(QCloseEvent *)
{
  this->~Menu();
}

void Menu::change_position(int && i)
{
  if(position + i < 0)
    position = 2;
  else if(position + i > 2)
    position = 0;
  else
    position += i;

}

void Menu::arrow_animation()
{
  if(animation)
  {
    if(animation_position > 3)
    {
      animation = false;
      animation_position = 0;
    }
    else
      animation_position++;
  }
}

void Menu::choice()
{
  switch(position)
  {
    case 0:
    {
      if(not is_paused)
      {
        is_paused = true;
        manual_panel = new Manual_panel();
        setVisible(false);
        manual_panel->show();

      }
      else
      {
        if(automatic)
          auto_panel->show();
        else
          manual_panel->show();
        setVisible(false);
      }

    }
    break;
    case 1:
    {
      if(not is_paused)
      {
        is_paused = true;
        automatic = true;
        auto_panel = new Auto_panel();
        auto_panel->show();
        setVisible(false);
      }
      else
        is_paused = false;
    }
    break;
    case 2:
    {
      close();
    }
    break;
  }
}

void Menu::keyPressEvent(QKeyEvent * evt)
{
  switch (evt->key())
  {
    case Qt::Key_Up:
    {
        change_position(-1);
        animation = true;
    }
    break;
    case Qt::Key_Down:
    {
        change_position(1);
        animation = true;
    }
    break;
    case Qt::Key_Return:
    {
      //std::cout << "se undio x!" << std::endl;
      //std::cout << "pause is: "<< is_paused << std::endl;
      if(not (manual_panel->get_finished()))
        choice();
      else
      {
        manual_panel->change_finished();
        is_paused = false;
      }
    }
    break;
  }
}
