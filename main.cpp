#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <algorithm>
#include <thread>
#include <cctype>

using namespace std;
namespace fs = std::filesystem;

const string ROOT_DIR = "EDORA_DRIVES";

fs::path currentPath = fs::path(ROOT_DIR) / "C";
string currentDrive = "C:";
string currentUser = "user";

bool running = true;
bool panicMode = false;

vector<string> commandHistory;

bool insideDrive(const fs::path& path)
{
    try
    {
        fs::path driveRoot =
            fs::weakly_canonical(
                fs::path(ROOT_DIR) / currentDrive.substr(0, 1)
            );

        fs::path target =
            fs::weakly_canonical(path);

        string root = driveRoot.generic_string();
        string targetStr = target.generic_string();

        if (targetStr == root)
            return true;

        if (targetStr.size() > root.size() &&
            targetStr.compare(0, root.size(), root) == 0 &&
            targetStr[root.size()] == '/')
            return true;

        return false;
    }
    catch (...)
    {
        return false;
    }
}

fs::path resolvePath(const string& input)
{
    if (input.empty())
        return currentPath;

    fs::path p(input);

    if (p.is_absolute())
    {
        string s = p.string();

        if (s.size() >= 2 && s[1] == ':')
        {
            char drive = toupper(s[0]);

            if (drive == 'C' ||
                drive == 'D' ||
                drive == 'E')
            {
                string rest = s.substr(2);

                if (!rest.empty() &&
                    (rest[0] == '\\' ||
                     rest[0] == '/'))
                {
                    rest = rest.substr(1);
                }

                return fs::path(ROOT_DIR) /
                       string(1, drive) /
                       rest;
            }
        }

        return currentPath;
    }

    return currentPath / p;
}

