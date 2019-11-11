# ifndef AUTOPANEL_H
# define AUTOPANEL_H

# include <QWidget>
# include <QKeyEvent>
# include <QPainter>
# include <QDesktopWidget>
# include <QApplication>

# include <menu.h>

class Auto_panel : public QWidget
{
  Q_OBJECT

  private:


  public:
    static constexpr int WIDTH  = 1024;
    static constexpr int HEIGHT = 920;

    Auto_panel(QWidget * parent = nullptr);
    ~Auto_panel();

    void closeEvent(QCloseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

};

# endif
