#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
    Connect();
    NetworkSearch(); // TODO.
}

void MainWindow::Init() {
    NetworkInit();
    MusicPlayerInit();
    SqlInit();

    FontStyleInit();
    WinLayerInit();
    LableInit();
    WidgetInit();
    LineEditInit();
    ButtonInit();
    TableInit();
    ListWidgetInit();
}

void MainWindow::Connect() {
    ButtonSlot();
    TableSlot();
    SliderSlot();
    ListWidgetSlot();
    WidgetSlot();

    NetworkSlot();
    MusicPlayerSlot();
    SqlSlot();
}

void MainWindow::FontStyleInit() {
    NorFont.setFamily("幼圆");
    NorFont.setPointSize(15);
    LabFont.setFamily("楷体");
    LabFont.setPointSize(15);
}

void MainWindow::ButtonInit() {
    //MinimizeButton Init..
    MinBtn = new NewButton(ResPath + "min.png", ResPath + "min_1.png");
    MinBtn->setParent(this);
    MinBtn->move(this ->width() - 68, 25);

    // ColseButton Init..
    CloseBtn = new NewButton (ResPath + "cls.png", ResPath + "cls_1.png");
    CloseBtn->setParent(this);
    CloseBtn->move(this ->width() - 38, 25);

    // WinButton Init..
    WinIcon = new NewButton (ResPath + "mymusic.png", ResPath + "mymusic.png");
    WinIcon->setParent(this);
    WinIcon->move(12, 12);

    // PlayButton Init..
    PlayBtn = new NewButton(ResPath + "start.png", ResPath + "start_c.png", ResPath + "pause.png", ResPath + "pause_c.png");
    PlayBtn->setParent(this);
    PlayBtn ->move(478, 620);

    // Fast Forward Button Init..
    NextBtn = new NewButton(ResPath + "next.png", ResPath + "next_c.png");
    NextBtn->setParent(this);
    NextBtn->move(535, 623);

    // Fast Forward Button Init..
    PrevBtn = new NewButton(ResPath + "prev.png", ResPath + "prev_c.png");
    PrevBtn->setParent(this);
    PrevBtn->move(425, 623);

    // Fast Forward Button Init..
    FastForBtn = new NewButton(ResPath + "forward.png", ResPath + "forward_c.png");
    FastForBtn->setParent(this);
    FastForBtn->move(590, 623);

    // Rewind Button Init..
    RewindBtn = new NewButton(ResPath + "rewind.png", ResPath + "rewind_c.png");
    RewindBtn->setParent(this);
    RewindBtn->move(370, 623);

    // Volume Button Init.
    VolBtn = new NewButton(ResPath + "vol.png", ResPath + "vol_c.png", ResPath + "unvol.png", ResPath + "unvol_c.png");
    VolBtn->setParent(this);
    VolBtn->move(ui->VolSlider->x() - 30, ui->VolSlider->y() - 5);

    // Search Button Init.
    SearchBtn = new NewButton(ResPath + "Search.png", ResPath + "Search.png");
    SearchBtn->setParent(SearchEdit);
    SearchBtn->move(SearchEdit->width() - SearchBtn->width(), 2);
    SearchBtn->raise();

    AddBtn = new NewButton(ResPath + "add.png", ResPath + "add_c.png");
    AddBtn->setParent(SongGroupEdit);
    AddBtn->move(SongGroupEdit->width() - AddBtn->width() - 10, 6);
    AddBtn->raise();

    // Letter Buttons Init..
    for (int i = 0, letterPosX = 0, letterPosY = 0; i < LetterList.size(); ++i) {
        QString enter = ResPath + LetterList[i] + ".png";
        QString back = ResPath + LetterList[i] + "_c.png";
        NewButton *btn = new NewButton(enter, back);
        btn->setParent(SearchWidget);
        btn->move((letterPosX % 350) + SearchEdit->x() - 50, letterPosY + SearchEdit->y() + 50);
        LetterButtons.push_back(btn);
        letterPosX += 50;
        if (letterPosX % 350 == 0) letterPosY += 50;
    }

    // Music List Button.
    MusicListBtn = new NewButton(ResPath + "list.png", ResPath + "list_c.png");
    MusicListBtn->setParent(this);
    MusicListBtn->move(DurTimeLab->x(), VolBtn->y());

    // Music Img Button.
    QPixmap imgPix;
    imgPix.load(ResPath + "songer.png");

    ImgBtn = new QPushButton(this);
    ImgBtn->setGeometry(CurrTimeLab->x() - 100, CurrTimeLab->y() - 30, 30, 30);
    ImgBtn->setFixedSize(imgPix.width(), imgPix.height());
    ImgBtn->setIconSize(QSize(imgPix.width(), imgPix.height()));
    ImgBtn->setIcon(QIcon(imgPix));
    ImgBtn->setStyleSheet("QPushButton{border: 0px;}");

    // Lrc Button Init.
    LrcBtn = new NewButton(ResPath + "lrc_word.png", ResPath + "lrc_word.png");
    LrcBtn->setParent(this);
    LrcBtn->move(VolBtn->x() + 150, VolBtn->y());

    // Login Button init.
    LoginBtn = new QPushButton(this);
    LoginBtn->setGeometry(MinBtn->x() - 200, MinBtn->y() - 15, 150, 50);
    LoginBtn->setStyleSheet("QPushButton{background:rgba(0, 0, 0, 0);}");

    LoginLab = new QLabel(LoginBtn);
    LoginLab->setFont(LabFont);
    LoginLab->setText("登录");
    LoginLab->setGeometry(0, 0, LoginBtn->width(), LoginBtn->height());
}

