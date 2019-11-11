# ifndef MANUALPANEL_H
# define MANUALPANEL_H

# include <QWidget>
# include <QKeyEvent>
# include <QPainter>
# include <QDesktopWidget>
# include <QApplication>
# include <QRect>
# include <QTimer>
# include <QPixmap>

# include <ahNow.H>

# include <menu.h>
# include <player.h>
# include <object.h>

# include <list>
# include <stdlib.h>
# include <time.h>
# include <QVector2D>
# include <iostream>


class Manual_panel : public QWidget
{
  Q_OBJECT

  private:
    QPixmap background;
    QTimer timer1;
    Player player;
    QPixmap finish;
    QVector2D position_finish;
    list<Object> objects;
    bool finished = true;

  public:
    static constexpr int WIDTH  = 1024;
    static constexpr int HEIGHT = 920;
    static constexpr int PWIDTH = 32;
    static constexpr int PHEIGHT = 32;

    Manual_panel(QWidget * parent = nullptr);
    ~Manual_panel();

    void create_objects();
    bool colliding_objects(Object *);
    bool check_wining();
    bool get_finished();
    void change_finished();

    void closeEvent(QCloseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;

  public slots:
      void slot_update();

};

# endif