string displayPath()
{
    fs::path driveRoot =
        fs::path(ROOT_DIR) /
        currentDrive.substr(0, 1);

    fs::path relative;

    try
    {
        relative = fs::relative(
            currentPath,
            driveRoot
        );
    }
    catch (...)
    {
        relative = "";
    }

    string result = currentDrive + "\\";

    if (!relative.empty() &&
        relative.string() != ".")
    {
        string r = relative.string();

        replace(
            r.begin(),
            r.end(),
            '/',
            '\\'
        );

        result += r;
    }

    return result;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void printHeader()
{
    cout << "\n";
    cout << "+================================================+\n";
    cout << "|                  EDORA OS                      |\n";
    cout << "|               EDO SHELL v1.3                   |\n";
    cout << "+================================================+\n";
    cout << "| Virtual Operating System                       |\n";
    cout << "| Virtual Filesystem : ONLINE                    |\n";
    cout << "| EDO Security       : ACTIVE                    |\n";
    cout << "| Network            : AVAILABLE                |\n";
    cout << "+================================================+\n";
}

void printStatus()
{
    cout << "\n";
    cout << "+------------------------------------------------+\n";
    cout << "| USER  : " << left << setw(38)
         << currentUser << "|\n";

    cout << "| DRIVE : " << left << setw(38)
         << currentDrive << "|\n";

    cout << "| PATH  : " << left << setw(38)
         << displayPath() << "|\n";

    cout << "+------------------------------------------------+\n";
}

void setupDrives()
{
    vector<string> drives =
    {
        "C",
        "D",
        "E"
    };

    for (const string& drive : drives)
    {
        fs::create_directories(
            fs::path(ROOT_DIR) / drive
        );
    }

    fs::create_directories(
        fs::path(ROOT_DIR) /
        "C" /
        "system"
    );

    fs::create_directories(
        fs::path(ROOT_DIR) /
        "C" /
        "programs"
    );

    fs::create_directories(
        fs::path(ROOT_DIR) /
        "D" /
        "games"
    );

    fs::create_directories(
        fs::path(ROOT_DIR) /
        "D" /
        "data"
    );

    fs::create_directories(
        fs::path(ROOT_DIR) /
        "E" /
        "backup"
    );
}

void showHelp()
{
    cout << "\n";
    cout << "+================================================+\n";
    cout << "|                 EDORA COMMANDS                 |\n";
    cout << "+================================================+\n";

    cout << "help                       Show help\n";
    cout << "clear                      Clear screen\n";
    cout << "about                      About EDORA OS\n";
    cout << "whoami                     Show current user\n";
    cout << "pwd                        Show current path\n";
    cout << "drives                     Show virtual drives\n";

    cout << "\nFILESYSTEM\n";
    cout << "dir / ls                   List files\n";
    cout << "cd <folder>                Change directory\n";
    cout << "cd ..                      Go back\n";
    cout << "cd \\                       Drive root\n";
    cout << "mkdir <name>               Create folder\n";
    cout << "touch <file>               Create file\n";
    cout << "rm <name>                  Delete file/folder\n";
    cout << "cat <file>                 Read file\n";
    cout << "type <file>                Read file\n";
    cout << "copy <src> <dst>           Copy\n";
    cout << "move <src> <dst>           Move\n";
    cout << "rename <old> <new>         Rename\n";
    cout << "tree                       Directory tree\n";
    cout << "find <name>                Find file\n";

    cout << "\nTEXT TOOLS\n";
    cout << "echo <text>                Print text\n";
    cout << "grep <text> <file>         Search text\n";
    cout << "head <file>                First 10 lines\n";
    cout << "tail <file>                Last 10 lines\n";
    cout << "history                    Command history\n";

    cout << "\nEDITORS\n";
    cout << "bin <file>                 BIN editor\n";
    cout << "binread <file>             Read BIN\n";
    cout << "binhex <file>              HEX viewer\n";
    cout << "edo <file>                 EDO editor\n";
    cout << "edoread <file>             Decrypt EDO\n";
    cout << "edoraw <file>              Raw EDO\n";

    cout << "\nSYSTEM\n";
    cout << "time                       Real system time\n";
    cout << "date                       Real system date\n";
    cout << "datetime                   Date + time\n";
    cout << "clock                      Realtime clock\n";
    cout << "calc <a> <op> <b>          Calculator\n";
    cout << "ping <host>                Real network ping\n";
    cout << "neofetch                   EDORA info\n";
    cout << "sysinfo                    System information\n";

    cout << "\nSECURITY\n";
    cout << "sudo                       Root access\n";
    cout << "root                       Root status\n";

    cout << "\nOTHER\n";
    cout << "game                       Game menu\n";
    cout << "panic                      Kernel panic\n";
    cout << "delete systemcl -t         Delete simulation\n";
    cout << "reboot                     Reboot OS\n";
    cout << "shutdown                   Shutdown OS\n";
    cout << "exit                       Exit\n";

    cout << "+================================================+\n";
}

void showDrives()
{
    cout << "\nEDORA VIRTUAL DRIVES\n";
    cout << "--------------------\n";
    cout << "C:  System\n";
    cout << "D:  Data / Games\n";
    cout << "E:  Backup\n";
}

void listDirectory()
{
    cout << "\nDirectory of "
         << displayPath()
         << "\n\n";

    try
    {
        for (const auto& entry :
             fs::directory_iterator(currentPath))
        {
            if (entry.is_directory())
            {
                cout << "[DIR]  "
                     << entry.path()
                            .filename()
                            .string()
                     << "\n";
            }
            else
            {
                cout << "[FILE] "
                     << entry.path()
                            .filename()
                            .string()
                     << "\n";
            }
        }
    }
    catch (...)
    {
        cout << "Cannot access directory.\n";
    }
}

void makeDirectory(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: mkdir <name>\n";
        return;
    }

    fs::path p = resolvePath(name);

    if (!insideDrive(p))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        if (fs::create_directory(p))
            cout << "Directory created.\n";
        else
            cout << "Directory already exists.\n";
    }
    catch (...)
    {
        cout << "Failed to create directory.\n";
    }
}

void touchFile(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: touch <file>\n";
        return;
    }

    fs::path p = resolvePath(name);

    if (!insideDrive(p))
    {
        cout << "Access denied.\n";
        return;
    }

    ofstream file(p, ios::app);

    if (file)
        cout << "File created.\n";
    else
        cout << "Failed to create file.\n";
}

void readFile(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: cat <file>\n";
        return;
    }

    fs::path p = resolvePath(name);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(p);

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    cout << "\n";

    string line;

    while (getline(file, line))
        cout << line << "\n";
}