void MainWindow::LableInit() {
    WinLab = new QLabel(this);
    WinLab->setGeometry(0, 0, 1025, 70);
    WinLab->setStyleSheet("QLabel{background-color: rgb(174, 205, 210); border: solid;}");
    WinLab ->setFont(LabFont);
    WinLab ->setText("       KTV点歌");

    OrderSongLab = new NewLable("  点歌系统", this);
    OrderSongLab->setGeometry(0, 70, 160, 40);

    SongGroupLab = new NewLable("  歌单", this);
    SongGroupLab->setGeometry(0, OrderSongLab->y() + OrderSongLab->height() + 200, 160, 40);

    CurrTimeLab = new QLabel(this);
    CurrTimeLab->setGeometry((ui->MusicSlider->x()) - 75, ui->MusicSlider->y() - 15, 50, 50);
    CurrTimeLab ->setFont(LabFont);
    CurrTimeLab->setText("00:00");

    DurTimeLab = new QLabel(this);
    DurTimeLab->setGeometry((ui->MusicSlider->x() + ui->MusicSlider->width()) + 30, ui->MusicSlider->y() - 15, 50, 50);
    DurTimeLab->setFont(LabFont);
    DurTimeLab->setText("00:00");

    MusicNameLab = new QLabel(this);
    MusicNameLab->setGeometry(CurrTimeLab->x() - 30, CurrTimeLab->y() - 30, 200, 30);
    LabFont.setPointSize(12);
    MusicNameLab->setFont(LabFont);
    LabFont.setPointSize(15);
    MusicNameLab->setText("暂无歌曲");
}

void MainWindow::ListWidgetInit() {
    OrderSongLW = new NewListWidget(this, QStringList() << "热门歌曲" << "歌手点歌" << "拼音点歌" << "语种点歌" << "歌曲排名");
    OrderSongLW->setGeometry(0, WinLab->height() + OrderSongLab->height(), 160, 200);
    OrderSongLW->setFocusPolicy(Qt::NoFocus); // 去掉虚线框

    SongGroupLW = new NewListWidget(this, QStringList());
    SongGroupLW->setGeometry(0, SongGroupEdit->y() + SongGroupEdit->height(), 160, 170);
    SongGroupLW->setFocusPolicy(Qt::NoFocus); // 去掉虚线框

    SingerOrderWdt = new NewListWidget(this, SingerList);
    SingerOrderWdt->setGeometry(OrderSongLab->width() + 2, WinLab->height() + 25, SingerOrderWdt->width(), SingerOrderWdt->height() - 25);
    SingerOrderWdt->hide();
    WgtManager["SingerOrderWdt"] = SingerOrderWdt;

    LangueOrderWdt = new NewListWidget(this, QStringList() << "国语歌曲" << "英文歌曲" << "韩文歌曲" << "日本歌曲" << "俄语歌曲" << "德语歌曲" << "返回");
    LangueOrderWdt->setGeometry(OrderSongLab->width() + 2, WinLab->height() + 25, LangueOrderWdt->width(), LangueOrderWdt->height() - 25);
    LangueOrderWdt->hide();
    WgtManager["LangueOrderWdt"] = LangueOrderWdt;

    SongListWgt = new SongListWidget(this);
    SongListWgt->setGeometry(width(), height() - 100 - 530, 250, 530);
    SongListWgt->show();
}

void MainWindow::WinLayerInit() {
    this->resize(x, y);   // 设置主界面的宽高
    this->setFixedSize(QSize(x, y)); // 窗口最小 size
    setWindowFlags(Qt::FramelessWindowHint);  // 删除以前的 最大化 最小化 关闭自己写

    setWindowTitle("KTV点歌");  //主窗口的运行文件名称
    setWindowIcon(QIcon(ResPath + "mymusic.png"));  // 主窗口的图标设置
}

