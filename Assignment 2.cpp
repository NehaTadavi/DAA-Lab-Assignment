#Neha Tadavi
#PRN:124B2F006
#Movie Recommendation System 
// A popular OTT platform, StreamFlix, offers personalized recommendations by sorting movies
// based on user preferences, such as IMDB rating, release year, or watch time popularity.
// However, during peak hours, sorting large datasets slows down the system.
// As a backend engineer, you must:
// ● Implement Quicksort to efficiently sort movies based on various user-selected
// parameters.
// ● Handle large datasets containing of movies while maintaining fast response times


#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Movie {
public:
    string title;
    double imdbRating;
    int releaseYear;
    long long watchTime;

    Movie(string t, double r, int y, long long w) {
        title = t;
        imdbRating = r;
        releaseYear = y;
        watchTime = w;
    }
};

class QuickSort {
public:
    // Partition function (pivot is first element)
    int partition(vector<Movie>& arr, int low, int high, int choice) {
        Movie pivot = arr[low];
        int i = low + 1;
        int j = high;

        while (true) {
            // Comparison based on choice (1-rating, 2-year, 3-watchTime)
            while (i <= high && compare(arr[i], pivot, choice))
                i++;
            while (j >= low && compare(pivot, arr[j], choice))
                j--;

            if (i < j)
                swap(arr[i], arr[j]);
            else
                break;
        }
        swap(arr[low], arr[j]);
        return j;
    }

    void quickSort(vector<Movie>& arr, int low, int high, int choice) {
        if (low < high) {
            int p = partition(arr, low, high, choice);
            quickSort(arr, low, p - 1, choice);
            quickSort(arr, p + 1, high, choice);
        }
    }

    // Compare movies by selected parameter
    bool compare(Movie& a, Movie& b, int choice) {
        if (choice == 1) return a.imdbRating < b.imdbRating;   // IMDB Rating
        if (choice == 2) return a.releaseYear < b.releaseYear; // Release Year
        return a.watchTime < b.watchTime;                      // Watch Time
    }
};

int main() {
    int n;
    cout << "Enter number of movies: ";
    cin >> n;

    vector<Movie> movies;
    for (int i = 0; i < n; i++) {
        string title;
        double rating;
        int year;
        long long watch;
        cout << "Enter title, rating, year, watchTime: ";
        cin >> title >> rating >> year >> watch;
        movies.push_back(Movie(title, rating, year, watch));
    }

    cout << "Choose sorting parameter (1-Rating, 2-Year, 3-WatchTime): ";
    int choice;
    cin >> choice;

    QuickSort sorter;
    sorter.quickSort(movies, 0, n - 1, choice);

    cout << "\nSorted Movies:\n";
    for (auto& m : movies) {
        cout << m.title << " | Rating: " << m.imdbRating
             << " | Year: " << m.releaseYear
             << " | WatchTime: " << m.watchTime << endl;
    }

    return 0;

}