void removePath(const string& name)
{
    if (name.empty() ||
        name == "." ||
        name == "..")
    {
        cout << "Invalid target.\n";
        return;
    }

    fs::path p = resolvePath(name);

    if (!insideDrive(p))
    {
        cout << "Access denied.\n";
        return;
    }

    if (p ==
        fs::path(ROOT_DIR) /
        currentDrive.substr(0, 1))
    {
        cout << "Cannot delete drive root.\n";
        return;
    }

    try
    {
        if (fs::exists(p))
        {
            fs::remove_all(p);
            cout << "Deleted.\n";
        }
        else
        {
            cout << "Not found.\n";
        }
    }
    catch (...)
    {
        cout << "Delete failed.\n";
    }
}

void copyPath(
    const string& source,
    const string& destination)
{
    if (source.empty() ||
        destination.empty())
    {
        cout << "Usage: copy <src> <dst>\n";
        return;
    }

    fs::path src = resolvePath(source);
    fs::path dst = resolvePath(destination);

    if (!insideDrive(src) ||
        !insideDrive(dst))
    {
        cout << "Access denied.\n";
        return;
    }

    if (!fs::exists(src))
    {
        cout << "Source not found.\n";
        return;
    }

    try
    {
        if (fs::is_directory(dst))
            dst /= src.filename();

        fs::copy(
            src,
            dst,
            fs::copy_options::recursive |
            fs::copy_options::overwrite_existing
        );

        cout << "Copied successfully.\n";
    }
    catch (...)
    {
        cout << "Copy failed.\n";
    }
}

void movePath(
    const string& source,
    const string& destination)
{
    if (source.empty() ||
        destination.empty())
    {
        cout << "Usage: move <src> <dst>\n";
        return;
    }

    fs::path src = resolvePath(source);
    fs::path dst = resolvePath(destination);

    if (!insideDrive(src) ||
        !insideDrive(dst))
    {
        cout << "Access denied.\n";
        return;
    }

    if (!fs::exists(src))
    {
        cout << "Source not found.\n";
        return;
    }

    try
    {
        if (fs::is_directory(dst))
            dst /= src.filename();

        fs::rename(src, dst);

        cout << "Moved successfully.\n";
    }
    catch (...)
    {
        cout << "Move failed.\n";
    }
}

void renamePath(
    const string& oldName,
    const string& newName)
{
    if (oldName.empty() ||
        newName.empty())
    {
        cout << "Usage: rename <old> <new>\n";
        return;
    }

    fs::path oldPath =
        resolvePath(oldName);

    fs::path newPath =
        resolvePath(newName);

    if (!insideDrive(oldPath) ||
        !insideDrive(newPath))
    {
        cout << "Access denied.\n";
        return;
    }

    try
    {
        fs::rename(
            oldPath,
            newPath
        );

        cout << "Renamed successfully.\n";
    }
    catch (...)
    {
        cout << "Rename failed.\n";
    }
}

void printTree(
    const fs::path& path,
    string prefix = "")
{
    try
    {
        vector<fs::directory_entry> entries;

        for (const auto& entry :
             fs::directory_iterator(path))
        {
            entries.push_back(entry);
        }

        for (size_t i = 0;
             i < entries.size();
             i++)
        {
            bool last =
                (i == entries.size() - 1);

            cout << prefix;

            cout <<
                (last ? "`-- " : "|-- ");

            cout <<
                entries[i]
                    .path()
                    .filename()
                    .string();

            if (entries[i].is_directory())
            {
                cout << "\\\n";

                printTree(
                    entries[i].path(),
                    prefix +
                    (last ? "    " : "|   ")
                );
            }
            else
            {
                cout << "\n";
            }
        }
    }
    catch (...)
    {
    }
}

void showTree()
{
    cout << "\n"
         << displayPath()
         << "\\\n";

    printTree(currentPath);
}

void findFiles(
    const fs::path& path,
    const string& target)
{
    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(path))
        {
            string name =
                entry.path()
                     .filename()
                     .string();

            if (name.find(target) !=
                string::npos)
            {
                cout << displayPath()
                     << "\\"
                     << fs::relative(
                            entry.path(),
                            currentPath
                        ).string()
                     << "\n";
            }
        }
    }
    catch (...)
    {
    }
}

