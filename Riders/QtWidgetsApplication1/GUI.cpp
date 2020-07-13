#include "GUI.h"
#include "Service.h"
#include <QString>
#include <QMessageBox>
#include <QCloseEvent>
#include <QModelIndexList>
#include  <QPainter>
#include <QPointF>
GUI::GUI(Astronomer& a,StarService& starService, AstroService& astroService, QWidget* parent): QWidget(parent), starService{starService},astroService{astroService}
{
	this->a = a;
	try {
		this->init();
	}
	catch (exception& e) {
		QMessageBox error;
		error.setText(e.what());
		error.exec();
	}
}

void GUI::init()
{
	this->setWindowTitle(QString::fromStdString(a.getName()));
	this->stars = new QListWidget{};
	this->hLayout = new QHBoxLayout{this};
	this->viewButton = new QPushButton{};
	this->starName = new QLineEdit{};
	this->ra = new QLineEdit{};
	this->dec = new QLineEdit{};
	this->diameter = new QLineEdit{};
	this->starSearcher = new QLineEdit{};
	this->addStarButton = new QPushButton{};
	this->seeMyStars = new QCheckBox{};
	this->viewButton->setText("View");
	this->addStarButton->setText("Add");
	this->starName->setText("Name");
	this->ra->setText("ra");
	this->dec->setText("dec");
	this->diameter->setText("diameter");
	this->hLayout->addWidget(stars);
	this->hLayout->addWidget(starName);
	this->hLayout->addWidget(ra);
	this->hLayout->addWidget(dec);
	this->hLayout->addWidget(diameter);
	this->hLayout->addWidget(viewButton);
	this->hLayout->addWidget(addStarButton);
	this->hLayout->addWidget(seeMyStars);
	this->hLayout->addWidget(starSearcher);
	this->populateList();
	connectButtons();

}

void GUI::update()
{
	this->populateList();
}

void GUI::closeEvent(QCloseEvent* event)
{
	this->starService.write();
	event->accept();
}

void GUI::viewButtonHandler()
{
	int index = this->getSelectedIndex();
	Stars s = this->starService.getRepo()[index];
	QWidget* w = new QWidget{};
	QPainter painter(w);
	
	
	QDialog* openDialog = new QDialog{};
	QHBoxLayout* dialogLayout = new QHBoxLayout{ openDialog };
	QListWidget* dialogList = new QListWidget{};
//	QListWidget* dialogList = new QListWidget{};
//	QPaintEvent* p = new QPaintEvent;
	//QBoxLayout* bLayout = new QBoxLayout{ openDialog };
	
	dialogLayout->addWidget(dialogList);
	if (dialogList->count() > 0)
		dialogList->clear();
	try {
		for (auto star : this->starService.getRepo())
		{
			if (star.getConstellation() == s.getConstellation()) {
				/*QString itemInList = QString::fromStdString(star.toString());
				QListWidgetItem* item = new QListWidgetItem{ itemInList };
				dialogList->addItem(item);*/
				QRect geo = w->geometry();
				int x, y;
				x = geo.x() - 10;
				y = geo.y() - 10;
				painter.fillRect(star.getRa(), star.getDec(), star.getDiam(), star.getDiam(), QColor(220, 220, 220));
				//painter.drawRect(x + 10, y + 10, QString::fromStdString(star.getName()));
			}
		}
		w->show();
	}
	catch (exception& e) {
			QMessageBox msg;
			msg.setText(e.what());
			msg.show();
		}


		try {
			for (auto star : this->starService.getRepo())
			{
				if (star.getConstellation() == s.getConstellation()) {
					QString itemInList = QString::fromStdString(star.toString());
					QListWidgetItem* item = new QListWidgetItem{ itemInList };
					dialogList->addItem(item);
					//QRect geo = w->geometry();
					//int x, y;
					//x = geo.x() - 10;
					//y = geo.y() - 10;
					//painter.fillRect(star.getRa(), star.getDec(), star.getDiam(), star.getDiam(), QColor(220, 220, 220));
					//painter.drawRect(x + 10, y + 10, QString::fromStdString(star.getName()));
				}
			}
		}
		catch (exception& e) {
			QMessageBox msg;
			msg.setText(e.what());
			msg.show();
		}
		if (this->starService.getRepo().size() > 0)
			dialogList->setCurrentRow(0);

		openDialog->exec();

	
}

