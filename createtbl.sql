DROP TABLE IF EXISTS books;
DROP TABLE IF EXISTS authors;
DROP TABLE IF EXISTS ba;

CREATE TABLE books (bid SERIAL PRIMARY KEY, book  VARCHAR, UNIQUE(book));
CREATE TABLE authors (aid SERIAL PRIMARY KEY, author  VARCHAR, UNIQUE(author));
CREATE TABLE ba (bid INTEGER, aid INTEGER);

CREATE OR REPLACE FUNCTION add_author(VARCHAR) RETURNS INTEGER AS $$
    DECLARE
        rv INTEGER;
    BEGIN
        INSERT INTO authors(author) VALUES($1) ON CONFLICT (author) DO UPDATE SET author=EXCLUDED.author RETURNING aid INTO rv;
        RETURN rv;
    END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION add_book(VARCHAR, VARCHAR[]) RETURNS INTEGER AS $$
    DECLARE
        arr ALIAS FOR $2;
        author TEXT;
        authorid INTEGER;
        bookid INTEGER;
    BEGIN
        INSERT INTO books(book) VALUES($1) RETURNING bid INTO bookid;
        FOREACH author IN ARRAY arr LOOP
            SELECT add_author(author) INTO authorid;
            INSERT INTO ba(bid, aid) VALUES(bookid, authorid);
        END LOOP;
        RETURN bookid;
    END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION del_book(VARCHAR) RETURNS INTEGER AS $$
    DECLARE
        bookid INTEGER;
    BEGIN
        SELECT bid INTO bookid FROM books WHERE book=$1;
        DELETE FROM books WHERE bid=bookid;
        DELETE FROM ba WHERE bid=bookid;
        RETURN bookid;
    END ;
$$ LANGUAGE 'plpgsql' ;

CREATE OR REPLACE FUNCTION get_books(author VARCHAR) RETURNS TABLE(book VARCHAR) AS $$
    DECLARE
        id INTEGER;
    BEGIN
         SELECT aid INTO id FROM authors WHERE authors.author=$1;
         RETURN QUERY SELECT books.book FROM books
            JOIN ba ON ba.bid=books.bid
            JOIN authors on authors.aid=ba.aid
                WHERE authors.aid=id;
    END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_authors(book VARCHAR) RETURNS TABLE(author VARCHAR) AS $$
    DECLARE
        id INTEGER;
    BEGIN
        SELECT bid INTO id FROM books WHERE books.book=$1;
        RETURN QUERY SELECT authors.author FROM authors
            JOIN ba ON ba.aid=authors.aid
            JOIN books on books.bid=ba.bid
                WHERE books.bid=id;
    END;
$$ LANGUAGE 'plpgsql';

CREATE OR REPLACE FUNCTION get_books_anum(INTEGER) RETURNS TABLE(book VARCHAR) AS $$
    BEGIN
        RETURN QUERY SELECT books.book FROM books
            JOIN ba ON ba.bid=books.bid
            JOIN authors on authors.aid=ba.aid
            GROUP BY books.book
            HAVING COUNT(authors.aid) > $1;
    END;
$$ LANGUAGE 'plpgsql';
