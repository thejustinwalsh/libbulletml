# libBulletML
### A Modern Fork of [libBulletML](http://shinh.skr.jp/libbulletml/)

#### Manifesto
To provide a clean easy to build copy of libBulletML using modern C++ with minimal code changes to the core library.

#### Generate Project Files
libBulletML uses premake to generate project files for building the library. Follow the instructions for your platform below.

- Windows
  - Double click and run setup.bat from explorer
  - *or* from the repository root run `setup.bat` in a command console
- MacOS
  - Double click and run setup.command from finder
  - *or* from the repository root run `./setup.sh` in terminal
- Linux
  - From the repository root run `./setup.sh` in a terminal

#### Test Suite
Passing '--with-tests' to the setup script `setup.bat` or `setup.sh` will ensure that googletest is updated and cause premake to generate the tests project. Simply build and run the tests project to exercise all tests.

#### RoadMap
- ~~Remove dependencies on boost~~ :white_check_mark:
- ~~Update `std::auto_ptr` to `std::unique_ptr`~~ :white_check_mark:
- Provide a single xml parser using [rapidxml](https://github.com/dwd/rapidxml/blob/master/rapidxml.hpp)
- Provide a json parser using [rapidjson](https://github.com/miloyip/rapidjson)
- ~~Use [premake](https://premake.github.io) for project file generation~~ :white_check_mark:
- ~~Ensure the source is free from GPL restrictions~~ :white_check_mark:
