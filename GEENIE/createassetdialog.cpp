#include "createassetdialog.h"
#include "ui_createassetdialog.h"

createassetdialog::createassetdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::createassetdialog)
{
    ui->setupUi(this);
    this->p = parent;
    ui->comboBox->addItem("Texture Asset");
    ui->comboBox->addItem("MODEL_ASSET");
    ui->comboBox->addItem("MATERIAL_ASSET");
    ui->comboBox->addItem("SCRIPT_ASSET");
    ui->comboBox->addItem("AUDIO_ASSET");
    ui->comboBox->addItem("VIDEO_ASSET");
}

createassetdialog::~createassetdialog()
{
    delete ui;
}

void createassetdialog::on_pushButton_clicked()
{
    if(ui->lineEdit_2->text() != "")
    {
        this->file = ui->lineEdit_2->text();
        QDialog::accept();
    }
    else
    {
        QMessageBox *b = new QMessageBox(QMessageBox::NoIcon,"Inputerror","Please check your input.",QMessageBox::Ok);
        b->exec();
    }
}

void createassetdialog::on_pushButton_2_clicked()
{
    QDialog::reject();
}

void createassetdialog::on_pushButton_3_clicked()
{
    QString Path;
    AssetType type = (AssetType)ui->comboBox->currentIndex();
    if(type!=-1)
    switch (type) {
    case AssetType::MATERIAL_ASSET:
        Path = QFileDialog::getOpenFileName(this, tr("Load Material"), "C:/", "Material Files (*.bmp; *.dds; *.gif; *.hdr; *.jps; *.jpc; *.jpeg; *.jpg; *.attr; *.pic; *.png; *.pnm; *.pgm; *.pbm; *.rgb; *.sgi; *.rgba; *.int; *.inta; *.bw; *.tga; *.tiff; *.tif");
        break;
    case AssetType::TEXTURE_ASSET:
        Path = QFileDialog::getOpenFileName(this, tr("Load Texture"), "C:/", "Texture Files (*.bmp; *.dds; *.gif; *.hdr; *.jps; *.jpc; *.jpeg; *.jpg; *.attr; *.pic; *.png; *.pnm; *.pgm; *.pbm; *.rgb; *.sgi; *.rgba; *.int; *.inta; *.bw; *.tga; *.tiff; *.tif)");
        break;
    case AssetType::MODEL_ASSET:
        Path = QFileDialog::getOpenFileName(this, tr("Load Model"), "C:/", "Model Files (*.3dc; *.asc; *.ac; *.bsp; *.dae; *.dw; *.dxf; *.fbx; *.gem; *.geo; *.iv; *.wrl; *.ive; *.logo; *.lwo; *.lw; *.lws; *.md2; *.obj; *.ogr; *.flt; *.osg; *.shp; *.stl; *.sta; *.x)");
        break;
    case AssetType::SCRIPT_ASSET:
        Path = QFileDialog::getOpenFileName(this, tr("Load Script"), "C:/", "Script Files (*.py; *.lua)");
        break;
    case AssetType::AUDIO_ASSET:
        Path = QFileDialog::getOpenFileName(this, tr("Load Audio"), "C:/", "All Files (*.mp3; *.ogg)");
        break;
    case AssetType::VIDEO_ASSET:
        Path = QFileDialog::getOpenFileName(this, tr("Load Video"), "C:/", "Video files (*.mov; *.mpg; *.mpv; *.mp4; *.m4v; *.dv; *.avi; *.flv; *.swf)");
        break;
    default:
        break;
    }
    ui->lineEdit_2->setText(Path);
    this->type = type;
}

void createassetdialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    if(ui->lineEdit_2->text() !="")
    {
        ui->lineEdit_2->clear();
    }
    if(ui->comboBox->currentIndex()!=-1)
    {
        ui->lineEdit_2->setEnabled(true);
        ui->pushButton_3->setEnabled(true);
    }
    else
    {
        ui->lineEdit_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);

    }

}
AssetType createassetdialog::getType()
{
    return type;
}

QString createassetdialog::getFile()
{
    return this->file;
}

QString createassetdialog::getName()
{
    return name;
}
