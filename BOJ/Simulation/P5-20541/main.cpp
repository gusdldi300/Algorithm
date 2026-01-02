
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <cassert>

class Album
{
public:
    Album(int id, int parentId, const std::string& name);

public:
    int Id;
    int ParentId;

    std::string Name;
    std::map<std::string, Album*> Folders;
    std::set<std::string> Files;
};

Album::Album(int id, int parentId, const std::string& name)
    : Id(id)
    , ParentId(parentId)
    , Name(name)
{
}

static std::unordered_map<int, Album*> spAlbums;

static void RemoveFoldersRecursive(Album* removeAlbum, unsigned int* outRemovedFiles, unsigned int* outRemovedFolders)
{
    for (auto eraseIter = removeAlbum->Folders.begin(); eraseIter != removeAlbum->Folders.end(); ++eraseIter)
    {
        RemoveFoldersRecursive(eraseIter->second, outRemovedFiles, outRemovedFolders);
    }

    (*outRemovedFiles) += removeAlbum->Files.size();
    (*outRemovedFolders) += removeAlbum->Folders.size();
}

static void RemoveFolderFrom(std::map<std::string, Album*>* folders, const std::string& removeFolderName, unsigned int* outRemovedFiles, unsigned int* outRemovedFolders)
{
    assert(outRemovedFiles != nullptr);
    assert(outRemovedFolders != nullptr);

    RemoveFoldersRecursive(folders->find(removeFolderName)->second, outRemovedFiles, outRemovedFolders);

    folders->erase(removeFolderName);
    ++(*outRemovedFolders);
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int newAlbumId = 0;
    Album* pCurrentAlbum = new Album(newAlbumId, -1, "album");
    
    spAlbums.insert(std::pair<int, Album*>(newAlbumId, pCurrentAlbum));
    newAlbumId++;

    unsigned int commandsCount;
    std::cin >> commandsCount;

    for (unsigned int i = 0; i < commandsCount; ++i)
    {
        std::string command;
        std::string argument;

        std::cin >> command >> argument;

        if (command == "mkalb")
        {
            if (pCurrentAlbum->Folders.find(argument) != pCurrentAlbum->Folders.end())
            {
                std::cout << "duplicated album name" << std::endl;

                continue;
            }

            Album* pNewAlbum = new Album(newAlbumId, pCurrentAlbum->Id, argument);
            spAlbums.insert(std::pair<int, Album*>(newAlbumId, pNewAlbum));
            newAlbumId++;

            pCurrentAlbum->Folders.insert(std::pair<std::string, Album*>(argument, pNewAlbum));
        }
        else if (command == "rmalb")
        {
            unsigned int removedFiles = 0;
            unsigned int removedFolders = 0;

            if (argument == "-1")
            {
                if (pCurrentAlbum->Folders.size() > 0)
                {
                    RemoveFolderFrom(&(pCurrentAlbum->Folders), pCurrentAlbum->Folders.begin()->first, &removedFiles, &removedFolders);
                }
            }
            else if (argument == "0")
            {
                while (pCurrentAlbum->Folders.empty() == false)
                {
                    auto eraseIter = pCurrentAlbum->Folders.begin();

                    RemoveFolderFrom(&(pCurrentAlbum->Folders), eraseIter->first, &removedFiles, &removedFolders);
                }
            }
            else if (argument == "1")
            {
                if (pCurrentAlbum->Folders.size() > 0)
                {
                    auto eraseIter = pCurrentAlbum->Folders.end();
                    --eraseIter;

                    RemoveFolderFrom(&(pCurrentAlbum->Folders), eraseIter->first, &removedFiles, &removedFolders);
                }
            }
            else
            {
                if (pCurrentAlbum->Folders.find(argument) != pCurrentAlbum->Folders.end())
                {
                    RemoveFolderFrom(&(pCurrentAlbum->Folders), argument, &removedFiles, &removedFolders);
                }
            }

            std::cout << removedFolders << " " << removedFiles << std::endl;
        }
        else if (command == "insert")
        {
            if (pCurrentAlbum->Files.find(argument) != pCurrentAlbum->Files.end())
            {
                std::cout << "duplicated photo name" << std::endl;

                continue;
            }

            pCurrentAlbum->Files.insert(argument);
        }
        else if (command == "delete")
        {
            unsigned int deleteCount = 0;

            if (argument == "-1")
            {
                if (pCurrentAlbum->Files.size() > 0)
                {
                    auto eraseIter = pCurrentAlbum->Files.begin();
                    pCurrentAlbum->Files.erase(eraseIter);

                    ++deleteCount;
                }
            }
            else if (argument == "0")
            {
                deleteCount = pCurrentAlbum->Files.size();
                pCurrentAlbum->Files.erase(pCurrentAlbum->Files.begin(), pCurrentAlbum->Files.end());
            }
            else if (argument == "1")
            {
                if (pCurrentAlbum->Files.size() > 0)
                {
                    auto eraseIter = pCurrentAlbum->Files.end();
                    --eraseIter;

                    pCurrentAlbum->Files.erase(eraseIter);

                    ++deleteCount;
                }
            }
            else
            {
                if (pCurrentAlbum->Files.find(argument) != pCurrentAlbum->Files.end())
                {
                    pCurrentAlbum->Files.erase(argument);

                    ++deleteCount;
                }
            }

            std::cout << deleteCount << std::endl;
        }
        else if (command == "ca")
        {
            if (argument == "..")
            {
                if (pCurrentAlbum->Id > 0)
                {
                    pCurrentAlbum = spAlbums[pCurrentAlbum->ParentId];
                }
            }
            else if (argument == "/")
            {
                pCurrentAlbum = spAlbums[0];
            }
            else
            {
                if (pCurrentAlbum->Folders.find(argument) != pCurrentAlbum->Folders.end())
                {
                    pCurrentAlbum = pCurrentAlbum->Folders[argument];
                }
            }

            std::cout << pCurrentAlbum->Name << std::endl;
        }
    }

    for (auto albumIter = spAlbums.begin(); albumIter != spAlbums.end(); ++albumIter)
    {
        delete albumIter->second;
    }

    return 0;
}