void MainWindow::NetworkInit() {
    network = new Network();
}

void MainWindow::MusicPlayerInit() {
    Player = new MusicPlayer();
}

void MainWindow::SqlInit() {
    sql = new Sql();
}

void MainWindow::TableInit() {
    //关于tablewidget 上面的名字
    ColTableList = QStringList() << "歌曲" << "" << "操作" << "" << "作者" << "专辑" << "时间";
    ColSongTableList = QStringList() << "歌曲" << "" << "操作" << "" << "作者" << "专辑" << "时间" << "";
    QStringList UserAttribuesList = QStringList() << "序号" << "用户名" << "密码" << "";

    // 显示搜索音乐的窗口
    TableSearch = new NewTableWidget();
    TableSearch->setParent(this);
    TableSearch->setColumnCount(7);  // 设置列数
    TableSearch->setHorizontalHeaderLabels(ColTableList);// 设置列数的 名字
    TableSearch->setGeometry(OrderSongLab->width(), WinLab->height(), this ->width() - OrderSongLab->width() + 20, this ->height() - WinLab->height() - 101);

    TableSearch->setColumnWidth(0, TableSearch->width() / 7);
    TableSearch->setColumnWidth(1, (TableSearch->width() / 7));
    TableSearch->setColumnWidth(2, (TableSearch->width() / 7));
    TableSearch->setColumnWidth(3, (TableSearch->width() / 7));
    TableSearch->setColumnWidth(4, TableSearch->width() / 7);
    TableSearch->setColumnWidth(5, TableSearch->width() / 7);
    TableSearch->setColumnWidth(6, TableSearch->width() / 7);
    TableSearch->hide();

    WgtManager["TableSearch"] = TableSearch;

    TableSong = new NewTableWidget();
    TableSong->setParent(this);
    TableSong->setColumnCount(8);  // 设置列数
    TableSong->setHorizontalHeaderLabels(ColSongTableList);// 设置列数的 名字
    TableSong->setGeometry(OrderSongLab->width(), WinLab->height(), this ->width() - OrderSongLab->width() + 20, this ->height() - WinLab->height() - 101);

    TableSong->setColumnWidth(0, TableSong->width() / 8);
    TableSong->setColumnWidth(1, (TableSong->width() / 8));
    TableSong->setColumnWidth(2, (TableSong->width() / 8));
    TableSong->setColumnWidth(3, (TableSong->width() / 8));
    TableSong->setColumnWidth(4, TableSong->width() / 8);
    TableSong->setColumnWidth(5, TableSong->width() / 8);
    TableSong->setColumnWidth(6, TableSong->width() / 8);
    TableSong->setColumnWidth(7, TableSong->width() / 8);
    TableSong->hide();

    WgtManager["TableSong"] = TableSong;


    UserWidget = new QTableWidget();
    UserWidget->setParent(this);
    UserWidget->setColumnCount(4);  // 设置列数
    UserWidget->setHorizontalHeaderLabels(UserAttribuesList);// 设置列数的 名字
    UserWidget->setGeometry(OrderSongLab->width(), WinLab->height(), this ->width() - OrderSongLab->width() + 20, this ->height() - WinLab->height() - 101);

    UserWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); // 不可编辑
    UserWidget->setShowGrid(false); // 关闭网格
    UserWidget->setFocusPolicy(Qt::NoFocus); //去掉虚线格
    UserWidget->verticalHeader()->setHidden(true); // 去掉表头行号
    UserWidget->setStyleSheet("QTableWidget::Item::selected{background: white;}"
                               "QHeaderView::section{border: 0px solid white};"
                               "QTableWidget::Item::hover{background: black;}");


    UserWidget->setColumnWidth(0, UserWidget->width() / 4);
    UserWidget->setColumnWidth(1, UserWidget->width() / 4);
    UserWidget->setColumnWidth(2, UserWidget->width() / 4);
    UserWidget->setColumnWidth(3, UserWidget->width() / 4);
    UserWidget->hide();

    WgtManager["UserWidget"] = UserWidget;
}

void MainWindow::WidgetInit() {
    SearchWidget = new QWidget(this);
    SearchWidget->setGeometry(OrderSongLab->width(), WinLab->height(), this ->width() - OrderSongLab->width() + 20, this ->height() - WinLab->height() - 101);
    SearchWidget->hide();
    WgtManager["SearchWidget"] = SearchWidget;

    login = new LoginW(this, OrderSongLab->width(), WinLab->height(), this ->width() - OrderSongLab->width() + 20, this ->height() - WinLab->height() - 101);
    login->hide();
    WgtManager["login"] = login;

    RegWt = new Register(this, OrderSongLab->width(), WinLab->height(), this ->width() - OrderSongLab->width() + 20, this ->height() - WinLab->height() - 101);
    RegWt->hide();
    WgtManager["RegWt"] = RegWt;

    lrcWgt = new LrcWgt(nullptr);

    // ListofSong
    ListofSongWgt = new PlayList(this);
    WgtManager["ListofSongWgt"] = ListofSongWgt;
}

