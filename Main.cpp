#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;
namespace fs = filesystem;

int main()
{

    string downloadPath = "C:/Users/YourUsername/Downloads";

    unordered_map<string, string> category = {
        {"jpg", "Photos"}, {"jpeg", "Photos"}, {"png", "Photos"}, {"gif", "Photos"}, {"webp", "Photos"}, {"mp4", "Videos"}, {"mkv", "Videos"}, {"mov", "Videos"}, {"avi", "Videos"}, {"webm", "Videos"}, {"pdf", "Documents"}, {"docx", "Documents"}, {"txt", "Documents"}, {"pptx", "Documents"}, {"xlsx", "Documents"}, {"mp3", "Music"}, {"wav", "Music"}, {"flac", "Music"}, {"zip", "ZIPS and MC mods"}, {"7z", "ZIPS and MC mods"}, {"rar", "ZIPS and MC mods"}, {"jar", "ZIPS and MC mods"}, {"exe", "Applications"}, {"msi", "Applications"}};

    for (auto &file : fs::directory_iterator(downloadPath))
    {
        if (fs::is_regular_file(file))
        {
            string ext = file.path().extension().string();
            if (!ext.empty() && ext[0] == '.')
            {
                ext = ext.substr(1);

                string folderName = "Others";

                if (category.find(ext) != category.end())
                {
                    folderName = category[ext];
                }

                fs::path newFolder = downloadPath + "/" + folderName;

                if (!fs::exists(newFolder))
                {
                    fs::create_directory(newFolder);
                }

                fs::path newPath = newFolder / file.path().filename();
                fs::rename(file.path(), newPath);

                cout << "Moved " << file.path().filename() << " → " << folderName << endl;
            }
        }
    }

    cout << "Sorting complete!" << endl;
    return 0;
}
