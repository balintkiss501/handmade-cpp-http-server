Who needs WAMP/LAMP stack anyway, when you can roll your own?

That's a bit of an overstatement, this is my simple HTTP server exercise I made in C++ with Boost Asio library, to accept HTTP requests and display content from the public_html folder. This is still in progress. After launch, you can test it in browser or via cURL.

For the Windows executable (currently 32-bit), I cross-compiled it under Linux. If you want my approach, here's what you would do:

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


TODO:
- Convert Makefile-based build approach to autotools (CMake would be overkill for this)
- Make it modular
- Implement the 404 HTTP response
- Handle URL endpoints, like "http://localhost:8080/here-is-something"
