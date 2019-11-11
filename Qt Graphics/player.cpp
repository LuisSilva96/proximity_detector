# include "player.h"

Player::Player()
{
  player.load(":/simulation/sprites/circulito.png");
  sensor[0][0].load(":/simulation/sprites/UP3.png");
  sensor[0][1].load(":/simulation/sprites/UP2.png");
  sensor[0][2].load(":/simulation/sprites/UP.png");
  sensor[1][0].load(":/simulation/sprites/DOWN3.png");
  sensor[1][1].load(":/simulation/sprites/DOWN2.png");
  sensor[1][2].load(":/simulation/sprites/DOWN.png");
  sensor[2][0].load(":/simulation/sprites/RIGHT3.png");
  sensor[2][1].load(":/simulation/sprites/RIGHT2.png");
  sensor[2][2].load(":/simulation/sprites/RIGHT.png");
  sensor[3][0].load(":/simulation/sprites/LEFT3.png");
  sensor[3][1].load(":/simulation/sprites/LEFT2.png");
  sensor[3][2].load(":/simulation/sprites/LEFT.png");

  position.setX(20);
  position.setY(20);
  player_rect = new QRect(20,20, player.width(), player.height());
}

Player::~Player()
{
  //empty
}

void Player::update_rect()
{
  QRect * new_rect = new QRect(position.x(),position.y(),player_rect->width(),
    player_rect->height());
  player_rect = new_rect;
}

void Player::proximity(list<Object> & objects)
{

  QVector2D tmp, tmp1;
  bool aux_n = false, aux_s = false, aux_e = false, aux_o = false;
  north = 2000;
  south = 2000;
  east = 2000;
  west = 2000;

  float temporal;

  for (auto object : objects)
  {
    for(int i = object.get_x(); i <= object.get_x() + object.width(); i++)
    {
      if(i >= position.x() && i <= position.x() + player_rect->width()
          && position.y() >= object.get_y() )
      {
        tmp.setX(position.x());
        tmp.setY(position.y());

        tmp1.setX(position.x());
        tmp1.setY(object.get_y() + object.height());

        temporal = tmp.distanceToPoint(tmp1);
        if(temporal < north)
        {
          north = temporal;
          aux_n = true;
        }
      }
      else if(i >= position.x() && i <= position.x() + player_rect->width()
          && position.y() <= object.get_y())
      {
        tmp.setX(position.x());
        tmp.setY(position.y() + player_rect->height());

        tmp1.setX(position.x());
        tmp1.setY(object.get_y());

        temporal = tmp.distanceToPoint(tmp1);
        if(temporal < south)
        {
          south = temporal;
          aux_s = true;
        }

      }
    }

    if(aux_n == false)
      north = 2000;
    if(aux_s == false)
      south = 2000;

    for(int i = object.get_y(); i <= object.get_y() + object.height(); i++)
    {
      if(i >= position.y() && i <= position.y() + player_rect->height()
          && position.x() <= object.get_x())
      {
        tmp.setX(position.x()+ player_rect->width());
        tmp.setY(position.y());

        tmp1.setX(object.get_x());
        tmp1.setY(position.y());

        temporal = tmp.distanceToPoint(tmp1);
        if(temporal < east)
        {
          east = temporal;
          aux_e = true;
        }
      }
      if(i >= position.y() && i <= position.y() + player_rect->height()
          && position.x() >= object.get_x())
      {
        tmp.setX(position.x());
        tmp.setY(position.y());

        tmp1.setX(object.get_x() + object.width());
        tmp1.setY(position.y());

        temporal = tmp.distanceToPoint(tmp1);
        if(temporal < west)
        {
          west = temporal;
          aux_o = true;
        }
      }
    }

    if(aux_e == false)
      east = 2000;
    if(aux_o == false)
      west = 2000;
  }
/*
  std::cout << "North: " << north << std::endl;
  std::cout << "South: " << south << std::endl;
  std::cout << "East: " << east << std::endl;
  std::cout << "West: " << west << std::endl;
*/
}

