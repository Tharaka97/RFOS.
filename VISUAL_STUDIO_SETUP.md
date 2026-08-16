# RFOS - Visual Studio setup

Open **RFOS.sln** in Visual Studio 2022 or newer. The project is configured as a native C++17 x64 console application.

## Run
1. In Visual Studio Installer, ensure **Desktop development with C++** is installed.
2. Open `RFOS.sln`.
3. Select `Debug` and `x64` in the toolbar.
4. Right-click RFOS in Solution Explorer and choose **Set as Startup Project** if needed.
5. Use **Build > Build Solution** (`Ctrl+Shift+B`).
6. Use **Debug > Start Without Debugging** (`Ctrl+F5`) or press `F5` to debug.

The Debug executable is normally `x64\Debug\RFOS.exe`.

## GitHub
### Create a new GitHub repository from this solution
1. Open `RFOS.sln`.
2. Select **Git > Create Git Repository**.
3. Choose **GitHub** and sign in.
4. Enter a repository name such as `RFOS-SEP401`.
5. Choose repository visibility.
6. Confirm the local path points to this RFOS folder.
7. Select **Create and Push**.

### If you already created a GitHub repository with files in it
1. Select **Git > Clone Repository** and clone it.
2. Copy the RFOS solution/project/source files into the cloned folder.
3. Open `RFOS.sln` there.
4. Open **Git Changes**, enter a commit message, select **Commit All**, then **Push**.