void findCommand(const string& target)
{
    if (target.empty())
    {
        cout << "Usage: find <name>\n";
        return;
    }

    bool found = false;

    try
    {
        for (const auto& entry :
             fs::recursive_directory_iterator(
                 currentPath))
        {
            string name =
                entry.path()
                     .filename()
                     .string();

            if (name.find(target) !=
                string::npos)
            {
                cout << "[FOUND] "
                     << fs::relative(
                            entry.path(),
                            currentPath
                        ).string()
                     << "\n";

                found = true;
            }
        }
    }
    catch (...)
    {
        cout << "Search error.\n";
    }

    if (!found)
        cout << "No matching files found.\n";
}

void echoCommand(const string& text)
{
    cout << text << "\n";
}

void showHistory()
{
    cout << "\nEDORA COMMAND HISTORY\n";
    cout << "---------------------\n";

    if (commandHistory.empty())
    {
        cout << "No commands.\n";
        return;
    }

    for (size_t i = 0;
         i < commandHistory.size();
         i++)
    {
        cout << setw(4)
             << i + 1
             << "  "
             << commandHistory[i]
             << "\n";
    }
}

void grepCommand(
    const string& search,
    const string& fileName)
{
    if (search.empty() ||
        fileName.empty())
    {
        cout << "Usage: grep <text> <file>\n";
        return;
    }

    fs::path p =
        resolvePath(fileName);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(p);

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    string line;
    int lineNumber = 0;
    bool found = false;

    while (getline(file, line))
    {
        lineNumber++;

        if (line.find(search) !=
            string::npos)
        {
            cout << lineNumber
                 << ": "
                 << line
                 << "\n";

            found = true;
        }
    }

    if (!found)
        cout << "No matches found.\n";
}

vector<string> loadLines(
    const string& fileName)
{
    vector<string> lines;

    fs::path p =
        resolvePath(fileName);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
        return lines;

    ifstream file(p);

    string line;

    while (getline(file, line))
        lines.push_back(line);

    return lines;
}

void headCommand(const string& fileName)
{
    if (fileName.empty())
    {
        cout << "Usage: head <file>\n";
        return;
    }

    vector<string> lines =
        loadLines(fileName);

    if (lines.empty())
    {
        cout << "File empty or not found.\n";
        return;
    }

    int limit =
        min(10, (int)lines.size());

    for (int i = 0;
         i < limit;
         i++)
    {
        cout << lines[i] << "\n";
    }
}

void tailCommand(const string& fileName)
{
    if (fileName.empty())
    {
        cout << "Usage: tail <file>\n";
        return;
    }

    vector<string> lines =
        loadLines(fileName);

    if (lines.empty())
    {
        cout << "File empty or not found.\n";
        return;
    }

    int start =
        max(0, (int)lines.size() - 10);

    for (int i = start;
         i < (int)lines.size();
         i++)
    {
        cout << lines[i] << "\n";
    }
}

void binEditor(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: bin <file>\n";
        return;
    }

    fs::path p =
        resolvePath(name);

    if (!insideDrive(p))
    {
        cout << "Access denied.\n";
        return;
    }

    cout << "\nEDORA BIN EDITOR\n";
    cout << "Type /save to save.\n\n";

    ofstream file(
        p,
        ios::binary
    );

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    string line;

    while (true)
    {
        getline(cin, line);

        if (line == "/save")
            break;

        file.write(
            line.c_str(),
            line.size()
        );

        file.put('\n');
    }

    file.close();

    cout << "Saved.\n";
}

void binRead(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: binread <file>\n";
        return;
    }

    fs::path p =
        resolvePath(name);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(
        p,
        ios::binary
    );

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    char c;

    while (file.get(c))
        cout << c;
}

void binHex(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: binhex <file>\n";
        return;
    }

    fs::path p =
        resolvePath(name);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(
        p,
        ios::binary
    );

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    unsigned char c;
    int count = 0;

    cout << "\nHEX VIEW\n\n";

    while (file.read(
        reinterpret_cast<char*>(&c),
        1))
    {
        cout << hex
             << setw(2)
             << setfill('0')
             << static_cast<int>(c)
             << " ";

        count++;

        if (count % 16 == 0)
            cout << "\n";
    }

    cout << dec
         << setfill(' ')
         << "\n";
}

