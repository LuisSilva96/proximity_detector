# ifndef PLAYER_H
# define PLAYER_H

# include <QPixmap>
# include <QPainter>
# include <QVector2D>
# include <QKeyEvent>
# include <QSet>
# include <QRect>

# include <object.h>

# include <list>

using namespace std;

class Player
{
  private:
    QPixmap player;
    QPixmap sensor[4][3];
    QVector2D position;
    float north = 2000;
    float south = 2000;
    float east = 2000;
    float west = 2000;
    QSet<int> keys_pressed;
    QRect * player_rect;

  public:
    static constexpr int SPEED = 6;

    Player();
    ~Player();

    void update_rect();
    void proximity(list<Object> &);
    QPixmap proximity_sprite();
    void draw(QPainter &);
    void move(QKeyEvent *, list<Object> &);
    int get_x();
    int get_y();
    void set_x(int &&);
    void set_y(int &&);
    QRect get_rect();
    bool colliding_player(list<Object> &, int &&, int &&);
    void release_key(QKeyEvent *);

};

# endif
