#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QObject>
#include <QFileDialog>

class FileDialog : public QObject
{
    Q_OBJECT

public:
    FileDialog();

    /**
     * Opens file dialog.
     * @return Filename of selected file.
     */
    QString openFile();

    /**
     * Checks if user selected file or user pressed cancel button
     * @return True if file is properly opened. Otherwise false.
     */
    bool isGood() const;

private:
    bool mIsGood;
};

#endif // FILEDIALOG_H
