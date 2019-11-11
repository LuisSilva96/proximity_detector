# ifndef MENU_H
# define MENU_H

//QT INCLUDES
# include <QWidget>
# include <QPixmap>
# include <QPainter>
# include <QKeyEvent>
# include <QTimer>
# include <QDesktopWidget>
# include <QApplication>

//ALEPH INCLUDES
# include <ahNow.H>

//SENSOR INCLUDES
# include <manual_panel.h>
# include <auto_panel.h>
# include <iostream>

class Manual_panel;
class Auto_panel;
class Menu;
extern Menu * menu;

class Menu : public QWidget
{
  Q_OBJECT

  private:
    Manual_panel * manual_panel;
    Auto_panel * auto_panel;
    QPixmap background;
    QPixmap background1;
    QPixmap * arrows[5];
    QPixmap * options[5];
    QTimer timer;
    int position;
    bool is_paused = false;
    bool automatic = false;

    bool animation = false;
    int animation_position = 0;

  public:
    static constexpr int WIDTH  = 1024;
    static constexpr int HEIGHT = 920;

    Menu(QWidget * parent = nullptr);
    ~Menu();

    void change_position(int &&);
    void arrow_animation();
    void choice();

    void closeEvent(QCloseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

  public slots:
    void slot_update();

};

# endif
