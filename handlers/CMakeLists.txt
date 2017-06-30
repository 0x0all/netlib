set(SRC AddBook.cpp AddBook.h
        GetBooks.cpp GetBooks.h
        GetAuthors.cpp GetAuthors.h
        GetBooksAnum.cpp GetBooksAnum.h
        DelBook.h DelBook.cpp
        HttpPerf.h HttpPerf.cpp)

add_library(netlibhandlers ${SRC})
