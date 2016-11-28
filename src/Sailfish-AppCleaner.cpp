
#include <QtQuick>
#include <sailfishapp.h>
#include "cleaner.h"

int main(int argc, char *argv[]) {

	// так надо
	QScopedPointer<QGuiApplication> application(SailfishApp::application(argc, argv));
	QScopedPointer<QQuickView> view(SailfishApp::createView());
	// смарт поинтер на экземпляр нашего класса
	QScopedPointer<Cleaner> hCleaner(new Cleaner(view.data()));
	view->rootContext()->setContextProperty("h_cleaner", hCleaner.data());
	view->setSource(SailfishApp::pathTo("qml/Sailfish-AppCleaner.qml"));
	view->show();
	return application->exec();

	/*
	qmlRegisterType<Cleaner>("org.yukhnin.cleaner",1, 0, "QMLCleaner");
	return SailfishApp::main(argc, argv);
	*/
}

