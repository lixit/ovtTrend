#include <QtWidgets>

#include "ovttrend.h"
#include "iconeditor.h"
#include "plotter.h"


MainWindow::MainWindow()
{
	createLeftTop();
	createLeftBottom();
	createDock();

	spreadsheet = new QSplitter(Qt::Vertical);
	spreadsheet->addWidget(scrollArea);
	spreadsheet->addWidget(LeftBottomTab);

	spreadsheet->setStretchFactor(1, 1);

	setCentralWidget(spreadsheet);

	createActions();
	createMenus();
	createContextMenu();
	createToolBars();
	createStatusBar();

	readSettings();

	setWindowIcon(QIcon(":/images/icon.png"));
	setCurrentFile("");

	QTimer::singleShot(0, this, SLOT(loadFiles()));
}

void MainWindow::createLeftTop()
{
	QStringList messageLabels;
	messageLabels << tr("Point Name") << tr("Description") << tr("End Value") << tr("Units") << tr("Low Scale") << tr("High Scale");

	pointsTreeWidget = new QTreeWidget;
	pointsTreeWidget->setHeaderLabels(messageLabels);
	addMessage(tr("Point name 1"),
			   tr("This is point 1 description"),
			   tr("66666"));
	addMessage(tr("Point name 2"),
			   tr("Try to say something"),
			   tr("99999"));
	pointsTreeWidget->resizeColumnToContents(0);
	pointsTreeWidget->resizeColumnToContents(1);


	scrollArea = new QScrollArea;
	scrollArea->setWidget(pointsTreeWidget);
	scrollArea->setWindowTitle(QObject::tr("Points List Info"));
	scrollArea->setWidgetResizable(true);

}

void MainWindow::addMessage(const QString &subject, const QString &from,
							const QString &date)
{
	QTreeWidgetItem *newItem = new QTreeWidgetItem(pointsTreeWidget);
	newItem->setText(0, subject);
	newItem->setText(1, from);
	newItem->setText(2, date);

	if (!pointsTreeWidget->currentItem())
		pointsTreeWidget->setCurrentItem(newItem);
}


void MainWindow::createLeftBottom()
{
	Graph = new Plotter;

	QStringList messageLabels;
	messageLabels << tr("Date Time") << tr("Vaule") << tr("Low") << tr("High");

	detailTreeWidget = new QTreeWidget;
	detailTreeWidget->setHeaderLabels(messageLabels);

	QTreeWidgetItem *newItem = new QTreeWidgetItem(detailTreeWidget);
	newItem->setText(0, tr("2019-6-20 13:50"));
	newItem->setText(1, tr("1000"));
	newItem->setText(2, tr("2"));
	newItem->setText(3, tr("5000"));

	detailTreeWidget->resizeColumnToContents(0);
	detailTreeWidget->resizeColumnToContents(1);

	LeftBottomTab = new QTabWidget;
	LeftBottomTab->addTab(Graph, QObject::tr("Graph"));
	LeftBottomTab->addTab(detailTreeWidget, QObject::tr("Table view"));
}

void MainWindow::createDock()
{
	QStringList messageLabels;
	messageLabels << tr("Name") << tr("Location");

	dockTree = new QTreeWidget;
	dockTree->setHeaderLabels(messageLabels);

	QTreeWidgetItem *newItem = new QTreeWidgetItem(dockTree);
	newItem->setText(0, tr("something"));


	dockWidget = new QDockWidget(tr("Property"));
	dockWidget->setObjectName("propertyDockWidget");
	dockWidget->setWidget(dockTree);
	dockWidget->setAllowedAreas(Qt::LeftDockWidgetArea
	| Qt::RightDockWidgetArea);
	addDockWidget(Qt::RightDockWidgetArea, dockWidget);

	setCorner(Qt::TopRightCorner,Qt::LeftDockWidgetArea);

}

void MainWindow::closeEvent(QCloseEvent *event)
{
	if (okToContinue()) {
		writeSettings();
		event->accept();
	} else {
		event->ignore();
	}
}