void MainWindow::LineEditInit() {
    SearchEdit = new QLineEdit(SearchWidget);
    SearchEdit->setGeometry(SearchWidget->width() / 2 - 150, SearchWidget->height() / 2 - 100, 200, 40);
    SearchEdit->setFont(NorFont);
    SearchEdit->setStyleSheet(LineEditQSS);

    SongGroupEdit = new QLineEdit(this);
    SongGroupEdit->setGeometry(0, SongGroupLab->y() + SongGroupLab->height(), SongGroupLab->width(), 40);
    NorFont.setPointSize(13);
    SongGroupEdit->setFont(NorFont);
    NorFont.setPointSize(15);
    SongGroupEdit->setStyleSheet(LineEditQSS);
}

void MainWindow::ButtonSlot() {
    connect(MinBtn, &QPushButton::clicked, this, &MainWindow::SetMinWindow);
    connect(CloseBtn, &QPushButton::clicked, this, &MainWindow::CloseWindow);
    connect(PlayBtn, &QPushButton::clicked, Player, &MusicPlayer::SwitchPlayerStatue);
    connect(NextBtn, &QPushButton::clicked, Player, &MusicPlayer::Next);
    connect(PrevBtn, &QPushButton::clicked, Player, &MusicPlayer::Prev);
    connect(FastForBtn, &QPushButton::clicked, Player, &MusicPlayer::Fastward);
    connect(RewindBtn, &QPushButton::clicked, Player, &MusicPlayer::Rewind);
    connect(VolBtn, &QPushButton::clicked, Player, &MusicPlayer::SwitchVolumeState);
    connect(SearchBtn, &QPushButton::clicked, this, &MainWindow::ClickedSearchButton);
    connect(AddBtn, &QPushButton::clicked, this,  &MainWindow::AddSongGroup);

    for (int i = 0; i < LetterButtons.size(); ++i) {
        connect(LetterButtons[i], &QPushButton::clicked, this, [=] () {
            SearchText += LetterList[i];
            SearchEdit->setText(SearchText);
        });
    }

    connect(MusicListBtn, &QPushButton::clicked, this, &MainWindow::ShowMusicList);

    connect(LrcBtn, &QPushButton::clicked, this, &MainWindow::ShowAndHideLrcWgt);

    connect(LoginBtn, &QPushButton::clicked, this, &MainWindow::RequestLogin);
}

void MainWindow::SliderSlot() {
    connect(ui->MusicSlider, &QSlider::sliderMoved, this, &MainWindow::MusicSliderValChanged);

    connect(ui->VolSlider, &QSlider::valueChanged, this, &MainWindow::VolumeSliderValChanged);
}

void MainWindow::NetworkSlot() {
    connect(network, &Network::SearchIsFinished, this, &MainWindow::BuildSearchTable);
    connect(network, &Network::GetMusicFinished, this, [=] () {
        if (currSearchTabCol == 0 || currSearchTabCol == 1) {
            if (Player->SetLoadMusic(network->GetMusicStruct())) {
                InsertSongListWgt(network->GetMusicStruct().name, Player->GetCurrMediaIdx());
            }
        }
        else if (currSearchTabCol == 2) {
            if (Player->PlayTheNextSong(network->GetMusicStruct())) {
                InsertSongListWgt(network->GetMusicStruct().name, Player->GetCurrMediaIdx() + 1);
            }
        }
        else if (currSearchTabCol == 3) {
            sql->InsertListOfSong(network->GetMusicStruct(), ListofSongWgt->TargetName);
        }
    });

    connect(network, &Network::GetNetworkImgFinished, this, [=] () {
        QPixmap pix = network->GetImgPix();
        pix = PixmapToRound(pix, 30);
        ImgBtn->setFixedSize(pix.width(), pix.height());
        ImgBtn->setIconSize(QSize(pix.width(), pix.height()));
        ImgBtn->setIcon(QIcon(pix));
    });

    connect(network, &Network::AnlzLrcStrFinished, Player, &MusicPlayer::GetAnlzLrcMap);
}

