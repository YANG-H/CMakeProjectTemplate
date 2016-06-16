# CMakeProjectTemplate
This is a template for cmake projects.

## Usage
0. Copy the files (at least `./cmake`, `./ext`, `./src` and `./CMakeLists.txt`) to your project folder;
1. Configure the name of your project in `./CMakeLists.txt`;
2. Configure the dependencies of your project in `./ext/CMakeLists.txt`, 
make sure that a `googletest-master.zip` is under `./ext/googletest` if `BuildUnitTest` is `on`;
3. Build.