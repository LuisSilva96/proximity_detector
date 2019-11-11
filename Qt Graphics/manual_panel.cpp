# include "manual_panel.h"

Manual_panel::Manual_panel(QWidget * parent)
  : QWidget(parent)
{
  setWindowFlags(Qt::CustomizeWindowHint);

  this->resize(WIDTH, HEIGHT);

  move(QApplication::desktop()->screen()->rect().center() - rect().center());

  background.load(":/simulation/sprites/simulationbackground.png");

  finish.load(":/simulation/sprites/objective.png");

  create_objects();

  change_finished();

  connect(&timer1, SIGNAL(timeout()), this, SLOT(slot_update()));

  timer1.setInterval(60);
  timer1.start();
}

Manual_panel::~Manual_panel()
{
	//empty
}

void Manual_panel::create_objects()
{
  srand(time(NULL));
  int roll_objects = rand() % 3 + 5;

  std::cout << roll_objects << std::endl;

  int roll_x, roll_y, height, width, color;

  for(int i = 0; i < roll_objects; i++)
  {
    roll_x = rand() % 950 + 1;
    roll_y = rand() % 850 + 1;
    while(roll_x + roll_y > 1400 || roll_x + roll_y < 500)
    {
      roll_x = rand() % 1024 + 1;
      roll_y = rand() % 920 + 1;
    }
    height = rand() % 100 + 100;
    width = rand() % 100 + 100;
    color = rand() % 14;

    Object * obj = new Object(roll_x,roll_y,height, width, color);

    if(colliding_objects(obj))
      i--;
    else
      objects.push_back(*obj);
  }
}

bool Manual_panel::colliding_objects(Object * obj)
{
  bool flag = false;

  for (auto object : objects)
  {
    QRect tmp = object.get_rect();
    flag = tmp.intersects(obj->get_rect());
    if(flag)
      break;
  }

  return flag;
}

bool Manual_panel::get_finished()
{
  return finished;
}

void Manual_panel::change_finished()
{
  if(finished)
    finished = false;
  else
    finished = true;
}

void Manual_panel::slot_update()
{

  repaint();
}

void Manual_panel::paintEvent(QPaintEvent *)
{
  QPainter painter1(this);

  setWindowState(Qt::WindowActive);

  painter1.drawPixmap(0, 0, background);

  painter1.drawPixmap(10,10,finish);
  painter1.drawPixmap(900,800,finish);

  position_finish.setX(900);
  position_finish.setY(800);

  for (auto obj : objects)
    obj.draw(painter1);

  player.draw(painter1);

}

void Manual_panel::closeEvent(QCloseEvent *)
{
  this->~Manual_panel();
}

bool Manual_panel::check_wining()
{
  if(player.get_x() >= 890 && player.get_x() <= 910)
    if(player.get_y() >= 790 && player.get_y() <= 810)
    {
      return true;
    }
  return false;
}

void Manual_panel::keyPressEvent(QKeyEvent * evt)
{
  switch (evt->key())
  {
    case Qt::Key_Up:
    {
        player.move(evt, objects);
    }
    break;
    case Qt::Key_Down:
    {
        player.move(evt, objects);
    }
    break;
    case Qt::Key_Right:
    {
        player.move(evt, objects);
    }
    break;
    case Qt::Key_Left:
    {
        player.move(evt, objects);
    }
    break;
    case Qt::Key_Escape:
    {
    	menu->show();
      setVisible(false);
    }
    break;
  }

  if(check_wining())
  {
    //player.set_x(20);
    //player.set_y(20);
    finished = true;
    menu->show();
    setVisible(false);
  }
}

void Manual_panel::keyReleaseEvent(QKeyEvent * evt)
{
  player.release_key(evt);
}
