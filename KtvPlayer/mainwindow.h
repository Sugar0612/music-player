#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <map>
#include <QMap>
#include <QPair>
#include <QMessageBox>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QMouseEvent>
#include <list>
#include <QPair>

#include <QMainWindow>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QTableWidget>
#include <QHeaderView>
#include <QTimer>
#include <QLineEdit>
#include <QListWidgetItem>

#include "Control/NewButton.h"
#include "Control/newlable.h"
#include "Control/Newlistwidget.h"
#include "Control/LoginWidget/loginw.h"
#include "Control/LoginWidget/register.h"
#include "Control/LrcWidget/Lrcwgt.h"
#include "Control/SongListWidget/SongListWidget.h"
#include "Control/PlayListWidget/PlayList.h"
#include "Control/newtablewidget.h"

#include "Module/Network/network.h"
#include "Module/MusicPlayer/MusicPlayer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void Init();
    void Connect();

    void FontStyleInit();
    void ButtonInit();
    void LableInit();
    void ListWidgetInit();
    void TableInit();
    void TimerInit();
    void WinLayerInit();
    void WidgetInit();
    void LineEditInit();

    void NetworkInit();
    void MusicPlayerInit();
    void SqlInit();

    void ButtonSlot();
    void NetworkSlot();
    void WidgetSlot();
    void MusicPlayerSlot();
    void TableSlot();
    void SliderSlot();
    void TimerSlot();
    void ListWidgetSlot();
    void SqlSlot();

    void OpenWgt(QString name);
    QPixmap PixmapToRound (QPixmap pix, int radius);
private slots:

    void SetMinWindow(bool); //最小化屏幕

    void CloseWindow();

    void NetworkSearch();

    void BuildSearchTable(QVector<mst>);

    void SelectMusic(int row, int col); // 点击搜索窗口

    void SelectItemOperate(int row, int col);

    void MusicSliderValChanged(int);

    void BuildTimeLab(int, int);

    void VolumeSliderValChanged(int);

    void SelectSongListWidgetItem(QListWidgetItem*);

    void SelectSingerListWidgetItem(QListWidgetItem*);

    void SelectLanguListWidgetItem(QListWidgetItem*);

    void SelectDayListWidgetItem(QListWidgetItem*);

    void ClickedSearchButton();

    void RegisterUser(QString, QString);

    void LoginUser(QString, QString);

    void LoginManager(QString, QString);

    void BuildUserWidget();

    void DeleteUserinfo(int row, int col);

    void ShowMusicList();

    void SetMusicNameLabTxt(QString);

    void ShowAndHideLrcWgt();

    void InsertSongListWgt(QString name, int idx);

    void AddSongGroup();

    void BuildSongGruops(QVector<QString>);

    void ClickedMouseAction(int ,int);

    void ChooseSongGroupLWItem(QListWidgetItem*);

    void BuildTableSong(QVector<mst>, QString);

    void RequestLogin();
private:
    Ui::MainWindow *ui;

private:
    int currSonglistIndex = -1;
    int currSingerIndex = -1;
    int currLangueIndex = -1;
    int currSearchTabCol = -1;

    const QString ResPath = ":/Resources/Texture/";
    int x = 1025, y = 700;  //记录初始的宽和高
    QStringList ColTableList{}, ColSongTableList{};

