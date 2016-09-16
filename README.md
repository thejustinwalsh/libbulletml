# libBulletML
## A Modern Fork of [libBulletML](http://shinh.skr.jp/libbulletml/)

#### Manifesto
To provide a clean easy to build copy of libBulletML using modern C++ with minimal code changes to the core library.

#### RoadMap
- Remove dependencies on boost
- Update `std::auto_ptr` to `std::unique_ptr`
- Provide a single xml parser using [rapidxml](https://github.com/dwd/rapidxml/blob/master/rapidxml.hpp)
- Provide a json parser using [rapidjson](https://github.com/miloyip/rapidjson)
- Use [premake](https://premake.github.io) for project file generation
- Ensure the source is free from GPL restrictions
