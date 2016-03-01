Who needs WAMP/LAMP stack anyway, when you can roll your own?

That's a bit of an overstatement, this is my simple HTTP server exercise I made in C++ with Boost Asio library, to accept HTTP requests and display content from the public_html folder. This is still in progress. After launching "server" or "server.exe", you can test it in browser or via cURL.

[Download Linux 64-bit](https://github.com/balintkiss501/handmade-cpp-http-server/releases/download/linux64_v1.0.0/handmade-cpp-http-server_linux64_v1.1.0.tar.gz)

[Download Windows 32-bit](https://github.com/balintkiss501/handmade-cpp-http-server/releases/download/win32_v1.0.0/handmade-cpp-http-server_win32_v1.1.0.zip)

For the Windows executable (currently 32-bit), I cross-compiled it under Linux. If you want my approach, here's what you would do:

```bash
$ sudo aptitude install mingw-w64
$ wget -c 'http://sourceforge.net/projects/boost/files/boost/1.60.0/boost_1_60_0.tar.bz2/download' -o boost_1_60_0.tar.bz2
$ tar -xvf boost_1_60_0.tar.bz2
$ cd boost_1_60_0
$ echo "using gcc : : i686-mingw32-g++ ;" > user-config.jam
$ ./bootstrap.sh --with-libraries=system,thread
$ ./b2 \
    --user-config=user-config.jam \
    toolset=gcc \
    cflags=-m32 \
    cxxflags=-m32 \
    target-os=windows \
    architecture=x86 \
    address-model=32 \
    instruction-set=i686 \
    threading=multi \
    threadapi=win32 \
    --layout=tagged \
    stage
$ sudo cp -r boost /usr/i686-w64-mingw3/include/boost
$ sudo cp stage/lib/libboost_system-mt.a /usr/i686-w64-mingw32/lib/libboost_system.a
$ sudo cp stage/lib/libboost_thread_win32-mt.a /usr/i686-w64-mingw32/lib/libboost_thread.a
$ sudo cp stage/lib/libboost_chrono-mt.a /usr/i686-w64-mingw32/lib/libboost_chrono.a
```