private:
    QList<mst> ThisListSong{}; // 某个歌单的歌曲info
    QVector<NewButton*> LetterButtons{};
    std::map<QString, QWidget*> WgtManager{};

    QLabel *WinLab {}, *CurrTimeLab{}, *DurTimeLab{}, *MusicListLab{}, *MusicNameLab{}, *LoginLab{};
    QFont NorFont, LabFont;
    NewTableWidget *TableSearch{}, *TableSong{};  //用来显示歌曲
    QTableWidget *UserWidget{};  //用来显示用户

    QTimer *timer; // 定时更新Slidder.
    QWidget *SearchWidget{};
    QLineEdit *SearchEdit{}, *SongGroupEdit{};

    NewButton *CloseBtn {}, *MinBtn{}, *WinIcon{}, *PlayBtn{}, *FastForBtn{}, *RewindBtn{}, *NextBtn{}, *PrevBtn{}, *VolBtn{};
    NewButton *SearchBtn{}, *AddBtn{};
    NewButton *MusicListBtn{}, *LrcBtn{}, *LikeBtn{};
    QPushButton *ImgBtn{}, *LoginBtn{};

    NewLable *OrderSongLab {}, *SongGroupLab{};
    NewListWidget *OrderSongLW{}, *SongGroupLW{};
    NewListWidget *SingerOrderWdt{}, *LangueOrderWdt{}, *DayOrderWdt{};
    SongListWidget *SongListWgt{};

    PlayList *ListofSongWgt{};
    LrcWgt *lrcWgt{};
    Sql *sql{};

    LoginW *login{};
    Register *RegWt{};
    MusicPlayer *Player{};
    Network *network{};

    void paintEvent(QPaintEvent* event); // 绘制事件

    const QString LineEditQSS = "QLineEdit{height: 20px;border-style:none; padding:6px; border-radius: 20px;background:rgba(174,205,210,100); }";
    QString SearchText = "";
    QStringList LetterList = QStringList() << "A" << "B" << "C" << "D" << "E" << "F" << "G" << "H" << "I" << "J" << "K" << "L" << "M" << "N" <<
                                              "O" << "P" << "Q" << "R" << "S" << "T" << "U" << "V" << "W" << "X" << "Y" << "Z";

    QStringList SingerList = QStringList()  << "周杰伦" << "许嵩" << "刘德华" << "张杰" << "郑源" << "林俊杰" << "张学友" << "邓丽君" << "刀郎" << "王菲" << "王力宏" << "梁静茹" << "李玉刚" << "汪峰"
                                            << "韩红" << "陈奕迅" << "张靓颖" << "黄小琥" << "罗志祥" << "张惠妹" << "宋祖" << "任贤齐" << "萧亚轩" << "丁当" << "张信哲" << "小沈阳" << "乌兰托娅" << "卓依婷"
                                            << "刘若英" << "伍佰" << "潘玮柏" << "许巍" << "张宇" << "黄家驹" << "萧敬腾" << "孙燕姿" << "刘欢" << "田馥甄" << "李宇春" << "李炜" << "蔡依林" << "孙楠" << "腾格尔" << "齐秦"
                                            << "龚琳娜" << "罗百吉" << "费玉清" << "迪克牛仔" << "杨丞琳" << "林宥嘉" << "林忆莲" << "By2"
                                            << "凤凰传奇" << "棉花糖" << "小虎队" << "S.H.E" << "胡歌" << "蔡琴" << "王心凌" << "萨顶顶" << "周传雄" << "周华健" << "五月天" << "郑智化" << "谢霆锋" << "汤潮" << "王杰" << "杨钰莹"
                                            << "苏打绿" << "花儿乐队" << "信" << "魏晨" << "那英" << "胡彦斌" << "杨坤" << "张震岳" << "陈小春" << "陈翔" << "金莎" << "江映蓉" << "张韶涵" << "姜育恒" << "张雨生" << "动力火车"
                                            << "飞轮海" << "蒋大为" << "方大同" << "光良" << "信乐团" << "周笔畅" << "王若琳" << "孟庭苇" << "罗大佑" << "韩磊" << "龙梅子" << "孙悦" << "南拳妈妈" << "羽泉" << "李谷一" << "范玮琪"
                                            << "郭书瑶" << "武艺" << "郭静" << "许飞" << "易欣" << "莫文蔚" << "阿宝" << "杨培安" << "林志炫" << "刘惜君" << "唐禹哲" << "温岚" << "后弦" << "谭咏麟" << "姜玉阳" << "央金兰泽"
                                            << "成龙" << "曾轶可" << "斯琴高丽" << "蔡健雅" << "范晓萱" << "王蓉" << "李宗盛" << "李娜" << "张国荣" << "阿杜" << "费翔" << "吴克群" << "许茹芸" << "邰正宵" << "梁咏琪" << "李玟"
                                            << "宇桐非" << "黄龄" << "陈楚生" << "李健" << "董文华" << "张也" << "黎明" << "田震" << "郁可唯" << "何洁" << "纵贯线" << "毛宁" << "毛阿敏" << "李玲玉" << "郭峰" << "倪安东" << "朴树" << "阎维文" << "韩晶"
                                            << "郭富城" << "屠洪刚" << "草蜢" << "戴佩妮" << "山野" << "赵薇" << "何润东" << "胡夏" << "汤灿" << "卫兰" << "苏醒" << "梅艳芳" << "BOBO" << "阿牛" << "张芸京" << "范逸臣" << "黄圣依" << "黄立行" << "曹格" << "安以轩" << "郭书瑶" << "黄英" << "返回";

private:

    bool leftflag = false;
    QLabel *LrcLab = nullptr;
    QPoint glbal_p, win_p;   // 用win_p - glabel_p 就是 偏移量

    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
};
#endif // MAINWINDOW_H
