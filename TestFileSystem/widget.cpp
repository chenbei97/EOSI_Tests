#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(qApp->applicationDirPath());
    model->setReadOnly(true);
    model->setFilter(QDir::AllDirs|QDir::NoDotAndDotDot);

//    qDebug()<<"root path = "<<model->rootPath();
//    qDebug()<<"root dir = "<<model->rootDirectory();
//    qDebug()<<"row = "<<model->rowCount();
//    qDebug()<<"col = "<<model->columnCount();

    QTreeView *tree = new QTreeView;
    tree->setModel(model);
    tree->header()->setMinimumSectionSize(500);

    //tree->setRootIndex(model->index(QDir::rootPath()));
    auto batchpath = "C:/Users/22987/Desktop/EOSI/EOSI/bin";
    tree->setRootIndex(model->index(batchpath));

    auto btn = new QPushButton(tr("确定"));
    imageview = new QTableView;
    imagemodel = new QStandardItemModel;
    imageview->setModel(imagemodel);
    imageview->horizontalHeader()->setMinimumSectionSize(ImageSize);
    imageview->verticalHeader()->setMinimumSectionSize(ImageSize);
    imageview->horizontalHeader()->setVisible(false);
    imageview->verticalHeader()->setVisible(false);
    //imageview->setGridStyle(Qt::PenStyle::NoPen);
    imagemodel->setRowCount(3);
    imagemodel->setColumnCount(5);
    imageview->setEditTriggers(QTableView::NoEditTriggers);
    imageview->setShowGrid(false);
    imageview->setItemDelegate(new ImageDelegate);

    QSplitter * s = new QSplitter(Qt::Vertical);
    auto lay = new QVBoxLayout;
    s->addWidget(tree);
    s->addWidget(imageview);
    s->setStretchFactor(0,1);
    s->setStretchFactor(1,4);
    lay->addWidget(s);
//    auto blay = new QHBoxLayout;
//    blay->addStretch();
//    blay->addWidget(btn);
//    lay->addLayout(blay);
    setLayout(lay);

    resize(1800,1200);

    //connect(model,&QFileSystemModel::directoryLoaded,this,&Widget::onDirectoryLoaded);
    //connect(model,&QFileSystemModel::fileRenamed,this,&Widget::onFileRenamed);
    //connect(model,&QFileSystemModel::rootPathChanged,this,&Widget::onRootPathChanged);
    //connect(tree,&QTreeView::collapsed,this,&Widget::onCollapsed);
    //connect(tree,&QTreeView::expanded,this,&Widget::onExpanded);
    connect(tree,&QTreeView::clicked,this,&Widget::onItemClicked);
}

void Widget::onItemClicked(const QModelIndex &index)
{
    auto model = static_cast<const QFileSystemModel*>(index.model());
    auto path = model->filePath(index);
    qDebug()<<"clicked  path info = "<<path;

    QDir dir(path);
    dir.setFilter(QDir::Files);
    QFileInfoList list = dir.entryInfoList(QStringList()<<"*.jpg"<<"*.png");
    if (list.count() == 0) return;
    imagemodel->clear();
    QList<QPair<QPixmap,QString>> mpixs;
    foreach(auto fileinfo, list) {
        auto imgpath = fileinfo.filePath();
        //qDebug()<<imagepath;
        QImageReader reader;
        reader.setFileName(imgpath);
        reader.setAutoTransform(true); // reader.read()会自动进行元数据转换
        auto source_size = reader.size();
        auto target_size = source_size.scaled(ImageSize,ImageSize,Qt::KeepAspectRatio); // 原尺寸=>目标尺寸的保持纵横比尺寸
        reader.setScaledSize(target_size);
        auto pix = QPixmap::fromImageReader(&reader);
        mpixs.append(qMakePair(pix,imgpath));
    }
    const int cols = 5;
    auto rows = mpixs.count() / cols;
    if (rows * 5 < mpixs.count())
        rows += 1;
    imagemodel->setRowCount(rows);
    imagemodel->setColumnCount(cols);
    qDebug()<<"rows = "<<rows<<" count = "<<mpixs.count();

    for(int r = 0; r < rows; ++ r) {
        for(int c = 0; c < cols; ++c) {
            auto idx = r * cols + c;
            //qDebug()<<"idx = "<<idx<<" r = "<<r<<" c = "<<c;
            if (idx >= mpixs.count())
                break;
            imagemodel->setData(imagemodel->index(r,c),mpixs.at(idx).first,Qt::DecorationRole);
            imagemodel->setData(imagemodel->index(r,c),mpixs.at(idx).second,Qt::UserRole+1);
            imageview->setColumnWidth(c,CellSize);
            imageview->setRowHeight(r,CellSize);
        }
    }
}

void Widget::onCollapsed(const QModelIndex &index)
{
    auto model = static_cast<const QFileSystemModel*>(index.model());
    qDebug()<<" collapsed index = "<<index<<" fileinfo = "<<model->fileInfo(index);
}

void Widget::onExpanded(const QModelIndex &index)
{
    auto model = static_cast<const QFileSystemModel*>(index.model());
    qDebug()<<" expand index = "<<index<<" fileinfo = "<<model->fileInfo(index);
}

void Widget::onFileRenamed(const QString &path, const QString &oldName, const QString &newName)
{
    qDebug()<<"file rename path ="<<path<<" oldname"<<oldName<<" new name = "<<newName;
}

void Widget::onDirectoryLoaded(const QString &path)
{
    qDebug()<<"DirectoryLoaded path ="<<path;
}

void Widget::onRootPathChanged(const QString &newPath)
{
    qDebug()<<"RootPathChanged path ="<<newPath;
}

Widget::~Widget()
{
}

