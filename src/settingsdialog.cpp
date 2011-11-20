#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->load();
    connect(this, SIGNAL(rejected()), this, SLOT(load()));
    connect(this, SIGNAL(accepted()), this, SLOT(save()));
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::load()
{
    QSettings settings;

    settings.beginGroup("Interface");
    ui->interfaceNotifications->setChecked(settings.value("Notifications", true).toBool());
    settings.endGroup();

    settings.beginGroup("Network");
    ui->networkProxy->setChecked(settings.value("Proxy", false).toBool());
    ui->networkProxyType->setCurrentIndex(settings.value("ProxyType", 1).toInt());
    ui->networkProxyHost->setText(settings.value("ProxyHost", "127.0.0.1").toString());
    ui->networkProxyPort->setValue(settings.value("ProxyPort", 3128).toInt());
    ui->networkProxyUser->setText(settings.value("ProxyUser", "").toString());
    ui->networkProxyPassword->setText(settings.value("ProxyPassword", "").toString());
    settings.endGroup();
}


void SettingsDialog::save()
{
    QSettings settings;

    settings.beginGroup("Interface");
    settings.setValue("Notifications", ui->interfaceNotifications->isChecked());
    settings.endGroup();

    settings.beginGroup("Network");
    settings.setValue("Proxy", ui->networkProxy->isChecked());
    settings.setValue("ProxyType", ui->networkProxyType->currentIndex());
    settings.setValue("ProxyHost", ui->networkProxyHost->text());
    settings.setValue("ProxyPort", ui->networkProxyPort->value());
    settings.setValue("ProxyUser", ui->networkProxyUser->text());
    settings.setValue("ProxyPassword", ui->networkProxyPassword->text());
    settings.endGroup();
}