char shiftChar(
    char c,
    int shift)
{
    if (c >= 'a' &&
        c <= 'z')
    {
        return char(
            (c - 'a' +
             shift +
             26) %
            26 +
            'a'
        );
    }

    if (c >= 'A' &&
        c <= 'Z')
    {
        return char(
            (c - 'A' +
             shift +
             26) %
            26 +
            'A'
        );
    }

    return c;
}

string shiftText(
    const string& text,
    int shift)
{
    string result = text;

    for (char& c : result)
        c = shiftChar(c, shift);

    return result;
}

string edoEncrypt(
    const string& text)
{
    return shiftText(text, 2);
}

string edoDecrypt(
    const string& text)
{
    return shiftText(text, -2);
}

void edoEditor(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: edo <file>\n";
        return;
    }

    fs::path p =
        resolvePath(name);

    if (!insideDrive(p))
    {
        cout << "Access denied.\n";
        return;
    }

    cout << "\nEDO EDITOR\n";
    cout << "Encryption: EDO Caesar +2\n";
    cout << "Type /save to save.\n\n";

    string content;
    string line;

    while (true)
    {
        getline(cin, line);

        if (line == "/save")
            break;

        content += line;
        content += '\n';
    }

    string encrypted =
        edoEncrypt(content);

    ofstream file(
        p,
        ios::binary
    );

    if (!file)
    {
        cout << "Cannot save file.\n";
        return;
    }

    file.write(
        encrypted.data(),
        encrypted.size()
    );

    file.close();

    cout << "Encrypted and saved.\n";
}

void edoRead(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: edoread <file>\n";
        return;
    }

    fs::path p =
        resolvePath(name);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(
        p,
        ios::binary
    );

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    string content(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    cout << "\n";
    cout << edoDecrypt(content);
}

