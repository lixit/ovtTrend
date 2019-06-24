#ifndef OVTTREND_H
#define OVTTREND_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtCharts>
using namespace QtCharts;


class Plotter;
class IconEditor;
class QAction;
class QLabel;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

protected:
	void closeEvent(QCloseEvent *event);

private slots:
	void loadFiles();  //command line parameters
	void newFile();
	void open();
	bool save();
	bool saveAs();
	void find();
	void goToCell();
	void sort();
	void about();
	void openRecentFile();
	void updateStatusBar();
	void spreadsheetModified();

private:
	void createActions();
	void createMenus();
	void createContextMenu();
	void createToolBars();
	void createStatusBar();
	void readSettings();
	void writeSettings();
	bool okToContinue();
	bool loadFile(const QString &fileName);
	bool saveFile(const QString &fileName);
	void setCurrentFile(const QString &fileName);
	void updateRecentFileActions();

	void createLeftTop();
	void createLeftBottom();
	void createDock();

	void addMessage(const QString &subject, const QString &from,
					const QString &date);
	QString strippedName(const QString &fullFileName);

	QTreeWidget *pointsTreeWidget;
	QScrollArea *scrollArea; //左上角点列表
	QChartView *Graph;
	QTableView *LeftBottomTableView;
	QTreeWidget *detailTreeWidget;
	QTabWidget * LeftBottomTab; //左下角视图
	QTreeWidget *dockTree;
	QDockWidget *dockWidget; //右边点属性
	QSplitter *spreadsheet; //主页面


//	FindDialog *findDialog;
	QLabel *locationLabel;
	QLabel *formulaLabel;
	QStringList recentFiles;
	QString curFile;

	enum { MaxRecentFiles = 5 };
	QAction *recentFileActions[MaxRecentFiles];
	QAction *separatorAction;

//	QMenu *homeMenu;
	QAction *homeAction;
	QMenu *formatMenu;
	QMenu *trendMenu;
	QMenu *helpMenu;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;

	QAction *newAction;
	QAction *openAction;
	QAction *saveAction;
	QAction *saveAsAction;
	QAction *exitAction;
	QAction *cutAction;
	QAction *copyAction;
	QAction *pasteAction;
	QAction *deleteAction;

	QAction *pauseAction;
	QAction *refreshAction;

	QAction *selectRowAction;
	QAction *selectColumnAction;
	QAction *selectAllAction;
	QAction *recalculateAction;
	QAction *sortAction;
	QAction *showGridAction;
	QAction *autoRecalcAction;
	QAction *aboutAction;
	QAction *aboutQtAction;
};


#endif // OVTTREND_H
