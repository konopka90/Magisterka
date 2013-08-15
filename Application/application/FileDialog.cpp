#include "FileDialog.h"

FileDialog::FileDialog()
{
}


QString FileDialog::openFile()
{
    mIsGood = true;

    QFileDialog fd;
    QString file = fd.getOpenFileName(0,QString("Select file"));

    QFile f(file);
    if(file == "" || !f.exists())
    {
        mIsGood = false;
    }

    return file;
}

bool FileDialog::isGood() const
{
    return mIsGood;
}