void edoRaw(const string& name)
{
    if (name.empty())
    {
        cout << "Usage: edoraw <file>\n";
        return;
    }

    fs::path p =
        resolvePath(name);

    if (!insideDrive(p) ||
        !fs::is_regular_file(p))
    {
        cout << "File not found.\n";
        return;
    }

    ifstream file(
        p,
        ios::binary
    );

    if (!file)
    {
        cout << "Cannot open file.\n";
        return;
    }

    string content(
        (istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>()
    );

    cout << "\nRAW EDO DATA\n";
    cout << "--------------------------------------------------\n";
    cout << content << "\n";
}

tm getLocalTime()
{
    auto now =
        chrono::system_clock::now();

    time_t t =
        chrono::system_clock::to_time_t(now);

    tm localTime{};

#ifdef _WIN32
    localtime_s(
        &localTime,
        &t
    );
#else
    localtime_r(
        &t,
        &localTime
    );
#endif

    return localTime;
}

void showTime()
{
    tm localTime =
        getLocalTime();

    cout << "\nEDORA SYSTEM TIME\n";
    cout << "------------------\n";
    cout << put_time(
        &localTime,
        "%H:%M:%S"
    ) << "\n";
}

void showDate()
{
    tm localTime =
        getLocalTime();

    cout << "\nEDORA SYSTEM DATE\n";
    cout << "------------------\n";
    cout << put_time(
        &localTime,
        "%d/%m/%Y"
    ) << "\n";
}

void showDateTime()
{
    tm localTime =
        getLocalTime();

    cout << "\nEDORA SYSTEM CLOCK\n";
    cout << "------------------\n";
    cout << put_time(
        &localTime,
        "%d/%m/%Y %H:%M:%S"
    ) << "\n";
}

void clockCommand()
{
    while (true)
    {
        clearScreen();

        tm localTime =
            getLocalTime();

        cout << "\n";
        cout << "+================================+\n";
        cout << "|        EDORA REAL CLOCK        |\n";
        cout << "+================================+\n";
        cout << "|                                |\n";
        cout << "|        ";

        cout << put_time(
            &localTime,
            "%H:%M:%S"
        );

        cout << "                 |\n";

        cout << "|                                |\n";
        cout << "|        ";

        cout << put_time(
            &localTime,
            "%d/%m/%Y"
        );

        cout << "              |\n";

        cout << "|                                |\n";
        cout << "+================================+\n";
        cout << "| Press ENTER to exit            |\n";
        cout << "+================================+\n";

        for (int i = 0;
             i < 10;
             i++)
        {
            if (cin.rdbuf()->in_avail() > 0)
            {
                string temp;
                getline(cin, temp);
                return;
            }

            this_thread::sleep_for(
                chrono::milliseconds(100)
            );
        }
    }
}

void calcCommand(
    const string& a,
    const string& op,
    const string& b)
{
    if (a.empty() ||
        op.empty() ||
        b.empty())
    {
        cout << "Usage: calc <a> <op> <b>\n";
        cout << "Example: calc 10 + 20\n";
        return;
    }

    try
    {
        double x = stod(a);
        double y = stod(b);
        double result = 0;

        if (op == "+")
            result = x + y;

        else if (op == "-")
            result = x - y;

        else if (op == "*")
            result = x * y;

        else if (op == "/")
        {
            if (y == 0)
            {
                cout << "Cannot divide by zero.\n";
                return;
            }

            result = x / y;
        }

        else
        {
            cout << "Unknown operator.\n";
            return;
        }

        cout << "Result: "
             << result
             << "\n";
    }
    catch (...)
    {
        cout << "Invalid number.\n";
    }
}

void pingHost(const string& host)
{
    if (host.empty())
    {
        cout << "Usage: ping <host>\n";
        return;
    }

#ifdef _WIN32
    string command =
        "ping " + host;
#else
    string command =
        "ping -c 4 " + host;
#endif

    system(command.c_str());
}

void neoFetch()
{
    cout << "\n";

    cout << "        ______ ____   ____  ____      _\n";
    cout << "       |  ____|  _ \\ / __ \\|  _ \\    / \\\n";
    cout << "       | |__  | | | | |  | | |_) |  / _ \\\n";
    cout << "       |  __| | | | | |  | |  _ <  / ___ \\\n";
    cout << "       | |____| |_| | |__| | |_) |/ /   \\ \\\n";
    cout << "       |______|____/ \\____/|____//_/     \\_\\\n";

    cout << "\n";

    cout << "EDORA OS\n";
    cout << "-----------------------------\n";
    cout << "Shell       : EDO Shell v1.3\n";
    cout << "Filesystem  : Virtual FS\n";
    cout << "Drive       : " << currentDrive << "\n";
    cout << "User        : " << currentUser << "\n";
    cout << "Security    : ACTIVE\n";
    cout << "Kernel      : EDORA Kernel\n";
    cout << "Network     : AVAILABLE\n";
}

void sysInfo()
{
    cout << "\nEDORA SYSTEM INFORMATION\n";
    cout << "-----------------------------\n";
    cout << "OS          : EDORA OS\n";
    cout << "Version     : 1.3\n";
    cout << "Shell       : EDO Shell\n";
    cout << "Filesystem  : EDORA Virtual FS\n";
    cout << "Security    : EDO Security\n";
    cout << "User        : " << currentUser << "\n";
    cout << "Drive       : " << currentDrive << "\n";
    cout << "Path        : " << displayPath() << "\n";
}

void about()
{
    cout << "\n";
    cout << "+===============================================+\n";
    cout << "|                 ABOUT EDORA                   |\n";
    cout << "+===============================================+\n";
    cout << "| OS          : EDORA OS                        |\n";
    cout << "| Version     : 1.3                             |\n";
    cout << "| Shell       : EDO Shell                       |\n";
    cout << "| Filesystem  : EDORA Virtual Filesystem        |\n";
    cout << "| Security    : EDO Security                    |\n";
    cout << "| Network     : Real Ping                       |\n";
    cout << "| Developer   : EDORA STUDIO                    |\n";
    cout << "+===============================================+\n";
}

void gameMenu()
{
    cout << "\n";
    cout << "+================================+\n";
    cout << "|          EDORA GAMES           |\n";
    cout << "+================================+\n";
    cout << "| 1. Guess Number                |\n";
    cout << "| 2. Exit                        |\n";
    cout << "+================================+\n";

    cout << "Select: ";

    int choice;

    cin >> choice;
    cin.ignore(10000, '\n');

    if (choice == 1)
    {
        srand(
            static_cast<unsigned>(
                time(nullptr)
            )
        );

        int secret =
            rand() % 100 + 1;

        int guess;

        cout << "\n";
        cout << "Guess a number from 1 to 100.\n";

        while (true)
        {
            cout << "Guess: ";
            cin >> guess;

            if (guess == secret)
            {
                cout << "Correct! You win!\n";
                break;
            }

            if (guess < secret)
                cout << "Higher!\n";
            else
                cout << "Lower!\n";
        }

        cin.ignore(10000, '\n');
    }
}

void sudoAccess()
{
    if (currentUser == "root")
    {
        cout << "Already root.\n";
        return;
    }

    string password;

    cout << "Password: ";

    cin >> password;

    cin.ignore(
        10000,
        '\n'
    );

    if (password == "1234")
    {
        currentUser = "root";
        cout << "Root access granted.\n";
    }
    else
    {
        cout << "Access denied.\n";
    }
}

void rootStatus()
{
    if (currentUser == "root")
        cout << "You are root.\n";
    else
        cout << "You are a normal user.\n";
}

void kernelPanic()
{
    clearScreen();

    cout << "\n";
    cout << "+================================================+\n";
    cout << "|                 KERNEL PANIC                   |\n";
    cout << "+================================================+\n";
    cout << "| EDORA Kernel encountered a fatal error.        |\n";
    cout << "|                                                |\n";
    cout << "| System halted.                                 |\n";
    cout << "+================================================+\n";

    panicMode = true;
}

void systemDeleteSimulation()
{
    if (currentUser != "root")
    {
        cout << "Permission denied. Root required.\n";
        return;
    }

    cout << "\n";
    cout << "EDORA SYSTEM DELETE\n";
    cout << "WARNING: SYSTEM DIRECTORY DELETION REQUESTED\n";
    cout << "Simulation mode enabled.\n\n";

    cout << "[1/5] Checking system...\n";
    cout << "[2/5] Checking dependencies...\n";
    cout << "[3/5] Preparing deletion...\n";
    cout << "[4/5] Simulation...\n";
    cout << "[5/5] Cancelled for safety.\n";

    cout << "\nEDORA OS remains intact.\n";
}

void reboot()
{
    cout << "\nRestarting EDORA OS...\n";

    currentDrive = "C:";
    currentPath =
        fs::path(ROOT_DIR) /
        "C";

    currentUser = "user";

    clearScreen();

    printHeader();

    cout << "\n";
    cout << "EDORA OS restarted successfully.\n";
}

void shutdownOS()
{
    cout << "\n";
    cout << "Shutting down EDORA OS...\n";
    cout << "Saving virtual filesystem...\n";
    cout << "Stopping EDO Shell...\n";
    cout << "Goodbye.\n";

    running = false;
}

int main()
{
    setupDrives();

    clearScreen();

    printHeader();

    cout << "\n";
    cout << "Type 'help' for available commands.\n";

    while (running)
    {
        if (panicMode)
            break;

        printStatus();

        cout << "\n";

        cout << currentUser
             << "@edora:"
             << displayPath()
             << "$ ";

        string input;

        getline(
            cin,
            input
        );

        if (input.empty())
            continue;

        commandHistory.push_back(input);

        stringstream ss(input);

        string cmd;

        ss >> cmd;

        if (cmd == "help")
        {
            showHelp();
        }

        else if (cmd == "clear")
        {
            clearScreen();
        }

        else if (cmd == "about")
        {
            about();
        }

        else if (cmd == "whoami")
        {
            cout << currentUser << "\n";
        }

        else if (cmd == "pwd")
        {
            cout << displayPath()
                 << "\n";
        }

        else if (cmd == "drives")
        {
            showDrives();
        }

        else if (
            cmd == "C:" ||
            cmd == "c:")
        {
            currentDrive = "C:";
            currentPath =
                fs::path(ROOT_DIR) /
                "C";
        }

        else if (
            cmd == "D:" ||
            cmd == "d:")
        {
            currentDrive = "D:";
            currentPath =
                fs::path(ROOT_DIR) /
                "D";
        }

        else if (
            cmd == "E:" ||
            cmd == "e:")
        {
            currentDrive = "E:";
            currentPath =
                fs::path(ROOT_DIR) /
                "E";
        }

        else if (
            cmd == "dir" ||
            cmd == "ls")
        {
            listDirectory();
        }

        else if (cmd == "cd")
        {
            string target;

            ss >> target;

            if (target.empty())
            {
                cout << displayPath()
                     << "\n";

                continue;
            }

            if (target == "\\")
            {
                currentPath =
                    fs::path(ROOT_DIR) /
                    currentDrive.substr(0, 1);

                continue;
            }

            fs::path p =
                resolvePath(target);

            if (!insideDrive(p))
            {
                cout << "Access denied.\n";
                continue;
            }

            if (!fs::exists(p) ||
                !fs::is_directory(p))
            {
                cout << "Directory not found.\n";
                continue;
            }

            currentPath =
                fs::weakly_canonical(p);
        }

        else if (cmd == "mkdir")
        {
            string name;

            ss >> name;

            makeDirectory(name);
        }

        else if (cmd == "touch")
        {
            string name;

            ss >> name;

            touchFile(name);
        }

        else if (cmd == "rm")
        {
            string name;

            ss >> name;

            removePath(name);
        }

        else if (
            cmd == "cat" ||
            cmd == "type")
        {
            string name;

            ss >> name;

            readFile(name);
        }

        else if (cmd == "copy")
        {
            string a;
            string b;

            ss >> a >> b;

            copyPath(a, b);
        }

        else if (cmd == "move")
        {
            string a;
            string b;

            ss >> a >> b;

            movePath(a, b);
        }

        else if (cmd == "rename")
        {
            string a;
            string b;

            ss >> a >> b;

            renamePath(a, b);
        }

        else if (cmd == "tree")
        {
            showTree();
        }

        else if (cmd == "find")
        {
            string target;

            ss >> target;

            findCommand(target);
        }

        else if (cmd == "echo")
        {
            string text;

            getline(ss, text);

            if (!text.empty() &&
                text[0] == ' ')
            {
                text.erase(0, 1);
            }

            echoCommand(text);
        }

        else if (cmd == "history")
        {
            showHistory();
        }

        else if (cmd == "grep")
        {
            string search;
            string file;

            ss >> search >> file;

            grepCommand(
                search,
                file
            );
        }

        else if (cmd == "head")
        {
            string file;

            ss >> file;

            headCommand(file);
        }

        else if (cmd == "tail")
        {
            string file;

            ss >> file;

            tailCommand(file);
        }

        else if (cmd == "bin")
        {
            string name;

            ss >> name;

            binEditor(name);
        }

        else if (cmd == "binread")
        {
            string name;

            ss >> name;

            binRead(name);
        }

        else if (cmd == "binhex")
        {
            string name;

            ss >> name;

            binHex(name);
        }

        else if (cmd == "edo")
        {
            string name;

            ss >> name;

            edoEditor(name);
        }

        else if (cmd == "edoread")
        {
            string name;

            ss >> name;

            edoRead(name);
        }

        else if (cmd == "edoraw")
        {
            string name;

            ss >> name;

            edoRaw(name);
        }

        else if (cmd == "time")
        {
            showTime();
        }

        else if (cmd == "date")
        {
            showDate();
        }

        else if (cmd == "datetime")
        {
            showDateTime();
        }

        else if (cmd == "clock")
        {
            clockCommand();
        }

        else if (cmd == "calc")
        {
            string a;
            string op;
            string b;

            ss >> a >> op >> b;

            calcCommand(
                a,
                op,
                b
            );
        }

        else if (cmd == "ping")
        {
            string host;

            ss >> host;

            pingHost(host);
        }

        else if (cmd == "neofetch")
        {
            neoFetch();
        }

        else if (cmd == "sysinfo")
        {
            sysInfo();
        }

        else if (cmd == "game")
        {
            gameMenu();
        }

        else if (cmd == "sudo")
        {
            sudoAccess();
        }

        else if (cmd == "root")
        {
            rootStatus();
        }

        else if (cmd == "panic")
        {
            kernelPanic();
        }

        else if (cmd == "delete")
        {
            string arg1;
            string arg2;

            ss >> arg1 >> arg2;

            if (arg1 == "systemcl" &&
                arg2 == "-t")
            {
                systemDeleteSimulation();
            }
            else
            {
                cout << "Unknown delete command.\n";
            }
        }

        else if (cmd == "reboot")
        {
            reboot();
        }

        else if (cmd == "shutdown")
        {
            shutdownOS();
        }

        else if (cmd == "exit")
        {
            running = false;
        }

        else
        {
            cout << "'"
                 << cmd
                 << "' is not recognized as an EDORA command.\n";
        }
    }

    return 0;
}
