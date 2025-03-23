#include <iostream>

using namespace std;

class Movie
{

private:

    string title;
    string director;
    string genre;
    int duration;

public:

    Movie();
    Movie(string title, string director, string genre, int duration);

    void playMovie();
    string getTitle();
    string getDirector();
    string getGenre();
    int getDuration();

    ~Movie();
};

Movie::Movie()
{
    title = "<NULL>";
    director = "<NULL>";
    genre = "<NULL>";
    duration = 0;
}

Movie::Movie(string title, string director, string genre, int duration)
{
    Movie::title = title;
    Movie::director = director;
    Movie::genre = genre;
    Movie::duration = duration;
}

void Movie::playMovie()
{
    cout << "Title: " << title << endl;
    cout << "Director: " << director << endl;
    cout << "Genre: " << genre << endl;
    cout << "Duration: " << duration << endl;
}

string Movie::getTitle()
{
    return title;
}

string Movie::getDirector()
{
    return director;
}

string Movie::getGenre()
{
    return genre;
}

int Movie::getDuration()
{
    return duration;
}

Movie::~Movie()
{
    cout << "Movie Destroyed?" << endl;
}


class MoviePlaylist
{

private:

    Movie** myPlaylist;
    int movieCount;
    int capacity;

public:

    MoviePlaylist();
    ~MoviePlaylist();
};

MoviePlaylist::MoviePlaylist()
{
    // *myPlaylist = (Movie*) calloc(5, sizeof(Movie));

    *myPlaylist = new Movie[5];

    movieCount = 0;
    capacity = 5;
}

MoviePlaylist::~MoviePlaylist()
{
    delete[] myPlaylist;
}