void MainWindow::loadFiles()  //handle command line parameters
{
	QStringList args = QApplication::arguments();
	args.removeFirst();
	if (!args.isEmpty()) {
		foreach (QString arg, args)
			open();
	} else {
		newFile();
	}
}


void MainWindow::newFile()
{
	if (okToContinue()) {

		setCurrentFile("");
	}
}

void MainWindow::open()
{
	if (okToContinue()) {
		QString fileName = QFileDialog::getOpenFileName(this,
								   tr("Open Spreadsheet"), "/home/x/Desktop",
								   tr("Spreadsheet files (*.sp)\n"
									"Comma_separated values files (*.csv)\n"
									"Lotus 1-2-3 files (*wk1 *wks)"
									 ));
		if (!fileName.isEmpty())
			loadFile(fileName);
	}
}

bool MainWindow::save()
{
	if (curFile.isEmpty()) {
		return saveAs();
	} else {
		return saveFile(curFile);
	}
}

bool MainWindow::saveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
							   tr("Save Spreadsheet"), ".",
							   tr("Spreadsheet files (*.sp)"));
	if (fileName.isEmpty())
		return false;

	return saveFile(fileName);
}

void MainWindow::find()
{
//	if (!findDialog) {
//		findDialog = new FindDialog(this);
//		connect(findDialog, SIGNAL(findNext(const QString &,
//											Qt::CaseSensitivity)),
//				spreadsheet, SLOT(findNext(const QString &,
//										   Qt::CaseSensitivity)));
//		connect(findDialog, SIGNAL(findPrevious(const QString &,
//												Qt::CaseSensitivity)),
//				spreadsheet, SLOT(findPrevious(const QString &,
//											   Qt::CaseSensitivity)));
//	}

//	findDialog->show();
//	findDialog->raise();
//	findDialog->activateWindow();
}

void MainWindow::goToCell()
{
//	GoToCellDialog dialog(this);
//	if (dialog.exec()) {
//		QString str = dialog.lineEdit->text().toUpper();
//		spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,
//									str[0].unicode() - 'A');
//	}
}

void MainWindow::sort()
{
//	SortDialog dialog(this);
//	QTableWidgetSelectionRange range = spreadsheet->selectedRange();
//	dialog.setColumnRange('A' + range.leftColumn(),
//						  'A' + range.rightColumn());

//	if (dialog.exec()) {
//		SpreadsheetCompare compare;
//		compare.keys[0] =
//			  dialog.primaryColumnCombo->currentIndex();
//		compare.keys[1] =
//			  dialog.secondaryColumnCombo->currentIndex() - 1;
//		compare.keys[2] =
//			  dialog.tertiaryColumnCombo->currentIndex() - 1;
//		compare.ascending[0] =
//			  (dialog.primaryOrderCombo->currentIndex() == 0);
//		compare.ascending[1] =
//			  (dialog.secondaryOrderCombo->currentIndex() == 0);
//		compare.ascending[2] =
//			  (dialog.tertiaryOrderCombo->currentIndex() == 0);
//		spreadsheet->sort(compare);
//	}
}


void MainWindow::about()
{
	QMessageBox::about(this, tr("About OvtTrend"),
			tr("<h2>OvtTrend Alpha</h2>"
			   "<p>Copyright &copy; 2019 Xitong Inc."
			   "<p>OvtTrend is a small application that "
			   "demonstrates QAction, QMainWindow, QMenuBar, "
			   "QStatusBar, QTableWidget, QToolBar, and many other "
			   "Qt classes."));
}

void MainWindow::openRecentFile()
{
	if (okToContinue()) {
		QAction *action = qobject_cast<QAction *>(sender());
		if (action)
			loadFile(action->data().toString());
	}
}