void MainWindow::MusicPlayerSlot() {
    connect(Player, &MusicPlayer::ChangedPlayerState, PlayBtn, &NewButton::SwitchButtonIcon);
    connect(Player, &MusicPlayer::ChangedVolumeState, VolBtn, &NewButton::SwitchButtonIcon);
    connect(Player, &MusicPlayer::GetMusicName, this, &MainWindow::SetMusicNameLabTxt);
    connect(Player, &MusicPlayer::SetLrcTxt, lrcWgt, &LrcWgt::SetLrc);

    connect(Player, &MusicPlayer::MusicTimeout, this, [=] () {
        int curr = Player->GetCurrTime() / 100;
        int dur = Player->GetMusicDuration() / 1000;
        BuildTimeLab(curr, dur);
        int val = (float)((curr  * 1.0f) / dur) * 100;
        ui->MusicSlider->setValue(val);
    });

    connect(Player, &MusicPlayer::GetMusicNetImg, network, &Network::StartRequestNetImg);
    connect(Player, &MusicPlayer::PlzAnlzLrcStr, network, &Network::AnlzLrcStr);

    connect(Player, &MusicPlayer::GetInitMusicList, sql, &Sql::GetUserMscList);
    connect(Player, &MusicPlayer::InsertMscInfoInSql, sql, &Sql::InsertMscInfo);
    connect(Player, &MusicPlayer::RequestSqlDeleteMusic, sql, &Sql::DeleteMusicInfo);
    connect(Player, &MusicPlayer::PlayerIsEmpty, this, [=] () {
        LabFont.setPointSize(12);
        MusicNameLab->setFont(LabFont);
        LabFont.setPointSize(15);
        MusicNameLab->setText("暂无歌曲");

        QPixmap imgPix;
        imgPix.load(ResPath + "songer.png");
        ImgBtn->setFixedSize(imgPix.width(), imgPix.height());
        ImgBtn->setIconSize(QSize(imgPix.width(), imgPix.height()));
        ImgBtn->setIcon(QIcon(imgPix));

        lrcWgt->SetLrc("暂无歌词");
        CurrTimeLab->setText("00:00");
        DurTimeLab->setText("00:00");
        ui->MusicSlider->setValue(0);
    });
}

void MainWindow::TableSlot() {
    connect(TableSearch, &QTableWidget::cellClicked, this, &MainWindow::SelectMusic);
    connect(UserWidget, &QTableWidget::cellClicked, this, &MainWindow::DeleteUserinfo);
    connect(TableSearch, &NewTableWidget::ClickedMouse, this, &MainWindow::ClickedMouseAction);
    connect(ListofSongWgt, &PlayList::RequestSqlBuildList, sql, &Sql::GetPlaysongList);
    connect(ListofSongWgt, &PlayList::cellClickedItem, this, [=] () {
            ListofSongWgt->hide();
            network->SelectNetworkMusic(ListofSongWgt->GetTargetRow());
    });
    connect(TableSong, &QTableWidget::cellClicked, this, &MainWindow::SelectItemOperate);
}

void MainWindow::ListWidgetSlot() {
    connect(OrderSongLW, &NewListWidget::itemClicked, this, &MainWindow::SelectSongListWidgetItem);
    connect(SingerOrderWdt, &NewListWidget::itemClicked, this, &MainWindow::SelectSingerListWidgetItem);
    connect(LangueOrderWdt, &NewListWidget::itemClicked, this, &MainWindow::SelectLanguListWidgetItem);
    connect(SongListWgt, &SongListWidget::DeleteListMusic, Player, &MusicPlayer::DeleteMusicInMediaPlayer);
    connect(SongListWgt, &SongListWidget::RequestPlayMusic, Player, &MusicPlayer::PlayerMusic);
    connect(SongGroupLW, &NewListWidget::DeleteSongGroup, sql, &Sql::DeleteSongGroup);
    connect(SongGroupLW, &NewListWidget::itemClicked, this, &MainWindow::ChooseSongGroupLWItem);
}

void MainWindow::WidgetSlot() {
    connect(RegWt, &Register::CloseRegister, this, [=] () {
        OpenWgt("login");
    });

    connect(RegWt, &Register::RequestRegister, this, &MainWindow::RegisterUser);

    connect(login, &LoginW::ShowRegister, this, [=] () {
        OpenWgt("RegWt");
    });

    connect(login, &LoginW::RequestLogin, this, &MainWindow::LoginUser);

    connect(login, &LoginW::RequestLoginManager, this, &MainWindow::LoginManager);
}

void MainWindow::SqlSlot() {
    connect(sql, &Sql::GetSqlMscListFinished, Player, &MusicPlayer::InitPlayList);
    connect(sql, &Sql::GetSqlMscListFinished, SongListWgt, &SongListWidget::BuildSongListInit);
    connect(sql, &Sql::GetSqlSongGroupsFinished, this, &MainWindow::BuildSongGruops);
    connect(sql, &Sql::GetSqlSongListFinished, ListofSongWgt, &PlayList::GetListofSong);
}

void MainWindow::SetMinWindow(bool) {
    showMinimized();
}

void MainWindow::CloseWindow() {
    this->close();
    lrcWgt->close();
}

