# include <object.h>

Object::Object(int & x, int & y, int & height, int & width, int & color)
{
  create_palette();
  object = new QRect(x, y, width, height);

  brush = new QBrush(QColor(palette[color][0],palette[color][1],palette[color][2]));

  position.setX(x);
  position.setY(y);

}

void Object::create_palette()
{
  palette[0][0] = 240;
  palette[0][1] = 98;
  palette[0][2] = 146;

  palette[1][0] = 156;
  palette[1][1] = 39;
  palette[1][2] = 176;

  palette[2][0] = 244;
  palette[2][1] = 67;
  palette[2][2] = 54;

  palette[3][0] = 81;
  palette[3][1] = 45;
  palette[3][2] = 168;

  palette[4][0] = 48;
  palette[4][1] = 63;
  palette[4][2] = 159;

  palette[5][0] = 25;
  palette[5][1] = 118;
  palette[5][2] = 210;

  palette[6][0] = 1;
  palette[6][1] = 87;
  palette[6][2] = 155;

  palette[7][0] = 0;
  palette[7][1] = 131;
  palette[7][2] = 143;

  palette[8][0] = 0;
  palette[8][1] = 105;
  palette[8][2] = 92;

  palette[9][0] = 67;
  palette[9][1] = 160;
  palette[9][2] = 71;

  palette[10][0] = 124;
  palette[10][1] = 179;
  palette[10][2] = 66;

  palette[11][0] = 175;
  palette[11][1] = 180;
  palette[11][2] = 43;

  palette[12][0] = 251;
  palette[12][1] = 192;
  palette[12][2] = 45;

  palette[13][0] = 121;
  palette[13][1] = 85;
  palette[13][2] = 72;

  palette[14][0] = 117;
  palette[14][1] = 117;
  palette[14][2] = 117;
}

QRect Object::get_rect()
{
  return *object;
}

int Object::get_x()
{
  return position.x();
}

int Object::get_y()
{
  return position.y();
}

QVector2D Object::get_position()
{
  return position;
}

int Object::height()
{
  return object->height();
}

int Object::width()
{
  return object->width();
}

void Object::draw(QPainter & painter)
{
  painter.fillRect(*object, get_brush());
}

QBrush Object::get_brush()
{
  return *brush;
}

Object::~Object()
{
  //empty
}