void MainWindow::updateStatusBar()
{
//	locationLabel->setText(spreadsheet->currentLocation());
//	formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified()
{
	setWindowModified(true);
	updateStatusBar();
}

void MainWindow::createActions()
{
	newAction = new QAction(tr("&New"), this);
	newAction->setIcon(QIcon(":/images/new.png"));
	newAction->setShortcut(QKeySequence::New);
	newAction->setStatusTip(tr("Create a new spreadsheet file"));
	connect(newAction, SIGNAL(triggered()), this, SLOT(newFile()));

	openAction = new QAction(tr("&Open..."), this);
	openAction->setIcon(QIcon(":/images/open.png"));
	openAction->setShortcut(QKeySequence::Open);
	openAction->setStatusTip(tr("Open an existing spreadsheet file"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

	saveAction = new QAction(tr("&Save"), this);
	saveAction->setIcon(QIcon(":/images/save.png"));
	saveAction->setShortcut(QKeySequence::Save);
	saveAction->setStatusTip(tr("Save the spreadsheet to disk"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

	saveAsAction = new QAction(tr("Save &As..."), this);
	saveAsAction->setStatusTip(tr("Save the spreadsheet under a new "
								  "name"));
	connect(saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

	for (int i = 0; i < MaxRecentFiles; ++i) {
		recentFileActions[i] = new QAction(this);
		recentFileActions[i]->setVisible(false);
		connect(recentFileActions[i], SIGNAL(triggered()),
				this, SLOT(openRecentFile()));
	}

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+Q"));
	exitAction->setStatusTip(tr("Exit the application"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	cutAction = new QAction(tr("Cu&t"), this);
	cutAction->setIcon(QIcon(":/images/cut.png"));
	cutAction->setShortcut(QKeySequence::Cut);
	cutAction->setStatusTip(tr("Cut the current selection's contents "
							   "to the clipboard"));
//	connect(cutAction, SIGNAL(triggered()), spreadsheet, SLOT(cut()));

	copyAction = new QAction(tr("&Copy"), this);
	copyAction->setIcon(QIcon(":/images/copy.png"));
	copyAction->setShortcut(QKeySequence::Copy);
	copyAction->setStatusTip(tr("Copy the current selection's contents "
								"to the clipboard"));
//	connect(copyAction, SIGNAL(triggered()), spreadsheet, SLOT(copy()));

	pasteAction = new QAction(tr("&Paste"), this);
	pasteAction->setIcon(QIcon(":/images/paste.png"));
	pasteAction->setShortcut(QKeySequence::Paste);
	pasteAction->setStatusTip(tr("Paste the clipboard's contents into "
								 "the current selection"));
//	connect(pasteAction, SIGNAL(triggered()),
//			spreadsheet, SLOT(paste()));

	deleteAction = new QAction(tr("&Delete"), this);
	deleteAction->setShortcut(QKeySequence::Delete);
	deleteAction->setStatusTip(tr("Delete the current selection's "
								  "contents"));
//	connect(deleteAction, SIGNAL(triggered()),
//			spreadsheet, SLOT(del()));

	selectRowAction = new QAction(tr("&Row"), this);
	selectRowAction->setStatusTip(tr("Select all the cells in the "
									 "current row"));
//	connect(selectRowAction, SIGNAL(triggered()),
//			spreadsheet, SLOT(selectCurrentRow()));

	selectColumnAction = new QAction(tr("&Column"), this);
	selectColumnAction->setStatusTip(tr("Select all the cells in the "
										"current column"));
//	connect(selectColumnAction, SIGNAL(triggered()),
//			spreadsheet, SLOT(selectCurrentColumn()));

	selectAllAction = new QAction(tr("&All"), this);
	selectAllAction->setShortcut(QKeySequence::SelectAll);
	selectAllAction->setStatusTip(tr("Select all the cells in the "
									 "spreadsheet"));
//	connect(selectAllAction, SIGNAL(triggered()),
//			spreadsheet, SLOT(selectAll()));

	findAction = new QAction(tr("&Find..."), this);
	findAction->setIcon(QIcon(":/images/find.png"));
	findAction->setShortcut(QKeySequence::Find);
	findAction->setStatusTip(tr("Find a matching cell"));
	connect(findAction, SIGNAL(triggered()), this, SLOT(find()));

	goToCellAction = new QAction(tr("&Go to Cell..."), this);
	goToCellAction->setIcon(QIcon(":/images/gotocell.png"));
	goToCellAction->setShortcut(tr("Ctrl+G"));
	goToCellAction->setStatusTip(tr("Go to the specified cell"));
	connect(goToCellAction, SIGNAL(triggered()),
			this, SLOT(goToCell()));

	recalculateAction = new QAction(tr("&Recalculate"), this);
	recalculateAction->setShortcut(tr("F9"));
	recalculateAction->setStatusTip(tr("Recalculate all the "
									   "spreadsheet's formulas"));
//	connect(recalculateAction, SIGNAL(triggered()),
//			spreadsheet, SLOT(recalculate()));

	sortAction = new QAction(tr("&Sort..."), this);
	sortAction->setStatusTip(tr("Sort the selected cells or all the "
								"cells"));
	connect(sortAction, SIGNAL(triggered()), this, SLOT(sort()));

	showGridAction = new QAction(tr("&Show Grid"), this);
	showGridAction->setCheckable(true);

	showGridAction->setStatusTip(tr("Show or hide the spreadsheet's "
									"grid"));
//	connect(showGridAction, SIGNAL(toggled(bool)),
//			spreadsheet, SLOT(setShowGrid(bool)));
#if QT_VERSION < 0x040102
	// workaround for a QTableWidget bug in Qt 4.1.1
	connect(showGridAction, SIGNAL(toggled(bool)),
			spreadsheet->viewport(), SLOT(update()));
#endif

	autoRecalcAction = new QAction(tr("&Auto-Recalculate"), this);
	autoRecalcAction->setCheckable(true);
//	autoRecalcAction->setChecked(spreadsheet->autoRecalculate());
	autoRecalcAction->setStatusTip(tr("Switch auto-recalculation on or "
									  "off"));
//	connect(autoRecalcAction, SIGNAL(toggled(bool)),
//			spreadsheet, SLOT(setAutoRecalculate(bool)));

	aboutAction = new QAction(tr("&About"), this);
	aboutAction->setStatusTip(tr("Show the application's About box"));
	connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

	aboutQtAction = new QAction(tr("About &Qt"), this);
	aboutQtAction->setStatusTip(tr("Show the Qt library's About box"));
	connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(saveAsAction);
	separatorAction = fileMenu->addSeparator();
	for (int i = 0; i < MaxRecentFiles; ++i)
		fileMenu->addAction(recentFileActions[i]);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	editMenu = menuBar()->addMenu(tr("&Edit"));
	editMenu->addAction(cutAction);
	editMenu->addAction(copyAction);
	editMenu->addAction(pasteAction);
	editMenu->addAction(deleteAction);

	selectSubMenu = editMenu->addMenu(tr("&Select"));
	selectSubMenu->addAction(selectRowAction);
	selectSubMenu->addAction(selectColumnAction);
	selectSubMenu->addAction(selectAllAction);

	editMenu->addSeparator();
	editMenu->addAction(findAction);
	editMenu->addAction(goToCellAction);

	toolsMenu = menuBar()->addMenu(tr("&Tools"));
	toolsMenu->addAction(recalculateAction);
	toolsMenu->addAction(sortAction);

	optionsMenu = menuBar()->addMenu(tr("&Options"));
	optionsMenu->addAction(showGridAction);
	optionsMenu->addAction(autoRecalcAction);

	menuBar()->addSeparator();

	helpMenu = menuBar()->addMenu(tr("&Help"));
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

void MainWindow::createContextMenu()
{
	spreadsheet->addAction(cutAction);
	spreadsheet->addAction(copyAction);
	spreadsheet->addAction(pasteAction);
	spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("&File"));
	fileToolBar->addAction(newAction);
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(saveAction);

	editToolBar = addToolBar(tr("&Edit"));
	editToolBar->addAction(cutAction);
	editToolBar->addAction(copyAction);
	editToolBar->addAction(pasteAction);
	editToolBar->addSeparator();
	editToolBar->addAction(findAction);
	editToolBar->addAction(goToCellAction);
}

void MainWindow::createStatusBar()
{
	locationLabel = new QLabel(" Program loaded! ");
	locationLabel->setAlignment(Qt::AlignHCenter);
	locationLabel->setMinimumSize(locationLabel->sizeHint());

	formulaLabel = new QLabel;
	formulaLabel->setIndent(3);

	statusBar()->addWidget(locationLabel);
	statusBar()->addWidget(formulaLabel, 1);

	connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)),
			this, SLOT(updateStatusBar()));
	connect(spreadsheet, SIGNAL(modified()),
			this, SLOT(spreadsheetModified()));

	updateStatusBar();
}

void MainWindow::readSettings()
{
	QSettings settings("QtSpreedSheetInc.", "Spreadsheet");

	restoreGeometry(settings.value("geometry").toByteArray());

	recentFiles = settings.value("recentFiles").toStringList();
	updateRecentFileActions();

	bool showGrid = settings.value("showGrid", true).toBool();
	showGridAction->setChecked(showGrid);

	bool autoRecalc = settings.value("autoRecalc", true).toBool();
	autoRecalcAction->setChecked(autoRecalc);
}

void MainWindow::writeSettings()
{
	QSettings settings("QtSpreedSheetInc.", "Spreadsheet");

	settings.setValue("geometry", saveGeometry());
	settings.setValue("recentFiles", recentFiles);
	settings.setValue("showGrid", showGridAction->isChecked());
	settings.setValue("autoRecalc", autoRecalcAction->isChecked());
	qDebug() << settings.fileName();
}

bool MainWindow::okToContinue()
{
	if (isWindowModified()) {
		int r = QMessageBox::warning(this, tr("Spreadsheet"),
						tr("The document has been modified.\n"
						   "Do you want to save your changes?"),
						QMessageBox::Yes | QMessageBox::No
						| QMessageBox::Cancel);
		if (r == QMessageBox::Yes) {
			return save();
		} else if (r == QMessageBox::Cancel) {
			return false;
		}
	}
	return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
//	if (!spreadsheet->readFile(fileName)) {
//		statusBar()->showMessage(tr("Loading canceled"), 2000);
//		return false;
//	}

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File loaded"), 2000);
	return true;
}

bool MainWindow::saveFile(const QString &fileName)
{
//	if (!spreadsheet->writeFile(fileName)) {
//		statusBar()->showMessage(tr("Saving canceled"), 2000);
//		return false;
//	}

	setCurrentFile(fileName);
	statusBar()->showMessage(tr("File saved"), 2000);
	return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
	curFile = fileName;
	setWindowModified(false);

	QString shownName = tr("Untitled");
	if (!curFile.isEmpty()) {
		shownName = strippedName(curFile);
		recentFiles.removeAll(curFile);
		recentFiles.prepend(curFile);
		updateRecentFileActions();
	}

	setWindowTitle(tr("%1[*] - %2").arg(shownName)
								   .arg(tr("OvtTrend")));
}

void MainWindow::updateRecentFileActions()
{
	QMutableStringListIterator i(recentFiles);
	while (i.hasNext()) {
		if (!QFile::exists(i.next()))
			i.remove();
	}

	for (int j = 0; j < MaxRecentFiles; ++j) {
		if (j < recentFiles.count()) {
			QString text = tr("&%1 %2")
						   .arg(j + 1)
						   .arg(strippedName(recentFiles[j]));
			recentFileActions[j]->setText(text);
			recentFileActions[j]->setData(recentFiles[j]);
			recentFileActions[j]->setVisible(true);
		} else {
			recentFileActions[j]->setVisible(false);
		}
	}
	separatorAction->setVisible(!recentFiles.isEmpty());
}

QString MainWindow::strippedName(const QString &fullFileName)
{
	return QFileInfo(fullFileName).fileName();
}