void MainWindow::NetworkSearch() {
    network->search("热门歌单", 10);
}

void MainWindow::BuildSearchTable(QVector<mst> info) {
    TableSearch->setRowCount(0);
    for (int i = 0; i < info.size(); ++i) {
        TableSearch->setRowCount(i + 1);

        TableSearch->setItem(i,0,new QTableWidgetItem(info[i].name));
        TableSearch->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文字居中

        TableSearch->setItem(i,1,new QTableWidgetItem("Play"));
        TableSearch->item(i, 1)->setIcon(QIcon(ResPath + "begin.png"));
        TableSearch->item(i, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSearch->setItem(i,2,new QTableWidgetItem("NextPlay"));
        TableSearch->item(i, 2)->setIcon(QIcon(ResPath + "looper.png"));
        TableSearch->item(i, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSearch->setItem(i,3,new QTableWidgetItem("Add playlist"));
        TableSearch->item(i, 3)->setIcon(QIcon(ResPath + "add.png"));
        TableSearch->item(i, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSearch->setItem(i,4,new QTableWidgetItem(info[i].singername));
        TableSearch->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSearch->setItem(i,5,new QTableWidgetItem(info[i].album_name));
        TableSearch->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSearch->setItem(i,6,new QTableWidgetItem(info[i].time));
        TableSearch->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    TableSearch->show();
    OpenWgt("TableSearch");
}

void MainWindow::InsertSongListWgt(QString name, int idx) {
     qDebug() << name << ", " << idx;
    if (name.isEmpty()) return;
    SongListWgt->InsertSongListWgt(name, idx);
}

void MainWindow::SelectMusic(int row, int col) {
    currSearchTabCol = col;
    if (col == 0 || col == 1 || col == 2) {
        network->SelectNetworkMusic(row);
    }
    else if (col == 3) {
        int item_x = TableSearch->GetMousePos().x() + TableSearch->x() + 20, item_y = TableSearch->GetMousePos().y() + TableSearch->y() + 35;
        ListofSongWgt->Move(item_x, item_y);
        ListofSongWgt->raise();
        ListofSongWgt->SetTargetRow(row);
    }
}

void MainWindow::MusicSliderValChanged(int val) {
    Player->SetMusicPosition(val);
}

void MainWindow::VolumeSliderValChanged(int val) {
    Player->SetCurrVol(val);
}

void MainWindow::BuildTimeLab(int curr, int dur) {
    QString currMin = QString::number(curr / 60);
    QString currSec = QString::number(curr % 60);
    QString durMin = QString::number(dur / 60);
    QString durSec = QString::number(dur % 60);

    if (currMin.size() == 1) currMin.insert(0, '0');
    if (currSec.size() == 1) currSec.insert(0, '0');
    if (durMin.size() == 1) durMin.insert(0, '0');
    if (durSec.size() == 1) durSec.insert(0, '0');

    CurrTimeLab->setText(currMin + ":" + currSec);
    DurTimeLab->setText(durMin + ":" + durSec);
}

void MainWindow::SelectSongListWidgetItem(QListWidgetItem* item) {
    int index = OrderSongLW->row(item);
    switch(index) {
    case 0:
        if (currSonglistIndex != index) {
            network->search(item->text(), 10);
            currSonglistIndex = index;
            currSingerIndex = -1;
            currLangueIndex = -1;
        }
        break;
    case 1:
        OpenWgt("SingerOrderWdt");
        break;
    case 2:
        OpenWgt("SearchWidget");
        break;
    case 3:
        OpenWgt("LangueOrderWdt");
        break;
    case 4:
        if (currSonglistIndex != index) {
            network->SearchRank();
            currSonglistIndex = index;
            currSingerIndex = -1;
            currLangueIndex = -1;
        }
        break;
    default:
        break;
    }
}

void MainWindow::SelectSingerListWidgetItem(QListWidgetItem* item) {
    int index = SingerOrderWdt->row(item);
    if (index == SingerList.size() - 1) {
        SingerOrderWdt->hide();
        return;
    }

    if (currSingerIndex != index) {
        network->search(item->text(), 10);
        currSingerIndex = index;
        currLangueIndex = -1;
        currSonglistIndex = -1;
    }
}

void MainWindow::SelectLanguListWidgetItem(QListWidgetItem *item) {
    int index = LangueOrderWdt->row(item);
    if (index == 6) {
        LangueOrderWdt->hide();
        return;
    }

    if (currLangueIndex != index) {
        network->search(item->text(), 10);
        currLangueIndex = index;
        currLangueIndex = -1;
        currSonglistIndex = -1;
    }
}

void MainWindow::ClickedSearchButton() {
    network->search(SearchEdit->text(), 10);
    SearchEdit->setText("");
    SearchText = "";
}

void MainWindow::OpenWgt(QString name) {
    //if (WgtManager[name] == nullptr) return;
    for (auto p : WgtManager) {
        if (name == p.first) WgtManager[p.first]->show();
        else WgtManager[p.first]->hide();
    }
}

void MainWindow::RegisterUser(QString name, QString pwd) {
    if (name.size() == 0 || pwd.size() == 0) return;

    int newId = sql->GetUserCount();
    bool res = sql->InsertUser(QString("%0").arg(newId + 1), name, pwd);
    if (res) {
        OpenWgt("login");
        RegWt->ClearLineEditText();
    }
    else QMessageBox::warning(this, "Error", "用户名被注册了", QMessageBox::Ok);
}

void MainWindow::LoginUser(QString name, QString pwd) {
    if (name.size() == 0 || pwd.size() == 0) return;
    bool res = sql->LoginUser(name, pwd);
    if (res) {
        OpenWgt("");
        login->ClearLineEditText();
        QString UserName = sql->GetUserName();
        LoginLab->setText(QString("%0,欢迎!").arg(UserName));
        emit Player->GetInitMusicList(UserName);
        sql->GetUserSongGroups(UserName);
        network->search("热门歌曲", 10);
    }
    else QMessageBox::warning(this, "Error", "用户名与密码不匹配", QMessageBox::Ok);
}

void MainWindow::LoginManager(QString name, QString pwd) {
    if (name.size() == 0 || pwd.size() == 0) return;
    bool res = sql->LoginManager(name, pwd);
    if (res) {
        BuildUserWidget();
        login->ClearLineEditText();
    }
    else QMessageBox::warning(this, "Error", "管理账号错误", QMessageBox::Ok);
}

void MainWindow::BuildUserWidget() {
    UserWidget->setRowCount(0);
    QVector<QVector<QString>> UserInfo = sql->GetUserInfo();
    for (int i = 0; i < UserInfo.size(); ++i) {
        UserWidget ->setRowCount(i + 1);

        UserWidget->setItem(i,0,new QTableWidgetItem(UserInfo[i][0]));
        UserWidget->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文字居中

        UserWidget->setItem(i,1,new QTableWidgetItem(UserInfo[i][1]));
        UserWidget->item(i, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        UserWidget->setItem(i,2,new QTableWidgetItem(UserInfo[i][2]));
        UserWidget->item(i, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        UserWidget->setItem(i,3,new QTableWidgetItem("Delete"));
        UserWidget->item(i, 3)->setIcon(QIcon(ResPath + "cls.png"));
        UserWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    TableSearch->show();
    OpenWgt("UserWidget");
}

void MainWindow::DeleteUserinfo(int row, int col) {
    if (col == 3) {
        QMessageBox::StandardButton res = QMessageBox::information(this, "询问", "确定删除该用户该用户吗?", QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Cancel);
        if (res == QMessageBox::Ok) {
            QString userName = UserWidget->item(row, 1)->text();
            bool res = sql->DeleteUserInfo(userName);
            if (res) {
                UserWidget->removeRow(row);
            }
            else QMessageBox::warning(this, "error", "删除失败", QMessageBox::Ok);
        }
    }
}

void MainWindow::ShowMusicList() {
    SongListWgt->raise();

    int ax1 = SongListWgt->x() == width() ? width() : (width() - 250);
    int ax2 = SongListWgt->x() == width() ? (width() - 250) : width();

    QPropertyAnimation *anim = new QPropertyAnimation(SongListWgt, "geometry");
    anim->setDuration(200);
    anim->setStartValue(QRect(ax1, SongListWgt->y(), SongListWgt->width(), SongListWgt->height()));
    anim->setEndValue(QRect(ax2, SongListWgt->y(), SongListWgt->width(), SongListWgt->height()));
    anim->setEasingCurve(QEasingCurve::Linear);
    anim->start();
}

QPixmap MainWindow::PixmapToRound(QPixmap pix, int radius) {
    QSize size(2 * radius, 2 * radius);
    QBitmap bit(size);
    QPainter painter(&bit);

    //经典抗锯齿
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
    painter.setBrush(Qt::black);
    painter.drawRoundedRect(0, 0, size.width(), size.height(), 10, 10);
    QPixmap ans = pix.scaled(size);
    ans.setMask(bit);
    return ans;
}

void MainWindow::SetMusicNameLabTxt(QString text) {
    MusicNameLab->setText(text);
}

void MainWindow::ShowAndHideLrcWgt() {
    lrcWgt->isHidden() ? lrcWgt->show() : lrcWgt->hide();
}

void MainWindow::AddSongGroup() {
    QString name = SongGroupEdit->text();
    if (name.size() == 0) return;

    if(sql->InsertNewSongGroup(name)) {
        SongGroupEdit->setText("");
        SongGroupLW->AddItem_(name);
    }
}

void MainWindow::BuildSongGruops(QVector<QString> groups) {
    for (int i = 0; i < groups.size(); ++i) {
        SongGroupLW->AddItem_(groups[i]);
    }
}

void MainWindow::ClickedMouseAction(int x, int y) {
    QVector4D pos = ListofSongWgt->GetPlayListRange();
    if (x < pos.x() || x > pos.z() || y < pos.y() || y > pos.w()) {
        ListofSongWgt->hide();
    }
}

void MainWindow::ChooseSongGroupLWItem(QListWidgetItem *item) {
    QString listname = item->text();

    BuildTableSong(sql->GetMusicInThisList(listname), listname);
}

void MainWindow::BuildTableSong(QVector<mst> info, QString name) {
    TableSong->SetClickedItemText(name);
    ThisListSong = QList<mst>(info.begin(), info.end());
    TableSong->setRowCount(0);
    for (int i = 0; i < ThisListSong.size(); ++i) {
        TableSong ->setRowCount(i + 1);

        TableSong->setItem(i,0,new QTableWidgetItem(ThisListSong[i].name));
        TableSong->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);//文字居中

        TableSong->setItem(i,1,new QTableWidgetItem("Play"));
        TableSong->item(i, 1)->setIcon(QIcon(ResPath + "begin.png"));
        TableSong->item(i, 1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSong->setItem(i,2,new QTableWidgetItem("NextPlay"));
        TableSong->item(i, 2)->setIcon(QIcon(ResPath + "looper.png"));
        TableSong->item(i, 2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSong->setItem(i,3,new QTableWidgetItem("Add playlist"));
        TableSong->item(i, 3)->setIcon(QIcon(ResPath + "add.png"));
        TableSong->item(i, 3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSong->setItem(i,4,new QTableWidgetItem(ThisListSong[i].singername));
        TableSong->item(i,4)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSong->setItem(i,5,new QTableWidgetItem(ThisListSong[i].album_name));
        TableSong->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSong->setItem(i,6,new QTableWidgetItem(ThisListSong[i].time));
        TableSong->item(i,6)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

        TableSong->setItem(i,7,new QTableWidgetItem("Delete"));
        TableSong->item(i, 7)->setIcon(QIcon(ResPath + "cls.png"));
        TableSong->item(i, 7)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    TableSong->show();
    OpenWgt("TableSong");
}

void MainWindow::SelectItemOperate(int row, int col) {
    if(col == 0 || col == 1) {
        if (Player->SetLoadMusic(ThisListSong[row])) {
            InsertSongListWgt(ThisListSong[row].name, Player->GetCurrMediaIdx());
        }
    }
    else if (col == 2) {
        if (Player->PlayTheNextSong(ThisListSong[row])) {
            InsertSongListWgt(ThisListSong[row].name, Player->GetCurrMediaIdx() + 1);
        }
    }
    else if (col == 3) {
        sql->InsertListOfSong(ThisListSong[row], ListofSongWgt->TargetName);
    }
    else if (col == 7) {
        sql->DeleteMusicInThisList(TableSong->GetClickItemText(), ThisListSong[row]);
        ThisListSong.removeAt(row);
        TableSong->removeRow(row);
    }
}

void MainWindow::RequestLogin() {
     if (login->CheckUserinfo()) {
        QJsonObject json = login->JsonReadOnlyInFile();
        QPair<bool, QString> p = sql->GetUserPassword(json["account"].toString(), json["password"].toString());

        if (p.first) {
            LoginUser(json["account"].toString(), p.second);
        }
        else {
            OpenWgt("login");
        }
     }
     else {
        OpenWgt("login");
     }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);  // 避免编译器警告

    //绘制分割线
    QPainter paint(this);
    paint.setPen(QColor(Qt::black));
    paint.drawLine(OrderSongLab->width(), WinLab->height() - 30, OrderSongLab->width(), this ->height() - WinLab->height() - 30);
    paint.drawLine(0, this ->height() - WinLab->height() - 30, this ->width(), this ->height() - WinLab->height() - 30);
    paint.drawLine(0, OrderSongLW->y() + OrderSongLW->height(), OrderSongLW->width(), OrderSongLW->y() + OrderSongLW->height());
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) {
    // 移动窗口
    if(leftflag && e->pos().y() >= 0 && e->pos().y() <= this->height()) {
        win_p = e->globalPos();
        this->move(win_p - glbal_p);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    // 点击窗口
    if(e->button() == Qt::LeftButton && e->pos().y() >= 0 && e->pos().y() <= this->height()) {
        leftflag = true;
        glbal_p = e->globalPos() - this->pos();
    }
}