QPixmap Player::proximity_sprite()
{
  int i, j = 3;
  float min = 2000;

  if(north < south && north < east && north < west)
  {
    min = north;
    i = 0;
  }
  else if(south < north && south < east && south < west)
  {
    min = south;
    i = 1;
  }
  else if(east < north && east < south && east < west)
  {
    min = east;
    i = 2;
  }
  else if(west < north && west < south && west < east)
  {
    min = west;
    i = 3;
  }

  if(min <= 20)
    j = 2;
  else if (min > 20 && min < 80)
    j = 1;
  else if(min >= 80 && min < 140)
    j = 0;

  if(j == 3)
    return player;

  return sensor[i][j];

}

void Player::draw(QPainter & painter)
{
  painter.drawPixmap(position.x(), position.y(), player);
  painter.drawPixmap(position.x(), position.y(), proximity_sprite());
}

QRect Player::get_rect()
{
  return *player_rect;
}

bool Player::colliding_player(list<Object> & objects, int && i, int && j)
{
  bool flag = false;

  QRect * look_up = new QRect(player_rect->x()+i, player_rect->y()+j,
    player_rect->height(), player_rect->width());

  for (auto object : objects)
  {
    QRect tmp = object.get_rect();
    flag = tmp.intersects(*look_up);
    if(flag)
      break;
  }

  if(look_up->x() < 0 || look_up->x() > 920 || look_up->y() < 0 || look_up->y() > 820)
    flag = true;

  return flag;
}

void Player::move(QKeyEvent * evt, list<Object> & objects)
{
  if(evt->key() == Qt::Key_Up or evt->key() == Qt::Key_Down
    or evt->key() == Qt::Key_Left or evt->key() == Qt::Key_Right)
  {
    keys_pressed.insert(evt->key());
  }

  if (keys_pressed.size() == 1)
  {
    switch (evt->key())
    {
      case Qt::Key_Up:
      {
        if(not(colliding_player(objects, 0, -8)))
        {
          position.setY(position.y() - SPEED);
        }
      }
      break;
      case Qt::Key_Down:
      {
        if(not(colliding_player(objects, 0, 8)))
        {
          position.setY(position.y() + SPEED);
        }
      }
      break;
      case Qt::Key_Right:
      {
        if(not(colliding_player(objects, 8, 0)))
        {
          position.setX(position.x() + SPEED);
        }
      }
      break;
      case Qt::Key_Left:
      {
        if(not(colliding_player(objects, -8, 0)))
        {
          position.setX(position.x() - SPEED);
        }
      }
      break;
    }
  }

  if (keys_pressed.size() > 1)
  {
    if (keys_pressed.contains(Qt::Key_Up) and keys_pressed.contains(Qt::Key_Right))
    {
      if(not(colliding_player(objects, 8, -8)))
      {
        position.setY(position.y() - SPEED);
        position.setX(position.x() + SPEED);
        update_rect();
      }
    }
    if (keys_pressed.contains(Qt::Key_Up) and keys_pressed.contains(Qt::Key_Left))
    {
      if(not(colliding_player(objects, -8, -8)))
      {
        position.setY(position.y() - SPEED);
        position.setX(position.x() - SPEED);
        update_rect();
      }
    }
    if (keys_pressed.contains(Qt::Key_Down) and keys_pressed.contains(Qt::Key_Right))
    {
      if(not(colliding_player(objects, 8, 8)))
      {
        position.setY(position.y() + SPEED);
        position.setX(position.x() + SPEED);
        update_rect();
      }
    }
    if (keys_pressed.contains(Qt::Key_Down) and keys_pressed.contains(Qt::Key_Left))
    {
      if(not(colliding_player(objects, -8, 8)))
      {
        position.setY(position.y() + SPEED);
        position.setX(position.x() - SPEED);
        update_rect();
      }
    }
  }

  update_rect();
  proximity(objects);

}

int Player::get_x()
{
  return position.x();
}

int Player::get_y()
{
  return position.y();
}

void Player::set_x(int && x)
{
  position.setX(x);
}

void Player::set_y(int && y)
{
  position.setY(y);
}

void Player::release_key(QKeyEvent *evt)
{
  keys_pressed.remove(evt->key());
}
