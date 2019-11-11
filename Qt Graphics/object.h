# ifndef OBJECT_H
# define OBJECT_H

# include <QPainter>
# include <QVector2D>
# include <QPolygon>
# include <QVector>
# include <QPoint>
# include <QBrush>
# include <QColor>

# include <gsl/gsl_rng.h>
# include <iostream>

class Object
{
  private:
    QRect * object;
    QVector2D position;
    QBrush * brush;
    int palette[15][3];

  public:
    Object(int &, int &, int &, int &, int &);
    ~Object();

    void create_palette();
    QRect get_rect();
    int get_x();
    int get_y();
    QVector2D get_position();
    int height();
    int width();
    void draw(QPainter &);
    QBrush get_brush();

};

# endif
