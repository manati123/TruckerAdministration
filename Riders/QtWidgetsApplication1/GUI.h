#pragma once
#include <QPushButton>
#include <QListWidget>
#include <QString>
#include <QLineEdit>
#include <QHBoxLayout>
#include "Domain.h"
#include "Service.h"
#include <QDialog>
#include <qwidget.h>
#include <QCheckBox>
#include <QTableView>
#include "Observer.h"
class GUI : public QWidget, public Observer
{
	Q_OBJECT
public:
	GUI(Astronomer& a,StarService& starService, AstroService& astroService, QWidget* parent = Q_NULLPTR);
	void init();
	void update() override;
	//~GUI() { this->starService.write(); }
private:
	//void closeHandler();
	Astronomer a;
	//QCloseEvent* closeEvent;
	void closeEvent(QCloseEvent* event);
	QPushButton* viewButton;
	void viewButtonHandler();
	int getSelectedIndex();
	AstroService& astroService;
	StarService& starService;
	QListWidget* stars;
	QHBoxLayout* hLayout;
	QLineEdit* starName;
	QLineEdit* ra;
	QLineEdit* dec;
	QLineEdit* diameter;
	QPushButton* addStarButton;
	QCheckBox* seeMyStars;
	QLineEdit* starSearcher;
	void addStarButtonHandler();
	void checkBoxHandler();
	void starSearcherHandler();
	void connectButtons();
	void populateList();
	
signals:
	void itemsUpdatedSignal();
};