int GUI::getSelectedIndex()
{
	if (this->stars->count() == 0)
		return -1;
	QModelIndexList index = this->stars->selectionModel()->selectedIndexes();

	if (index.size() == 0) {
		return -1;
	}
	int indexAtRow = index.at(0).row();
	return indexAtRow;
}


void GUI::addStarButtonHandler()
{
	//this button will take the information from the QLineEdit widgets and translate them wether into int or string
	//the constellation will automatically be the one that the astronomer has and adds it to the displayed list
	//it then calls the function from the service to create the object and add it to the repo; --->>>>to be continued in service


	//	Stars(string name, string constellation, int ra, int dec, int diameter)
	std::string name = this->starName->text().toStdString(), constellation = this->a.getConstellation();
	int ra = this->ra->text().toInt(), dec = this->dec->text().toInt(), diameter = this->diameter->text().toInt();
	try {
		this->starService.add(name, constellation, ra, dec, diameter);
		//this->update();
		this->populateList();
	}
	catch (exception& e) {
		QMessageBox msg;
		msg.setText(e.what());
		msg.exec();
	}
}

void GUI::checkBoxHandler()
{
	if (this->stars->count() > 0)
		this->stars->clear();
	if (this->seeMyStars->isChecked()) {
		for (auto star : this->starService.getRepo())
		{
			if (star.getConstellation() == this->a.getConstellation()) {
				QString itemInList = QString::fromStdString(star.toString());
				QListWidgetItem* item = new QListWidgetItem{ itemInList };
				this->stars->addItem(item);
			}
		}
		if (this->starService.getRepo().size() > 0)
			this->stars->setCurrentRow(0);
	}
	else {
		this->populateList();
	}
}

void GUI::starSearcherHandler()
{
	if (this->stars->count() > 0)
		this->stars->clear();
	for (auto star : this->starService.getRepo()) {
		if (star.getName().find(this->starSearcher->text().toStdString()) != std::string::npos)
		{
			QString itemInList = QString::fromStdString(star.toString());
			QListWidgetItem* item = new QListWidgetItem{ itemInList };
			this->stars->addItem(item);
			
		}
	}
	if (this->starService.getRepo().size() > 0)
		this->stars->setCurrentRow(0);
	if (this->starSearcher->text().toStdString() == "")
		this->populateList();
}

void GUI::connectButtons()
{
	QObject::connect(this->seeMyStars, &QCheckBox::clicked, this, &GUI::checkBoxHandler);
	//QObject::connect(this->seeMyStars, &QCheckBox::, this, &GUI::checkBoxHandler)
	QObject::connect(this->addStarButton, &QPushButton::clicked, this, &GUI::addStarButtonHandler);
	QObject::connect(this->starSearcher, &QLineEdit::textChanged, this, &GUI::starSearcherHandler);
	QObject::connect(this->viewButton, &QPushButton::clicked, this, &GUI::viewButtonHandler);
	//QObject::connect(this->addStarButton, &QPushButton::clicked, update);
	//QObject::connect(this->closeEvent, &QCl )

}

void GUI::populateList()
{
	if (this->stars->count() > 0)
		this->stars->clear();
	try {
		for (auto star : this->starService.getRepo())
		{
			QString itemInList = QString::fromStdString(star.toString());
			QListWidgetItem* item = new QListWidgetItem{ itemInList };
			this->stars->addItem(item);
		}
	}
	catch (exception& e) {
		QMessageBox msg;
		msg.setText(e.what());
		msg.show();
	}
	if (this->starService.getRepo().size() > 0)
		this->stars->setCurrentRow(0);
}
