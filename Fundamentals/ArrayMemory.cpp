/*//////////////////////////////////////////////////////////////////
////       SKIRT -- an advanced radiative transfer code         ////
////       © Astronomical Observatory, Ghent University         ////
///////////////////////////////////////////////////////////////// */

#ifdef BUILDING_MEMORY
#include <QDateTime>
#include <QFileInfo>
#include "ArrayMemory.hpp"
#include "ProcessManager.hpp"
#endif

////////////////////////////////////////////////////////////////////

// Initialize static data members
QString ArrayMemory::_outputPath("");
QString ArrayMemory::_outputPrefix("");
QString ArrayMemory::_procNameShort("");
QString ArrayMemory::_procNameLong("");
QFile ArrayMemory::_file;
QTextStream ArrayMemory::_out;

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
void ArrayMemory::initialize(QString prefix, QString path)
{
    // Set the output prefix
    _outputPrefix = prefix;

    // Set the output path
    if (path.isEmpty()) _outputPath = "";
    else
    {
        QFileInfo test(path);
        if (!test.isDir()) throw std::runtime_error("Output path does not exist or is not a directory: " + path.toStdString());
        _outputPath = test.canonicalFilePath() + "/";
    }

    // Set the process name
    if (ProcessManager::isMultiProc())
    {
        _procNameShort = QString("P%1").arg(ProcessManager::rank(), 3, 10, QChar('0'));
        _procNameLong = "[" + _procNameShort + "] ";
    }

    // Determine the path of the log file
    QString filepath;
    if (ProcessManager::isRoot())
    {
        filepath = outFilePath("memory.txt");
    }
    else
    {
        filepath = outFilePath( "memory" + _procNameShort + ".txt");
    }

    _file.setFileName(filepath);
    if (!_file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Could not open the log file " + filepath.toStdString());

    _out.setDevice(&_file);
    _out.setCodec("UTF-8");
}
#endif

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
void ArrayMemory::finalize()
{
    if (_file.isOpen())
    {
        _out.flush();
        _file.close();
    }
}
#endif

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
QString ArrayMemory::outFilePath(QString name)
{
    return _outputPath + _outputPrefix + "_" + name;
}
#endif

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
void ArrayMemory::log_resize(size_t oldsize, size_t newsize)
{
    // Calculate the change in memory (in GB)
    double delta;
    if (oldsize < newsize) delta = (newsize - oldsize) * 8 * 1e-9;
    else if (oldsize > newsize) delta = (oldsize - newsize) * 8 * 1e-9;
    else delta = 0;

    // Log the amount of gained or released memory to the console, if larger than a certain threshold
    if (delta > 1e-5)
    {
        if (oldsize < newsize) log("+" + QString::number(delta) + " GB");
        else if (oldsize > newsize) log("-" + QString::number(delta) + " GB");
    }
}
#endif

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
void ArrayMemory::log(QString message)
{
    output(timestamp() + "   " + _procNameLong + message);
}
#endif

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
void ArrayMemory::output(QString message)
{
    if (_file.isOpen())
    {
        //std::unique_lock<std::mutex> lock(_mutex);
        _out << message << endl;
    }
}
#endif

//////////////////////////////////////////////////////////////////////

#ifdef BUILDING_MEMORY
QString ArrayMemory::timestamp()
{
    return QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss.zzz");
}
#endif

//////////////////////////////////////////////////////////////////////

