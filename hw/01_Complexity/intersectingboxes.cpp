/**
 * Authors: Haochen Ji, Rui Zhang
 */
#ifndef VERBOSE
#define VERBOSE 0
#endif

#ifndef TIMING
#define TIMING 0
#endif


/*
  Complexity Practice Assignment: Find overlapping boxes
  Complete the following code
  Read in a list of boxes expressed as x y w h
  x and y are the top-left corner of the box,
  w and h are its width and height
  Some boxes may intersect with others

  Display the ordinal position of each box which intersects
  with another and display the pair i,j
  Do not display the pair twice, thus is i intersects with j,
  do not also display j,i
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>

using namespace std;
class Box {
public:
    int x, y, w, h;
    Box(int x, int y, int w, int h) : x(x), y(y), w(w), h(h) {}
};

int main() {
    ifstream f("boxes.txt");
    vector<Box> boxes;
    boxes.reserve(100000); // preallocate room. If you are smart, do it based on the size of the file
    for (int x, y, w, h; f >> x >> y >> w >> h;) {
        boxes.emplace_back(x, y, w, h); // create a list of all boxes
    }
    uint64_t intersecting = 0;

    // this just shows how you iterate through the boxes
    // now you write the code to check for intersections
//    for (uint32_t i = 0; i < boxes.size(); i++) {
//        cout << boxes[i].x << " " << boxes[i].y << " " << boxes[i].w << " " << boxes[i].h << endl;
//    }

#if TIMING == 1
    auto start = std::chrono::high_resolution_clock::now();
#endif
    for (int i = 0; i < boxes.size(); ++i) {
        for (int j = i + 1; j < boxes.size(); ++j) {
            Box box_i = boxes[i], box_j = boxes[j];
            if ((box_i.x < box_j.x + box_j.w && box_i.x + box_i.w > box_j.x &&
                    box_i.y < box_j.y + box_j.h && box_i.y + box_i.h > box_j.y)) {
                intersecting++;
#if VERBOSE == 1
                cout << i << ", " << j << endl;
#endif
            }
        }
    }
    cout << "intersecting boxes: " << intersecting << endl;

#if TIMING == 1
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " microseconds" << endl;
#endif

/**
 * Algorithm designed by ourselves
 * Further improvement: sort pairs before output
 */
#ifdef CUSTOM_ALGO
    intersecting = 0;

#if TIMING == 1
    start = std::chrono::high_resolution_clock::now();
#endif

    vector<array<int, 3>> xs(boxes.size() * 2);
    vector<array<int, 3>> ys(boxes.size() * 2);
    vector<vector<bool>> overlap_x(boxes.size(), vector<bool>(boxes.size(), false));

    for (int i = 0; i < boxes.size(); ++i) {
        xs[i][0] = boxes[i].x;
        xs[i][1] = 1;
        xs[i][2] = i;
        xs[i + boxes.size()][0] = boxes[i].x + boxes[i].w;
        xs[i + boxes.size()][1] = 2;
        xs[i + boxes.size()][2] = i;
        ys[i][0] = boxes[i].y;
        ys[i][1] = 1;
        ys[i][2] = i;
        ys[i + boxes.size()][0] = boxes[i].y + boxes[i].h;
        ys[i + boxes.size()][1] = 2;
        ys[i + boxes.size()][2] = i;
    }

    sort(xs.begin(), xs.end(), [](const array<int, 3>& a, const array<int, 3>& b) {
        return a[0] < b[0];
    });
    sort(ys.begin(), ys.end(), [](const array<int, 3>& a, const array<int, 3>& b) {
        return a[0] < b[0];
    });

    unordered_set<int> ids;
    for (auto tmp : xs) {
        if (tmp[1] == 1) {
            for (auto id : ids) {
                overlap_x[id][tmp[2]] = true;
                overlap_x[tmp[2]][id] = true;
            }
            ids.insert(tmp[2]);
        } else {
            ids.erase(tmp[2]);
        }
    }

    ids.clear();
    for (auto tmp : ys) {
        if (tmp[1] == 1) {
            for (auto id : ids) {
                if (overlap_x[id][tmp[2]] || overlap_x[tmp[2]][id]) {
#if VERBOSE == 1
                    cout << min(id, tmp[2]) << ", " << max(id, tmp[2]) << endl;
#endif
                    intersecting++;
                }
            }
            ids.insert(tmp[2]);
        } else {
            ids.erase(tmp[2]);
        }
    }
    cout << "intersecting boxes: " << intersecting << endl;

#if TIMING == 1
    stop = std::chrono::high_resolution_clock::now();

    duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    cout << "Time taken: " << duration.count() << " microseconds" << endl;
#endif
#endif
    return 0;
}